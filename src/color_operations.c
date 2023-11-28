#include "../include/main.h"

/**
 * rgba_color_add - A function to add the 2 structs of the type ColorRGBA together
 *
 * @color1: the 1st struct
 * @color2: the 2nd struct
 * Return: the sum of the struct type ColorRGBA
 */
ColorRGBA rgba_color_add(ColorRGBA color1, ColorRGBA color2)
{
	ColorRGBA color;

	color.red = abs(color1.red + color2.red) % 255;
	color.green = abs(color1.green + color2.green) % 255;
	color.blue = abs(color1.blue + color2.blue) % 255;
	color.alpha = handle_mod1(color1.alpha + color2.alpha);
	return (color);
}

/**
 * rgba_color_sub - A function to subtract the 2 structs of the type ColorRGBA
 *
 * @color1: the 1st struct
 * @color2: the 2nd struct
 * Return: the difference of the struct of type ColorRGBA
 */
ColorRGBA rgba_color_sub(ColorRGBA color1, ColorRGBA color2)
{
	ColorRGBA color;

	color.red = abs(color1.red - color2.red) % 255;
	color.green = abs(color1.green - color2.green) % 255;
	color.blue = abs(color1.blue - color2.blue) % 255;
	color.alpha = handle_mod1(color1.alpha - color2.alpha);
	return (color);
}

/**
 * rgba_color_mul - A function to multiply the 2 structs of the type ColorRGBA together
 *
 * @color1: the 1st struct
 * @color2: the 2nd struct
 * Return: the product of the struct type ColorRGBA
 */
ColorRGBA rgba_color_mul(ColorRGBA color1, ColorRGBA color2)
{
	ColorRGBA color;

	color.red = abs(color1.red * color2.red) % 255;
	color.green = abs(color1.green * color2.green) % 255;
	color.blue = abs(color1.blue * color2.blue) % 255;
	color.alpha = handle_mod1(color1.alpha * color2.alpha);
	return (color);
}

/**
 * rgba_color_div - A function to divide the 2 structs of the type ColorRGBA
 *
 * @color1: the 1st struct
 * @color2: the 2nd struct
 * Return: the quotient of the struct type ColorRGBA
 */
ColorRGBA rgba_color_div(ColorRGBA color1, ColorRGBA color2)
{
	ColorRGBA color;

	color.red = abs(color1.red / color2.red) % 255;
	color.green = abs(color1.green / color2.green) % 255;
	color.blue = abs(color1.blue / color2.blue) % 255;
	color.alpha = handle_mod1(color1.alpha / color2.alpha);
	return (color);
}

/**
 * rgba_color_comp - A function to compare the 2 structs of the type ColorRGBA
 *
 * @color1: the 1st struct
 * @color2: the 2nd struct
 * Return: 1 when they're equal or else -1
 */
int rgba_color_comp(ColorRGBA color1, ColorRGBA color2)
{
	if (!(color1.red == color2.red))
		return (-1);
	if (!(color1.green == color2.green))
		return (-1);
	if (!(color1.blue == color2.blue))
		return (-1);
	if (!(color1.alpha == color2.alpha))
		return (-1);
	return (1);
}
