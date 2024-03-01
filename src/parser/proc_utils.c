/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proc_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 16:20:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 18:29:45 by smclacke      ########   odam.nl         */
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
			if (!process[i + 1] || !ft_spaced(process[i + 1]))
				return (syntax_error("near unexpected token 'newline'"));
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
	count = 0;
	while (process[i])
	{
		if (shelly_strcmp(process[i], PIPE) == 0)
			return (i - 1);
		if (proc_redir(process[i]))
		{
			if (!process[i + 1] || !ft_spaced(process[i + 1]))
				return (syntax_error("near unexpected token 'newline'"));
			i += 2;
		}
		else if (proc->cmd_flag != 1)
			i = set_flag(proc, i);
		while (process[i] && count_str_util(proc, process, i))
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	count_hds(char **process)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (process[i])
	{
		if (proc_redir(process[i]) == 2)
		{
			if (!(process[i + 1]) || !ft_spaced(process[i + 1]))
				return (syntax_error("near unexpected token 'newline'"));
			count += 1;
		}
		i++;
	}
	return (count);
}

int	proc_redir(char *input)
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

int	make_proc_arr(t_parser *proc, int proc_i, int proc_size)
{
	int		proc_j;

	proc_j = 0;
	while (proc_j < proc_size)
	{
		if (!proc->tokens[proc->start])
		{
			free_util(proc, proc->proc_arrs, proc->proc_arrs[proc_i], NULL);
			free_parser(proc);
			return (0);
		}
		proc->proc_arrs[proc_i][proc_j] = ft_strdup(proc->tokens[proc->start]);
		if (!proc->proc_arrs[proc_i][proc_j])
		{
			free_util(proc, proc->proc_arrs, proc->proc_arrs[proc_i], NULL);
			free_parser(proc);
			return (0);
		}
		proc_j++;
		proc->start++;
	}
	return (1);
}
