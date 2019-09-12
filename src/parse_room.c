/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	add_room(t_data *data, t_room **room)
{
	t_room		*tmp;
	static int	i;

	if (!i)
		i = 1;
	if (!data->rooms)
		data->rooms = *room;
	else
	{
		tmp = data->rooms;
		while (data->rooms->next)
			data->rooms = data->rooms->next;
		data->rooms->next = *room;
		data->rooms = tmp;
	}
	(*room)->id = i++;
	(*room)->next = NULL;
	(*room)->ant = NULL;
	(*room)->visited = 0;
	(*room)->tmp_visited = 0;
	data->room_nb++;
}

static int	check_coords(char *line)
{
	char	**tab;
	int		res;

	res = 0;
	tab = ft_strsplit((const char *)line, SPACE);
	if (ft_is_nb(tab[1]) && ft_is_nb(tab[2]))
		res = 1;
	free_char_tab(tab, 3);
	return (res);
}

void		parse_room(t_data *data, t_parse *parse, char *line)
{
	t_room	*room;

	if (parse->got_edge)
		parse->err = 1;
	else
	{
		room = malloc(sizeof(t_room));
		add_room(data, &room);
		room->name = get_room_name(line);
		if (parse->start_status == 1)
		{
			data->start_id = room->id;
			parse->start_status = 2;
		}
		if (parse->end_status == 1)
		{
			data->end_id = room->id;
			parse->end_status = 2;
		}
	}
}

int			check_dup(t_data *data, char *line)
{
	t_room	*room;
	char	*name;

	name = get_room_name(line);
	room = data->rooms;
	while (room)
	{
		if (!ft_strcmp(room->name, name))
		{
			free(name);
			return (0);
		}
		room = room->next;
	}
	free(name);
	return (1);
}

int			is_room(char *line)
{
	int	i;

	i = 0;
	if (count_char(line, SPACE) != 2 || line[0] == SPACE)
		return (0);
	while (line[i])
	{
		if (line[i] == SPACE && !line[i + 1])
			return (0);
		if (line[0] == 'L' || line[0] == SHARP)
			return (0);
		i++;
	}
	if (!check_coords(line))
		return (0);
	return (1);
}
