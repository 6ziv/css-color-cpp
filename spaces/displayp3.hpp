#pragma once
#ifndef CSS_COLOR_COLORSPACE_DISPLAYP3_HPP
#define CSS_COLOR_COLORSPACE_DISPLAYP3_HPP

#include "../colorspace_common.hpp"
#include "xyz.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace disp3_impl {
			struct disp3_to_xyz {
				inline constexpr static mat conv_mat =
				{
					vec{0.4865709486482162, 0.26566769316909306, 0.1982172852343625},
					vec{0.2289745640697488, 0.6917385218365064,  0.079286914093745},
					vec{0.0000000000000000, 0.04511338185890264, 1.043944368900976}
				};
			};
			struct xyz_to_disp3 {
				inline constexpr static mat conv_mat = inverse_matrix(disp3_to_xyz::conv_mat);
			};

		}
		struct display_p3 {
			inline constexpr static std::string_view name = "display-p3";
			using base_type = xyz_d65;
			using to_base = disp3_impl::disp3_to_xyz;
			using from_base = disp3_impl::xyz_to_disp3;
			using arg_type = parser::element_types::predefined_colorspace_args;
		};


		REGISTER_COLORSPACE(display_p3);
		REGISTER_PERDEFINED(display-p3, display_p3, display_p3);
	}
}

#endif /* CSS_COLOR_COLORSPACE_DISPLAYP3_HPP */
