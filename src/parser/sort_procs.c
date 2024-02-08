/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/08 19:32:37 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	sort_vars(t_procs *proc, char **process)
{
	if (proc->cmd_flag == TRUE)
	{
		if (proc->str_count != 0)
		{
			proc->str = (char **)malloc(sizeof(char *)
				* (proc->str_count + 1));
			if (!proc->str)
				return ; //malloc error
		}
		get_strs(proc, process);
	}
	else
	{
		proc->cmd = NULL;
		proc->str = NULL;
	}
	if (proc->red_count != 0)
		get_reds(proc, process);
	else
		proc->redir = NULL;
	if (proc->hd_count != 0)
		get_hds(proc, process);
	else
		proc->hd = NULL;
}

void	sort_each_proc(t_procs *proc, char **proc_arr)
{
	proc->token_count = ft_arrlen(proc_arr);
	proc->red_count = count_reds(proc_arr);
	proc->str_count = count_strs(proc, proc_arr);
	proc->hd_count = count_hds(proc_arr);
	sort_vars(proc, proc_arr);
}

/**
 * normynorm
 */
int	get_procs(t_parser *proc)
{
	int	i;
	int	proc_i;
	int	proc_size;

	i = 0;
	proc_i = 0;
	proc_size = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	if (!proc->proc_arrs)
		return (free (proc), 0); // malloc error
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
