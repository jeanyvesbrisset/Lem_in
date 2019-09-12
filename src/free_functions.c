/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/06/30 17:25:18 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	free_rooms(t_room *room)
{
	t_room	*tmp;

	while (room)
	{
		tmp = room;
		free(room->name);
		room->name = NULL;
		room = room->next;
		free(tmp);
		tmp = NULL;
	}
	room = NULL;
}

void	free_t_bfs(t_bfs *elem)
{
	t_bfs	*tmp;

	while (elem)
	{
		tmp = elem;
		elem = elem->next;
		free(tmp);
	}
	elem = NULL;
}

void	free_edges(t_edge *edge)
{
	t_edge	*tmp;

	while (edge)
	{
		tmp = edge;
		edge = edge->next;
		free(tmp);
	}
	edge = NULL;
}

void	free_char_tab(char **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(tab[i++]);
	free(tab);
}

void	free_paths(t_path *path)
{
	t_path	*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
	path = NULL;
}
