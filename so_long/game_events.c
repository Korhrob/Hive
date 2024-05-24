/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "game_events.h"
#include "data.h"
#include "entity.h"

// game even when player collect a point (entity)
void	collect_point(t_runtime *rd, t_ent *ent)
{
	disable_ent(ent);
	rd->score++;
	if (rd->score >= rd->map->objects[Point])
		enable_ent(rd->exit_ent);
}
