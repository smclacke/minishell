/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/07 17:12:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	sort_vars(t_procs *proc, char **process)
{
	if (proc->cmd_flag == TRUE)
	{
		if (proc->str_count != 0)
		{
			proc->str = (char **)malloc(sizeof(char *) * (proc->str_count + 1));
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
