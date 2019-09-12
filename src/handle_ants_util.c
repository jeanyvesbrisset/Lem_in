/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ants_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	push_ants(t_ant **ants, t_ant *new)
{
	if (!(*ants))
		*ants = new;
	else
	{
		new->next = *ants;
		*ants = new;
	}
}

void		init_ants(t_data *data)
{
	t_ant	*new;
	t_ant	*ants;
	int		nb_ant;

	ants = NULL;
	nb_ant = data->ant;
	while (nb_ant)
	{
		new = malloc(sizeof(t_ant));
		new->number = nb_ant;
		new->next = NULL;
		push_ants(&ants, new);
		nb_ant--;
	}
	data->rms[data->start_id]->ant = ants;
}

void		free_ants(t_ant *ant)
{
	t_ant	*tmp;

	while (ant)
	{
		tmp = ant;
		ant = ant->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	adjust_repartion(t_data *data, int sum)
{
	t_path	*path;
	int		diff;

	if ((diff = sum - data->ant))
	{
		path = data->paths;
		if (diff < 0)
		{
			while (path && diff < 0)
			{
				path->ants++;
				path = path->next;
				diff++;
			}
		}
		else
		{
			while (path && diff > 0)
			{
				path->ants--;
				path = path->next;
				diff--;
			}
		}
	}
}

void		get_ants_repartition(t_data *data)
{
	t_path	*path;
	int		sum;

	path = data->paths;
	sum = 0;
	while (path)
	{
		path->ants = data->score - path->length + 1;
		sum += path->ants;
		path = path->next;
	}
	adjust_repartion(data, sum);
}
