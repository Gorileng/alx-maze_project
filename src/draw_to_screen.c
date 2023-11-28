#include "../include/main.h"

/**
 * draw_something - A basic functions to draw the line
 *
 * @instance: An SDL instance of the type struct SDL_Instance
 */
void draw_something(SDL_Instance *instance)
{
	SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance->renderer, 10, 10, 100, 100);
}

/**
 * draw_image - A function to draw the aimage onto a SDL Screen Surface
 *
 * @instance: An SDL instance of the type struct SDL_Instance
 */
void draw_image(SDL_Instance *instance)
{
	/* Apply the image */
	SDL_BlitSurface(instance->image, NULL, instance->screenSurface, NULL);
	/* Update the surface */
	SDL_UpdateWindowSurface(instance->window);
}

/**
 * drawMiniMap - A function to draw minimap.
 *
 * @WorldMap: The map will draw
 * @instance: The SDL_Instance will draw to
 * @player: The players to draw
 */
void drawMiniMap(int (*WorldMap)[MAP_WIDTH], SDL_Instance *instance,
				Vector player)
{
	SDL_Rect curRect;
	ColorRGBA color;

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

			color_walls(WorldMap, x, y, &color, 0);
			SDL_SetRenderDrawColor(instance->renderer, color.red, color.green,
									color.blue, (Uint8) (255 * color.alpha));
			SDL_RenderFillRect(instance->renderer, &rect);
		}
	}

	/* Draw the player */
	curRect.x = player.posX * TILE_SIZE;
	curRect.y = player.posY * TILE_SIZE;
	curRect.w = TILE_SIZE;
	curRect.h = TILE_SIZE;
	color = rgba_color_code("indigo");
	SDL_SetRenderDrawColor(instance->renderer, color.red, color.green,
							color.blue, (Uint8) (255 * color.alpha));
	SDL_RenderFillRect(instance->renderer, &curRect);

	/* Updates the screen */
	SDL_RenderPresent(instance->renderer);
}
