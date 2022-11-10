#pragma once
#ifndef CSS_COLOR_PARSER_HPP
#define CSS_COLOR_PARSER_HPP

#include <string_view>
#include "const_math.hpp"
#include "colorspace.hpp"
#include "basic_io.hpp"
#include "const_str.hpp"
#include "element_types.hpp"
#include "named_colors.hpp"

namespace css_colors::details {
	namespace parser {
		namespace parser_impl {

			template<class colorspace>
			inline constexpr std::optional<vec> parse_color_impl(string_view_tokenizer& tokens) {
				vec ret = { 0,0,0 };


				if (tokens.skip_whitespace())return std::nullopt;//ignore whitespace

				std::optional<real> elem = parse_element<typename std::tuple_element<0, typename colorspace::arg_type>::type>(tokens);
				if (!elem.has_value())return std::nullopt;
				ret[0] = elem.value();

				if (tokens.skip_whitespace())return std::nullopt;
				if constexpr (colorspaces::is_legacy_v<colorspace>) {
					if (tokens.next_token() == ",") {
						tokens.skip_token();
						if (tokens.skip_whitespace())return std::nullopt;
					}
				}

				elem = parse_element<typename std::tuple_element<1, typename colorspace::arg_type>::type>(tokens);
				if (!elem.has_value())return std::nullopt;
				ret[1] = elem.value();

				if (tokens.skip_whitespace())return std::nullopt;
				if constexpr (colorspaces::is_legacy_v<colorspace>) {
					if (tokens.next_token() == ",") {
						tokens.skip_token();
						if (tokens.skip_whitespace())return std::nullopt;
					}
				}

				elem = parse_element<typename std::tuple_element<2, typename colorspace::arg_type>::type>(tokens);
				if (!elem.has_value())return std::nullopt;
				ret[2] = elem.value();

				return ret;
			}
			template<class real_colorspace>
			struct pesudo_predefined_colorspace {
				using arg_type = element_types::predefined_colorspace_args;
				using real_type = real_colorspace;
			};

			template<class real_colorspace, bool predefined = false>
			inline constexpr color parse_color_alpha_impl(string_view_tokenizer& tokens) {
				using colorspace = std::conditional_t<predefined, pesudo_predefined_colorspace<real_colorspace>, real_colorspace>;
				typed_color<colorspace> ret = { vec{0,0,0},static_cast<real>(1.0) };
				auto c = parse_color_impl<colorspace>(tokens);
				if (!c.has_value())return nullcolor;
				ret.first = c.value();

				//bool has_alpha = false;
				tokens.skip_whitespace();
				if ((colorspaces::is_legacy_v<colorspace> && tokens.next_token() == ",") || tokens.next_token() == "/") {
					tokens.skip_token();
					tokens.skip_whitespace();

					auto alpha = parse_element<element_types::number<element_types::alpha_range>>(tokens);
					if (!alpha)return nullcolor;
					ret.second = alpha.value();
				}
				else {
					ret.second = 1;
				}
				if constexpr (predefined) {
					ret.first[0] *= std::tuple_element_t<0, typename real_colorspace::arg_type>::scale;
					ret.first[1] *= std::tuple_element_t<1, typename real_colorspace::arg_type>::scale;
					ret.first[2] *= std::tuple_element_t<2, typename real_colorspace::arg_type>::scale;

				}
				//if (tokens.eof())return std::nullopt;
				return ret;
			}

			template <uint8_t id = 0>
			inline constexpr color try_predefined_colorspace(string_view_tokenizer& tokens) {
				if (const_iequal(tokens.next_token(), colorspaces::predefined_colorspace<id>::name)) {
					tokens.skip_token();
					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					auto r = parse_color_alpha_impl<typename colorspaces::predefined_colorspace<id>::colorspace, true>(tokens);
					if (!r)return nullcolor;

					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					return r;
				}
				return try_predefined_colorspace<id + 1>(tokens);
			}
			template <>
			inline constexpr color try_predefined_colorspace<colorspaces::predefined_colorspace_cnt>(string_view_tokenizer&) {
				return unknowncolor;
			}


