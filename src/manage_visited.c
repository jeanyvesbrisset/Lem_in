/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_visited.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:20:06 by jbrisset          #+#    #+#             */
/*   Updated: 2019/05/11 15:28:33 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		room_visited(t_data *data, int id)
{
	return (data->rms[id]->visited);
}

void	reinit_visited(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->edg_len)
	{
		data->edg[i]->visited = 0;
		i++;
	}
}

int		is_available(t_data *data, int i)
{
	if (data->edg[i]->tmp_flow)
		return (0);
	else
		return (1);
}
