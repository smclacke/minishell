/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/13 18:14:29 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int		ft_abs(int i)
{
	if (i < 0)
		i *= 1;
	return (i);
}

static	void	free_proc_arrs(t_parser *proc)
{
	int	i;

	i = 0;
	while (i < proc->proc_count)
	{
		ft_free_arr(proc->proc_arrs[i]);
		i++;
	}
	free(proc->proc_arrs);
}

void	free_parser(t_parser *procs)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	while (procs)
	{
		tmp = procs->next;
		if (procs->tokens)
			ft_free_arr(procs->tokens);
		if (procs->proc_arrs)
			free_proc_arrs(procs);
		if (procs->process)
		{
			while (procs->process[i])
			{
				free(procs->process[i]);
				i++;
			}
			free(procs->process);
		}
		// if (procs->proc)
		free_procs(procs->proc);
		free(procs);
		procs = tmp;
	}
	free(procs);
}

void	free_this_proc(t_parser *proc)
{
	int		i = 0;

	if (proc)
	{
		if (proc->process)
		{
			while (proc->process[i])
			{
				free(proc->process[i]);
				i++;
			}
			free(proc->process);
		}
		free(proc);
	}
}
