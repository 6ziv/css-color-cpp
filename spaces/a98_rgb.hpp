#pragma once
#ifndef CSS_COLOR_COLORSPACE_A98_RGB_HPP
#define CSS_COLOR_COLORSPACE_A98_RGB_HPP

#include "../colorspace_common.hpp"
#include "srgb.hpp"
#include "xyz.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace a98_rgb_impl
		{
			
			inline constexpr real adobe_decompress(const real& x) {
				return static_cast<real>(math::copysign(math::pow(math::abs(x), 563. / 256.), x));
			}
			inline constexpr real adobe_compress(const real& x) {
				return static_cast<real>(math::copysign(math::pow(math::abs(x), 256. / 563.), x));
			}
			struct linear_a98_to_xyz {
				constexpr static mat conv_mat = {
					vecd{{0.5766690429101305,   0.1855582379065463,   0.1882286462349947}} ,
					vecd{{0.29734497525053605,  0.6273635662554661,   0.07529145849399788}},
					vecd{{0.02703136138641234,  0.07068885253582723,  0.9913375368376388}}
				};
			};
			struct xyz_to_linear_a98 {
				constexpr static mat conv_mat = inverse_matrix(linear_a98_to_xyz::conv_mat);
			};
			struct a98_linear {
				using base_type = xyz_d65;
				using to_base = linear_a98_to_xyz;
				using from_base = xyz_to_linear_a98;
			};
			struct a98_rgb {
				using base_type = a98_linear;
				inline static constexpr std::string_view name = "a98-rgb";
				inline constexpr static std::string_view default_predefined_name = name;
				using to_base = as_conv<apply_to_vec<adobe_decompress>>;
				using from_base = as_conv<apply_to_vec<adobe_compress>>;

				using arg_type = parser::element_types::predefined_colorspace_args;
			};
		};
		using a98_rgb_impl::a98_rgb;
		REGISTER_COLORSPACE(a98_rgb);

		REGISTER_PERDEFINED(a98-rgb, a98_rgb, a98_rgb)
	}
}
#endif /* CSS_COLOR_COLORSPACE_A98_RGB_HPP */
