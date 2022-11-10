#pragma once
#ifndef CSS_COLOR_COLORSPACE_XYZ_HPP
#define CSS_COLOR_COLORSPACE_XYZ_HPP

#include "../colorspace_common.hpp"
#include "linear_rgb.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace xyz_impl {
			
			struct d65 {
				constexpr static mat tristimulus_matrix = {
					vecd{{0.4124564,0.3575761,0.1804375}},
					vecd{{0.2126729,0.7151522,0.0721750}},
					vecd{{0.0193339,0.1191920,0.9503041}}
				};
				constexpr static std::string_view xyz_name = "xyz-d65";
			};
			struct d50 {
				constexpr static mat tristimulus_matrix = {
					vecd{{0.4360747,0.3850649,0.1430804}},
					vecd{{0.2225045,0.7168786,0.0606169}},
					vecd{{0.0139322,0.0971045,0.7141733}}
					//vec{0.4360,0.3851,0.1431},
					//vec{0.2225,0.7169,0.0606},
					//vec{0.0139,0.0971,0.7139}
				};
				constexpr static std::string_view xyz_name = "xyz-d50";
			};
			
			template<class illuminant>
			struct xyz2rgb{
				constexpr static mat conv_mat = inverse_matrix(illuminant::tristimulus_matrix);
			};
			template<class illuminant>
			struct rgb2xyz {
				constexpr static mat conv_mat = illuminant::tristimulus_matrix;
			};
			template<class illuminant>
			struct predefined_name{
				inline constexpr static std::string_view name = std::string_view();
			};
			template<>
			struct predefined_name <d50>{
				inline constexpr static std::string_view name = "xyz-d50";
			};
			template<>
			struct predefined_name <d65> {
				inline constexpr static std::string_view name = "xyz-d65";
			};
			template<class illuminant>
			struct xyz {
				constexpr static std::string_view name = illuminant::xyz_name;
				constexpr static std::string_view default_predefined_name = predefined_name<illuminant>::name;
				using base_type = linear_rgb;
				using arg_type = std::tuple<parser::element_types::unbounded_percentage, parser::element_types::unbounded_percentage, parser::element_types::unbounded_percentage>;
				using to_base = xyz2rgb<illuminant>;
				using from_base = rgb2xyz<illuminant>;
				constexpr static vec ref_whitepoint = { vec_sum(illuminant::tristimulus_matrix[0]),vec_sum(illuminant::tristimulus_matrix[1]),vec_sum(illuminant::tristimulus_matrix[2]) };
			};
		}
		template<class illuminant>
		using xyz = xyz_impl::xyz<illuminant>;
		using xyz_d50 = xyz<xyz_impl::d50>;
		using xyz_d65 = xyz<xyz_impl::d65>;
		REGISTER_COLORSPACE(xyz_d50);
		REGISTER_COLORSPACE(xyz_d65);
		
		REGISTER_PERDEFINED(xyz-d50, xyz_d50, xyz_d50);
		REGISTER_PERDEFINED(xyz-d65, xyz_d65, xyz_d65);
		REGISTER_PERDEFINED(xyz, xyz_default, xyz_d65);
	}
}
#endif /* CSS_COLOR_COLORSPACE_XYZ_HPP */
