/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:01:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/07 16:58:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo norm
 */
static	int	make_proc_arr(t_parser *proc, int proc_i, int proc_size)
{
	int		proc_j;
	int		token_size;

	proc_j = 0;
	token_size = 0;
	while (proc_j < proc_size)
	{
		if (!proc->tokens[proc->start])
		{
			free(proc->tokens);
			free(proc);
			return (0); // errrrror
		}
		token_size = ft_strlen(proc->tokens[proc->start]);
		proc->proc_arrs[proc_i][proc_j] = ft_strdup(proc->tokens[proc->start]);
		if (!proc->proc_arrs[proc_i][proc_j])
		{
			free(proc->tokens[proc_i]);
			free(proc->tokens);
			free(proc->proc_arrs);
			free(proc);
			return (0); // malloc error
		}
		proc_j++;
		proc->start++;
	}
	return (1);
}

/**
 * normynorm
 */
static	int	get_procs(t_parser *proc)
{
	int	i;
	int	proc_i;
	int	proc_size;

	i = 0;
	proc_i = 0;
	proc_size = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	if (!proc->proc_arrs)
	{
		free (proc);
		return (0); // malloc error
	}
	while (proc->tokens[i])
	{
		proc->start = i;
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
			i++;
		proc_size = (i - proc->start);
		proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc_size + 1));
		if (!proc->proc_arrs)
		{
			free(proc->proc_arrs);
			free(proc);
			return (0); // malloc error
		}
		if (!make_proc_arr(proc, proc_i, proc_size))
			return (0); // error
		proc->proc_arrs[proc_i][proc_size] = NULL;
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
		{
			i++;
			proc_i++;
		}
	}
	return (1);
}

/**
 * normynorm
 */
static t_parser	*parse_tokens(char **tokens)
{
	t_parser	*proc;
	t_parser	*parser_list;
	t_parser	*new_node;
	int			i;

	i = 0;
	if (!tokens)
		return (NULL); //  error??
	proc = (t_parser *)malloc(sizeof(t_parser));
	if (!proc)
		return (NULL); // malloc error
	ft_bzero(proc, sizeof(t_parser));
	proc->tokens = tokens;
	proc->proc_count = (count_procs(tokens) + 1);
	parser_list = NULL;
	new_node = NULL;
	proc->process = (t_procs **)malloc(sizeof(t_procs *) * (proc->proc_count + 1));
	if (!proc->process)
	{
		free(proc);
		return (NULL); // malloc error
	}
	ft_bzero(proc->process, sizeof(t_procs));
	if (proc->proc_count > 1)
	{
		// handle mutli (())
		proc->multi_proc_b = TRUE;
		if (!get_procs(proc))
			return (NULL); // error
		while (i < proc->proc_count)
		{
			proc->process[i] = (t_procs *)malloc(sizeof(t_procs));
			if (!proc->process[i])
			{
				free(proc->process);
				return (NULL); // malloc error
			}
			ft_bzero(proc->process[i], sizeof(t_procs));
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
			if (!proc->process[i])
			{
				free(proc->process);
				return (NULL); // malloc error
			}
		ft_bzero(proc->process[i], sizeof(t_procs));
		sort_each_proc(proc->process[i], proc->tokens);
		proc->process[i]->proc_count = 1;
		new_node = parser_listnew(proc->process[i]);
		free(proc->process);
		parser_listadd_back(&parser_list, new_node);
	}
	if (!parser_list)
	{
		free_parser(proc);
		return (NULL);
	}
	parser_list->proc_count = (count_procs(tokens) + 1);
	return (parser_list);
}

t_parser		*parse_input(t_parser *procs, char *input)
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
		ft_free_arr(tokens);
		if (!procs)
		{
			free_parser(procs);
			return (NULL); // parser failed error
		}
		return (procs);
	}
	return (NULL); // parser failed error
}
