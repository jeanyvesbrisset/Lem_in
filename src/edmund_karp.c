/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmund_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/05/11 15:28:33 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		handle_double_flows(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = i + 1;
	while (j < data->edg_len)
	{
		if (data->edg[i]->tmp_flow && data->edg[j]->tmp_flow)
		{
			data->edg[i]->tmp_flow = 0;
			data->edg[j]->tmp_flow = 0;
		}
		i += 2;
		j = i + 1;
	}
}

static void		prepare_next_bfs(t_data *data)
{
	t_room	*room;
	int		i;

	i = 1;
	room = data->rooms;
	while (room)
	{
		room->visited = 0;
		room->tmp_visited = 0;
		room = room->next;
	}
	while (i < data->edg_len)
	{
		data->edg[i]->level = 0;
		data->edg[i]->pathed = 0;
		data->edg[i]->tmp_reversed = 0;
		if (data->edg[i]->flow && data->edg[i]->to != data->end_id)
			data->rms[data->edg[i]->to]->visited++;
		i++;
	}
}

static int		*get_paths_data(t_data *data)
{
	t_path	*tmp_paths;
	int		path_nb;
	int		sum_length;
	int		*path_data;

	path_nb = 0;
	sum_length = 0;
	path_data = malloc(sizeof(int) * 2);
	tmp_paths = data->tmp_paths;
	while (tmp_paths)
	{
		sum_length += tmp_paths->length - 1;
		tmp_paths = tmp_paths->next;
		path_nb++;
	}
	path_data[0] = path_nb;
	path_data[1] = sum_length;
	return (path_data);
}

static float	get_score(t_data *data)
{
	int		*paths_data;
	float	score;

	while (dfs_paths(data))
		;
	paths_data = get_paths_data(data);
	score = ((float)data->ant + (float)paths_data[1]) / (float)paths_data[0];
	free(paths_data);
	return (score);
}

int				edmund_karp(t_data *data)
{
	int		i;
	float	tmp_score;

	i = 0;
	tmp_score = 0;
	while (bfs(data))
	{
		i++;
		reinit_visited(data);
		set_flow(data);
		handle_double_flows(data);
		if (!data->score)
			data->score = get_score(data);
		else if ((tmp_score = get_score(data)) < data->score &&
			!got_overlap(data))
			data->score = tmp_score;
		else
		{
			free_paths(data->tmp_paths);
			break ;
		}
		cpy_tmp_data(data);
		prepare_next_bfs(data);
	}
	return (i);
}
