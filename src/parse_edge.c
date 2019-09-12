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

int				is_edge(char *line)
{
	int	i;

	i = 0;
	if (count_char(line, DASH) != 1 || line[0] == DASH || line[0] == 'L' ||
		line[0] == '#')
		return (0);
	while (line[i])
	{
		if (line[i] == SPACE || (line[i] == DASH && !line[i + 1]))
			return (0);
		if (line[i] == DASH && (line[i + 1] == 'L' || line[i + 1] == '#'))
			return (0);
		i++;
	}
	return (1);
}

static void		add_edge(t_data *data, t_edge **edge)
{
	t_edge	*tmp;

	if (!data->edges)
		data->edges = *edge;
	else
	{
		tmp = data->edges;
		while (data->edges->next)
			data->edges = data->edges->next;
		data->edges->next = *edge;
		data->edges = tmp;
	}
}

int				v_edge(t_data *data, char *line)
{
	t_room	*tmp;
	char	**rooms;
	int		from;
	int		to;

	from = 0;
	to = 0;
	rooms = ft_strsplit(line, DASH);
	tmp = data->rooms;
	while (data->rooms)
	{
		if (!ft_strcmp(data->rooms->name, rooms[0]))
			from = 1;
		if (!ft_strcmp(data->rooms->name, rooms[1]))
			to = 1;
		data->rooms = data->rooms->next;
	}
	data->rooms = tmp;
	free_char_tab(rooms, 2);
	if (from && to)
		return (1);
	else
		return (0);
}

static t_edge	*new_edge(void)
{
	t_edge	*new;

	new = malloc(sizeof(t_edge));
	new->flow = 0;
	new->tmp_flow = 0;
	new->level = 0;
	new->progress = 0;
	new->visited = 0;
	new->reversed = 0;
	new->pathed = 0;
	new->tmp_reversed = 0;
	new->next = NULL;
	return (new);
}

void			parse_edge(t_data *data, t_parse *parse, char *line)
{
	t_edge		*edge;
	t_edge		*edge_bis;
	char		**rooms;
	static int	i;

	rooms = ft_strsplit(line, DASH);
	if (!ft_strcmp(rooms[0], rooms[1]))
	{
		free_char_tab(rooms, 2);
		return ;
	}
	if (!i)
		i = 1;
	edge = new_edge();
	edge_bis = new_edge();
	edge->from = get_room_id(data, rooms[0]);
	edge->to = get_room_id(data, rooms[1]);
	edge_bis->from = edge->to;
	edge_bis->to = edge->from;
	add_edge(data, &edge);
	add_edge(data, &edge_bis);
	parse->got_edge = 1;
	data->edge_nb++;
	free_char_tab(rooms, 2);
}
