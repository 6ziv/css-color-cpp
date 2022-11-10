#pragma once
#ifndef CSS_COLOR_COLORSPACE_SRGB_HPP
#define CSS_COLOR_COLORSPACE_SRGB_HPP

#include "../colorspace_common.hpp"
namespace css_colors::details {
	namespace colorspaces {
		struct srgb
		{
			inline static constexpr std::string_view default_color_function_name[2] = {"rgba","rgb"};
			
			static constexpr std::string_view name = "rgba";
			static constexpr bool legacy = true;
			using arg_type = std::tuple<parser::element_types::byte, parser::element_types::byte, parser::element_types::byte>;
		};
		REGISTER_COLORSPACE(srgb);

		REGISTER_COLORFUNCTION(rgb, srgb);
		REGISTER_COLORFUNCTION(rgba, srgb);
		REGISTER_PERDEFINED(srgb, srgb, srgb);
	}
}
#endif /* CSS_COLOR_COLORSPACE_SRGB_HPP */
