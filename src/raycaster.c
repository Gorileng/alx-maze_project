#include "../include/main.h"

/**
 * raycaster - A function to perform the raycasting operations.
 *
 * @object: struct of the type Vector containing every coordinates of that oject
 * @time: Time of the current frame
 * @oldTime: Time of the previous frame
 * @instance: struct of the type SDL_Instance
 * @event: SDL Event
 * @delay: The delay of the flag (true or false)
 * @keys: A boolean array to store the key states
 * Return: 0 (Success)
 */
int raycaster(Vector object, double *time, double *oldTime,
			SDL_Instance *instance, SDL_Event *event, bool delay,
			const unsigned char *keys)
{
	while (!done(event, delay, keys))
		break;
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		/* x-coord in the camera space */
		double cameraX = 2 * x / SCREEN_WIDTH - 1;
		/* Calculate the ray direction vector */
		double rayDirX = object.dirX + object.planeX * cameraX;
		double rayDirY = object.dirY + object.planeY * cameraX;
		/* Calculate the map position of the ray origin */
		int mapX = floor(object.posX);
		int mapY = floor(object.posY);
		/* Calculate the distance to the next x and y grid lines */
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirY);
		/* Calculate the initial step and side distances */
		double sideDistX, sideDistY, perpWallDist;
		int stepX, stepY, wall_height, wall_top, wall_bottom;
		int hit = 0;
		int side = 0; /* was a NS or a EW wall hit? */
		int worldMap[MAP_WIDTH][MAP_HEIGHT];
		/* The world map */
		generate_map(worldMap);
		calculate_distances(object, rayDirX, rayDirY, &sideDistX,
			&sideDistY, &stepX, &stepY, mapX, mapY, deltaDistX, deltaDistY);
		int wall_code = DDA(&hit, &side, &sideDistX, &sideDistY, deltaDistX,
							deltaDistY, &mapX, &mapY, stepX, stepY, worldMap);

		calcuate_projection(side, sideDistX, sideDistY,	deltaDistX, deltaDistY,
						&perpWallDist, &wall_height, &wall_top, &wall_bottom);
		render_walls(instance->renderer, wall_top, wall_bottom, wall_code, side, x);
		/* drawMiniMap(worldMap, instance, object); */
	}
	fps_count(time, oldTime);

	return (0);
}

/**
 * calculate_distances - A function to calculate every important coordinates at
 * the given point in time.
 *
 * @object: struct of the type Vector containing every coordinates of that oject
 * @rayDirX: Ray position and the direction in x-axis
 * @rayDirY: Ray position and the direction in y-axis
 * @sideDistX: Length of ray from the current position to the next position on x-axis
 * @sideDistY: Length of ray from the current position to the next position on y-axis
 * @stepX: What direction to step in the x-axis (either +1 or -1)
 * @stepY: What direction to step in the y-axis (either +1 or -1)
 * @mapX: x-coordinate of the current box of map we are in
 * @mapY: y-coordinate of the current box of map we are in
 * @deltaDistX: Length of the ray from one point to another on the x-axis
 * @deltaDistY: Length of the ray from one point to another on the y-axis
 */
void calculate_distances(Vector object, double rayDirX, double rayDirY,
						double *sideDistX, double *sideDistY, int *stepX,
						int *stepY, int mapX, int mapY, double deltaDistX,
						double deltaDistY)
{
	*stepX = 0;
	*stepY = 0;
	/* calculate the step and the initial sideDist */
	if (rayDirX < 0)
	{
		*stepX = -1;
		*sideDistX = (object.posX - mapX) * deltaDistX;
	} else
	{
		*stepX = 1;
		*sideDistX = (mapX + 1.0 - object.posX) * deltaDistX;
	}

	if (rayDirY < 0)
	{
		*stepY = -1;
		*sideDistY = (object.posY - mapY) * deltaDistY;
	} else
	{
		*stepY = 1;
		*sideDistY = (mapY + 1.0 - object.posY) * deltaDistY;
	}
}

/**
 * DDA - A Digital Differential Analysis
 *
 * @hit: An integer value (1 if wall was hit else 0)
 * @side: Side of a wall that was the hit (NS or EW)
 * @sideDistX: Length of the ray from current position to the next position on x-axis
 * @sideDistY: Length the of ray from current position to the next position on y-axis
 * @deltaDistX: Length of the ray from one point to another on the x-axis
 * @deltaDistY: Length of the ray from one point to another on the y-axis
 * @mapX: x-coordinate of the current box of a map we are in
 * @mapY: y-coordinate of the current box of a map we are in
 * @stepX: What direction to step in the x-axis (either +1 or -1)
 * @stepY: What direction to step in the y-axis (either +1 or -1)
 * @worldMap: A 2-dimensional array of the integer values
 * Return: Code of a wall if the wall was hit else 0
 */
int DDA(int *hit, int *side, double *sideDistX, double *sideDistY,
		double deltaDistX, double deltaDistY, int *mapX, int *mapY, int stepX,
		int stepY, int (*worldMap)[MAP_WIDTH])
{
	/* perform the DDA */
	while (*hit == 0)
	{
		/* Move to the next grid cell */
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += deltaDistX;
			*mapX += stepX;
			*hit = worldMap[*mapX][*mapY];
			*side = 0;
		} else
		{
			*sideDistY += deltaDistY;
			*mapY += stepY;
			*hit = worldMap[*mapX][*mapY];
			*side = 1;
		}
	}

	return (*hit);
}

/**
 * calculate_projection - A function that will calculate values that are necessary for
 * camera projection.
 *
 * @side: Side of a wall that was hit on (NS or EW)
 * @sideDistX: Length of ray from the current position to the next position on x-axis
 * @sideDistY: Length of ray from the current position to the next position on y-axis
 * @deltaDistX: Length of ray from one point to another on the x-axis
 * @deltaDistY: Length of ray from one point to another on the y-axis
 * @perpWallDist: Perpendicular distance from the ray to wall
 * @wall_height: Height of a wall
 * @wall_top: Top of a wall
 * @wall_bottom: Bottom of a wall
 * Return: struct of the type Projection
 */
Projection calcuate_projection(int side, double sideDistX, double sideDistY,
						double deltaDistX, double deltaDistY,
						double *perpWallDist, int *wall_height, int *wall_top,
						int *wall_bottom)
{
	Projection pixel_coordinates;

	/*
	* Calculates the distance projected on camera direction
	* (Euclidean distance will give fisheye effect!)
	*/
	if (side == 0)
		*perpWallDist = (sideDistX - deltaDistX);
	else
		*perpWallDist = (sideDistY - deltaDistY);

	/* Calculates the height of the line to draw on screen */
	int lineHeight = (int)(SCREEN_HEIGHT / *perpWallDist);

	/* calculates the  lowest and highest pixel to fill in the current stripe */
	int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;

	pixel_coordinates.drawStart = drawStart;
	pixel_coordinates.drawEnd = drawEnd;

	/* Calculates the  wall height on screen */
	*wall_height = (int)(SCREEN_HEIGHT / *perpWallDist);

	/* Calculates the top and bottom pixels of the wall on screen */
	*wall_top = SCREEN_HEIGHT / 2 - *wall_height / 2;
	*wall_bottom = *wall_top + *wall_height;

	if (*wall_top < 0 && *wall_bottom)
		*wall_top = 0;

	return (pixel_coordinates);
}
