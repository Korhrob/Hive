/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H

# include "data.h"

int		render_ent(t_runtime *rd, t_ent *ent, int depth);
void	update_ent_position(t_runtime *rd, t_ent *ent);
double	get_render_scale(t_runtime *rd);

#endif