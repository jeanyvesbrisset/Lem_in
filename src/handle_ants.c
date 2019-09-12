/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_edge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	move_ant(t_data *data, t_room *src, t_room *dest)
{
	t_ant	*tmp;

	if (data->new_line)
		data->new_line = 0;
	else
		write(1, " ", 1);
	tmp = src->ant;
	ft_printf("L%d-%s", src->ant->number, dest->name);
	if (dest->id == data->end_id)
		data->ant_end++;
	src->ant = src->ant->next;
	tmp->next = dest->ant;
	dest->ant = tmp;
}

static void	reinit_progress(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->edg_len)
	{
		data->edg[i]->progress = 0;
		i++;
	}
}

static void	progress_ants(t_data *data)
{
	int		prev;
	int		curr;
	t_room	*prev_r;

	curr = data->end_id;
	while ((prev = get_previous(data, curr)))
	{
		while (curr != data->start_id)
		{
			prev_r = data->rms[prev];
			if (prev_r && prev_r->ant && prev != data->start_id)
				move_ant(data, prev_r, data->rms[curr]);
			curr = prev;
			prev = get_previous(data, curr);
		}
		curr = data->end_id;
	}
	reinit_progress(data);
}

static void	start_ants(t_data *data)
{
	t_path	*paths;
	t_room	*dest;
	t_room	*start;

	start = data->rms[data->start_id];
	paths = data->paths;
	while (paths)
	{
		if (paths->ants)
		{
			dest = data->rms[paths->id];
			if ((!dest->ant && dest->id != data->end_id) ||
				(dest->id == data->end_id))
			{
				move_ant(data, start, dest);
				data->ant_start--;
				paths->ants--;
			}
		}
		if (!data->ant_start)
			return ;
		paths = paths->next;
	}
}

void		handle_ants(t_data *data)
{
	t_room	*start;
	t_room	*end;

	start = data->rms[data->start_id];
	end = data->rms[data->end_id];
	write(1, "\n", 1);
	get_ants_repartition(data);
	data->ant_start = data->ant;
	init_ants(data);
	start_ants(data);
	data->new_line = 1;
	write(1, "\n", 1);
	while (data->ant_end < data->ant)
	{
		progress_ants(data);
		if (start->ant)
			start_ants(data);
		data->new_line = 1;
		write(1, "\n", 1);
	}
	free_ants(end->ant);
}
