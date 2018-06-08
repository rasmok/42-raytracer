/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 23:03:33 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/08 22:07:51 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	clampwhite(t_color c)
{
	unsigned char min;

	min = c.r;
	min = c.g < min ? c.g : min;
	min = c.b < min ? c.b : min;
	c.r -= min;
	c.g -= min;
	c.b -= min;
	return (c);
}

static void	get_shadow_illum(t_shadow *shadow, t_world *world, t_light light,
		int bounce)
{
	t_hit	*hit;
	t_line	sray;

	if ((hit = trace(shadow->sray, world->cobjlist)))
	{
		if (bounce < MAX_BOUNCE && hit->obj.transp > EPSILON)
		{
			shadow->il.in += (1 - hit->obj.transp) * (1 - shadow->il.in);
			sray = shadow->sray;
			shadow->sray = newray(translate_vec(hit->point, shadow->sray.v,
						EPSILON), shadow->sray.v);
			get_shadow_illum(shadow, world, light, bounce + 1);
			shadow->sray = sray;
			shadow->icol = add_scale_intcolors(shadow->icol,
					get_intcolor(pert_color(hit)), 1 - hit->obj.transp);
		}
		if (bounce == 0)
		{
			shadow->il.in = shadow->il.in > 1 ? 1 : shadow->il.in;
			shadow->il.in = shadow->il.in < 0 ? 0 : shadow->il.in;
			shadow->il.color = clampwhite(scale_convert_color(shadow->icol, 1));
		}
	}
}

void	castshadows(t_world *world, t_hit *hit, t_shadow **shadows)
{
	t_hit	*shit;
	int		i;
	int		shadow;

	i = 0;
	shadow = 0;
	while (i < world->nlights)
	{
		shadows[i] = ft_memalloc(sizeof(t_shadow));
		if (world->lights[i].type != 'd')
			shadows[i]->sray.v = normalize(newvector(hit->point,
						world->lights[i].o));
		else
			shadows[i]->sray.v = normalize(scale(world->lights[i].v, -1));
		shadows[i]->sray.o = translate_vec(hit->point, hit->normal,
				EPSILON * proj(hit->normal, hit->bounce));
		if (((shit = trace(shadows[i]->sray, world->cobjlist)) &&
					((world->lights[i].type != 'd' &&
					  magnitude(newvector(shadows[i]->sray.o, shit->point)) <
					  magnitude(newvector(hit->point, world->lights[i].o))) ||
					 world->lights[i].type == 'd')))
		{
			if (shit->obj.transp < EPSILON)
				shadow = 1;
			else
				get_shadow_illum(shadows[i], world, world->lights[i], 0);
		}
		if ((world->lights[i].type == 's' &&
				acos(dotprod(normalize(scale(shadows[i]->sray.v, -1)),
						world->lights[i].v)) > world->lights[i].angle) || shadow)
		{
			free(shadows[i]);
			shadows[i] = NULL;
		}
		free(shit);
		shadow = 0;
		i++;
	}
}
