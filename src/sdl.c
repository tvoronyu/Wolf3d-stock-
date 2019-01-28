#define SUR SDL_Surface *destination

#include "wolf3d.h"

SDL_Surface		*load_image(char *path)
{
	SDL_Surface	*texture;

	texture = IMG_Load(path);
	if (texture == NULL)
		ft_error(4, NULL);
	return (texture);
}

unsigned int	get_pixel_int(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;

	if (surface) {
        if ((pixels = (unsigned int *) surface->pixels)) {
//	if ((y * surface->w) + x < WIDTH * 4 * (HEIGHT - 1))
            if ((y * surface->w) + x < WIDTH * HEIGHT)
                return (pixels[(y * surface->w) + x]);
        } else
            write(1, "fe", 2);
    }
	return (0);
}

Mix_Music		*load_music(char *path)
{
	Mix_Music *music;

	if (!(music = Mix_LoadMUS(path)))
		ft_error(4, NULL);
	return (music);
}

void			apply_surface(int x, int y, SDL_Surface *sour, SUR)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(sour, NULL, destination, &offset);
}