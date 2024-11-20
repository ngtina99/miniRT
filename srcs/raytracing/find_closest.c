/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/20 16:32:47 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 16:32:47 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_sphere_intersections(t_intersection_context *ctx)
{
	int			i;
	t_vec3d		hit_point;
	t_obj_info	obj;

	i = 0;
	while (i < ctx->data->sphere_count)
	{
		if (ray_sphere_intersection(ctx->data->spheres[i], ctx->origin,
				ctx->direction, &hit_point))
		{
			ctx->inter->distance = calculate_distance(ctx->origin, hit_point);
			if (ctx->inter->distance < ctx->inter->min_distance)
			{
				ctx->inter->min_distance = ctx->inter->distance;
				obj.color = convert_rgb_to_int(ctx->data->spheres[i].color);
				obj.type = SPHERE;
				ctx->inter->hit = true;
				save_hit_values(ctx->closest_hit, hit_point, obj, i);
			}
		}
		i++;
	}
}

void	update_closest_hit(t_intersection_context *ctx, t_vec3d *hit_point,
		t_cylinder cylinder, int index)
{
	t_obj_info	obj;

	ctx->inter->distance = calculate_distance(ctx->origin, *hit_point);
	if (ctx->inter->distance < ctx->inter->min_distance)
	{
		ctx->inter->min_distance = ctx->inter->distance;
		obj.color = convert_rgb_to_int(cylinder.color);
		obj.type = CYLINDER;
		ctx->inter->hit = true;
		save_hit_values(ctx->closest_hit, *hit_point, obj, index);
	}
}

void	check_plane_intersections(t_intersection_context *ctx)
{
	int			i;
	t_vec3d		hit_point;
	t_obj_info	obj;

	i = 0;
	while (i < ctx->data->plane_count)
	{
		if (ray_plane_intersection(ctx->data->planes[i], ctx->origin,
				ctx->direction, &hit_point))
		{
			ctx->inter->distance = calculate_distance(ctx->origin, hit_point);
			if (ctx->inter->distance < ctx->inter->min_distance)
			{
				ctx->inter->min_distance = ctx->inter->distance;
				obj.color = convert_rgb_to_int(ctx->data->planes[i].color);
				obj.type = PLANE;
				ctx->inter->hit = true;
				save_hit_values(ctx->closest_hit, hit_point, obj, i);
			}
		}
		i++;
	}
}

void	check_cylinder_intersections(t_intersection_context *ctx)
{
	int			i;
	t_vec3d		hit_point;
	t_cylinder	cylinder;

	i = 0;
	while (i < ctx->data->cylinder_count)
	{
		cylinder = ctx->data->cylinders[i];
		if (ray_cylinder_intersection(cylinder, ctx->origin, ctx->direction,
				&hit_point))
			update_closest_hit(ctx, &hit_point, cylinder, i);
		if (ray_cylinder_top(cylinder, ctx->origin, ctx->direction,
				&hit_point))
			update_closest_hit(ctx, &hit_point, cylinder, i);
		if (ray_cylinder_bottom(cylinder, ctx->origin, ctx->direction,
				&hit_point))
			update_closest_hit(ctx, &hit_point, cylinder, i);
		i++;
	}
}

bool	find_closest_object(t_data *data, t_vec3d origin, t_vec3d direction,
		t_object_hit *closest_hit)
{
	t_inter_info			inter;
	t_intersection_context	ctx;

	inter.hit = false;
	inter.min_distance = INFINITY;
	ctx.data = data;
	ctx.origin = origin;
	ctx.direction = direction;
	ctx.inter = &inter;
	ctx.closest_hit = closest_hit;
	check_sphere_intersections(&ctx);
	check_plane_intersections(&ctx);
	check_cylinder_intersections(&ctx);
	return (inter.hit);
}
