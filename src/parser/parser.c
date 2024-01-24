/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 14:49:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo	maybe norm?
 * @todo	error handling
 * @todo	memory handling
 * @todo	remove print statements when everything works
*/
static int	get_procs(t_parser *proc)
{
	int		i;
	int		proc_i;
	int		proc_j;

	i = 0;
	proc->start = 0;
	proc_i = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	if (!proc->proc_arrs)
	{
		printf("maloc fucked proc_arrs\n");
		return (1);
	}
	while (proc->tokens[i])
	{
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
		{
			if (proc->tokens[i + 1] == NULL || is_pipe(proc->tokens[i + 1]))
			{
				proc->proc_size = i - proc->start;
				proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc->proc_size + 1));
				if (!proc->proc_arrs[proc_i])
				{
					printf("maloc fucked proc_arrs\n");
					return (1);
				}
				proc_j = 0;
				while (proc->start <= i && proc_j <= proc->proc_size)
				{
					proc->token_size = ft_strlen(proc->tokens[proc->start]);
					proc->proc_arrs[proc_i][proc_j] = (char *)malloc(sizeof(char) * (proc->token_size + 1));
					if (!proc->proc_arrs[proc_i][proc_j])
					{
						printf("maloc fucked proc_arrs\n");
						return (1);
					}
					ft_strcpy(proc->proc_arrs[proc_i][proc_j], proc->tokens[proc->start]);
					proc->start++;
					proc_j++;
				}
				proc_i++;
			}
			i++;
		}
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
			i++;
		proc->start = i;
	}
	return (0);
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
	// t_procs		*one_proc;
	t_parser	*proc;
	t_parser	*parser_list;
	t_parser	*new_node;
	int			i;

	i = 0;
	// one_proc = (t_procs *)malloc(sizeof(t_procs));
	// wrap it up
	// ft_bzero(one_proc, sizeof(t_procs));
	proc = (t_parser *)malloc(sizeof(t_parser));
	// wrap it up
	ft_bzero(proc, sizeof(t_parser));
	proc->tokens = tokens;
	proc->proc_count = count_procs(tokens);
	parser_list = NULL;
	new_node = NULL;
	if (proc->proc_count > 1)
	{
		proc->multi_proc_b = TRUE;
		if (get_procs(proc))
		{
			printf("error in get_procs()\n");
			return (NULL);
		}
		int		j = 0;
		while (i <= proc->proc_count)
		{
			j = 0;
			while (j <= proc->proc_size)
			{
				// printf("ptrrr = %p\n", proc->proc_arrs[i][j]);
				sort_each_proc(proc, &proc->proc_arrs[i][j], i);
				j++;
			}
			// new_node = parser_listnew(proc->process[i]);
			// parser_listadd_back(&parser_list, new_node);
			i++;
		}
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
