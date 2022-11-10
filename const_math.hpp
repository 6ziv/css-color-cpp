#pragma once
#ifndef CSS_COLOR_CONST_MATH_HPP
#define CSS_COLOR_CONST_MATH_HPP

#include <gcem.hpp>
#include <initializer_list>
#include <algorithm>
#include <type_traits>
namespace css_colors{
	namespace details {
		template<typename T,typename =void>
		struct float_point_check { 
			using type = T;
		};
				
		template<class overrider, typename = void>
		struct get_real_number_type_helper {
			using type = long double;
		};
		template<class overrider>
		struct get_real_number_type_helper<overrider,std::void_t<typename overrider::type>> {
			using type = typename overrider::type;
		};

		using real = typename get_real_number_type_helper<struct css_color_real_number>::type;
		static_assert(std::is_floating_point_v<real>, "Not a floating point type");
		namespace math {
			using namespace gcem;
			constexpr real pi = static_cast<real>(gcem::acos<real>(0) * 2);
			using std::min;
			using std::max;
			using std::minmax;
			using std::minmax_element;
			template<const int M>
			inline constexpr real fmod_wrap(const real& x) {
				real r = static_cast<real>(fmod(x, (real)M));
				if (r < 0)return r + M;
				else return r;
			}
		}
	}
}
#endif /* CSS_COLOR_CONST_MATH_HPP */
