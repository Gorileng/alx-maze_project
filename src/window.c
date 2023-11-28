#include "../include/main.h"

/**
 * initialize_SDL - A function that initializes the SDL
 *
 * @instance: An SDL instance of the type struct SDL_Instance
 * Return: A boolean success flag (true or false) 
 */
bool initialize_SDL(SDL_Instance *instance)
{
	bool success = true;
	/* Initializes the SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Failed to initialize SDL! SDL_Error: %s\n",
				SDL_GetError());
		success = false;
	} else
	{
		instance->window = SDL_CreateWindow("The Maze Project",
							SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (instance->window == NULL)
		{
			fprintf(stderr, "SDL failed to create Window! SDL_Error: %s\n",
					SDL_GetError());
			SDL_Quit();
			success = false;
		} else
		{
			/*instance->screenSurface=SDL_GetWindowSurface(instance->window);*/
			instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (instance->renderer == NULL)
			{
				fprintf(stderr, "Failed to create Renderer! SDL_Error: %s\n",
						SDL_GetError());
				SDL_Quit();
				success = false;
			}
			/* Colors the screen surface */
			/* colorFill(instance, "black"); */
		}
	}
	return (success);
}

/**
 * keep_window - A function to keep SDL window open.
 *
 * @quit: Boolean flag to keep a window open
 */
void keep_window(bool *quit)
{
	SDL_Event event;

	while (*quit == false)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				*quit = true;
				break;
			}
		}
	}
}

/**
 * end - A funtion to free the resources and quit the SDL subsystems.
 *
 * @instance: An SDL instance of the type struct SDL_Instance
 */
void end(SDL_Instance *instance)
{
	/* Deallocates the surface */
	SDL_FreeSurface(instance->image);
	instance->image = NULL;
	/* Deallocates the screen surface */
	SDL_FreeSurface(instance->screenSurface);
	instance->screenSurface = NULL;
	/* Destroys the Renderer */
	SDL_DestroyRenderer(instance->renderer);
	instance->renderer = NULL;
	/* Destroys the window */
	SDL_DestroyWindow(instance->window);
	instance->window = NULL;
	/* Free resources and Quit the SDL subsystems */
	SDL_Quit();
}

/**
 * colorFill - A function that fills the SDL Screen Surface with the specified color
 *
 * @instance: An SDL instance of the type struct SDL_Instance
 * @color_name: The name of a color as a string
 */
void colorFill(SDL_Instance *instance, char *color_name)
{
	/* Retrieves the color */
	ColorRGBA fill_color = rgba_color_code(color_name);
	/* Fills a surface with the color */
	SDL_FillRect(instance->screenSurface, NULL,
				SDL_MapRGBA(instance->screenSurface->format,
				fill_color.red, fill_color.green, fill_color.blue,
				(Uint8) (255 * fill_color.alpha)));
	/* Updates a surface */
	SDL_UpdateWindowSurface(instance->window);
}

/**
 * loadMedia - A function to the load media into the SDL_Surface.
 *
 * @instance: An SDL instance of the type struct SDL_Instance
 * @media_path: the relative path to a media
 * Return: A boolean success flag (true or false)
 */
bool loadMedia(SDL_Instance *instance, char *media_path)
{
	/* Loading the success flag */
	bool success = true;

	/* Load the splash image */
	instance->image = SDL_LoadBMP(media_path);
	if (instance->image == NULL)
	{
		fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", media_path,
				SDL_GetError());
		success = false;
	}

	return (success);
}
