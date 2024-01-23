/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/23 14:16:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	sort_vars(t_procs *proc, char **process)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	proc->cmd_flag = 0;
	proc->str = (char **)malloc(sizeof(char *) * (proc->str_count + 1));
	proc->redir = (char **)malloc(sizeof(char *) * (proc->red_count + 1));
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			proc->redir[k] = process[i];
			if (!process[i + 1])
			{
				printf("error\n");
				return ;
			}
			proc->redir[k + 1] = process[i + 1];
			k += 2;
			i += 2;
		}
		else if (proc->cmd_flag != 1)
		{
			proc->cmd_flag = 1;
			proc->cmd = process[i];
			i += 1;
		}
		while (process[i] && proc_redir(process[i]) == 0 && proc->cmd_flag != 0)
		{
			proc->str[j] = process[i];
			i++;
			j++;
		}
	}
}

void	sort_each_proc(t_procs *proc)
{
	(void) proc;
	
	int		i;
	// t_procs	*new_list;
	// t_procs	*new_node;

	i = 0;
	// new_list = (t_procs *)malloc(sizeof(t_procs));
	// ft_bzero(new_list, sizeof(t_procs));
	// ignore cmds, save strs in array, then make lists...
	if (proc->multi_proc_b == TRUE)
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
		proc->token_count = ft_arrlen(proc->tokens);
		proc->red_count = count_reds(proc->tokens);
		proc->str_count = count_strs(proc, proc->tokens);
		sort_vars(proc, proc->tokens);
		printf("proc->cmd = %s\n", proc->cmd);
		int	j = 0;
		int	k = 0;
		while (k < proc->red_count)
		{
			printf("reds[k] = %s\n", proc->redir[k]);
			k++;
		}
		while (j < proc->str_count)
		{
			printf("str[j] = %s\n", proc->str[j]);
			j++;
		}		
	}
}
