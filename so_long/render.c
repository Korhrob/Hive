/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "render.h"
#include "entity.h"
#include "const.h"
#include "data.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include "libft/libft.h"

// render unique instance of ent->sprite and set its depth
int	render_ent(t_runtime *rd, t_ent *ent, int depth)
{
	if (ent == NULL)
		return (-1);
	if (ent->sprite == NULL)
		return (-1);
	ent->mlx_id = mlx_image_to_window(rd->mlx, ent->sprite,
			round(ent->x * GRID * rd->scale),
			round(ent->y * GRID * rd->scale));
	depth += (ent == rd->player_ent);
	if (ent->mlx_id != -1)
		mlx_set_instance_depth(&ent->sprite->instances[ent->mlx_id], depth);
	return (ent->mlx_id);
}

// update a specific ent sprite position
void	update_ent_position(t_runtime *rd, t_ent *ent)
{
	if (ent == NULL)
		return ;
	if (ent->sprite == NULL)
		return ;
	if (ent->mlx_id == -1)
		return ;
	ent->sprite->instances[ent->mlx_id].x = round(ent->x * GRID * rd->scale);
	ent->sprite->instances[ent->mlx_id].y = round(ent->y * GRID * rd->scale);
}

// best matching render scale based on maps width and height
double	get_render_scale(t_runtime *rd)
{
	double	x_scale;
	double	y_scale;

	x_scale = (double)rd->width / ((double)rd->map->width * GRID);
	y_scale = (double)rd->height / ((double)rd->map->height * GRID);
	if (y_scale < x_scale)
		return (y_scale);
	return (x_scale);
}
