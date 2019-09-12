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

static int	init_flow_setter(t_data *data, t_bfs **queue)
{
	t_bfs	*node;

	while ((node = get_parent(data, data->end_id, 0)))
		push(queue, node);
	if (queue)
		return (1);
	return (0);
}

void		set_flow(t_data *data)
{
	t_bfs	*queue;
	t_bfs	*node;

	queue = NULL;
	init_flow_setter(data, &queue);
	while (!is_in_queue(queue, data->start_id, 2))
	{
		if ((node = get_parent(data, queue->from, queue->level)))
			push(&queue, node);
		else
			dequeue(&queue);
	}
	while (queue)
	{
		data->edg[queue->id]->tmp_flow = 1;
		dequeue(&queue);
	}
}
