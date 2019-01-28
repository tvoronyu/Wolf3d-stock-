//
// Created by taras on 2019-01-11.
//

#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <SDL.h>
# include <math.h>
# include <fcntl.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <SDL_ttf.h>
# include <time.h>
# include "../lib/libft/libft.h"
# include "../include/get_next_line.h"

# define WIDTH 1024
# define HEIGHT 768

typedef struct		s_raycast
{
    double			posX;
    double			posY;
    double			dir_x;
    double			dir_y;
    double			cameraX;
    double			ray_dir_x;
    double			ray_dir_y;
    double			plan_x;
    double			plan_y;
    double			delta_dist_x;
    double			delta_dist_y;
    double			side_dist_x;
    double			side_dist_y;
    double			dist_player;
    int				map_x;
    int				map_y;
    double				side;
    int				hit;
    int				step_x;
    int				step_y;
    int 			posMouseX;

    int             centerX;
    int             centerY;
    int             lenToCenter;
    double          agle;
    int             sizePrjPln;
    double          pov;
    double          fov;
    double          pov_t;
    double          fov_t;
    double          temp;
    int             updown;

}					t_raycast;

typedef struct		s_draw
{
    double			weight;
    double			floor_wall_y;
    double			floor_wall_x;
    int				draw_start;
    int				draw_end;
    int				tex_x;
    int				tex_y;
    int				floor_tex_x;
    int				floor_tex_y;
    double			perp_wall_dist;
    double			wall_x;
    double			current_floor_x;
    double			current_floor_y;
    double			current_dist;
    int				line_height;

}					t_draw;

typedef	struct		s_sdl
{
    SDL_Window		*win;
    SDL_Renderer	*ren;
    SDL_Texture		*screen;
    SDL_Surface		*up;
    SDL_Surface		*up_1;
    SDL_Surface		*floor;
    SDL_Surface		*wall[7];
    Mix_Music		*mus[3];
    TTF_Font        *font_ttf;
    SDL_Surface     *font_surface;
    SDL_Color             color;
    SDL_Rect		font_rect;
    SDL_Texture *font_text;
}					t_sdl;

typedef struct wolf_f
{
    t_raycast		raycast;
    t_draw 			draw;
    t_sdl			sdl;
    double			speed;
    Uint32				buf[HEIGHT][WIDTH];
    int             counter_str_on_map;
    int				for_exit;
    char            *name;
    char            **full_map;
    int             **array;
    int             width_arr;
    int             height_arr;
   int  pos_X;
   int  pos_Y;
    int             count;
    int             code_error;
    int				x;
    int				y;
    int				d;
} t_wolf;

int     main(int argc, char *argv[]);
int     ft_valid(t_wolf *wolf);
void    ft_error(int error, t_wolf *wolf);
void	ft_free_mas(char **ret);
int     ft_check_min_size_map(t_wolf *wolf);
int     ft_check_pos_player(t_wolf *wolf);
char**  ft_chrlen(char *str);
void    ft_write_mas_int(int n, t_wolf *wolf, char **str);
int     ft_check_size_map(t_wolf *wolf);

SDL_Texture			*load_img(SDL_Renderer *ren, SDL_Surface *bmp, char *imag);
//char				*ft_joinfree(char *s1, char *s2, int j);
//void				ft_error(int num);
//char				**open_read(t_wolf *wolf);
void				first_ar(t_wolf *wolf, char **str);
void				check_str(t_wolf *wolf, char **str);
void				make_arr(t_wolf *wolf, char **str);
int					**int_malloc(t_wolf *wolf);
void				check_rest(t_wolf *wolf);
int					len_int(char *str);
void				raycasting(t_wolf *wolf);
void				keys(t_wolf *wolf);
unsigned int		get_pixel_int(SDL_Surface *SDL_Surfaceace, int x, int y);
void				put_pixel32(SDL_Surface *SDL_Surfaceace, int x, int y, int pixel);
SDL_Surface			*load_image(char *path);
Mix_Music			*load_music(char *path);
//void				apply_SDL_Surfaceace(int x, int y, SDL_Surface *sour, SDL_Surface *destination);
void				ft_game(t_wolf *wolf);
void				fresh(t_wolf *wolf);


#endif //WOLF3D_WOLF3D_H
