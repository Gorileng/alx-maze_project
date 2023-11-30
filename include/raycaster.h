#ifndef _RAYCASTER_H_
#define _RAYCASTER_H_

/**
 * struct Vector - Typedef for the struct of the type Vector
 * @posX: x-coordinate of the object at the starting time
 * @posY: y-coordinate of the object at the starting time
 * @dirX: x-coordinate direction vector of the object at the time
 * @dirY: y-coordinate direction vector  of the object at the time
 * @planeX: x-coordinate of the object on a camera plane at the time
 * @planeY: y-coordinate of the object on a camera plane at the time
 *
 * Description: It is the struct that contains every cordinates of the object at a time
 */
typedef struct Vector
{
	int posX;
	int posY;
	int dirX;
	int dirY;
	int planeX;
	int planeY;
} Vector;

/**
 * struct Projection - Typedef for the struct of a type Projection
 * @drawStart: The coordinates of a first pixel to be drawn
 * @drawEnd: The coordinates of a last pixel to be drawn
 *
 * Description: It is the struct that contains a start and stop the cordinates for
 * camera projection.
 */
typedef struct Projection
{
	int drawStart;
	int drawEnd;
} Projection;

void calculate_distances(Vector object, double rayDirX, double rayDirY,
						double *sideDistX, double *sideDistY, int *stepX,
						int *stepY, int mapX, int mapY, double deltaDistX,
						double deltaDistY);
Projection calcuate_projection(int side, double sideDistX, double sideDistY,
						double deltaDistX, double deltaDistY,
						double *perpWallDist, int *wall_height, int *wall_top,
						int *wall_bottom);
int fps_count(double *time, double *oldTime);
unsigned long getTicks(void);
void cls(SDL_Surface *scr);

#endif /* _RAYCASTER_H_ */
