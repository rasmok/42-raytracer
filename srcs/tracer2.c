/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:48:49 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/27 22:24:42 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_inside_other(t_hit h, t_cobjlist *cobjlist, int neg,
		t_color *c)
{
	t_cobjlist	*cobjiter;
	t_objlist	*objiter;
	t_object	obj;
	int			negated;

	negated = 0;
	cobjiter = cobjlist;
	while (cobjiter && !negated)
	{
		objiter = cobjiter->cobject->objlist;
		while (objiter && !negated)
		{
			obj = *(objiter->object);
			if (obj.negative == neg && obj.inside_func(h, obj))
				negated = 1;
			*c = obj.c;
			objiter = objiter->next;
		}
		cobjiter = cobjiter->next;
	}
	return (negated);
}

void	intersect_positive(t_cobjlist *cobjlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit		newhit;
	t_color		othercol;
	t_sols		sols;
	t_line		transformed;

	transformed = ft_transform_line(obj, line);
	if ((sols.nbsols = obj.intersect_func(transformed,
					obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val(newhit, sols, hit->t,
			transformed)) > 0) && (newhit.t < hit->t || hit->t == -1) &&
			!is_inside_other(newhit, cobjlist, 1, &othercol))
		{
			newhit.col = obj.c;
			newhit.point = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, newhit.t));
			newhit.normal = obj.normal_func(obj, newhit.point, transformed);
			ft_transform_hit_back(&newhit);
			*hit = newhit;
			if (ft_dot_product(hit->normal, line.v) > 0)
			{
				hit->enter = 0;
				hit->normal = scale(hit->normal, -1);
			}
			else
				hit->enter = 1;
		}
	}
}

void	intersect_negative(t_cobjlist *cobjlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit		newhit;
	t_color		othercol;
	t_sols		sols;
	t_line		transformed;

	transformed = ft_transform_line(obj, line);
	if ((sols.nbsols = obj.intersect_func(transformed,
					obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val(newhit, sols, hit->t,
			transformed)) > 0) && (newhit.t < hit->t || hit->t == -1) &&
			is_inside_other(newhit, cobjlist, 0, &othercol))
		{
			newhit.col = othercol;
			newhit.point = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, newhit.t));
			newhit.normal = obj.normal_func(obj, newhit.point, transformed);
			ft_transform_hit_back(&newhit);
			*hit = newhit;
			if (ft_dot_product(hit->normal, line.v) > 0)
			{
				hit->enter = 0;
				hit->normal = scale(hit->normal, -1);
			}
			else
				hit->enter = 1;
		}
	}
}
