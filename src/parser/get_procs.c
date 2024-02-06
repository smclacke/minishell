/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_procs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 21:48:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/06 15:51:45 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo			NORM ERRORS AND MALLOC PROTECT FOR ALLL
 */


void	get_reds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->redir = (char **)malloc(sizeof(char *) * (proc->red_count + 1));
	while (process[i])
	{
		if (proc_redir(process[i]) && proc_redir(process[i]) != 2)
		{
			if (!process[i + 1])
			{
				printf("error 2\n");
				exit (EXIT_FAILURE);
			}
			proc->redir[j] = ft_strdup(process[i]);
			proc->redir[j + 1] = ft_strdup(process[i + 1]);
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
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
		{
			if (!process[i + 1])
			{
				printf("error 2\n");
				exit (EXIT_FAILURE);
			}
			proc->hd[j] = ft_strdup(process[i + 1]);
			j++;
			i++;
		}
		i++;
	}
}

/**
 * norm meeee
 */
void	get_strs(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->cmd_flag = 0;
	if (proc->str_count != 0)
		proc->str = (char **)malloc(sizeof(char *) * (proc->str_count + 1));
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
		if (process[i] && !proc_redir(process[i]) && proc->cmd_flag == 0)
		{
			proc->cmd_flag = 1;
			proc->cmd = ft_strdup(process[i]);
			i++;
		}
		while (process[i] && !proc_redir(process[i]) && proc->cmd_flag != 0)
		{
			proc->str[j] = ft_strdup(process[i]);
			i++;
			j++;
		}
	}
}
