#include "wolf3d.h"

void	keys(t_wolf *wolf)
{
	SDL_Event	event;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	double plan;
	double dir;
	double koef;

//	int updown;
//	double old;
//	double old_plane_x;

	koef = 0.05;
	dir = 0.0;
	plan = 0.0;
//	old = old_plane_x = 0.0;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			wolf->for_exit = 2;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			wolf->for_exit = 1;
        if (event.motion.xrel > -1000 && event.motion.xrel < 0)
        {
            dir = wolf->raycast.dir_x;
            wolf->raycast.dir_x = wolf->raycast.dir_x * cos(fabs(event.motion.xrel/700.0)) - wolf->raycast.dir_y * sin(fabs(event.motion.xrel/700.0));
            wolf->raycast.dir_y = dir * sin(fabs(event.motion.xrel/700.0)) + wolf->raycast.dir_y * cos(fabs(event.motion.xrel/700.0));
            plan = wolf->raycast.plan_x;
            wolf->raycast.plan_x = wolf->raycast.plan_x * cos(fabs(event.motion.xrel/700.0)) - wolf->raycast.plan_y * sin(fabs(event.motion.xrel/700.0));
            wolf->raycast.plan_y = plan * sin(fabs(event.motion.xrel/700.0)) + wolf->raycast.plan_y * cos(fabs(event.motion.xrel/700.0));
        }
        if (event.motion.xrel > 0 && event.motion.xrel < 1000)
        {
            dir = wolf->raycast.dir_x;
            wolf->raycast.dir_x = wolf->raycast.dir_x * cos(-(fabs(event.motion.xrel/700.0))) - wolf->raycast.dir_y * sin(-(fabs(event.motion.xrel/700.0)));
            wolf->raycast.dir_y = dir * sin(-(fabs(event.motion.xrel/700.0))) + wolf->raycast.dir_y * cos(-(fabs(event.motion.xrel/700.0)));
            plan = wolf->raycast.plan_x;
            wolf->raycast.plan_x = wolf->raycast.plan_x * cos(-(fabs(event.motion.xrel/700.0))) - wolf->raycast.plan_y * sin(-(fabs(event.motion.xrel/700.0)));
            wolf->raycast.plan_y = plan * sin(-(fabs(event.motion.xrel/700.0))) + wolf->raycast.plan_y * cos(-(fabs(event.motion.xrel/700.0)));
        }
//        void		mouse_move(t_wolf *holder, t_camera *camera, float old)
//        {
//            float old_plane_x;

//            holder->keys.xrel = holder->event.motion.xrel;
//            holder->keys.yrel = holder->event.motion.yrel;
//        if (event.motion.xrel > -1000 && event.motion.xrel < 1000)
//        {
//            wolf->raycast.updown -= event.motion.yrel;
//			wolf->raycast.updown = (wolf->raycast.updown < -350) ? -350 : wolf->raycast.updown;
//			wolf->raycast.updown = (wolf->raycast.updown > 650) ? 650 : wolf->raycast.updown;
//            old = wolf->raycast.dir_x;
//        wolf->raycast.dir_x = wolf->raycast.dir_x * cos(event.motion.xrel / 100.0 * -0.3) \
//		- wolf->raycast.dir_y * sin(event.motion.xrel / 100.0 * -0.3);
//        wolf->raycast.dir_y = old * sin(event.motion.xrel / 100.0 * -0.3) \
//		+ wolf->raycast.dir_y * cos(event.motion.xrel / 100.0 * -0.3);
//            old_plane_x = wolf->raycast.plan_x;
//        wolf->raycast.plan_x = wolf->raycast.plan_x * cos(event.motion.xrel / 100.0 * -0.3) \
//		- wolf->raycast.plan_y * sin(event.motion.xrel / 100.0 * -0.3);
//        wolf->raycast.plan_y = old_plane_x * sin(event.motion.xrel / 100.0 * -0.3) \
//		+ wolf->raycast.plan_y * cos(event.motion.xrel / 100.0 * -0.3);
//        }


//        if (event.button.type == SDL_MOUSEBUTTONDOWN)
//            if (event.button.button == SDL_BUTTON_LEFT)
//            {};
	}
	if (keys[SDL_SCANCODE_LSHIFT] == 1)
		wolf->speed = 0.2;
	else
    {
        if (keys[SDL_SCANCODE_LALT] == 1)
            wolf->speed = 0.04;
        else
            wolf->speed = 0.1;
    }
	if (keys[SDL_SCANCODE_RIGHT])
	{
		dir = wolf->raycast.dir_x;
		wolf->raycast.dir_x = wolf->raycast.dir_x * cos(-koef) - wolf->raycast.dir_y * sin(-koef);
		wolf->raycast.dir_y = dir * sin(-koef) + wolf->raycast.dir_y * cos(-koef);
		plan = wolf->raycast.plan_x;
		wolf->raycast.plan_x = wolf->raycast.plan_x * cos(-koef) - wolf->raycast.plan_y * sin(-koef);
		wolf->raycast.plan_y = plan * sin(-koef) + wolf->raycast.plan_y * cos(-koef);
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		dir = wolf->raycast.dir_x;
		wolf->raycast.dir_x = wolf->raycast.dir_x * cos(koef) - wolf->raycast.dir_y * sin(koef);
		wolf->raycast.dir_y = dir * sin(koef) + wolf->raycast.dir_y * cos(koef);
		plan = wolf->raycast.plan_x;
		wolf->raycast.plan_x = wolf->raycast.plan_x * cos(koef) - wolf->raycast.plan_y * sin(koef);
		wolf->raycast.plan_y = plan * sin(koef) + wolf->raycast.plan_y * cos(koef);
	}
	if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
	{
		if (wolf->array[(int)(wolf->raycast.posY)][(int)(wolf->raycast.posX
			+ wolf->raycast.dir_x * wolf->speed)] == 0)
			wolf->raycast.posX += wolf->raycast.dir_x * wolf->speed;
		if (wolf->array[(int)(wolf->raycast.posY + wolf->raycast.dir_y
			* wolf->speed)][(int)(wolf->raycast.posX)] == 0)
			wolf->raycast.posY += wolf->raycast.dir_y * wolf->speed;
	}
	if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
	{
		if (wolf->array[(int)(wolf->raycast.posY)][(int)(wolf->raycast.posX
			- wolf->raycast.dir_x * wolf->speed)] == 0)
			wolf->raycast.posX -= wolf->raycast.dir_x * wolf->speed;
		if (wolf->array[(int)(wolf->raycast.posY - wolf->raycast.dir_y
			* wolf->speed)][(int)(wolf->raycast.posX)] == 0)
			wolf->raycast.posY -= wolf->raycast.dir_y * wolf->speed;
	}
    if (keys[SDL_SCANCODE_D])
    {
        if (wolf->array[(int)(wolf->raycast.posY + wolf->raycast.plan_y * wolf->speed)]
        [(int)(wolf->raycast.posX)] == 0)
            wolf->raycast.posY += wolf->raycast.plan_y * wolf->speed;
        if (wolf->array[(int)(wolf->raycast.posY)]
            [(int)(wolf->raycast.posX + wolf->raycast.plan_x * wolf->speed)] == 0)
            wolf->raycast.posX += wolf->raycast.plan_x * wolf->speed;
    }
    if (keys[SDL_SCANCODE_A])
    {
        if (wolf->array[(int)(wolf->raycast.posY - wolf->raycast.plan_y * wolf->speed)]
            [(int)(wolf->raycast.posX)] == 0)
            wolf->raycast.posY -= wolf->raycast.plan_y * wolf->speed;
//        write(1, "test\n", 5);
        if (wolf->array[(int)(wolf->raycast.posY)]
            [(int)(wolf->raycast.posX - wolf->raycast.plan_x * wolf->speed)] == 0)
            wolf->raycast.posX -= wolf->raycast.plan_x * wolf->speed;
    }

	if (keys[SDL_SCANCODE_T])
		wolf->raycast.temp *= 1.1;
    if (keys[SDL_SCANCODE_Y])
        wolf->raycast.temp /= 1.1;
