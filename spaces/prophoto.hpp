#pragma once
#ifndef CSS_COLOR_COLORSPACE_PROPHOTO_HPP
#define CSS_COLOR_COLORSPACE_PROPHOTO_HPP

#include "../colorspace_common.hpp"
#include "../const_math.hpp"
#include "srgb.hpp"
#include "xyz.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace prophoto_rgb_impl
		{
			
			inline constexpr real prophoto_gamma(const real& x) {
				constexpr real Et = 1. / 512.;
				real absolute = math::abs(x);
				return static_cast<real>((absolute >= Et) ? math::copysign(math::pow(absolute, 1. / 1.8), x) : (16. * x));
			}
			inline constexpr real prophoto_gamma_inv(const real& x) {
				constexpr real Et2 = 16. / 512.;
				real absolute = math::abs(x);
				return static_cast<real>((absolute <= Et2) ? absolute / 16 : math::copysign(math::pow(absolute, 1.8), x));
			}
			
			struct linear_prophoto_to_xyz {
				constexpr static mat conv_mat = {
					vecd{{ 0.7977604896723027, 0.13518583717574031, 0.0313493495815248 }},
					vecd{{ 0.2880711282292934, 0.7118432178101014, 0.00008565396060525902 }},
					vecd{{ 0.0, 0.0, 0.8251046025104601 }}
				};
			};
			struct xyz_to_linear_prophoto {
				constexpr static mat conv_mat = inverse_matrix(linear_prophoto_to_xyz::conv_mat);
			};
			struct prophoto_linear {
				using base_type = xyz_d50;
				using to_base = linear_prophoto_to_xyz;
				using from_base = xyz_to_linear_prophoto;
			};
			struct prophoto_rgb {
				using base_type = prophoto_linear;
				inline static constexpr std::string_view name = "prophoto-rgb";
				inline constexpr static std::string_view default_predefined_name = name;
				using to_base = as_conv<apply_to_vec<prophoto_gamma_inv>>;
				using from_base = as_conv<apply_to_vec<prophoto_gamma>>;

				using arg_type = parser::element_types::predefined_colorspace_args;
			};
		};
		using prophoto_rgb_impl::prophoto_rgb;
		REGISTER_COLORSPACE(prophoto_rgb);

		REGISTER_PERDEFINED(prophoto-rgb, prophoto_rgb, prophoto_rgb)
	}
}
#endif /* CSS_COLOR_COLORSPACE_PROPHOTO_HPP */
