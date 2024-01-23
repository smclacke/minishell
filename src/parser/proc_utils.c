/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proc_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 16:20:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/23 16:45:40 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	count_reds(char **process)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (process[i])
	{
		if (proc_redir(process[i]) && proc_redir(process[i]) != 2)
		{
			if (!process[i + 1])
			{
				printf("error\n");
				return (EXIT_FAILURE);
			}
			count += 2;
		}
		i++;
	}
	return (count);
}

int	count_strs(t_procs *proc, char **process)
{
	int		i;
	int		count;

	i = 0;
	proc->cmd_flag = 0;
	count = 0;
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			if (!process[i + 1])
			{
				printf("error\n");
				return (EXIT_FAILURE);
			}
			i += 2;
		}
		else if (proc->cmd_flag != 1)
		{
			proc->cmd_flag = 1;
			i += 1;
		}
		while (process[i] && proc_redir(process[i]) == 0 && proc->cmd_flag != 0)
		{
			count++;
			i++;
		}
	}
	return (count);
}

int		count_hds(char **process)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
			count += 2;
		i++;
	}
	return (count);
}

int		proc_redir(char *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (1);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (2);
	else if (ft_strcmp(input, MORE) == 0)
		return (3);
	else if (ft_strcmp(input, LESS) == 0)
		return (4);
	return (0);
}

