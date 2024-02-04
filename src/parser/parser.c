/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/04 20:54:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo comments
 * @todo malloc protect
 * @todo norm
 * @todo errors
 */
static	void	make_proc_arr(t_parser *proc, int proc_i, int proc_size)
{
	int		proc_j;
	int		token_size;

	proc_j = 0;
	token_size = 0;
	while (proc_j < proc_size)
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
		proc_size = (i - proc->start);
		proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc_size + 1));
		// wrap
		make_proc_arr(proc, proc_i, proc_size);
		proc->proc_arrs[proc_i][proc_size] = NULL; 
	// needs to change to proc_size + 1, but buffer overflow so find where there isnt enough memory
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
		{
			i++;
			proc_i++;
		}
	}
}

/**
 * @todo	maybe norm?
 * @todo	bzero procs struct??
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
	proc->proc_count = (count_procs(tokens) + 1);

	parser_list = NULL;
	new_node = NULL;

	proc->process = (t_procs **)malloc(sizeof(t_procs *) * (proc->proc_count + 1));
	// wrap it up
	if (proc->proc_count > 1)
	{
		// handle mutli (())
		proc->multi_proc_b = TRUE;
		get_procs(proc);
		while (i < proc->proc_count)
		{
			proc->process[i] = (t_procs *)malloc(sizeof(t_procs));
			// wrap it up
			sort_each_proc(proc->process[i], proc->proc_arrs[i]);
			proc->process[i]->proc_count = proc->proc_count;
			new_node = parser_listnew(proc->process[i]);
			parser_listadd_back(&parser_list, new_node);
			i++;
		}
	}	
	else if (proc->proc_count == 1)
	{
		// handle singular ())()
		proc->multi_proc_b = FALSE;
		proc->process[i] = (t_procs *)malloc(sizeof(t_procs));
		// wrap it up
		sort_each_proc(proc->process[i], proc->tokens);
		proc->process[i]->proc_count = 1;
		new_node = parser_listnew(proc->process[i]);
		parser_listadd_back(&parser_list, new_node);
	}
	return (parser_list);
}
