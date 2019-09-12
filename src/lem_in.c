/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	init_data(t_data *data)
{
	data->edge_nb = 0;
	data->room_nb = 0;
	data->new_line = 1;
	data->ant = 0;
	data->ant_end = 0;
	data->score = 0;
	data->rooms = NULL;
	data->edges = NULL;
	data->edg = NULL;
	data->rms = NULL;
	data->paths = NULL;
	data->tmp_paths = NULL;
}

static void	free_edg(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->edg_len)
	{
		free(data->edg[i]);
		i++;
	}
	free(data->edg);
}

static void	free_data(t_data *data)
{
	free_edges(data->edges);
	free_rooms(data->rooms);
	free_paths(data->paths);
	if (data->rms)
		free(data->rms);
	if (data->edg)
		free_edg(data);
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	init_data(&data);
	if (parse(&data))
	{
		cpy_edges_to_tab(&data);
		index_rooms(&data);
		if (edmund_karp(&data))
			handle_ants(&data);
		else
			ft_printf("\nNo path was found for the little ants... :(\n");
	}
	else
		write(2, "ERROR\n", 6);
	free_data(&data);
}
