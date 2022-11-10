#pragma once
#ifndef CSS_COLOR_COLORSPACE_OKLAB_HPP
#define CSS_COLOR_COLORSPACE_OKLAB_HPP

#include "../colorspace_common.hpp"
#include "xyz.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace oklab_impl {
			
			struct xyz_to_oklab_helper1 {
				inline constexpr static mat conv_mat = {
					vecd{{+0.8189330101,+0.3618667424,-0.1288597137}},
					vecd{{+0.0329845436,+0.9293118715,+0.0361456387}},
					vecd{{+0.0482003018,+0.2643662691,+0.6338517070}}
				};
			};
			struct oklab_helper2_to_oklab {
				inline constexpr static mat conv_mat = { 
					vecd{{+0.2104542553,+0.7936177850,-0.0040720468}},
					vecd{{+1.9779984951,-2.4285922050,+0.4505937099}},
					vecd{{+0.0259040371,+0.7827717662,-0.8086757660}}
				};
			};
			
			struct oklab_helper2_from_oklab {
				inline constexpr static mat conv_mat = inverse_matrix(oklab_helper2_to_oklab::conv_mat);
			};
			struct xyz_from_oklab_helper1 {
				inline constexpr static mat conv_mat = inverse_matrix(xyz_to_oklab_helper1::conv_mat);
			};

			struct oklab_helper1 {
				using base_type = xyz_d65;
				using to_base = xyz_from_oklab_helper1;
				using from_base = xyz_to_oklab_helper1;
			};
			struct oklab_helper2 {
				inline constexpr static real cube(const real& x) {
					return x * x * x;
				}
				inline constexpr static real cubrt(const real& x) {
					return static_cast<real>(math::pow(x,1./3));
				}
				using base_type = oklab_helper1;
				using to_base = as_conv<apply_to_vec<cube>>;
				using from_base = as_conv<apply_to_vec<cubrt>>;
			};

		
			using ab_range = parser::element_types::common_range<true, 2, 5>;
			struct oklab {
				inline constexpr static std::string_view name = "oklab";
				inline static constexpr std::string_view default_color_function_name = name;
				using base_type = oklab_helper2;
				using to_base = oklab_helper2_from_oklab;
				using from_base = oklab_helper2_to_oklab;
				using arg_type = std::tuple<parser::element_types::percent_1, parser::element_types::number<ab_range>, parser::element_types::number<ab_range>>;
			};
		}
		using oklab_impl::oklab;
		REGISTER_COLORSPACE(oklab);
		REGISTER_COLORFUNCTION(oklab, oklab);
	}
}

#endif /* CSS_COLOR_COLORSPACE_OKLAB_HPP */
