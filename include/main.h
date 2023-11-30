#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include "applied_math.h"
#include "colors.h"
#include "raycaster.h"
#include "renderer.h"

/* The dimensional constants */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_HEIGHT 24
#define MAP_WIDTH 24
#define BLOCK_HEIGHT 64
#define PLAYER_HEIGHT 32
#define FOV 66
#define COLOR_DEPTH 32
#define TILE_SIZE 16

#define KEYS 322

/* The boolean values */
#define false 0
#define true 1

typedef _Bool bool;

/**
 * struct SDL_Instance - Typedef for the struct of a type SDL_Instance
 * @window: SDL Window will be rendering to
 * @renderer: The SDL Renderer
 * @screenSurface: SDL Screen Surface that is contained by the window
 * @image: The image that will load and show on the screen
 *
 * Description: The struct for a SDL_Instance.
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *screenSurface;
	SDL_Surface *image;
} SDL_Instance;

_Bool initialize_SDL(SDL_Instance *instance);
void keep_window(bool *quit);
void colorFill(SDL_Instance *instance, char *color_name);
void end(SDL_Instance *instance);
_Bool loadMedia(SDL_Instance *instance, char *media_path);
_Bool done(SDL_Event *event, bool delay, const unsigned char *keys);
void readKeys(const unsigned char *keys);
int poll_events(void);

void draw_image(SDL_Instance *instance);
void draw_something(SDL_Instance *instance);

/**
 * generate_map - The function to generate a map to be rendered in a game.
 *
 * @worldMap: A 2-dimensional matrix of the integers to render a game map
 */
void generate_map(int (*worldMap)[MAP_WIDTH]);

/**
 * drawMiniMap - The function to draw a minimap.
 *
 * @WorldMap: A map to draw
 * @instance: SDL_Instance to draw to
 * @player: player to draw
 */
void drawMiniMap(int (*WorldMap)[MAP_WIDTH], SDL_Instance *instance,
				Vector player);

int raycaster(Vector object, double *time, double *oldTime,
			SDL_Instance *instance, SDL_Event *event, bool delay,
			const unsigned char *keys);
int DDA(int *hit, int *side, double *sideDistX, double *sideDistY,
		double deltaDistX, double deltaDistY, int *mapX, int *mapY, int stepX,
		int stepY, int (*worldMap)[MAP_WIDTH]);
int verLine(int x, int y1, int y2, ColorRGBA *color, SDL_Instance *instance);

/**
 * color_walls - Assigns the color code to each the integer case
 *
 * @worldMap: A 2-dimensional array of the integer values
 * @mapX: x-coordinate of the current box of a map we are in
 * @mapY: y-coordinate of the current box of a map we are in
 * @color: struct of the type ColorRGBA that contains RGBA value of the given color
 * @side: Side of a wall that was hit to (NS or EW)
 */
void color_walls(int (*worldMap)[MAP_WIDTH], int mapX, int mapY,
				ColorRGBA *color, int side);

#endif /*_MAIN_H_*/
