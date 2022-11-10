#pragma once
#ifndef CSS_COLOR_COLORSPACE_LINEAR_RGB_HPP
#define CSS_COLOR_COLORSPACE_LINEAR_RGB_HPP

#include "../colorspace_common.hpp"
#include "srgb.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace linear_rgb_impl
		{
			
			inline constexpr real srgb_gamma(const real& linear) {
				constexpr real x = (real)0.04045;
				constexpr real phi = (real)12.92;
				constexpr real threshold = x / phi;
				constexpr real a = (real)0.055;
				constexpr real gamma = (real)2.4;
				if (linear <= threshold)return linear * phi;
				return ((1 + a) * math::pow(linear, 1 / gamma) - a) * 255;
			}
			inline constexpr real srgb_gamma_inv(const real& encoded255) {
				auto encoded = encoded255 / 255;
				constexpr real x = (real)0.04045;
				constexpr real phi = (real)12.92;
				//constexpr real threshold = x / phi;
				constexpr real a = (real)0.055;
				constexpr real gamma = (real)2.4;
				if (encoded <= x)return encoded / phi;
				return math::pow((encoded + a) / (1 + a), gamma);
			}
			struct linear_rgb {
				using base_type = srgb;
				inline static constexpr std::string_view name = "srgb-linear";
				constexpr static std::string_view default_predefined_name = name;
				using to_base = as_conv<apply_to_vec<srgb_gamma>>;
				using from_base = as_conv<apply_to_vec<srgb_gamma_inv>>;

				using arg_type = parser::element_types::predefined_colorspace_args;
			};
		};
		using linear_rgb_impl::linear_rgb;
		REGISTER_COLORSPACE(linear_rgb);

		REGISTER_PERDEFINED(srgb-linear,linear_rgb,linear_rgb)
	}
}
#endif /* CSS_COLOR_COLORSPACE_LINEAR_RGB_HPP */
