/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:44:37 by jbrisset          #+#    #+#             */
/*   Updated: 2019/04/25 10:44:39 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			check_ants(t_data *data, t_parse *parse, char *line)
{
	long long	ants;

	ants = ft_atoi(line);
	if (ft_is_nb(line) && ants > 0 && ants <= 2147483647)
	{
		parse->got_ants = 1;
		data->ant = (int)ants;
		return (1);
	}
	parse->err = 1;
	return (0);
}

static int	init_parse(t_parse *parse, t_map **new, t_map **map)
{
	*map = NULL;
	*new = new_line();
	parse->err = 0;
	parse->got_ants = 0;
	parse->got_edge = 0;
	parse->start_status = 0;
	parse->end_status = 0;
	return (1);
}

static int	is_cmd(t_parse *parse, char *line)
{
	if (!ft_strcmp(line, "##start"))
	{
		if (!parse->start_status && parse->end_status != 1)
		{
			parse->start_status = 1;
			return (1);
		}
		else
			parse->err = 1;
	}
	else if (!ft_strcmp(line, "##end"))
	{
		if (!parse->end_status && parse->start_status != 1)
		{
			parse->end_status = 1;
			return (1);
		}
		else
			parse->err = 1;
	}
	return (0);
}

int			free_new(t_map **new)
{
	free((*new)->line);
	free(*new);
	return (1);
}

int			parse(t_data *data)
{
	t_map	*map;
	t_map	*new;
	t_parse	p;
	int		i;
	int		ret;

	i = init_parse(&p, &new, &map);
	while ((ret = get_next_line(0, &new->line) > 0) && !p.err)
	{
		if (i++ == 1)
			check_ants(data, &p, new->line);
		else if (is_room(new->line) && check_dup(data, new->line))
			parse_room(data, &p, new->line);
		else if (is_edge(new->line) && v_edge(data, new->line) && !p.err)
			parse_edge(data, &p, new->line);
		else if ((is_cmd(&p, new->line) || (new->line[0] == SHARP)))
			;
		else if (free_new(&new))
			break ;
		if (!p.err)
			new = add_line(&map, new);
	}
	if (!ret || p.err)
		free_new(&new);
	return (check_parsing(p, map));
}
