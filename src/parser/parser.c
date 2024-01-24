/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 12:08:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
					printf("proc->arr[%i][%i] = %s\n", proc_i, proc_j, proc->proc_arrs[proc_i][proc_j]);
					proc->start++;
					proc_j++;
				}
				printf("-------------------------------\n");
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


// static	t_parser	*make_parser_list(t_parser *procs, t_parser *proc_list, int proc_count)
// {
// 	t_parser	*new_list;
// 	t_parser	*node;
// 	int			i;
// 	(void) proc_count;

// 	new_list = NULL;
// 	i = 0;
// 	// if (proc_count == 1)
// 	// 	new_list = one_proc(procs);
// 	// else
// 	// {
// 		while (i < procs->proc_count)
// 		{
// 			node = parser_listnew(procs->proc_arrs[i]);
// 			parser_listadd_back(&new_list, node);
// 			i++;
// 		}
// 	// }
// 	proc_list = new_list;
// 	return (proc_list);
// }

// static	t_parser	*one_proc(t_procs *proc)
// {
// 	t_parser	*new_list;
// 	t_parser	*node;
// 	int			i;

// 	new_list = NULL;
// 	i = 0;
// 	node = parser_listnew(proc);
// 	parser_listadd_back(&new_list, node);
// 	return (new_list);
// }

/**
 * find strs and put into **str array, then make list, the add everything to right var
 * otherwise meta is overriden/ needs ** and malloc...
*/
t_parser	*parse_tokens(char **tokens)
{
	t_procs		*one_proc;
	t_parser	*proc;
	t_parser	*parser_list;
	t_parser	*new_node;
	int			i;

	i = 0;
	one_proc = (t_procs *)malloc(sizeof(t_procs));
	// wrap it up
	ft_bzero(one_proc, sizeof(t_procs));
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
		printf("proc count = %i\n", proc->proc_count);
		int		j = 0;
		while (i <= proc->proc_count)
		{
			j = 0;
			while (j <= proc->proc_size)
			{
				// printf("ptrrr = %p\n", proc->proc_arrs[i][j]);
				sort_each_proc(proc, one_proc, &proc->proc_arrs[i][j], i);
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
		sort_each_proc(proc, one_proc, proc->tokens, 0);
		new_node = parser_listnew(proc->process[0]);
		parser_listadd_back(&parser_list, new_node);
	}
	while (parser_list)
	{
		int		j = 0;
		
		printf("cmd = %s\n", parser_list->proc->cmd);
		int		k = 0;
		while (k < parser_list->proc->str_count)
		{
			printf("strs = %s\n", parser_list->proc->str[k]);
			k++;
		}
		j++;
		parser_list = parser_list->next;
	}
	return (parser_list);
}
