/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/05/11 15:28:33 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	enqueue(t_bfs **queue, t_bfs *node)
{
	t_bfs	*tmp_q;

	tmp_q = *queue;
	if (!(*queue))
		*queue = node;
	else
	{
		while ((*queue)->next)
			(*queue) = (*queue)->next;
		(*queue)->next = node;
		(*queue) = tmp_q;
	}
}

void	push(t_bfs **queue, t_bfs *node)
{
	if (!(*queue))
		*queue = node;
	else
	{
		node->next = *queue;
		*queue = node;
	}
}

void	dequeue(t_bfs **queue)
{
	t_bfs	*tmp;

	tmp = *queue;
	if (!(*queue))
		return ;
	if (!(*queue)->next)
	{
		free(*queue);
		*queue = NULL;
	}
	else
	{
		*queue = (*queue)->next;
		free(tmp);
	}
}

int		is_in_queue(t_bfs *queue, int id, int code)
{
	if (!queue)
		return (0);
	while (queue)
	{
		if (code == 1 && queue->id == id)
			return (1);
		else if (code == 2 && queue->from == id)
			return (1);
		else if (code == 3 && queue->to == id)
			return (1);
		queue = queue->next;
	}
	return (0);
}
