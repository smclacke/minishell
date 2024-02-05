/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/05 18:42:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo	protect all mallocs
 * @todo	norm - if red // make red arr func(), if hd // make hd arr func ().... 
*/
static	void	sort_vars(t_procs *proc, char **process)
{
	if (proc->cmd_flag != 0 || proc->str_count != 0)
	{
		proc->str = (char **)malloc(sizeof(char *) * (proc->str_count + 1));
		// if (!proc->str)
		// 	sarah_error(NULL, "malloc sort_vars");
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

/**
 * @todo	norm
 * @todo	free proc_arr or tokens once sorted into proc struct
 * @todo	malloc protection 
 * @todo	bzeros?
 * @brief	count_hds looks for the hd meta and saves the number of hds
*/
void	sort_each_proc(t_procs *proc, char **proc_arr)
{
	proc->token_count = ft_arrlen(proc_arr);
	proc->red_count = count_reds(proc_arr);
	proc->str_count = count_strs(proc, proc_arr);
	proc->hd_count = count_hds(proc_arr);
	sort_vars(proc, proc_arr);
}
