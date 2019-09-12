/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:34:46 by jbrisset          #+#    #+#             */
/*   Updated: 2019/06/27 17:34:54 by jbrisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define START	"##start"
# define END	"##end"
# define DASH	'-'
# define SPACE	' '
# define SHARP	'#'
# define STEP_0	0
# define STEP_1	1
# define STEP_2	2

# include "libft/ft_printf.h"

typedef struct	s_ant
{
	int				number;
	struct s_ant	*next;
}				t_ant;

typedef struct	s_path
{
	int				id;
	int				ants;
	int				length;
	struct s_path	*next;
}				t_path;

typedef struct	s_bfs
{
	int				id;
	int				from;
	int				to;
	int				rev;
	int				level;
	struct s_bfs	*next;
}				t_bfs;

typedef struct	s_room
{
	char			*name;
	int				id;
	int				visited;
	int				tmp_visited;
	t_ant			*ant;
	struct s_room	*next;
}				t_room;

typedef struct	s_edge
{
	int				from;
	int				to;
	int				flow;
	int				tmp_flow;
	int				visited;
	int				reversed;
	int				pathed;
	int				tmp_reversed;
	int				level;
	int				progress;
	struct s_edge	*next;
}				t_edge;

typedef	struct	s_map
{
	char			*line;
	struct s_map	*next;
}				t_map;

typedef struct	s_parse
{
	int				err;
	int				got_ants;
	int				got_edge;
	int				start_status;
	int				end_status;
}				t_parse;

typedef struct	s_data
{
	int				edge_nb;
	int				room_nb;
	int				start_id;
	int				end_id;
	float			score;
	int				ant;
	int				ant_start;
	int				ant_end;
	int				new_line;
	t_room			*rooms;
	t_room			**rms;
	t_edge			*edges;
	t_edge			**edg;
	int				edg_len;
	t_path			*tmp_paths;
	t_path			*paths;
}				t_data;

/*
**	parsing.c
*/

int				parse(t_data *data);

/*
**	map.c
*/

t_map			*new_line(void);
t_map			*add_line(t_map **map, t_map *newline);
int				check_parsing(t_parse parse, t_map *map);

/*
**	parse_edge.c
*/

int				is_edge(char *line);
int				v_edge(t_data *data, char *line);
void			parse_edge(t_data *data, t_parse *parse, char *line);

/*
**	parse_room.c
*/

int				is_room(char *line);
int				check_dup(t_data *data, char *line);
void			parse_room(t_data *data, t_parse *parse, char *line);

/*
**	edmund_karp.c
*/

int				edmund_karp(t_data *data);

/*
**	edkarp_util.c
*/

int				got_overlap(t_data *data);
void			cpy_tmp_data(t_data *data);

/*
**	bfs.c
*/

int				bfs(t_data *data);

/*
**	bfs_util.c
*/

int				init_queue(t_data *data, t_bfs **queue);
t_bfs			*get_elem(t_data *data, int from, int to, int level);

/*
**	queue_util.c
*/

void			push(t_bfs **queue, t_bfs *node);
void			enqueue(t_bfs **queue, t_bfs *node);
void			dequeue(t_bfs **queue);
int				is_in_queue(t_bfs *queue, int id, int code);

/*
**	getters.c
*/

int				get_room_id(t_data *data, char *str);
char			*get_room_name(char *line);
int				get_rev_id(int id);

/*
**	paths_manager.c
*/

int				dfs_paths(t_data *data);
int				get_previous(t_data *data, int id);

/*
**	set_flow.c
*/

void			set_flow(t_data *data);

/*
**	set_flow_util.c
*/

t_bfs			*get_parent(t_data *data, int to, int prev_level);

/*
**	manage_visited.c
*/

void			reinit_visited(t_data *data);
int				room_visited(t_data *data, int id);
int				is_available(t_data *data, int i);

/*
**	handle_ants.c
*/

void			handle_ants(t_data *data);

/*
**	handle_ants_util.c
*/

void			init_ants(t_data *data);
void			get_ants_repartition(t_data *data);
void			free_ants(t_ant *ant);

/*
**	free_functions.c
*/

void			free_t_bfs(t_bfs *elem);
void			free_rooms(t_room *room);
void			free_edges(t_edge *edge);
void			free_char_tab(char **tab, int len);
void			free_paths(t_path *path);

/*
**	index_data.c
*/

void			cpy_edges_to_tab(t_data *data);
void			index_rooms(t_data *data);

#endif