//    if (keys[SDL_SCANCODE_U])
//        SDL_SetRelativeMouseMode(0);
//    if (keys[SDL_SCANCODE_I])
//        SDL_SetRelativeMouseMode(1);
//	if (keys[SDL_SCANCODE_KP_1])
//		Mix_PlayMusic(wolf->sdl.mus[0], 1);
//	if (keys[SDL_SCANCODE_KP_2])
//		Mix_PlayMusic(wolf->sdl.mus[1], 1);
//	if (keys[SDL_SCANCODE_KP_3])
//		Mix_PlayMusic(wolf->sdl.mus[2], 1);
}

void	render(t_wolf *wolf)
{
	int n;
    unsigned int color;
//	int r;
//	int g;
//	int b;

	wolf->raycast.cameraX = (double)((wolf->x * 2) / (double)(WIDTH) - 1);
	wolf->raycast.ray_dir_x = wolf->raycast.dir_x + wolf->raycast.plan_x * wolf->raycast.cameraX;
	wolf->raycast.ray_dir_y = wolf->raycast.dir_y + wolf->raycast.plan_y * wolf->raycast.cameraX;
	if ((int)wolf->raycast.posX > wolf->width_arr)
        wolf->raycast.posX = wolf->width_arr;
	if ((int)wolf->raycast.posY > wolf->height_arr)
        wolf->raycast.posY = wolf->height_arr;
	wolf->raycast.map_x = (int)wolf->raycast.posX;
	wolf->raycast.map_y = (int)wolf->raycast.posY;
//	printf("%d\n", wolf->raycast.map_x);
	wolf->raycast.delta_dist_x = fabs(1 / wolf->raycast.ray_dir_x);
	wolf->raycast.delta_dist_y = fabs(1 / wolf->raycast.ray_dir_y);
	wolf->raycast.hit = 0;
//	printf("%f\n", wolf->raycast.plan_x);
//	printf("%f\n", wolf->raycast.delta_dist_x);
//	printf("%f\n", wolf->raycast.dir_x);

//    write(1, "4\n", 2);

	if (wolf->raycast.ray_dir_x < 0)
	{
		wolf->raycast.step_x = -1;
		wolf->raycast.side_dist_x = (wolf->raycast.posX - wolf->raycast.map_x) * wolf->raycast.delta_dist_x;
	}
	else
	{
		wolf->raycast.step_x = 1;
		wolf->raycast.side_dist_x = (wolf->raycast.map_x + 1.0 - wolf->raycast.posX) * wolf->raycast.delta_dist_x;
	}
	if (wolf->raycast.ray_dir_y < 0)
	{
		wolf->raycast.step_y = -1;
		wolf->raycast.side_dist_y = (wolf->raycast.posY - wolf->raycast.map_y) * wolf->raycast.delta_dist_y;
	}
	else
	{
		wolf->raycast.step_y = 1;
		wolf->raycast.side_dist_y = (wolf->raycast.map_y + 1.0 - wolf->raycast.posY) * wolf->raycast.delta_dist_y;
	}
//	printf("%f\n", wolf->raycast.side_dist_x);
	while (wolf->raycast.hit == 0)
	{
		if (wolf->raycast.side_dist_x < wolf->raycast.side_dist_y)
		{
			wolf->raycast.side_dist_x += wolf->raycast.delta_dist_x;
			wolf->raycast.map_x += wolf->raycast.step_x;
			wolf->raycast.side = 0;
		}
		else
		{
			wolf->raycast.side_dist_y += wolf->raycast.delta_dist_y;
			wolf->raycast.map_y += wolf->raycast.step_y;
			wolf->raycast.side = 1;
		}
		if (wolf->array[wolf->raycast.map_y][wolf->raycast.map_x] > 0)
			wolf->raycast.hit = 1;
	}
	if (wolf->raycast.side == 0)
		wolf->draw.perp_wall_dist = (wolf->raycast.map_x - wolf->raycast.posX + (1 - wolf->raycast.step_x) / 2) / wolf->raycast.ray_dir_x;
	else
		wolf->draw.perp_wall_dist = (wolf->raycast.map_y - wolf->raycast.posY + (1 - wolf->raycast.step_y) / 2) / wolf->raycast.ray_dir_y;
	if (wolf->draw.perp_wall_dist < 0.05)
        wolf->draw.perp_wall_dist = 0.05;
	wolf->draw.line_height = (int)(HEIGHT / wolf->draw.perp_wall_dist);
//	if (wolf->draw.line_height >= 1000)
//        wolf->draw.line_height = 1000;
//	if (wolf->draw.line_height < 0)
//		wolf->draw.line_height = 0;
//	printf("%d\n", wolf->draw.line_height);
	wolf->draw.draw_start = (-wolf->draw.line_height / 2 + HEIGHT / 2);
//    wolf->draw.draw_start += 10;
//	printf("%d\n", wolf->draw.draw_start);
	if (wolf->draw.draw_start < 0)
		wolf->draw.draw_start = 0;
	wolf->draw.draw_end = (wolf->draw.line_height / 2 + HEIGHT / 2);
//    wolf->draw.draw_end += 10;
	if (wolf->draw.draw_end >= HEIGHT)
		wolf->draw.draw_end = HEIGHT - 1;
	n = wolf->array[wolf->raycast.map_y][wolf->raycast.map_x] - 1;
    if (wolf->raycast.side == 0)
    {
        if (wolf->raycast.ray_dir_x > 0)
            n = 0;
        else
            n = 1;
    }
    else
    {
        if (wolf->raycast.ray_dir_y > 0)
            n = 2;
        else
            n = 3;
    }
//	printf("%d\n", n);
//    printf("%f\n", wolf->raycast.side_dist_x);
	if (wolf->raycast.side == 0)
		wolf->draw.wall_x = wolf->raycast.posY + wolf->draw.perp_wall_dist * wolf->raycast.ray_dir_y;
	else
		wolf->draw.wall_x = wolf->raycast.posX + wolf->draw.perp_wall_dist * wolf->raycast.ray_dir_x;
	wolf->draw.wall_x -= floor(wolf->draw.wall_x);
	wolf->draw.tex_x = (int)(wolf->draw.wall_x * 256.0);
//	printf("%f\n",wolf->draw.wall_x );
	if (wolf->raycast.side == 0 && wolf->raycast.ray_dir_x > 0)
		wolf->draw.tex_x = 256.0 - wolf->draw.tex_x - 1;
	if (wolf->raycast.side == 1 & wolf->raycast.ray_dir_y < 0)
		wolf->draw.tex_x = 256.0 - wolf->draw.tex_x - 1;
	wolf->y = wolf->draw.draw_start;
	while (++wolf->y < wolf->draw.draw_end)
	{
		wolf->d = wolf->y * 256 - HEIGHT * 128 + wolf->draw.line_height * 128;
		wolf->draw.tex_y = ((wolf->d * 256.0) / wolf->draw.line_height / 256);
		if ((color = get_pixel_int(wolf->sdl.wall[n], wolf->draw.tex_x, wolf->draw.tex_y)) != 0)
		{
//		    r = ((color >> 16) & 255) / 2;
//		    g = ((color >> 8) & 255) / 2;
//		    b = ((color & 255) / 2);
//		    color = (256 * 256 * r) + (256 * g) + b;
//            if (wolf->draw.line_height / 10 < 50)
//            {
//				if (wolf->draw.line_height > 100) {
//					r = ((color >> 16) & 255) / fabs((wolf->draw.line_height / 10) / 10.0);
//					g = ((color >> 8) & 255) / fabs((wolf->draw.line_height / 10) / 10.0);
//					b = ((color & 255) / fabs((wolf->draw.line_height / 10) / 10.0));
//					color = (256 * 256 * r) + (256 * g) + b;
//				}
////                printf("%f\n", fabs((wolf->draw.line_height / 10) / 10.0));
//            }

//            else if (wolf->draw.line_height < 100)
//            {
//                r = ((color >> 16) & 255) / 1.7;
//                g = ((color >> 8) & 255) / 1.7;
//                b = ((color & 255) / 1.7);
//                color = (256 * 256 * r) + (256 * g) + b;
//            }
//            else if (wolf->draw.line_height < 150)
//            {
//                r = ((color >> 16) & 255) / 1.5;
//                g = ((color >> 8) & 255) / 1.5;
//                b = ((color & 255) / 1.5);
//                color = (256 * 256 * r) + (256 * g) + b;
//            }
//            else if (wolf->draw.line_height < 250)
//            {
//                r = ((color >> 16) & 255) / 1.2;
//                g = ((color >> 8) & 255) / 1.2;
//                b = ((color & 255) / 1.2);
//                color = (256 * 256 * r) + (256 * g) + b;
//            }
//            else
//                {
//                    r = ((color >> 16) & 255) * 1.2;
//                    g = ((color >> 8) & 255) * 1.2;
//                    b = ((color & 255) * 1.2);
//                    color = (256 * 256 * r) + (256 * g) + b;
//                }
            wolf->buf[wolf->y][wolf->x] = color;
        }
	}
//    printf("%d\n", abs(wolf->draw.line_height / 100 - 200));
	if (wolf->raycast.side == 0 && wolf->raycast.ray_dir_x > 0)
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x;
		wolf->draw.floor_wall_y = wolf->raycast.map_y + wolf->draw.wall_x;
	}
	else if (wolf->raycast.side == 0 && wolf->raycast.ray_dir_x < 0)
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x + 1.0;
		wolf->draw.floor_wall_y = wolf->raycast.map_y + wolf->draw.wall_x;
	}
	else if (wolf->raycast.side == 1 && wolf->raycast.ray_dir_y > 0)
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x + wolf->draw.wall_x;
		wolf->draw.floor_wall_y = wolf->raycast.map_y;
	}
	else
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x + wolf->draw.wall_x;
		wolf->draw.floor_wall_y = wolf->raycast.map_y + 1.0;
	}
	wolf->raycast.dist_player = 0.0;
