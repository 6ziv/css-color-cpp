#pragma once
#ifndef CSS_COLOR_COLORSPACE_LCH_HPP
#define CSS_COLOR_COLORSPACE_LCH_HPP

#include "../colorspace_common.hpp"
#include "lab.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace lch_impl {
			
			inline constexpr vec lch2lab(const vec& lch) {
				return vec({ lch[0],
					lch[1] * math::cos(lch[2] * math::pi / 180),
					lch[1] * math::sin(lch[2] * math::pi / 180) });
			}
			inline constexpr vec lab2lch(const vec& lab) {
				//real hue = math::atan(lab[2],lab[1])
				real hue = math::atan2(lab[2], lab[1]) * 180 / math::pi;
				if (hue < 0)hue += 360;
				return vec({ lab[0],
					math::sqrt(lab[1] * lab[1] + lab[2] * lab[2]),
					hue
				});
			}
			
			using chroma_range = parser::element_types::common_range<true, 150, 1, 0, parser::element_types::no_upper_bound, 0>;
			struct lch {
				inline constexpr static std::string_view name = "lch";
				inline static constexpr std::string_view default_color_function_name = name;
				using base_type = lab;
				using to_base = as_conv<lch2lab>;
				using from_base = as_conv<lab2lch>;
				using arg_type = std::tuple<parser::element_types::percent_100, parser::element_types::number<chroma_range>, parser::element_types::degree>;
			};
		}
		using lch_impl::lch;
		REGISTER_COLORSPACE(lch);
		REGISTER_COLORFUNCTION(lch, lch);
	}
}

#endif /* CSS_COLOR_COLORSPACE_LCH_HPP */
