/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/23 13:34:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	get_procs(t_procs *proc)
{
	int		i;
	int		start;
	int		end;
	int		proc_i;
	int		proc_j;

	i = 0;
	start = 0;
	end = 0;
	proc_i = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * proc->proc_count);
	if (!proc->proc_arrs)
	{
		printf("maloc fucked proc_arrs\n");
		return (1);
	}
	while (proc->tokens[i])
	{
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
		{
			if (proc->tokens[i + 1] == NULL || is_pipe(proc->tokens[i + 1]))
			{
				proc->proc_size = i - start;
				proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc->proc_size + 1));
				if (!proc->proc_arrs[proc_i])
				{
					printf("maloc fucked proc_arrs\n");
					return (1);
				}
				proc_j = 0;
				while (start <= i && proc_j <= proc->proc_size)
				{
					proc->token_size = ft_strlen(proc->tokens[start]);
					proc->proc_arrs[proc_i][proc_j] = (char *)malloc(sizeof(char) * (proc->token_size + 1));
					if (!proc->proc_arrs[proc_i][proc_j])
					{
						printf("maloc fucked proc_arrs\n");
						return (1);
					}
					ft_strcpy(proc->proc_arrs[proc_i][proc_j], proc->tokens[start]);
					printf("proc->arr[%i][%i] = %s\n", proc_i, proc_j, proc->proc_arrs[proc_i][proc_j]);
					start++;
					proc_j++;
				}
				printf("-------------------------------\n");
				proc_i++;
			}
			i++;
		}
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
			i++;
		start = i;
	}
	return (0);
}

static	int	count_strs(char **process)
{
	int		i;
	int		cmd_flag;
	int		count;

	i = 0;
	cmd_flag = 0;
	count = 0;
	while (process[i])
	{
		printf("process[i] = %s\n", process[i]);
		// if (proc_redir(process[i]))
		// 	i += 2;
		// if (cmd_flag != 1)
		// {
		// 	cmd_flag = 1;
		// 	i += 1;
		// }
		// while (process[i] && proc_redir(process[i]) == 0 && cmd_flag != 0)
		// 	count++;
		i++;
	}
	count = 2;
	return (count);
}

static	void	sort_vars(t_procs *proc, char **process)
{
	int		i;
	int		j;
	int		cmd_flag;
	int		count;

	i = 0;
	j = 0;
	cmd_flag = 0;
	count = count_strs(process);
	proc->str = (char **)malloc(sizeof(char *) * (count + 1));
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			proc->meta = process[i];
			proc->file = process[i + 1];
			i += 2;
		}
		else if (cmd_flag != 1)
		{
			cmd_flag = 1;
			proc->cmd = process[i];
			i += 1;
		}
		while (process[i] && proc_redir(process[i]) == 0 && cmd_flag != 0)
		{
			proc->str[j] = process[i];
			i++;
			j++;
		}
	}
}

void	sort_each_proc(t_procs *proc, bool multi_proc)
{
	(void) proc;
	
	int		i;
	// t_procs	*new_list;
	// t_procs	*new_node;

	i = 0;
	// new_list = (t_procs *)malloc(sizeof(t_procs));
	// ft_bzero(new_list, sizeof(t_procs));
	// ignore cmds, save strs in array, then make lists...
	if (multi_proc == true)
	{
		// while(proc->proc_arrs[i])
		// {
		// 	make_str_array(proc, proc->proc_arrs[i]);
		// 	i++;
		// }
		// sort rest of the tokens
		// sort_proc(proc); / does this work for ***procs? or only tokens...
		return ;
	}
	else
	{
		sort_vars(proc, proc->tokens);
		// int		count = ft_arr_len(proc->tokens);
		// i = 0;
		// int	j = 0;
		// while (i < count)
		// {
		// 	printf("cmd = %s\n", proc->cmd);
		// 	printf("meta = %s\n", proc->meta);
		// 	printf("file = %s\n", proc->file);
		// 	while (proc->str[j])
		// 	{
		// 		printf("str[j] = %s\n", proc->str[j]);
		// 		j++;
		// 	}
		// 	i++;
		// }
	}
}
