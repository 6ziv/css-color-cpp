#pragma once
#ifndef CSS_COLOR_COLORSPACE_OKLCH_HPP
#define CSS_COLOR_COLORSPACE_OKLCH_HPP

#include "../colorspace_common.hpp"
#include "srgb.hpp"
#include "lch.hpp"
#include "oklab.hpp"
namespace css_colors::details {
	namespace colorspaces {
		namespace oklch_impl {
			using chroma_range = parser::element_types::common_range<true, 2, 5, 0, parser::element_types::no_upper_bound, 0>;
		}
		struct oklch {
			inline constexpr static std::string_view name = "oklch";
			inline static constexpr std::string_view default_color_function_name = name;

			using base_type = oklab;
			using to_base = lch::to_base;
			using from_base = lch::from_base;
			using arg_type = std::tuple<parser::element_types::percent_1, parser::element_types::number<oklch_impl::chroma_range>, parser::element_types::degree>;
		};


		REGISTER_COLORSPACE(oklch);
		REGISTER_COLORFUNCTION(oklch, oklch);
	}
}

#endif /* CSS_COLOR_COLORSPACE_OKLCH_HPP */
