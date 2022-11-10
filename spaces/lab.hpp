#pragma once
#ifndef CSS_COLOR_COLORSPACE_LAB_HPP
#define CSS_COLOR_COLORSPACE_LAB_HPP

#include "../colorspace_common.hpp"
#include "xyz.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace lab_impl {
			
			inline constexpr real lab2xyz_helper(const real& x) {
				constexpr real epsilon = static_cast<real>(216. / 24389);  // 6^3/29^3
				constexpr real kappa = static_cast<real>(24389. / 27);   // 29^3/3^3
				auto cube = x * x * x;
				if (cube > epsilon)return cube;
				else return static_cast<real>((x - (16.0 / 116)) / (kappa / 116));
			}
			inline constexpr vec lab2xyz_d50(const vec& lab) {
				vec ret{ 0,0,0 };
				ret[1] = static_cast<real>((lab[0] + 16.0) / 116.0);
				ret[0] = static_cast<real>(lab[1] / 500.0 + ret[1]);
				ret[2] = static_cast<real>(ret[1] - lab[2] / 200.0);
				return elementwise_mul(apply_to_vec<lab2xyz_helper>(ret), xyz_d50::ref_whitepoint);
			}
			inline constexpr real xyz2lab_helper(const real& x) {
				constexpr real epsilon = static_cast<real>(216. / 24389);  // 6^3/29^3
				constexpr real kappa = static_cast<real>(24389. / 27);   // 29^3/3^3
				if (x > epsilon)return static_cast<real>(math::pow(x, 1. / 3));
				else return static_cast<real>((kappa / 116.) * x + 16. / 116.);
			}
			inline constexpr vec xyz_d502lab(const vec& xyz_ref) {
				auto f = apply_to_vec<xyz2lab_helper>(
					elementwise_mul(xyz_ref, vec{ 1 / xyz_d50::ref_whitepoint[0],1 / xyz_d50::ref_whitepoint[1],1 / xyz_d50::ref_whitepoint[2] })
				);
				return vec{ 116 * f[1] - 16,500 * (f[0] - f[1]),200 * (f[1] - f[2]) };
			}
			struct lab {
				inline constexpr static std::string_view name = "lab";
				inline constexpr static std::string_view default_color_function_name = "lab";
				using base_type = xyz_d50;
				using to_base = as_conv<lab2xyz_d50>;
				using from_base = as_conv<xyz_d502lab>;
				using ab_type = parser::element_types::number < parser::element_types::common_range<true, 125, 1, parser::element_types::no_lower_bound, parser::element_types::no_upper_bound, 0>>;
				using arg_type = std::tuple<parser::element_types::percent_100, ab_type, ab_type>;
			};
		}
		using lab_impl::lab;
		REGISTER_COLORSPACE(lab);
		REGISTER_COLORFUNCTION(lab, lab);
	}
}

#endif /* CSS_COLOR_COLORSPACE_LAB_HPP */
