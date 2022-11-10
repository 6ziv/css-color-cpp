#pragma once
#include "spaces/srgb.hpp"
#include "colorspace_convert.hpp"
#include "const_str.hpp"
#include <array>
#include <string_view>
namespace css_colors::details {
	namespace named_colors {
		constexpr std::array<std::pair<std::string_view, uint32_t>, 149> named =
		{
			std::pair<std::string_view, uint32_t>({"aliceblue",			0xF0F8FFFFul}),
			{"antiquewhite",		0xFAEBD7FFul},		{"aqua",				0x00FFFFFFul},
			{"aquamarine",			0x7FFFD4FFul},		{"azure",				0xF0FFFFFFul},
			{"beige",				0xF5F5DCFFul},		{"bisque",				0xFFE4C4FFul},
			{"black",				0x000000FFul},		{"blanchedalmond",		0xFFEBCDFFul},
			{"blue",				0x0000FFFFul},		{"blueviolet",			0x8A2BE2FFul},
			{"brown",				0xA52A2AFFul},		{"burlywood",			0xDEB887FFul},
			{"cadetblue",			0x5F9EA0FFul},		{"chartreuse",			0x7FFF00FFul},
			{"chocolate",			0xD2691EFFul},		{"coral",				0xFF7F50FFul},
			{"cornflowerblue",		0x6495EDFFul},		{"cornsilk",			0xFFF8DCFFul},
			{"crimson",				0xDC143CFFul},		{"cyan",				0x00FFFFFFul},
			{"darkblue",			0x00008BFFul},		{"darkcyan",			0x008B8BFFul},
			{"darkgoldenrod",		0xB8860BFFul},		{"darkgray",			0xA9A9A9FFul},
			{"darkgreen",			0x006400FFul},		{"darkgrey",			0xA9A9A9FFul},
			{"darkkhaki",			0xBDB76BFFul},		{"darkmagenta",			0x8B008BFFul},
			{"darkolivegreen",		0x556B2FFFul},		{"darkorange",			0xFF8C00FFul},
			{"darkorchid",			0x9932CCFFul},		{"darkred",				0x8B0000FFul},
			{"darksalmon",			0xE9967AFFul},		{"darkseagreen",		0x8FBC8FFFul},
			{"darkslateblue",		0x483D8BFFul},		{"darkslategray",		0x2F4F4FFFul},
			{"darkslategrey",		0x2F4F4FFFul},		{"darkturquoise",		0x00CED1FFul},
			{"darkviolet",			0x9400D3FFul},		{"deeppink",			0xFF1493FFul},
			{"deepskyblue",			0x00BFFFFFul},		{"dimgray",				0x696969FFul},
			{"dimgrey",				0x696969FFul},		{"dodgerblue",			0x1E90FFFFul},
			{"firebrick",			0xB22222FFul},		{"floralwhite",			0xFFFAF0FFul},
			{"forestgreen",			0x228B22FFul},		{"fuchsia",				0xFF00FFFFul},
			{"gainsboro",			0xDCDCDCFFul},		{"ghostwhite",			0xF8F8FFFFul},
			{"gold",				0xFFD700FFul},		{"goldenrod",			0xDAA520FFul},
			{"gray",				0x808080FFul},		{"green",				0x008000FFul},
			{"greenyellow",			0xADFF2FFFul},		{"grey",				0x808080FFul},
			{"honeydew",			0xF0FFF0FFul},		{"hotpink",				0xFF69B4FFul},
			{"indianred",			0xCD5C5CFFul},		{"indigo",				0x4B0082FFul},
			{"ivory",				0xFFFFF0FFul},		{"khaki",				0xF0E68CFFul},
			{"lavender",			0xE6E6FAFFul},		{"lavenderblush",		0xFFF0F5FFul},
			{"lawngreen",			0x7CFC00FFul},		{"lemonchiffon",		0xFFFACDFFul},
			{"lightblue",			0xADD8E6FFul},		{"lightcoral",			0xF08080FFul},
			{"lightcyan",			0xE0FFFFFFul},		{"lightgoldenrodyellow",0xFAFAD2FFul},
			{"lightgray",			0xD3D3D3FFul},		{"lightgreen",			0x90EE90FFul},
			{"lightgrey",			0xD3D3D3FFul},		{"lightpink",			0xFFB6C1FFul},
			{"lightsalmon",			0xFFA07AFFul},		{"lightseagreen",		0x20B2AAFFul},
			{"lightskyblue",		0x87CEFAFFul},		{"lightslategray",		0x778899FFul},
			{"lightslategrey",		0x778899FFul},		{"lightsteelblue",		0xB0C4DEFFul},
			{"lightyellow",			0xFFFFE0FFul},		{"lime",				0x00FF00FFul},
			{"limegreen",			0x32CD32FFul},		{"linen",				0xFAF0E6FFul},
			{"magenta",				0xFF00FFFFul},		{"maroon",				0x800000FFul},
			{"mediumaquamarine",	0x66CDAAFFul},		{"mediumblue",			0x0000CDFFul},
			{"mediumorchid",		0xBA55D3FFul},		{"mediumpurple",		0x9370DBFFul},
			{"mediumseagreen",		0x3CB371FFul},		{"mediumslateblue",		0x7B68EEFFul},
			{"mediumspringgreen",	0x00FA9AFFul},		{"mediumturquoise",		0x48D1CCFFul},
			{"mediumvioletred",		0xC71585FFul},		{"midnightblue",		0x191970FFul},
			{"mintcream",			0xF5FFFAFFul},		{"mistyrose",			0xFFE4E1FFul},
			{"moccasin",			0xFFE4B5FFul},		{"navajowhite",			0xFFDEADFFul},
			{"navy",				0x000080FFul},		{"oldlace",				0xFDF5E6FFul},
			{"olive",				0x808000FFul},		{"olivedrab",			0x6B8E23FFul},
			{"orange",				0xFFA500FFul},		{"orangered",			0xFF4500FFul},
			{"orchid",				0xDA70D6FFul},		{"palegoldenrod",		0xEEE8AAFFul},
			{"palegreen",			0x98FB98FFul},		{"paleturquoise",		0xAFEEEEFFul},
			{"palevioletred",		0xDB7093FFul},		{"papayawhip",			0xFFEFD5FFul},
			{"peachpuff",			0xFFDAB9FFul},		{"peru",				0xCD853FFFul},
			{"pink",				0xFFC0CBFFul},		{"plum",				0xDDA0DDFFul},
			{"powderblue",			0xB0E0E6FFul},		{"purple",				0x800080FFul},
			{"rebeccapurple",		0x663399FFul},		{"red",					0xFF0000FFul},
			{"rosybrown",			0xBC8F8FFFul},		{"royalblue",			0x4169E1FFul},
			{"saddlebrown",			0x8B4513FFul},		{"salmon",				0xFA8072FFul},
			{"sandybrown",			0xF4A460FFul},		{"seagreen",			0x2E8B57FFul},
			{"seashell",			0xFFF5EEFFul},		{"sienna",				0xA0522DFFul},
			{"silver",				0xC0C0C0FFul},		{"skyblue",				0x87CEEBFFul},
			{"slateblue",			0x6A5ACDFFul},		{"slategray",			0x708090FFul},
			{"slategrey",			0x708090FFul},		{"snow",				0xFFFAFAFFul},
			{"springgreen",			0x00FF7FFFul},		{"steelblue",			0x4682B4FFul},
			{"tan",					0xD2B48CFFul},		{"teal",				0x008080FFul},
			{"thistle",				0xD8BFD8FFul},		{"tomato",				0xFF6347FFul},
			{"transparent",			0x00000000ul},		{"turquoise",			0x40E0D0FFul},
			{"violet",				0xEE82EEFFul},		{"wheat",				0xF5DEB3FFul},
			{"white",				0xFFFFFFFFul},		{"whitesmoke",			0xF5F5F5FFul},
			{"yellow",				0xFFFF00FFul},		{"yellowgreen",			0x9ACD32FFul}
		};
		inline constexpr int const_binary_lookup(int lower, int upper, const std::string_view& token) {
			if (lower == upper && const_iequal(named[lower].first, token))return lower;
			if (lower >= upper)return -1;
			int midpoint = (lower + upper) / 2;
			if (const_iless(named[midpoint].first, token))return const_binary_lookup(midpoint + 1, upper, token);
			else return const_binary_lookup(lower, midpoint, token);
		}
		inline constexpr color lookup_named_color(const std::string_view& token) {
			auto index = const_binary_lookup(0, static_cast<int>(named.size()), token);
			if (index == -1)return unknowncolor; else return colorspaces::u32_to_color(named[index].second);
			/*auto iter = std::lower_bound(named.cbegin(), named.cend(), token,
				[](const std::pair<std::string_view, uint32_t>& lhs, const std::string_view& rhs)->bool {
					return const_iless(lhs.first, rhs);
				});
			if (iter == named.cend() || !const_iequal(iter->first, token))
				return std::nullopt;*/
				//auto iter = named.cbegin();
				//return colorspaces::u32_to_color(iter->second);
		}

	};
}