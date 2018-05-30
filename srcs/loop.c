/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 02:47:18 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/30 02:51:03 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	any_key_pressed(t_world *world)
{
	int i;

	i = -1;
	while (++i < nkeys)
		if (world->keys[i])
			return (1);
	return (0);
}

int		get_input(t_world *e, char *filename)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
			ft_keys_event(e, event, 1, filename);
		if (event.type == SDL_KEYUP)
			ft_keys_event(e, event, 0, filename);
		if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
		if (event.window.event == SDL_WINDOWEVENT_CLOSE ||
				(event.key.keysym.sym == SDLK_ESCAPE
				 && event.type == SDL_KEYDOWN))
		{
			e->cancel_render = 1;
			printf("cancel AND EXIT OR NOTHING\n");
			join_threads(e);
			return (1);
		}
	}
	if (any_key_pressed(e))
	{
		//if (e->cancel_render == 0)
		//{
		e->keys[mouse_move] = 0;
		//join_threads(e);
		if (e->keys[key_enter] == 1)
		{
			e->keys[key_enter] = 0;
			e->cancel_render = 0;
			paint_threaded(e);
			//paint_not_threaded(e);
		}
		else
		{
			ft_process(e);
			e->cancel_render = 1;
			e->progress = 0;
			printf("INPUT PRESSED, CANCELING RENDERING\n");
			paint_threaded_fast(e);
		}
		//}
		//SDL_Delay(12);
	}
	return (0);
}

void	ft_loop(t_world *e, char *filename)
{
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	paint_threaded_fast(e);
	while (!get_input(e, filename))
		;
	end(e);
}
