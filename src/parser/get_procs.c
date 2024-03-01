/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_procs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 21:48:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 18:29:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	copy_over(t_procs *proc, char **process, int i, int j)
{
	proc->redir[j] = ft_strdup(process[i]);
	if (!proc->redir[j])
		malloc_error(NULL, NULL, NULL, 0);
	proc->redir[j + 1] = ft_strdup(process[i + 1]);
	if (!proc->redir[j + 1])
		malloc_error(NULL, NULL, NULL, 0);
}

int	get_reds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->redir = (char **)malloc(sizeof(char *) * (proc->red_count + 1));
	if (!proc->redir)
		malloc_error(NULL, proc, NULL, 1);
	while (process[i])
	{
		if (proc_redir(process[i]) && proc_redir(process[i]) != 2)
		{
			if (!process[i + 1])
				return (syntax_error("near unexpected token 'newline'"));
			copy_over(proc, process, i, j);
			j += 2;
			i++;
		}
		i++;
	}
	return (0);
}

int	get_hds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->hd = (char **)malloc(sizeof(char *) * (proc->hd_count + 1));
	if (!proc->hd)
		malloc_error(NULL, proc, NULL, 1);
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
		{
			if (!process[i + 1])
				return (syntax_error("near unexpected token 'newline'"));
			proc->hd[j] = ft_strdup(process[i + 1]);
			if (!proc->hd[j])
				malloc_error(NULL, NULL, NULL, 0);
			j++;
			i++;
		}
		i++;
	}
	return (0);
}

static	int	handle_cmd(t_procs *proc, char *process)
{
	proc->cmd_flag = 1;
	proc->cmd = ft_strdup(process);
	if (!proc->cmd)
		malloc_error(NULL, NULL, NULL, 0);
	return (0);
}

int	get_strs(t_procs *proc, char **process)
{
	int		i;

	i = 0;
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			if (!process[i + 1])
				return (syntax_error("near unexpected token 'newline'"));
			i += 2;
		}
		if (process[i] && !proc_redir(process[i]) && proc->cmd_flag == 0)
		{
			handle_cmd(proc, process[i]);
			i++;
		}
		while (process[i] && get_strs_util(proc, process, i))
		{
			copy_strs(proc, process[i]);
			i++;
		}
		if (process[i] && ft_strcmp(process[i], PIPE) == 0)
			i++;
	}
	return (0);
}
