# CSS Color Parser: A Color Parser in C++

#### Features:

[css-color-parser-cpp](https://github.com/mapbox/css-color-parser-cpp) is a little old, but is still very handy and reliable. You can rely on that if you do not need the features listed below.

* **More Colorspaces** : HSL,HWB,CIE/Oklab LAB/LCH,sRGB,display-p3,a98-rgb,... . To get a full list, look inside 'spaces' directory.

* __Compile-Time Parsing__ : With the 'constexpr' keywork in C++ and the awesome [gcem](https://github.com/kthohr/gcem) library, it is finally possible to parse a color in compile-time. Also, linear transformations (matrices) are merged at compile-time to improve runtime performance.

* __Converting Between Colorspaces__ : Though parsing a color string as rgba is still the main purpose of this library, this library also supports converting between colorspaces.

* __Extensibility__ : New colorspaces can be easily added to the library. 



#### To parse colors

For an example on how to use, see css_color.cpp.



Basically, we declare a color constant  like this:

`constexpr css_colors::color const_color = css_colors::parse("brown");`

or we can read color from istream:

```C++
css_colors::color c;
std::cin >> c;
```

We convert between registered colorspaces (and print) like this:

`std::cout << c.as<css_colors::colorspaces::oklab>() << std::endl;`

As I understand, to meet the standard (who cares), we need to clamp the colors before use.

`c = css_colors::clamp(c);`



And we can also print hex notations by applying `std::hex`  to the ostream, or get a uint32 representing the argb channels from the color by `css_colors::to_dword(c, "argb")`.



To get a string representation, using stringstream is recommended. Though there may be some functions in "details" namespace, they are intended for internal use (as some functionalities are performed within stream output operator)



#### To add new colorspaces

Now we image a new colorspace named 'foo', and we will add it into the library in a few steps. We start by declaring `struct foo` within namespace css_colors:\:details::colorspaces. Then, we need to provide following information.

###### 1.base type and conversions.

In this library, convertions between colorspaces are managed as a tree, in which 'srgb' is the root node. (We only care about the paths, so root node makes no difference.)

To add a node representing our new colorspace foo, we need a new undirected edge to connect it to any existing node (for example, bar). And this existing node (bar) is called the base_type of our colorspace foo.

After base_type is determined, we need the conversions between base_type and our new colorspace. If the conversion is linear, we use a matrix to represent it.

```c++
struct foo_to_base{
    constexpr static mat conv_mat = {
        vecd{{0,0,1}} ,
        vecd{{0,1,0}},
        vecd{{1,0,0}}
    };
}
struct foo_from_base{
    constexpr static mat conv_mat = 
        inverse_matrix(foo_to_base::conv_mat);
}
```

If the conversion is not linear, we have to declare them as functions.

```c++
inline constexpr vec revert_elements(const vec& x){
    return vec{vec[2],vec[1],vec[0]};
}
using foo_to_base=as_conv<pass_through>;
using foo_from_base=as_conv<pass_through>;

/* Or we may do some element-wise transform on a vector
inline constexpr real func(const real& x) {
    return math::pow(x,0.5);
}
using foo_to_base=as_conv<apply_to_vec<func>>;
*/
```

Now, we have all necessary information to convert this new colorspace with others. We simply tell the library what we know by adding three typedefs in struct foo:

```c++
using base_type = bar;
using to_base = foo_to_base;
using from_base = foo_from_base;
```





###### 2.Argument types

"Predefined colors" colorspaces, or say, colorspace that can be used like `color(colorspace-name param1 param2 param3)`, all have the same parameter types, as specified in [section 10.1](https://www.w3.org/TR/css-color-4/#color-function) of [this draft](https://www.w3.org/TR/css-color-4/) : three elements which can be either real number or percentages, and they are interpreted in the default way (0%=0,100%=1). 

In this circumstance, we need to declare in struct foo:

`using arg_type = parser::element_types::predefined_colorspace_args;`



However, if our new colorspace can be used with a color function, we may need different ways to parse those elements. Thus, we declare arg_type as a tuple of length 3, each element represents an element type. See element_types for predefined element types.



###### 3.names

Now we still need to define some string_views to help parsing or serialization. They are listed as follows:

* name(required): name of the colorspace. May be used in some debug messages.

* default_predefined_name ("Predefined colors" colorspaces):
  
  * if it is a string_view, then it represents the associated name. 
  - if it is an array of two string_view-s ,then the elements represent the name used with or without alpha channel (see [here](https://www.w3.org/TR/css-color-4/#serializing-sRGB-values) ).

* default_color_function_name (colorspaces that can be used with a color function like `rgb()`) :same as default_predefined_name, but used in color functions instead of `color()`.

###### 4.legacy mode

A constexpr static boolean value `legacy=true` may be added in declared struct to support a legacy form in which there are comma-s between elements.

Note that this value also affects color serialization, according to [Section 15.2](https://www.w3.org/TR/css-color-4/#serializing-sRGB-values). Currently, only srgb-related colors will be serialized in legacy mode. We may declare another boolean value `out_legacy=false` to avoid this.



###### 5.serialize_as

[Section 15.2](https://www.w3.org/TR/css-color-4/#serializing-sRGB-values) claims that rgb,hsl,hwb colors will also be serialized in rgb/rgba format. To achieve similar effect on out colorspace foo (for example, always serialize foo as baz), we may add `using serialize_as = baz` to struct foo.

The library will do a type cast from foo to baz before the overloaded output operator.



Now we have declared struct foo in namespace css_colors:\:details::colorspaces, We only need to add a few lines following struct declaration. 

```c++
REGISTER_COLORSPACE(foo);
REGISTER_COLORFUNCTION(foo, foo);
REGISTER_PERDEFINED(foo, foo, foo);
```

`REGISTER_COLORSPACE` takes the colorspace struct name as a parameter.

`REGISTER_COLORFUNCTION ` takes the color function name as first parameter, and colorspace struct name as second parameter. When there are multiple color functions(like rgb and rgba), we should make multiple calls to this.

`REGISTER_PERDEFINED` takes the predefined colorspace name as first parameter, but colorspace struct name as third parameter. The second parameter is used to create a helper class named "PREDEFINEDfoo_helper" (so, unlike the first parameter, it cannot contain '-'; and unlike the third, it should be unique when a colorspace contains multiple predefined names).



These macros will use the given colorspace type info to instantiate some templates, to help the library get information about colorspaces.

Include our new header (say, foo.hpp) from colorspace.hpp, after including "colorspace_common.hpp". Order within colorspaces (that do not depend on each other) is not so important, but the order should stay the same in different translation units. (That is obviously true if we only include "css_colors.hpp", and the buildsystem always recompiles affected sources when headers changed.)
