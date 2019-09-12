/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/05/11 15:28:33 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_bfs		*get_adj(t_data *data, int from, int level)
{
	t_bfs	*node;
	int		i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->from == from && data->edg[i]->to != data->start_id &&
			!(data->edg[i]->visited) && !(data->edg[i]->tmp_flow) &&
			((data->edg[get_rev_id(i)]->level != level)))
		{
			node = malloc(sizeof(t_bfs));
			node->id = i;
			node->from = data->edg[i]->from;
			node->to = data->edg[i]->to;
			node->rev = 0;
			node->level = level + 1;
			node->next = NULL;
			return (node);
		}
		i++;
	}
	return (NULL);
}

t_bfs		*get_priority_adj(t_data *data, int from, int lev)
{
	int		i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->to == from && data->edg[i]->tmp_flow &&
			is_available(data, get_rev_id(i)))
		{
			return (get_elem(data, data->edg[i]->to, data->edg[i]->from, lev));
		}
		i++;
	}
	return (NULL);
}

static void	manage_priority(t_data *data, t_bfs **tmp, t_bfs **queue)
{
	if ((*tmp)->to != data->start_id)
	{
		data->edg[(*tmp)->id]->level = (*tmp)->level;
		push(queue, *tmp);
		data->edg[(*tmp)->id]->visited = STEP_1;
	}
	else
		free(*tmp);
}

static void	manage_adj(t_data *data, t_bfs **tmp, t_bfs **queue)
{
	data->edg[(*tmp)->id]->level = (*tmp)->level;
	enqueue(queue, *tmp);
	data->edg[(*tmp)->id]->visited = STEP_1;
}

int			bfs(t_data *data)
{
	t_bfs	*queue;
	t_bfs	*tmp;

	if (!init_queue(data, &queue))
		return (0);
	while (!is_in_queue(queue, data->end_id, 3) && queue)
	{
		if ((tmp = get_priority_adj(data, queue->to, queue->level)))
			manage_priority(data, &tmp, &queue);
		else if (((room_visited(data, queue->to) && queue->rev) ||
			(!room_visited(data, queue->to))) &&
			(tmp = get_adj(data, queue->to, queue->level)))
			manage_adj(data, &tmp, &queue);
		else
			dequeue(&(queue));
	}
	if (queue)
	{
		free_t_bfs(queue);
		return (1);
	}
	return (0);
}
