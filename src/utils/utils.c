/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/14 15:29:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int		ft_abs(int i)
{
	if (i < 0)
		i *= 1;
	return (i);
}

void	free_proc_arrs(t_parser *proc, int count)
{
	int	i;

	i = 0;
	printf("hello\n");
	while (i < count)
	{
		printf("here\n");
		ft_free_arr(proc->proc_arrs[i]);
		i++;
	}
		// free(proc->proc_arrs[i]);
	free(proc->proc_arrs);
}

void	ft_free_process(t_parser *proc)
{
	int		i = 0;
	if (proc->process)
	{
		while(proc->process[i])
		{
			free(proc->process[i]);
			i++;
		}
		free(proc->process);
	}
}

void	free_parser(t_parser *procs)
{
	t_parser	*tmp;
	int			count;
	int			i;

	count = procs->proc_count;
	i = 0;
	while (procs)
	{
		tmp = procs->next;
		if (count > 1)
			free_proc_arrs(procs, count);
		else
			free(procs->tokens);
		free_procs(procs->proc);
		free(procs);
		procs = tmp;
	}
	free(procs);
}

