/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 19:01:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	int	sort_this_out(t_parser *proc, int i)
{
	if (proc->proc_count > 1)
	{
		if (sort_each_proc(proc->process[i], proc->proc_arrs[i]) == E_STOP)
			return (0);
	}
	else
	{
		if (sort_each_proc(proc->process[i], proc->tokens) == E_STOP)
			return (ft_free_process(proc), free(proc), 0);
	}
	return (1);
}

static	t_parser	*handle_procs(t_parser *proc)
{
	t_parser	*parser_list;
	t_parser	*new_node;
	int			i;

	i = 0;
	parser_list = NULL;
	new_node = NULL;
	while (i < proc->proc_count)
	{
		proc->process[i] = (t_procs *)malloc(sizeof(t_procs));
		if (!proc->process[i])
			malloc_error(NULL, proc->process[i], NULL, 0);
		ft_bzero(proc->process[i], sizeof(t_procs));
		if (sort_this_out(proc, i) == 0)
			return (NULL);
		proc->process[i]->proc_count = proc->proc_count;
		new_node = parser_listnew(proc->process[i]);
		parser_listadd_back(&parser_list, new_node);
		parser_list->proc_count = proc->process[i]->proc_count;
		i++;
	}
	free_lots_stuff(proc);
	return (parser_list);
}

static	t_parser	*init_parser(char **tokens)
{
	t_parser	*proc;

	proc = (t_parser *)malloc(sizeof(t_parser));
	if (!proc)
		malloc_error(NULL, NULL, NULL, 0);
	ft_bzero(proc, sizeof(t_parser));
	proc->tokens = tokens;
	proc->proc_count = (count_procs(tokens) + 1);
	if (!proc->proc_count)
		return (free_lots_stuff(proc), free_parser(proc), NULL);
	proc->process = (t_procs **)malloc(sizeof(t_procs *)
			* (proc->proc_count + 1));
	if (!proc->process)
		malloc_error(proc, NULL, NULL, 0);
	ft_bzero(proc->process, (sizeof(t_procs *) * (proc->proc_count + 1)));
	return (proc);
}

static t_parser	*parse_tokens(char **tokens)
{
	t_parser	*proc;
	t_parser	*parser_list;

	if (!tokens)
		return (NULL);
	proc = init_parser(tokens);
	if (!proc)
		return (ft_free_arr(tokens), NULL);
	parser_list = NULL;
	if (proc->proc_count > 1)
	{
		if (!get_procs(proc))
		{
			free_lots_stuff(proc);
			ft_free_arr(tokens);
			return (free_parser(proc), NULL);
		}
	}
	parser_list = handle_procs(proc);
	if (parser_list == NULL)
		return (ft_free_arr(tokens), NULL);
	ft_free_arr(tokens);
	return (parser_list);
}

t_parser	*parse_input(t_parser *procs, char *input)
{
	char	**tokens;

	if (input == NULL)
		return (NULL);
	if (!is_space(input))
		add_history(input);
	tokens = lexer(input);
	free(input);
	if (tokens)
	{
		procs = parse_tokens(tokens);
		if (!procs)
			return (NULL);
		ft_free_process(procs);
		return (procs);
	}
	return (NULL);
}