//	printf("start %d\n", wolf->draw.draw_start);
//	printf("end %d\n", wolf->draw.draw_end);
//	wolf->draw.draw_end -= 50;
	if (wolf->draw.draw_end < 0)
		wolf->draw.draw_end = HEIGHT;
	wolf->y = wolf->draw.draw_end - 1;
//    write(1, "5\n", 2);
	while (++wolf->y < HEIGHT)
	{
		wolf->draw.current_dist = HEIGHT / (2.0 * wolf->y - HEIGHT);
		wolf->draw.weight = (wolf->draw.current_dist - wolf->raycast.dist_player) / (wolf->draw.perp_wall_dist - wolf->raycast.dist_player);
		wolf->draw.current_floor_x = wolf->draw.weight * wolf->draw.floor_wall_x + (1.0 - wolf->draw.weight) * wolf->raycast.posX;
		wolf->draw.current_floor_y = wolf->draw.weight * wolf->draw.floor_wall_y + (1.0 - wolf->draw.weight) * wolf->raycast.posY;
		wolf->draw.floor_tex_x = (int)(wolf->draw.current_floor_x * 256) % 256;
		wolf->draw.floor_tex_y = (int)(wolf->draw.current_floor_y * 256) % 256;
		color = get_pixel_int(wolf->sdl.floor, wolf->draw.floor_tex_x, wolf->draw.floor_tex_y);
//		printf("%d\n", wolf->sdl.floor->w);


//		r = ((color >> 16) & 255) / 2;
//		g = ((color >> 8) & 255) / 2;
//		b = ((color & 255) / 2);
//		color = (256 * 256 * r) + (256 * g) + b;
//	printf("%d\n", wolf->y);
//		if (wolf->draw.line_height < 100) {
//			r = ((color >> 16) & 255) / fabs((wolf->draw.line_height / 10) / 10.0);
//			g = ((color >> 8) & 255) / fabs((wolf->draw.line_height / 10) / 10.0);
//			b = ((color & 255) / fabs((wolf->draw.line_height / 10) / 10.0));
//			color = (256 * 256 * r) + (256 * g) + b;
//		}
		wolf->buf[wolf->y][wolf->x] = color;

//        write(1, "1\n", 2);
//    if (wolf->draw.floor_tex_x >= WIDTH - 100 || wolf->draw.floor_tex_y > HEIGHT)
//    {
//        write(1, "1\n",2);
//    }
		color = get_pixel_int(wolf->sdl.up_1, wolf->draw.floor_tex_x, wolf->draw.floor_tex_y);
//		printf("%d\n", color);

//		if (wolf->draw.line_height > 100) {
//			r = ((color >> 16) & 255) / fabs((wolf->draw.line_height / 10) / 10.0);
//			g = ((color >> 8) & 255) / fabs((wolf->draw.line_height / 10) / 10.0);
//			b = ((color & 255) / fabs((wolf->draw.line_height / 10) / 10.0));
//			color = (256 * 256 * r) + (256 * g) + b;
//		}
//        if (wolf->draw.line_height < 50)
//        {
//            r = ((color >> 16) & 255) / 2;
//            g = ((color >> 8) & 255) / 2;
//            b = ((color & 255) / 2);
//            color = (256 * 256 * r) + (256 * g) + b;
//        }
//        else if (wolf->draw.line_height < 100)
//        {
//            r = ((color >> 16) & 255) / 1.7;
//            g = ((color >> 8) & 255) / 1.7;
//            b = ((color & 255) / 1.7);
//            color = (256 * 256 * r) + (256 * g) + b;
//        }
//        else if (wolf->draw.line_height < 150)
//        {
//            r = ((color >> 16) & 255) / 1.5;
//            g = ((color >> 8) & 255) / 1.5;
//            b = ((color & 255) / 1.5);
//            color = (256 * 256 * r) + (256 * g) + b;
//        }
//        else if (wolf->draw.line_height < 250)
//        {
//            r = ((color >> 16) & 255) / 1.2;
//            g = ((color >> 8) & 255) / 1.2;
//            b = ((color & 255) / 1.2);
//            color = (256 * 256 * r) + (256 * g) + b;
//        }
//        if (color > 16777215)
//        {
//            write(1, "2\n", 2);
//        }
		wolf->buf[WIDTH / 4 * 3 - wolf->y][wolf->x] = color;
	}
