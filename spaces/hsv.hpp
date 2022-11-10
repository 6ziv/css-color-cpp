#pragma once
#ifndef CSS_COLOR_COLORSPACE_HSV_HPP
#define CSS_COLOR_COLORSPACE_HSV_HPP

#include "../colorspace_common.hpp"
#include "srgb.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace hsv_impl {
			
			inline constexpr vec hsv2hsl(const vec& hsv) {
				const auto& [h, s, v] = hsv;
				real l = v * (1 - s / 2);
				real a = math::min<real>(l, 1 - l);
				real rs = (a != 0) ? (v - l) / a : 0;
				return { h,rs,l };
			};
			inline constexpr vec hsl2hsv(const vec& hsl) {
				const auto& [h, s, l] = hsl;
				real v = l + s * math::min<real>(l, 1 - l);
				real rs = (v != 0) ? 2 * (1 - l / v) : 0;
				return { h,rs,v };
			}

			struct hsv {
				using base_type = hsl;
				inline constexpr static std::string_view name = "hsv";

				using to_base = as_conv<hsv2hsl>;
				using from_base = as_conv<hsl2hsv>;
				using arg_type = parser::element_types::predefined_colorspace_args;
			};
		}
		using hsv_impl::hsv;
		//REGISTER_COLORSPACE(hsv);
	}
}

#endif /* CSS_COLOR_COLORSPACE_HSV_HPP */
