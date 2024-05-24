/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DATA_H
# define DATA_H

# include "list.h"
# include "MLX42/include/MLX42/MLX42.h"

// Entity Type
typedef enum e_type
{
	Floor,
	Wall,
	Player,
	Point,
	Exit,
	Error
}	t_type;

/* Entity
*	x position
*	y position
*	mlx render id
*	mlx image
*	ent type
*	ent is rendered and can be interacted with
*/
typedef struct s_ent
{
	int			x;
	int			y;
	int			mlx_id;
	mlx_image_t	*sprite;
	t_type		type;
	int			enabled;
}	t_ent;

/* Map Node
*	x position
*	y position
*	tile type (ent)
*/
typedef struct s_map_node
{
	int		x;
	int		y;
	t_type	type;
}	t_map_node;

/* Map Data
*	map width
*	map height
*	array of ent types
*	2d array of map nodes
*/
typedef struct s_map
{
	int			width;
	int			height;
	int			objects[6];
	t_map_node	**nodes;
}	t_map;

/*	Runtime Data
*	mlx instance
*	window width
*	window height
*	map data instance
*	list of all entities
*	reference to player ent
*	reference to exit ent
*	array mlx images for each ent type
*	collected points
*	moves squares
*	is any key held down
*	flag if resource loading succeeds
*/
typedef struct s_runtime
{
	mlx_t		*mlx;
	int			width;
	int			height;
	double		scale;
	t_map		*map;
	t_list		**ent_list;
	t_ent		*player_ent;
	t_ent		*exit_ent;
	mlx_image_t	*sprites[6];
	int			score;
	int			moves;
	int			key_down;
	int			resources_ok;
}	t_runtime;

void	error_msg(int error_code);

#endif