//	printf("%d\n", wolf->draw.floor_tex_y * wolf->sdl.up->w + wolf->draw.floor_tex_x);
//	printf("%d\n", wolf->draw.floor_tex_y);
//	printf("%d\n", wolf->draw.floor_tex_x);
//	printf("%d\n", WIDTH / 4 * 3 - wolf->y);
//if (wolf->x > WIDTH) {
//    printf("%d\n", wolf->y);
//    printf("%d\n", wolf->x);
//
//}
//    printf("%d\n", wolf->draw.floor_tex_y);
}


//void	raycasting(t_wolf *wolf)
//{
//	wolf->x = -1;
//	while (++wolf->x < WIDTH)
//		render(wolf);
//}

void	ft_game(t_wolf *wolf) {
//	wolf->raycast.agle = 60.0 / 320.0;
//	printf("%f\n", wolf->raycast.agle);
//    wolf->raycast.agle = 60.0 / WIDTH;
//    wolf->raycast.lenToCenter =  (WIDTH / 2) / tan(30 * 3.14 / 180);
//    wolf->raycast.cenetrX = WIDTH / 2;
//    wolf->raycast.centerY = HEIGHT / 2;
//    wolf->raycast.agle = 60.0 / WIDTH;
//    wolf->sizePrjPln = WIDTH * HEIGHT;
//    wolf->fov = 60.0;
//    wolf->pov = 45.0;
    int i = 0, m;

//while (i < (y * surface->w) + x)
//    i++;
//printf("%d\n", i);
//    printf("%d\n", wolf->raycast.lenToCenter);
//    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(1);
    SDL_SetRelativeMouseMode(0);
    SDL_SetRelativeMouseMode(1);
    SDL_WarpMouseInWindow(wolf->sdl.win, WIDTH / 2, HEIGHT / 2);
//    Mix_PlayMusic(wolf->sdl.mus[0], -1);
//    wolf->raycast.temp = 0.5;
//    int t1 = wolf->width_arr * 12, t2 = wolf->height_arr * 12;
    TTF_Init();
    if (wolf->for_exit == 0) // wolf->for_exit = флажок виходу
        while (wolf->for_exit == 0) {
            static int my_time;
            static int fps;
            static int my_fps;
            char *s;

            if (time(NULL) != my_time) {
                my_fps = fps;
                fps = 0;
                my_time = (int) time(NULL);
            } else
                fps++;
            s = ft_itoa(my_fps);
//
////            SDL_SetRelativeMouseMode(0);
////            SDL_SetRelativeMouseMode(1);
            wolf->sdl.font_ttf = TTF_OpenFont("Roboto-Bold.ttf", 20);
            int tw, th, ww, wh;
            SDL_GetWindowSize(wolf->sdl.win, &ww, &wh);
            SDL_Color color = {255, 255, 34, 255};
            char *test = ft_strjoin("FPS ", s);
            if ((wolf->sdl.font_surface = TTF_RenderText_Solid(wolf->sdl.font_ttf, test, color))) {
                if ((wolf->sdl.font_text = SDL_CreateTextureFromSurface(wolf->sdl.ren, wolf->sdl.font_surface))) {
                    if ((SDL_QueryTexture(wolf->sdl.font_text, NULL, NULL, &tw, &th))) {
                        wolf->sdl.font_rect.x = WIDTH - 100;
                        wolf->sdl.font_rect.y = HEIGHT - 40;
                        wolf->sdl.font_rect.w = tw;
                        wolf->sdl.font_rect.h = th;
                        SDL_UpdateTexture(wolf->sdl.screen, NULL, wolf->buf, WIDTH << 2);
                        SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.screen, NULL, NULL);
                        SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.font_text, NULL, &wolf->sdl.font_rect);
                        SDL_RenderPresent(wolf->sdl.ren);
                    }
                    else
                        printf("%s\n", SDL_GetError());
                }
                else
                    printf("%s\n", SDL_GetError());
            }
            else
                printf("%s\n", SDL_GetError());

            SDL_DestroyTexture(wolf->sdl.font_text);
            SDL_FreeSurface(wolf->sdl.font_surface);
            TTF_CloseFont(wolf->sdl.font_ttf);
            free(test);
            wolf->x = -1;
            while (++wolf->x < WIDTH)
                render(wolf);
            keys(wolf);
            free(s);
            int t1 = wolf->width_arr, t2 = wolf->height_arr;
            if (t1 < ww / 4 && t2 < wh / 4) {
                int i = -1, m, q, w;

                while (i++ < wolf->height_arr * 6) {
                    m = -1;
                    while (m++ < wolf->width_arr * 6) {
                        wolf->buf[i][m] = (256 * 256 * 0) + (256 * 0) + 0;
                        q = i;
                        w = m;
                        while (q < i + 6) {
                            w = m;
                            while (w < m + 6) {
                                wolf->buf[(int) wolf->raycast.posY * 6 + abs(i - q)][(int) wolf->raycast.posX * 6 +
                                                                                     abs(m - w)] =
                                        (256 * 256 * 255) + (256 * 0) + 0;
                                w++;
                            }
                            q++;
                        }
                        q = i;
                        w = m;
                        if ((int) ((q / 6) - 1) >= 0)
                            if ((int) ((w / 6) - 1) >= 0)
                                if (wolf->array[(int) ((q / 6) - 1)][(int) ((w / 6) - 1)] != 0) {
                                    while (q < i + 6) {
                                        w = m;
                                        while (w < m + 6) {
                                            wolf->buf[(int) ((i / 6) - 1) * 6 + abs(i - q)][(int) ((m / 6) - 1) * 6 +
                                                                                            abs(m - w)] =
                                                    (256 * 256 * 200) + (256 * 200) + 50;
                                            w++;
                                        }
                                        q++;
                                    }
                                }
                    }
                }
            }

            TTF_Quit();
        }
}