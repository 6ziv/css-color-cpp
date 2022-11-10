#pragma once
#ifndef CSS_COLOR_COLORSPACE_REC2020_HPP
#define CSS_COLOR_COLORSPACE_REC2020_HPP

#include "../colorspace_common.hpp"
#include "../const_math.hpp"
#include "srgb.hpp"
#include "xyz.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace rec2020_impl
		{
			
			inline constexpr real rec2020_gamma(const real& x) {
				constexpr real alpha = static_cast<real>(1.09929682680944);
				constexpr real beta = static_cast<real>(0.018053968510807);
				real absolute = math::abs(x);
				if (absolute > beta)return static_cast<real>(math::copysign(alpha * math::pow(absolute, 0.45) - (alpha - 1), x));
				return static_cast<real>(4.5 * x);
			}
			inline constexpr real rec2020_gamma_inv(const real& x) {
				constexpr real alpha = static_cast<real>(1.09929682680944);
				constexpr real beta = static_cast<real>(0.018053968510807);
				real absolute = math::abs(x);
				if (absolute < beta * 4.5)return static_cast<real>(x / 4.5);
				return static_cast<real>(math::copysign(math::pow((absolute + alpha - 1) / alpha, 1. / 0.45), x));
			}
			
			struct linear_rec2020_to_xyz {
				constexpr static mat conv_mat = {
					vecd{{ 63426534. / 99577255.,  20160776. / 139408157.,  47086771. / 278816314.  }},
					vecd{{ 26158966. / 99577255., 472592308. / 697040785.,   8267143. / 139408157. }},
					vecd{{ 4.994106574466076e-17,  19567812. / 697040785., 295819943. / 278816314. }}
				};
			};
			struct xyz_to_linear_rec2020 {
				constexpr static mat conv_mat = inverse_matrix(linear_rec2020_to_xyz::conv_mat);
			};
			struct rec2020_linear {
				using base_type = xyz_d50;
				using to_base = linear_rec2020_to_xyz;
				using from_base = xyz_to_linear_rec2020;
			};
			struct rec2020 {
				using base_type = rec2020_linear;
				inline static constexpr std::string_view name = "rec2020";
				inline constexpr static std::string_view default_predefined_name = name;
				using to_base = as_conv<apply_to_vec<rec2020_gamma_inv>>;
				using from_base = as_conv<apply_to_vec<rec2020_gamma>>;

				using arg_type = parser::element_types::predefined_colorspace_args;
			};
		};
		using rec2020_impl::rec2020;
		REGISTER_COLORSPACE(rec2020);

		REGISTER_PERDEFINED(rec2020, rec2020, rec2020)
	}
}
#endif /* CSS_COLOR_COLORSPACE_REC2020_HPP */
