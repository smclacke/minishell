/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proc_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 16:20:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/16 19:49:48 by smclacke      ########   odam.nl         */
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
				syntax_error("syntax error near unexpected token 'newline'");
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
		if (proc_redir(process[i]))
		{
			if (!process[i + 1])
				syntax_error("syntax error near unexpected token 'newline'");
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
				syntax_error("syntax error near unexpected token 'newline'");
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
	int		token_size;

	proc_j = 0;
	token_size = 0;
	while (proc_j < proc_size)
	{
		if (!proc->tokens[proc->start])
		{
			free_util(proc, proc->proc_arrs, proc->proc_arrs[proc_i], NULL);
			free_parser(proc);
			return (0);
		}
		token_size = ft_strlen(proc->tokens[proc->start]);
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
