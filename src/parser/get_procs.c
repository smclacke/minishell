/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_procs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 21:48:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/01 16:19:58 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	get_reds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (process[i])
	{
		if (proc_redir(process[i]) && proc_redir(process[i]) != 2)
		{
			if (!process[i + 1])
			{
				printf("error 2\n");
				exit (EXIT_FAILURE);
			}
			proc->redir[j] = process[i];
			proc->redir[j + 1] = process[i + 1];
			j += 2;
			i++;
		}
		i++;
	}
}

void	get_hds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
		{
			if (!process[i + 1])
			{
				printf("error 2\n");
				exit (EXIT_FAILURE);
			}
			proc->hd[j] = process[i];
			proc->hd[j + 1] = process[i + 1];
			j += 2;
			i++;
		}
		i++;
	}
}

void	get_strs(t_procs *proc, char **process)
{
	int		i;
	int		j;
	int		cmd_flag;

	i = 0;
	j = 0;
	cmd_flag = 0;
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			if (!process[i + 1])
				{
					printf("error 2\n");
					exit (EXIT_FAILURE);
				}
			i += 2;
		}
		if (process[i] && !proc_redir(process[i]) && cmd_flag == 0)
		{
			cmd_flag = 1;
			proc->cmd = process[i];
			i++;
		}
		while (process[i] && !proc_redir(process[i]) && cmd_flag != 0)
		{
			proc->str[j] = process[i];
			i++;
			j++;
		}
	}
}
