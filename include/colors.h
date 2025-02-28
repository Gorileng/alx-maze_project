#ifndef _COLORS_H_
#define _COLORS_H_

/**
 * struct ColorRGBA - Typedef for the struct of the type Vector
 * @red: The R value of a color
 * @green: The G value of a color
 * @blue: The B value of a color
 * @alpha: The value between 0.0 (fully transparent) and the 1.0 (fully opaque)
 *
 * Description: A struct that contains RGBA values of the color.
 */
typedef struct ColorRGBA
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	float alpha;
} ColorRGBA;

ColorRGBA rgba_color_code(char *color);
ColorRGBA rgba_color_add(ColorRGBA color1, ColorRGBA color2);
void rgba_add(ColorRGBA *color, int n, float a);
ColorRGBA rgba_color_sub(ColorRGBA color1, ColorRGBA color2);
void rgba_sub(ColorRGBA *color, int n, float a);
ColorRGBA rgba_color_mul(ColorRGBA color1, ColorRGBA color2);
void rgba_mul(ColorRGBA *color, int n, float a);
ColorRGBA rgba_color_div(ColorRGBA color1, ColorRGBA color2);
void rgba_div(ColorRGBA *color, int n, float a);
int rgba_color_comp(ColorRGBA color1, ColorRGBA color2);

ColorRGBA color_wall(int wall_code,	int side);

#endif /* _COLORS_H_ */
