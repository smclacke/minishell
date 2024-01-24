/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 17:09:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * while tokens + !pipe
 * get process tokens !start----------end!
 * make array[i] filled with those tokens
 * tokens[i]++ if pipe, move over
 * array[i] ++ move to next process
 * do again
 * 
 * proc_arr[i]
	* get proc tokens...
	* add to proc_arr[i][j++]
 * proc_arr[i++]
	* skip pipe
	* get proc tokens...
	* add to proc_arr[i][j++]
 * ........................
*/

	
/**
 * @todo	maybe norm?
 * @todo	error handling
 * @todo	memory handling - add malloc protection back when it works
 * @todo	remove print statements when everything works
*/
static void	get_procs(t_parser *proc)
{
	int		i;
	int		proc_i;
	int		proc_j;

	i = 0;
	proc->start = 0;
	proc_i = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	printf("proc->proc_count = %i\n", proc->proc_count);
	while (proc->tokens[i])
	{
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
		{
			if (proc->tokens[i + 1] == NULL || is_pipe(proc->tokens[i + 1]))
			{
				proc->proc_size = (i - proc->start) + 1;
				// make array ..
				make_proc_array(proc);
				printf("proc->proc_size = %i\n", proc->proc_size);
				proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc->proc_size + 1));
				while (proc_i <proc->proc_size)
				proc_j = 0;
				printf("proc->start = %i\n", proc->start);
				printf("pos i = %i\n", i);
				while (proc->start <= i)
				{
					proc->token_size = ft_strlen(proc->tokens[proc->start]);
					printf("proc->token_size = %i\n", proc->token_size);
					proc->proc_arrs[proc_i][proc_j] = (char *)malloc(sizeof(char) * (proc->token_size + 1));
					while (proc_j <= proc->token_size)
					{
						printf("where break?\n");
						ft_strcpy(proc->proc_arrs[proc_i][proc_j], proc->tokens[proc->start]);
						printf("proc->arr[%i][%i] = %s\n", proc_i, proc_j, proc->proc_arrs[proc_i][proc_j]);
						proc_j++;
					}
					proc->start++;
				}
			}
			i++;
		}
		proc_i++;
		if (is_pipe(proc->tokens[i]))
		{
			printf("proc->start = %i\n", proc->start);
			proc->start = i;
			i++;
			printf("im here\n");
			exit (EXIT_SUCCESS);
			// proc->proc_arrs[proc_i][proc_j] = NULL;
			// // proc_j = 0;
			// printf("start = %i\n", proc->start);
		}
	}
}

	// if (!proc->proc_arrs)
	// {
	// 	printf("maloc fucked proc_arrs\n");
	// 	return (1);
	// }
				// if (!proc->proc_arrs[proc_i])
				// {
				// 	printf("maloc fucked proc_arrs\n");
				// 	return (1);
				// }
					// if (!proc->proc_arrs[proc_i][proc_j])
					// {
					// 	printf("maloc fucked proc_arrs\n");
					// 	return (1);
					// }

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
	if (proc->proc_count > 0)
	{
		proc->multi_proc_b = TRUE;
		get_procs(proc);
		// if (get_procs(proc))
		// {
		// 	printf("error in get_procs()\n");
		// 	return (NULL);
		// }
		while (i <= proc->proc_count)
		{
			sort_each_proc(proc, proc->proc_arrs[i], i);
			// new_node = parser_listnew(proc->process[i]);
			// parser_listadd_back(&parser_list, new_node);
			i++;
		}
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
