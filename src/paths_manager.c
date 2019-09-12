/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			get_previous(t_data *data, int id)
{
	int	i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->to == id && data->edg[i]->flow &&
			!(data->edg[i]->progress))
		{
			data->edg[i]->progress = 1;
			return (data->edg[i]->from);
		}
		i++;
	}
	return (0);
}

static void	add_path(t_data *data, int id)
{
	t_path	*path;

	path = malloc(sizeof(t_path));
	path->id = id;
	path->length = 0;
	path->ants = 0;
	path->next = NULL;
	if (!data->tmp_paths)
		data->tmp_paths = path;
	else
	{
		path->next = data->tmp_paths;
		data->tmp_paths = path;
	}
}

static int	get_path(t_data *data, int id)
{
	int	i;

	i = 1;
	while (i < data->edg_len)
	{
		if (data->edg[i]->from == id && data->edg[i]->tmp_flow &&
			!(data->edg[i]->pathed))
		{
			data->edg[i]->pathed = 1;
			return (data->edg[i]->to);
		}
		i++;
	}
	return (0);
}

int			dfs_paths(t_data *data)
{
	int		first;
	int		curr;
	int		next;

	first = 0;
	curr = data->start_id;
	next = get_path(data, curr);
	while (curr && next)
	{
		if (curr == data->start_id)
			add_path(data, next);
		curr = next;
		data->tmp_paths->length++;
		next = get_path(data, curr);
	}
	if (curr == data->start_id && !next)
		return (0);
	else
		return (1);
}
