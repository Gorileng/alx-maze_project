#include "../include/main.h"

/**
 * deg - A function to convert the given value of either the Gradients
 * or the Radians to Degrees.
 *
 * @val: Value in the Gradients or the Radians
 * @format: 'g' for the Gradient or 'r' for the Radians
 * Return: Value in the Degrees or else -1
 */
double deg(float val, char format)
{
	if (format == 'g')
		val *= 0.9;
	else if (format == 'r')
		val = val * 180 / PI;
	else
		return (-1);

	return (val);
}

/**
 * grd - A function to convert the given value of either the Degrees
 * or the Radians to Gradients.
 *
 * @val: Value in the Degrees or the Radians
 * @format: 'd' for the Degrees or 'r' for the Radians
 * Return: Value in the Gradients or else -1
 */
double grd(float val, char format)
{
	if (format == 'd')
		val /= 0.9;
	else if (format == 'r')
		val = val * 200 / PI;
	else
		return (-1);

	return (val);
}

/**
 * rad - A function to convert the given value of either the Degrees
 * or the Gradients to Radians.
 *
 * @val: Value in the Degrees or the Gradients
 * @format: 'd' for the Degrees or 'g' for the Gradients
 * Return: Value in the Radians or else -1
 */
double rad(float val, char format)
{
	if (format == 'd')
		val = val * PI / 180;
	else if (format == 'g')
		val = val * PI / 200;
	else
		return (-1);

	return (val);
}
