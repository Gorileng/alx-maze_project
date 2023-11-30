#ifndef _RENDERING_H_
#define _RENDERING_H_

/* The divider for making a minimap smaller */
#define MINIMAP_DIVIDER 16
/* The dividers for making a player in a minimap smaller */
#define MINIMAP_PLAYER_WIDTH 4
#define MINIMAP_PLAYER_HEIGHT 4

void render_walls(SDL_Renderer *renderer, int wall_top, int wall_bottom,
				int wall_code, int side, int x);

#endif /* _RENDERING_H_ */
