#include "../include/main.h"

/**
 * getTicks - A function that will return time in milliseconds
 * since the program started.
 *
 * Return: unsigned long value of time in milliseconds
 */
unsigned long getTicks(void)
{
	return (SDL_GetTicks());
}

/**
 * poll_events - A function that polls for the events and then returns
 *
 * Return: 0 if there's no events, 1 if events
 */
int poll_events(void)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				if (key.keysym.sym == SDLK_ESCAPE)
					return (1);
				break;
		}
	}
	return (0);
}
