#include "../include/main.h"

/**
 * done - A function that will return 1 if you close a window or press escape
 * key. And handles everything that is needed per frame.
 *
 * @event: SDL Event
 * @delay: the delay flag (true or false)
 * @keys: A boolean array to store the key states
 * Return: A boolean success flag (true or false) 
 */
bool done(SDL_Event *event, bool delay, const unsigned char *keys)
{
	/* delay gives the CPU some free time */
	/* use once per frame to avoid the 100% usage of the CPU core */
	if (delay)
		SDL_Delay(5); /* so it consumes the less processing power */
	SDL_PollEvent(event);
	/**
	 * while (SDL_PollEvent(event))
	 * {
	 *	if (event->type == SDL_QUIT)
	 *		return (true);
	 * }
	 */
	/* readKeys(keys); */
	if (keys[SDLK_ESCAPE])
		return (true);

	return (false);
}

/**
 * readKeys - A function that gives the value of the pressed key to keys array.
 *
 * @keys: A boolean array to store the key states
 */
void readKeys(const unsigned char *keys)
{
	SDL_PumpEvents();
	keys = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < 1; i++)
	{
		if (keys[i] == 1)
			break;
	}
}
