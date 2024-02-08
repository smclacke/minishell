/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_procs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 21:48:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/08 19:30:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	get_reds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->redir = (char **)malloc(sizeof(char *) * (proc->red_count + 1));
	if (!proc->redir)
		return ; // malloc error
	while (process[i])
	{
		if (proc_redir(process[i]) && proc_redir(process[i]) != 2)
		{
			if (!process[i + 1])
				return ; // syntax error
			proc->redir[j] = ft_strdup(process[i]);
			if (!proc->redir[j])
				return ; // malloc error
			proc->redir[j + 1] = ft_strdup(process[i + 1]);
			if (!proc->redir[j + 1])
				return ; // malloc error
			j += 2;
			i++;
		}
		i++;
	}
}

/**
 * @note changed hds, ignoring << meta, hd_count= actual hd_count
 * 		hd_array = array delimiters e.g. hd[0] = eof hd[1] = end ...  
*/
void	get_hds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->hd = (char **)malloc(sizeof(char *) * (proc->hd_count + 1));
	if (!proc->hd)
		return ; // malloc error
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
		{
			if (!process[i + 1])
				return ; // syntax error
			proc->hd[j] = ft_strdup(process[i + 1]);
			if (!proc->hd[j])
				return ; //malloc error
			j++;
			i++;
		}
		i++;
	}
}

static	int	copy_strs(t_procs *proc, char *process)
{
	proc->str[proc->index] = ft_strdup(process);
	if (!proc->str[proc->index])
		return (-1); // malloc error
	proc->index++;
	return (0);
}

static	int	handle_cmd(t_procs *proc, char *process)
{
	proc->cmd_flag = 1;
	proc->cmd = ft_strdup(process);
	if (!proc->cmd)
		return (-1); // malloc error
	return (0);
}

/**
 * norm meeee
 */
void	get_strs(t_procs *proc, char **process)
{
	int		i;

	i = 0;
	proc->cmd_flag = 0;
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			if (!process[i + 1])
				return ; // syntax error
			i += 2;
		}
		if (process[i] && !proc_redir(process[i]) && proc->cmd_flag == 0)
		{
			handle_cmd(proc, process[i]);
			i++;
		}
		while (process[i] && !proc_redir(process[i]) && proc->cmd_flag != 0)
		{
			copy_strs(proc, process[i]);
			i++;
		}
	}
}
