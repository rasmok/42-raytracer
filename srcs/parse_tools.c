/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:50:13 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/29 17:34:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cobject		*ft_new_cobject(void)
{
	t_cobject *cobject;

	if (!(cobject = ft_memalloc(sizeof(t_cobject))))
		return (NULL);
	cobject->objlist = NULL;
	cobject->o = ft_new_vec3(0, 0, 0);
	cobject->r = ft_new_vec3(0, 0, 0);
	cobject->s = ft_new_vec3(1, 1, 1);
	cobject->c = get_color(0xFFFFFF);
	cobject->pert = e_none;
	cobject->transp = 0;
	cobject->refract = 0;
	cobject->reflect = 0;
	cobject->shine = 30;
	cobject->objlist = NULL;
	cobject->negative = 0;
	cobject->regular = 1;
	return (cobject);
}

t_object		*ft_new_object(t_cobject cobject)
{
	t_object *object;

	if (!(object = ft_memalloc(sizeof(t_object))))
		return (NULL);
	object->o = ft_new_vec3(0, 0, 0);
	object->r = ft_new_vec3(0, 0, 0);
	object->s = ft_new_vec3(1, 1, 1);
	object->c = get_color(cobject.c.col);
	object->transp = cobject.transp;
	object->pert = cobject.pert;
	object->refract = cobject.refract;
	object->reflect = cobject.reflect;
	object->shine = cobject.shine;
//	object->cuts = ft_lstdup(NULL);
	object->cuts = NULL;
	object->negative = 0;
	return (object);
}

t_cut		*ft_new_cut(void)
{
	t_cut *cut;

	if (!(cut = ft_memalloc(sizeof(t_cut))))
		return (NULL);
	cut->value = 0;
	cut->cut_xyz = ft_new_vec3(1, 0, 0);
	cut->relative = 1;
	cut->circular = 0;
	cut->inequality = less_than;
	return (cut);
}

void			ft_init_light(t_light *light)
{
	light->o = ft_new_vec3(0, 0, 0);
	light->v = ft_new_vec3(0, 1, 0);
	light->c = get_color(0xFFFFFF);
	light->intensity = 1;
	light->angle = M_PI / 4;
}
