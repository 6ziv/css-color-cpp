#pragma once
#ifndef CSS_COLOR_COLORSPACE_HWB_HPP
#define CSS_COLOR_COLORSPACE_HWB_HPP

#include "../colorspace_common.hpp"
#include "hsl.hpp"
#include "linear_rgb.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace hwb_impl {
			
			inline constexpr vec hwb2rgb(const vec& hwb) {
				const auto& [h, w, b] = hwb;
				if (w + b >= 1) {
					return { w / (w + b), w / (w + b), w / (w + b) };
				}
				auto t = hsl::to_base::conv({ h,1,0.5 });
				for (size_t i = 0; i < 3; i++) {
					t[i] = t[i] * (1 - w - b) + w;
				}
				return t;
			}
			inline constexpr vec rgb2hwb(const vec& rgb) {
				const auto& [r,g, b] = rgb;
				auto hsl = hsl::from_base::conv({ r,g,b });
				auto white = math::min({ r,g,b });
				auto black = 1 - math::max({ r, g, b });
				return {hsl[0],white,black};
			}
			struct hwb {
				inline constexpr static std::string_view name = "hwb";
				inline constexpr static std::string_view default_color_function_name = name;
				using base_type = srgb;
				using to_base = as_conv<hwb2rgb>;
				using from_base = as_conv<rgb2hwb>;
				using arg_type = std::tuple<parser::element_types::degree, parser::element_types::percentage, parser::element_types::percentage>;
				using serialize_as = srgb;
			};
		}
		using hwb_impl::hwb;
		REGISTER_COLORSPACE(hwb);
		REGISTER_COLORFUNCTION(hwb, hwb);
	}
}
#endif /* CSS_COLOR_COLORSPACE_HWB_HPP */
