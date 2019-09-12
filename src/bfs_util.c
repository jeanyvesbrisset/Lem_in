/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/06/30 17:21:16 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_bfs	*get_init(t_data *data)
{
	t_bfs	*node;
	int		i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->from == data->start_id && !(data->edg[i]->visited) &&
			!(data->edg[i]->tmp_flow) && !room_visited(data, data->edg[i]->to))
		{
			if (data->edg[i]->to != data->start_id)
			{
				node = malloc(sizeof(t_bfs));
				node->id = i;
				node->from = data->edg[i]->from;
				node->to = data->edg[i]->to;
				node->rev = 0;
				node->level = 1;
				node->next = NULL;
				return (node);
			}
		}
		i++;
	}
	return (NULL);
}

int		init_queue(t_data *data, t_bfs **queue)
{
	t_bfs	*node;

	*queue = NULL;
	while (!is_in_queue(*queue, data->end_id, 3) && (node = get_init(data)))
	{
		data->edg[node->id]->level = 1;
		data->edg[node->id]->visited = STEP_1;
		enqueue(queue, node);
	}
	if (queue)
		return (1);
	else
		return (0);
}

t_bfs	*get_elem(t_data *data, int from, int to, int level)
{
	t_bfs	*node;
	int		i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->from == from && data->edg[i]->to == to &&
			!data->edg[i]->tmp_flow && !data->edg[i]->tmp_reversed)
		{
			node = malloc(sizeof(t_bfs));
			node->id = i;
			node->from = data->edg[i]->from;
			node->to = data->edg[i]->to;
			data->edg[i]->tmp_reversed = 1;
			node->rev = 1;
			node->level = level - 1;
			node->next = NULL;
			return (node);
		}
		i++;
	}
	return (NULL);
}