			template <uint8_t id = 0>
			inline constexpr color try_color_func(string_view_tokenizer& tokens) {
				if (const_iequal(tokens.next_token(), colorspaces::color_function<id>::name)) {
					tokens.skip_token();
					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					if (tokens.next_token() != "(")return nullcolor;
					tokens.skip_token();

					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					auto r = parse_color_alpha_impl<typename colorspaces::color_function<id>::colorspace>(tokens);
					if (!r)return nullcolor;

					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					if (tokens.next_token() != ")")return nullcolor;
					tokens.skip_token();

					return r;
				}
				else return try_color_func<id + 1>(tokens);
			}
			template<>
			inline constexpr color try_color_func<colorspaces::color_function_cnt>(string_view_tokenizer& tokens) {
				//check for the color() function here.
				if (const_iequal(tokens.next_token(), "color")) {
					tokens.skip_token();
					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					if (tokens.next_token() != "(")return nullcolor;
					tokens.skip_token();

					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					auto r = try_predefined_colorspace(tokens);
					if (!r)return nullcolor;

					while (!tokens.eof() && tokens.next_token().empty())tokens.skip_token();
					if (tokens.next_token() != ")")return nullcolor;
					tokens.skip_token();

					return r;
				}

				return unknowncolor;
			}

			inline constexpr color try_named(string_view_tokenizer& tokens) {
				return named_colors::lookup_named_color(tokens.next_token());
			}

			inline constexpr color hex6(const std::string_view& str) {
				uint32_t u32 = 0;
				for (const auto& ch : str) {
					auto t = const_as_hex(ch);
					if (t < 0)return nullcolor;
					u32 = u32 * 16 + t;
				}
				return colorspaces::u32_to_color((u32 << 8) | 0xFF);
			}
			inline constexpr color hex6(const std::array<char, 6>& str) {
				return hex6(std::string_view(str.data(), 6));
			}
			inline constexpr color hex8(const std::string_view& str) {
				uint32_t u32 = 0;
				for (const auto& ch : str) {
					auto t = const_as_hex(ch);
					if (t < 0)return nullcolor;
					u32 = u32 * 16 + t;
				}
				return colorspaces::u32_to_color(u32);
			}
			inline constexpr color hex8(const std::array<char, 8>& str) {
				return hex8(std::string_view(str.data(), 8));
			}
			inline constexpr color hex4(const std::string_view& str) {
				return hex8(std::array<char, 8>({ str[0],str[0],str[1],str[1],str[2],str[2],str[3],str[3] }));
			}
			inline constexpr color hex4(const std::array<char, 4>& str) {
				return hex4(std::string_view(str.data(), 4));
			}
			inline constexpr color hex3(const std::string_view& str) {
				return hex4(std::array<char, 4>({ str[0],str[1],str[2],'f' }));
			}
			inline constexpr color try_hex_notation(string_view_tokenizer& tokens) {
				if (tokens.next_token() == "#") {
					tokens.skip_token();
					tokens.next_token();
					switch (tokens.next_token().length()) {
					case 8:
						return hex8(tokens.next_token());
					case 6:
						return hex6(tokens.next_token());
					case 4:
						return hex4(tokens.next_token());
					case 3:
						return hex3(tokens.next_token());
					default:
						return nullcolor;
					}
				}
				return unknowncolor;
			}

			template<class... Args>
			inline constexpr color parse_color(Args ...args) {
				string_view_tokenizer tokenizer(args...);
				while (!tokenizer.eof() && tokenizer.next_token().empty())
					tokenizer.skip_token();
				{
					auto r = try_named(tokenizer);
					if (r || r.is_null())return r;
				}
				{
					auto r = try_hex_notation(tokenizer);
					if (r || r.is_null())return r;
				}
				{
					auto r = try_color_func(tokenizer);
					if (r || r.is_null())return r;
				}
				return nullcolor;
			};
			template<class colorspace>
			struct parse_typed_color_helper {
				template<class... Args>
				inline static constexpr std::optional<typed_color<colorspace>> parse(Args ...args) {
					color c = parse_color(args...);
					if (c.first == colorspaces::to_index_v<colorspace>)
						return typed_color<colorspace>(c.second);
					else {
						return colorspaces::dynamic_convert<colorspace>::conv(c);
					}
				}
			};
			template<class colorspace>
			struct parse_color_as_helper {
				template<class... Args>
				inline static constexpr color parse(Args ...args) {
					auto parsed = parse_typed_color_helper<colorspace>::parse(args...);
					if (parsed)return parsed.value();
					else return nullcolor;
				}
			};
			template<>
			struct parse_color_as_helper<colorspaces::unknown_colorspace> {
				template<class... Args>
				inline static constexpr color parse(Args ...args) {
					return parse_color(args...);
				}
			};
			template<class colorspace = colorspaces::unknown_colorspace,class ...Args>
			inline static constexpr color parse(Args ...args) {
				return parse_color_as_helper<colorspace>::parse(args...);
			};
		}
		using parser_impl::parse_color;
		using parser_impl::parse;
	}
}


#endif /* CSS_COLORPARSER_HPP */
