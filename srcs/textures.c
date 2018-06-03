/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 05:33:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/03 07:59:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_get_pixel(int x, int y, t_bmp_parser parser)
{
	int		nb;
	char	color[4];

	nb = (x * (parser.bpp / 8)) + (y * (parser.bpp / 8) * parser.width);
	color[0] = parser.pixels[nb];
	color[1] = parser.pixels[nb + 1];
	color[2] = parser.pixels[nb + 2];
	color[3] = 0;
	return (*(int *)color);
}

int		texture_sphere(t_object obj, t_hit *hit)
{

	t_point3d p = normalize(hit->old_normal);
	float u = 0.5 + ((atan2(p.z, p.x)) / (2 * M_PI));
	float v = 0.5 - (asin(p.y) / M_PI);
	u = (int)(u * obj.parser.width);
	v = (int)(v * obj.parser.height);
	int col = ft_get_pixel(u, v, obj.parser);
	return (col);
}

int		texture_plane(t_object obj, t_hit *hit)
{
	(void) obj;
	t_point3d m_UAxis;
	m_UAxis.x = hit->old_normal.y;
	m_UAxis.y = hit->old_normal.z;
	m_UAxis.z = -hit->old_normal.x;
	t_point3d m_VAxis = crossprod(m_UAxis, hit->old_normal);
	float u = (int)(ft_dot_product(hit->old_point, m_UAxis) * obj.parser.width + 1000) % (obj.parser.width);
	float v = (int)(ft_dot_product(hit->old_point, m_VAxis) * obj.parser.height + 1000) % (obj.parser.height);
	if (u < 0)
		u *= -1;
	if (v < 0)
		v *= -1;
	int col = ft_get_pixel(u, v, obj.parser);
	return (col);
}

int		texture_cylinder(t_object obj, t_hit *hit)
{
	(void) obj;
	(void) hit;

	return (0);
}

int		texture_cone(t_object obj, t_hit *hit)
{
	(void) obj;
	(void) hit;

	return (0);
}

