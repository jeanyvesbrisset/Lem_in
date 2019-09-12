/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/06/30 17:26:04 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		get_room_id(t_data *data, char *str)
{
	t_room	*room;

	room = data->rooms;
	while (room)
	{
		if (!ft_strcmp(room->name, str))
			return (room->id);
		room = room->next;
	}
	return (0);
}

char	*get_room_name(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != SPACE)
		i++;
	return (ft_strndup(line, i));
}

int		get_rev_id(int id)
{
	if (id % 2 == 0)
		return (id - 1);
	else
		return (id + 1);
}
