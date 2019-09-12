/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	cpy_edge(t_edge **src, t_edge **dest)
{
	(*dest) = malloc(sizeof(t_edge));
	(*dest)->from = (*src)->from;
	(*dest)->to = (*src)->to;
	(*dest)->flow = (*src)->flow;
	(*dest)->tmp_flow = (*src)->tmp_flow;
	(*dest)->visited = (*src)->visited;
	(*dest)->reversed = (*src)->reversed;
	(*dest)->pathed = (*src)->pathed;
	(*dest)->tmp_reversed = (*src)->tmp_reversed;
	(*dest)->level = (*src)->level;
	(*dest)->progress = (*src)->progress;
	(*dest)->next = NULL;
}

void	cpy_edges_to_tab(t_data *data)
{
	t_edge	*edge;
	int		i;

	edge = data->edges;
	data->edg_len = (data->edge_nb * 2) + 1;
	data->edg = malloc(sizeof(t_edge) * data->edg_len);
	data->edg[0] = NULL;
	i = 1;
	while (i < data->edg_len && edge)
	{
		cpy_edge(&edge, &data->edg[i]);
		edge = edge->next;
		i++;
	}
}

void	index_rooms(t_data *data)
{
	t_room	*room;
	int		i;

	room = data->rooms;
	data->rms = malloc(sizeof(t_room) * data->room_nb + 1);
	data->rms[0] = NULL;
	i = 1;
	while (i < (data->room_nb + 1) && room)
	{
		data->rms[i] = room;
		room = room->next;
		i++;
	}
}
