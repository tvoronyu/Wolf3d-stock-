#include "wolf3d.h"

void  ft_init_all(t_wolf *wolf)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    ft_error(3, wolf);
  if (!(wolf->sdl.win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
    HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN)))
    ft_error(3, wolf);
  if (!(wolf->sdl.ren = SDL_CreateRenderer(wolf->sdl.win, -1, SDL_RENDERER_ACCELERATED
    | SDL_RENDERER_PRESENTVSYNC)))
    ft_error(3, wolf);
  if (!(wolf->sdl.screen = SDL_CreateTexture(wolf->sdl.ren,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
    ft_error(3, wolf);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    ft_error(3, wolf);
  if (TTF_Init() < 0)
      ft_error(3, wolf);
  wolf->sdl.up = load_image("texture/ceil.jpg");
  wolf->sdl.up_1 = load_image("texture/ceil.jpg");
  wolf->sdl.floor = load_image("texture/floor.jpg");
  wolf->sdl.wall[0] = load_image("texture/11.jpg");
  wolf->sdl.wall[1] = load_image("texture/16.jpg");
  wolf->sdl.wall[2] = load_image("texture/13.jpg");
  wolf->sdl.wall[3] = load_image("texture/14.jpg");
  wolf->sdl.wall[4] = load_image("texture/15.jpg");
  wolf->sdl.mus[0] = load_music("texture/sound.mp3");
  wolf->raycast.dir_x = -1.0;
  wolf->raycast.dir_y = 0.0;
  wolf->raycast.plan_x = 0.0;
  wolf->raycast.plan_y = 0.66;
  wolf->speed = 0.1;
  wolf->for_exit = 0;
  wolf->raycast.posMouseX = 0;
}

int    ft_count_str_on_map(t_wolf *wolf)
{
    int n;
    int fd;
    char *line;

    n = 0;
    fd = open(wolf->name, O_RDWR);
    if (fd > 2)
    {
        while (get_next_line(fd, &line))
        {
            n++;
            free(line);
        }
        close(fd);
    }
    return (n);
}

void  ft_read_map_on_file(t_wolf *wolf)
{
    int fd;
    char *line;
    char **str;

    line = NULL;
    if ((wolf->counter_str_on_map = ft_count_str_on_map(wolf)))
    {
        fd = open(wolf->name, O_RDWR);
        str = (char**)malloc(sizeof(char*) * wolf->counter_str_on_map + 1);
        str[wolf->counter_str_on_map] = NULL;
        wolf->counter_str_on_map = 0;
        while (get_next_line(fd, &line))
        {
            str[wolf->counter_str_on_map++] = ft_strjoin(line, "\n");
            free(line);
        }
    }
    wolf->full_map = str;
    close(fd);
}

void ft_read(t_wolf *wolf)
{
    int fd;

    fd = open(wolf->name, O_DIRECTORY);
    if (fd >= 0)
        ft_error(1, wolf);
    ft_read_map_on_file(wolf);

}

int     main(int argc, char *argv[])
{
   t_wolf *wolf;

   if (argc == 2)
   {
      wolf = (t_wolf*)malloc(sizeof(t_wolf));
       ft_bzero(wolf, sizeof(t_wolf));
       wolf->name = argv[1];
       ft_read(wolf);
       if (ft_valid(wolf))
           ft_error(2, wolf);
         ft_free_mas(wolf->full_map);
         ft_init_all(wolf); 
         ft_game(wolf);
         system("leaks wolf3d");
   }
   return (0);
}