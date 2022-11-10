#pragma once
#ifndef CSS_COLOR_COLORSPACE_HSL_HPP
#define CSS_COLOR_COLORSPACE_HSL_HPP

#include "../colorspace_common.hpp"
#include "srgb.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace hsl_impl {
			
			inline constexpr real hsl2rgb_helper(const real& h, const real&, const real& l, const real& a, int n)
			{
				real k = math::fmod(n + h / 30, 12);
				return l - a * math::max<real>(-1, math::min<real>({ k - 3, 9 - k, 1 }));
			}
			inline constexpr vec hsl2srgb(const vec& v) {
				const auto& [h, s, l] = v;
				real a = s * math::min<real>(l, 1 - l);
				return { 255 * hsl2rgb_helper(h,s,l,a,0),255 * hsl2rgb_helper(h,s,l,a,8), 255 * hsl2rgb_helper(h,s,l,a,4) };
			};
			inline constexpr vec srgb2hsl(const vec& v) {
				auto r = v[0] / 255, g = v[1] / 255, b = v[2] / 255;
				const auto& [pmin, pmax] = math::minmax_element(v.cbegin(), v.cend());
				real h = 0, s = 0, l = (*pmin + *pmax) / 2;
				real d = *pmax - *pmin;
				if (d != 0) {
					real t = math::min(l, 1 - l);
					s = (t != 0) ? (*pmax - l) / t : 0;
					switch (std::distance(v.cbegin(), pmax)) {
					case 0:h = (g - b) / d + (g < b ? 6 : 0); break;
					case 1:h = (b - r) / d + 2; break;
					case 2:h = (r - g) / d + 4; break;
					}
					h = h * 60;
				}
				return { h,s,l };
			}

			struct hsl {
				inline constexpr static std::string_view name = "hsl";
				inline constexpr static std::string_view default_color_function_name = name;
				inline constexpr static bool legacy = true;
				using base_type = srgb;
				using to_base = as_conv<hsl2srgb>;
				using from_base = as_conv<srgb2hsl>;
				using arg_type = std::tuple<parser::element_types::degree, parser::element_types::percentage, parser::element_types::percentage>;
				using serialize_as = srgb;
			};
		}
		using hsl_impl::hsl;
		REGISTER_COLORSPACE(hsl);
		REGISTER_COLORFUNCTION(hsl, hsl);
		REGISTER_COLORFUNCTION(hsla, hsl);
	}
}

#endif /* CSS_COLOR_COLORSPACE_HSL_HPP */
