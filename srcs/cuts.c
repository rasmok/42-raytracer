/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 20:02:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/05 07:46:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** return 1 if the point should be cut, 0 if not
*/

double		get_sum(t_color color)
{
	return (color.r + color.g + color.b);
}

int			ft_evaluate_cut_color(t_cut cut, t_hit hit)
{
	t_illum illum;
	hit.old_point = hit.point;
	hit.old_normal = hit.normal;
	illum = get_object_color(&hit);
	if (cut.color == 0xff0000)
		return (cut.inequality((illum.color.r / get_sum(illum.color)), cut.value));
	else if (cut.color == 0x00ff00)
		return (cut.inequality((illum.color.g / get_sum(illum.color)), cut.value));
	else
		return (cut.inequality((illum.color.b / get_sum(illum.color)), cut.value));
}

int			ft_evaluate_cut(t_cut cut, t_point3d point, t_hit hit)
{
	if (cut.color)
		return (ft_evaluate_cut_color(cut, hit));
	else if (!cut.circular)
		return (cut.inequality(point.x * cut.cut_xyz.x + point.y * cut.cut_xyz.y + 
				point.z * cut.cut_xyz.z, cut.value));
	else
		return (cut.inequality(point.x *  point.x * cut.cut_xyz.x + 
					point.y * point.y * cut.cut_xyz.y + 
						point.z * point.z * cut.cut_xyz.z, cut.value));
}
