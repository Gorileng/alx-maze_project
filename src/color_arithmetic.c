#include "../include/main.h"

/**
 * handle_mod1 - Function to handle the module of operations by 1
 *
 * @target: The target of module operation
 * Return: Float value of an operation
 */
float handle_mod1(float target)
{
	if (target >= 1.0)
		return (target - (fabs(target)));
	else if (target <= -1.0)
		return (target + (fabs(target)) + 1);
	else
		return (target);
}

/**
 * rgba_add - A function to add the given values to RGB and the A of color
 *
 * @color: The struct of a target color
 * @n: An integer to be added to a Red, Green, and Blue values of the color
 * @a: A float value to be added to Alpha value of the color
 */
void rgba_add(ColorRGBA *color, int n, float a)
{
	color->red = abs(color->red + n) % 255;
	color->green = abs(color->green + n) % 255;
	color->blue = abs(color->blue + n) % 255;
	color->alpha = color->alpha + a;
	color->alpha = handle_mod1(color->alpha);
}

/**
 * rgba_sub - A function to subtract a given values from RGB and A of the color
 *
 * @color: The struct of target color
 * @n: An integer to be subtracted from RGB values of the color
 * @a: A float value to be subtracted from Alpha value of the color
 */
void rgba_sub(ColorRGBA *color, int n, float a)
{
	color->red = abs(color->red - n) % 255;
	color->green = abs(color->green - n) % 255;
	color->blue = abs(color->blue - n) % 255;
	color->alpha = color->alpha - a;
	color->alpha = handle_mod1(color->alpha);
}

/**
 * rgba_mul - A function to multiply RGB and A by the given values
 *
 * @color: The struct of target color
 * @n: An integer to multiply with a Red, Green, and Blue values of the color
 * @a: A float value to multiply with Alpha value of the color
 */
void rgba_mul(ColorRGBA *color, int n, float a)
{
	color->red = abs(color->red * n) % 255;
	color->green = abs(color->green * n) % 255;
	color->blue = abs(color->blue * n) % 255;
	color->alpha = color->alpha * a;
	color->alpha = handle_mod1(color->alpha);
}

/**
 * rgba_div - A function to divide RGB and A by the given values
 *
 * @color: The struct of a target color
 * @n: An integer to divide Red, Green, and Blue values of the color with
 * @a: A float value to divide Alpha value of the color with
 */
void rgba_div(ColorRGBA *color, int n, float a)
{
	color->red = abs(color->red / n) % 255;
	color->green = abs(color->green / n) % 255;
	color->blue = abs(color->blue / n) % 255;
	color->alpha = color->alpha / a;
	color->alpha = handle_mod1(color->alpha);
}
