/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENTITY_H
# define ENTITY_H

# include "data.h"

t_ent	*create_ent(t_runtime *rd, int x, int y, t_type type);
int		create_entities(t_runtime *rd, t_map *map);
void	enable_ent(t_ent *ent);
void	disable_ent(t_ent *ent);

#endif