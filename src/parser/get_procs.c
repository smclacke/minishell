/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_procs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 21:48:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/05 17:38:38 by smclacke      ########   odam.nl         */
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
	if (!proc->redir)
		sarah_error("malloc error get_reds");
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

/**
 * @brief	finds the hd meta, skips it, saves the delimiters in the
 * 		hd array so iterating through that array looks like this:
 * 		hd_count = 3
 * 		hd[0] = eof | hd[1] = end | hd[2] = stop
 */
void	get_hds(t_procs *proc, char **process)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	proc->hd = (char **)malloc(sizeof(char *) * (proc->hd_count + 1));
	if (!proc->hd)
		sarah_error("malloc error het_hds");
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
		{
			if (!process[i + 1])
			{
				printf("error 2\n");
				exit (EXIT_FAILURE);
			}
			proc->hd[j] = process[i + 1];
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
	int		len;

	i = 0;
	j = 0;
	proc->cmd_flag = 0;
	len = 0;
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
			len = ft_strlen(process[i]);
			proc->cmd = (char *)malloc(sizeof(process[i] + 1));
			if (!proc->cmd)
				sarah_error("malloc error get_strs");
			proc->cmd_flag = 1;
			proc->cmd = process[i];
			i++;
		}
		while (process[i] && !proc_redir(process[i]) && proc->cmd_flag != 0)
		{
			proc->str[j] = process[i];
			i++;
			j++;
		}
	}
}
