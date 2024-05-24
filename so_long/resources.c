/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "const.h"
#include "data.h"
#include "resources.h"
#include "MLX42/include/MLX42/MLX42.h"
#include "math.h"

// validates that sprite for each entity type was loaded
// return 1 on success
// return 0 on fail and print error msg
int	validate_resources(t_runtime *rd)
{
	int	i;

	i = 0;
	while (i <= (int)Exit)
	{
		if (rd->sprites[i] == NULL)
		{
			error_msg(-8);
			return (0);
		}
		i++;
	}
	return (1);
}

// loads sprite for each entity type
// if resource doesnt exist sets it to NULL
void	load_resources(t_runtime *rd)
{
	int				i;
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	i = (int)Floor;
	while (i <= (int)Exit)
	{
		img = NULL;
		tex = load_texture((t_type)i);
		if (tex != NULL)
		{
			img = mlx_texture_to_image(rd->mlx, tex);
			mlx_delete_texture(tex);
		}
		if (img != NULL)
		{
			mlx_resize_image(img,
				round(GRID * rd->scale),
				round(GRID * rd->scale));
			rd->sprites[i] = img;
		}
		else
			rd->sprites[i] = NULL;
		i++;
	}
}

// loads specific png and returns it as mlx_texture_t
mlx_texture_t	*load_texture(t_type type)
{
	mlx_texture_t	*tex;
	char			*path;

	tex = NULL;
	path = NULL;
	if (type == Floor)
		path = "textures/floor.png";
	else if (type == Wall)
		path = "textures/wall.png";
	else if (type == Player)
		path = "textures/player.png";
	else if (type == Point)
		path = "textures/point.png";
	else if (type == Exit)
		path = "textures/exit.png";
	if (path != NULL)
		tex = mlx_load_png(path);
	return (tex);
}

// frees all sprites assigned for entity types
void	free_resources(t_runtime *rd)
{
	int	i;

	i = (int)Floor;
	while (i <= (int)Exit)
	{
		mlx_delete_image(rd->mlx, rd->sprites[i]);
		i++;
	}
}
