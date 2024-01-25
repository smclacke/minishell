/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/25 15:27:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	make_proc_arr(t_parser *proc, int proc_i, int proc_size)
{
	int		proc_j;
	int		token_size;

	proc_j = 0;
	token_size = 0;
	while (proc_j <= proc_size)
	{
		if (!proc->tokens[proc->start])
		{
			printf("this one\n");
			exit(EXIT_SUCCESS);
		}
		token_size = ft_strlen(proc->tokens[proc->start]);
		proc->proc_arrs[proc_i][proc_j] = (char *)malloc(sizeof(char) * (token_size + 1));
		// wrap
		ft_strcpy(proc->proc_arrs[proc_i][proc_j], proc->tokens[proc->start]);
		printf(" MAKING ARRAYS: [%i][%i] = %s\n", proc_i, proc_j, proc->proc_arrs[proc_i][proc_j]);
		printf("----------------------------------------------\n");
		if (!proc->proc_arrs[proc_i][proc_j])
		{
			printf("noooo, this one\n");
			exit(EXIT_SUCCESS);
		}
		proc_j++;
		proc->start++;
	}
}

static	void	get_procs(t_parser *proc)
{
	int	i;
	int	proc_i;
	int	proc_size;

	i = 0;
	proc_i = 0;
	proc_size = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	// wrap
	while (proc->tokens[i])
	{
		proc->start = i;
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
			i++;
		proc_size = (i - proc->start) - 1;
		proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc_size + 1));
		// wrap
		make_proc_arr(proc, proc_i, proc_size);
		proc->proc_arrs[proc_i][proc_size] = NULL;
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
		{
			i++;
			proc_i++;
		}
	}
	print_proc_arrs(proc);
}

/**
 * @todo	maybe norm?
 * @todo	error handling
 * @todo	memory handling, malloc protection
 * @todo	remove print statements when everything works
 * @todo 	do I need alllll of these vars??
*/
t_parser	*parse_tokens(char **tokens)
{
	t_parser	*proc;
	t_parser	*parser_list;
	t_parser	*new_node;
	int			i;

	i = 0;
	proc = (t_parser *)malloc(sizeof(t_parser));
	// wrap it up
	ft_bzero(proc, sizeof(t_parser));
	proc->tokens = tokens;
	proc->proc_count = count_procs(tokens);
	parser_list = NULL;
	new_node = NULL;
	if (proc->proc_count > 0)
	{
		proc->multi_proc_b = TRUE;
		get_procs(proc);
		// while (i < proc->proc_count)
		// {
		// 	sort_each_proc(proc, proc->proc_arrs[i], i);
		// 	i++;
		// }
		// new_node = parser_listnew(proc->process[i]);
		// parser_listadd_back(&parser_list, new_node);
		printf("im done\n");
		return (EXIT_SUCCESS);
	}
	else
	{
		proc->multi_proc_b = FALSE;
		sort_each_proc(proc, proc->tokens, 0);
		new_node = parser_listnew(proc->process[0]);
		parser_listadd_back(&parser_list, new_node);
	}
	print_parser(parser_list);
	return (parser_list);
}
