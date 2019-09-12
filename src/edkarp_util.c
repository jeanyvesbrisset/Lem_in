/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edkarp_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/06/30 17:23:33 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	cpy_tmp_data(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->edg_len)
	{
		data->edg[i]->flow = data->edg[i]->tmp_flow;
		data->edg[i]->reversed = data->edg[i]->tmp_reversed;
		i++;
	}
	if (data->paths)
		free_paths(data->paths);
	data->paths = data->tmp_paths;
	data->tmp_paths = NULL;
}

int		got_overlap(t_data *data)
{
	t_room	*room;
	int		i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->tmp_flow && data->edg[i]->to != data->end_id)
			data->rms[data->edg[i]->to]->tmp_visited++;
		i++;
	}
	room = data->rooms;
	while (room)
	{
		if (room->tmp_visited != 0 && room->tmp_visited != 1 &&
			room->id != data->end_id)
			return (1);
		room = room->next;
	}
	return (0);
}
