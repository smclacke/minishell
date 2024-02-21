/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   more_space.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 20:51:27 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/21 18:30:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	set_flag(t_procs *proc, int i)
{
	proc->cmd_flag = 1;
	i += 1;
	return (i);
}

int		count_str_util(t_procs *proc, char **process, int i)
{
	if (proc_redir(process[i]) == 0 && proc->cmd_flag != 0
		&& shelly_strcmp(process[i], PIPE) != 0)
			return (1);
	return (0);
}

int		get_strs_util(t_procs *proc, char **process, int i)
{
	if (!proc_redir(process[i]) && proc->cmd_flag != 0
			&& shelly_strcmp(process[i], PIPE) != 0)
			return (1);
	return (0);
}

int	copy_strs(t_procs *proc, char *process)
{
	proc->str[proc->index] = ft_strdup(process);
	if (!proc->str[proc->index])
	{
		free(process);
		malloc_error(NULL, proc, NULL, 1);
	}
	proc->index++;
	return (0);
}
