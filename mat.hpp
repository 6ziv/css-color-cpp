#pragma once
#ifndef CSS_COLOR_MAT_HPP
#define CSS_COLOR_MAT_HPP

#include <array>
#include "const_math.hpp"
namespace css_colors::details {
	using vec = std::array<real, 3>;
	using mat = std::array<vec, 3>;
	struct vec_double_initializer :
		public std::array<double, 3>
	{
		constexpr operator vec()noexcept {
			return vec{ static_cast<real>(at(0)),static_cast<real>(at(1)),static_cast<real>(at(2)) };
		}
	};
	using vecd = vec_double_initializer;
	
	
	inline constexpr real cofactor(const mat& matrix, size_t row, size_t col) {
		size_t r1 = (row == 0 ? 1 : 0), r2 = (row == 2 ? 1 : 2);
		size_t c1 = (col == 0 ? 1 : 0), c2 = (col == 2 ? 1 : 2);
		return matrix[r1][c1] * matrix[r2][c2] - matrix[r1][c2] * matrix[r2][c1];
	}
	inline constexpr mat inverse_matrix(const mat& matrix)
	{
		real det = cofactor(matrix, 0, 0) * matrix[0][0] - cofactor(matrix, 0, 1) * matrix[0][1] + cofactor(matrix, 0, 2) * matrix[0][2];
		return {
			vec{+cofactor(matrix,0,0) / det,-cofactor(matrix,1,0) / det,+cofactor(matrix,2,0) / det},
			vec{-cofactor(matrix,0,1) / det,+cofactor(matrix,1,1) / det,-cofactor(matrix,2,1) / det},
			vec{+cofactor(matrix,0,2) / det,-cofactor(matrix,1,2) / det,+cofactor(matrix,2,2) / det}
		};
	}
	inline constexpr real vec_sum(const vec& v) {
		return v[0] + v[1] + v[2];
	}
	inline constexpr static vec row(const mat& m, size_t i) {
		return { m[0][i],m[1][i],m[2][i] };
	}
	inline constexpr static vec elementwise_mul(const vec& a, const vec& b) {
		return vec{ a[0] * b[0] , a[1] * b[1] , a[2] * b[2] };
	}
	inline constexpr static real operator*(const vec& a, const vec& b) {
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	}
	inline constexpr static vec operator*(const mat& m, const vec& v) {
		return { m[0] * v,m[1] * v,m[2] * v };
	}
	inline constexpr static vec operator*(const vec& v, const mat& m) {
		return { v * row(m,0),v * row(m,1),v * row(m,2) };
	}
	inline constexpr static mat operator*(const mat& m1, const mat& m2) {
		return { m1[0] * m2,m1[1] * m2,m1[2] * m2 };
	}


	template<real F(const real&)>
	inline constexpr vec apply_to_vec(const vec& v) {
		return vec{ F(v[0]),F(v[1]),F(v[2]) };
	}

	template<vec F(const vec&)>
	struct as_conv {
		inline constexpr static vec conv(const vec& v) {
			return F(v);
		}
	};

}
#endif /* CSS_COLOR_MAT_HPP */
