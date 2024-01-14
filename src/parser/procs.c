/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/14 20:47:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	get_procs(t_procs *proc)
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
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	while (proc->tokens[i])
	{
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
		{
			if (!proc->tokens[i + 1] || is_pipe(proc->tokens[i + 1]))
			{
				proc->proc_size = (i - start) + 1;
				proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc->proc_size + 1));
				proc_j = 0;
				while (start <= i)
				{
					proc->token_size = ft_strlen(proc->tokens[start]);
					proc->proc_arrs[proc_i][proc_j] = (char *)malloc(sizeof(char) * (proc->token_size + 1));
					proc->proc_arrs[proc_i][proc_j] = proc->tokens[start];
					start++;
					proc_j++;
				}
				proc->proc_arrs[proc_i][proc_j] = NULL;
				proc_i++;
			}
			i++;
		}
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
			i++;
		start = i;
	}
	proc->proc_arrs[proc_i] = NULL;
}

static void	sort_proc(char **proc)
{
	(void) proc;
	printf("sort each process here\n");
	return ;
}

void	sort_each_proc(t_procs *proc, bool multi_proc)
{
	int		i;
	// (void)	proc;

	i = 0;
	if (multi_proc == true)
	{
		printf("more\n");
		while (proc->proc_arrs[i])
		{
			sort_proc(proc->proc_arrs[i]);
			i++;
		}
		return ;
	}
	else
	{
		printf("just one\n");
		sort_proc(proc->tokens);
	}
}
