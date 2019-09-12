/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/05/11 15:28:33 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		get_lowest_level(t_data *data, int to, int prev_level)
{
	int		level;
	int		i;

	level = 0;
	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->to == to && data->edg[i]->level &&
			((data->edg[i]->level != prev_level && prev_level) || !prev_level))
		{
			if ((!level || (data->edg[i]->level < level && level)))
				level = data->edg[i]->level;
		}
		i++;
	}
	return (level);
}

static t_bfs	*new_parent(t_edge *edge, int i)
{
	t_bfs	*node;

	node = malloc(sizeof(t_bfs));
	if (node)
	{
		node->id = i;
		node->from = edge->from;
		node->to = edge->to;
		node->level = edge->level;
		node->rev = 0;
		node->next = NULL;
	}
	return (node);
}

static t_bfs	*get_priority_parent(t_data *data, int to, int level)
{
	int	i;

	i = 1;
	if (to == data->end_id)
		return (NULL);
	while (i < data->edg_len)
	{
		if (data->edg[i]->to == to && !data->edg[i]->visited &&
			data->edg[i]->level == level && data->edg[i]->reversed)
		{
			data->edg[i]->visited = 1;
			return (new_parent(data->edg[i], i));
		}
		i++;
	}
	return (NULL);
}

t_bfs			*get_parent(t_data *data, int to, int prev_level)
{
	t_bfs	*node;
	int		level;
	int		i;

	i = 1;
	level = get_lowest_level(data, to, prev_level);
	if ((node = get_priority_parent(data, to, level)))
		return (node);
	while (i < data->edg_len)
	{
		if (data->edg[i]->to == to && !data->edg[i]->visited &&
			data->edg[i]->level == level)
		{
			data->edg[i]->visited = 1;
			return (new_parent(data->edg[i], i));
		}
		i++;
	}
	return (NULL);
}
