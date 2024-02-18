/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/18 16:43:08 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
		if (proc->proc_count > 1)
			sort_each_proc(proc->process[i], proc->proc_arrs[i]);
		else
			sort_each_proc(proc->process[i], proc->tokens);
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
	int			i;

	i = 0;
	if (!tokens)
		return (NULL);
	proc = init_parser(tokens);
	parser_list = NULL;
	if (proc->proc_count > 1)
	{
		if (!get_procs(proc))
			return (NULL);
	}
	parser_list = handle_procs(proc);
	if (!parser_list)
		return (free_parser(proc), NULL);
	ft_free_arr(tokens);
	return (parser_list);
}

t_parser	*parse_input(t_parser *procs, char *input)
{
	char	**tokens;

	if (!input[0])
		return (NULL);
	if (!is_space(input))
		add_history(input);
	tokens = lexer(input);
	free(input);
	if (tokens)
	{
		procs = parse_tokens(tokens);
		if (!procs)
			general_error("error parsing input");
		ft_free_process(procs);
		return (procs);
	}
	general_error("error parsing input");
	return (0);
}
