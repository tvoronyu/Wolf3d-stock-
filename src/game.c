/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvoronyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:25:50 by tvoronyu          #+#    #+#             */
/*   Updated: 2019/01/24 19:27:44 by tvoronyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_check_side_and_step_help(t_wolf *wolf)
{
	if (wolf->raycast.ray_dir_y < 0)
	{
		wolf->raycast.step_y = -1;
		wolf->raycast.side_dist_y = (wolf->raycast.pos_y
				- wolf->raycast.map_y) * wolf->raycast.delta_dist_y;
	}
	else
	{
		wolf->raycast.step_y = 1;
		wolf->raycast.side_dist_y = (wolf->raycast.map_y
				+ 1.0 - wolf->raycast.pos_y) * wolf->raycast.delta_dist_y;
	}
}

void	ft_raycast(t_wolf *wolf)
{
	wolf->x = -1;
	if (wolf->pause)
	{
		SDL_SetRelativeMouseMode(0);
		SDL_SetRelativeMouseMode(1);
		while (++wolf->x < WIDTH)
			render(wolf);
		if (wolf->t1 < wolf->ww / 4 && wolf->t2 < wolf->wh / 4)
		{
			wolf->i = -1;
			ft_draw_wall(wolf);
		}
	}
}

void	ft_game(t_wolf *wolf)
{
	SDL_SetRelativeMouseMode(1);
	SDL_WarpMouseInWindow(wolf->sdl.win, WIDTH / 2, HEIGHT / 2);
	Mix_PlayMusic(wolf->sdl.mus[0], -1);
	while (wolf->loop)
	{
		ft_fps(wolf);
		ft_init_ttf(wolf);
		render_texture(wolf);
		ft_raycast(wolf);
		keys(wolf);
	}
	SDL_DestroyTexture(wolf->sdl.screen);
	TTF_Quit();
}
