/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_map		*add_line(t_map **map, t_map *newline)
{
	t_map *head;

	head = *map;
	if (*map)
	{
		while ((*map)->next)
			*map = (*map)->next;
		(*map)->next = newline;
		*map = head;
	}
	else
		*map = newline;
	return (new_line());
}

t_map		*new_line(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	new->line = NULL;
	new->next = NULL;
	return (new);
}

static int	fprint_map(t_map *map, int display)
{
	t_map	*tmp;

	while (map)
	{
		if (map->line && display)
			ft_printf("%s\n", map->line);
		free(map->line);
		tmp = map;
		map = map->next;
		free(tmp);
	}
	return (display);
}

int			check_parsing(t_parse parse, t_map *map)
{
	if (parse.got_ants && parse.got_edge &&
		parse.end_status == 2 && parse.start_status == 2)
		return (fprint_map(map, 1));
	else
		return (fprint_map(map, 0));
}
