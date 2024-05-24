/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include "list.h"
# include "data.h"

int		char_to_enum(char c);
t_list	**read_map(t_map *md, char *filename);
int		validate_map(t_map *md);

#endif