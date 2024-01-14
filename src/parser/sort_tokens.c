/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_tokens.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/14 18:42:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * char ** proc;
 * 
 * proc[0] = [echo] [hi]
 * proc[1] = [cd] [..]
*/

void	get_procs(t_procs *proc)
{
	int	i = 0;

	while (proc->tokens[i])
	{
		printf("tokens = %s\n", proc->tokens[i]);
		i++;
	}

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
			i++;
		proc->proc_size = i - start;
		proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc->proc_size + 1));
		proc_j = 0;
		while (start <= i)
		{
			proc->proc_arrs[proc_i][proc_j] = proc->tokens[start];
			start++;
			proc_j++;
		}
		proc_i++;
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
			i++;
		start = i;
	}
	proc->proc_arrs[proc_i] = 0;
	// proc_i = 0;
	// proc_start = 0;
	// proc_end = 0;
	// while (tokens && tokens[proc_end])
	// {
	// 	while (tokens[proc_end] && !is_pipe(tokens[proc_end]))
	// 		proc_end++;	
	// 	proc_size = proc_end - proc_start;
	// 	printf("proc_size = %i\n", proc_size);
	// 	proc = (char *)malloc(sizeof(char) * (proc_size + 1));
	// 	while (proc_start < proc_end)
	// 	{
	// 		proc[proc_i] = tokens[proc_start];
	// 		proc_start++;
	// 		proc_i++;
	// 	}
	// 	proc_start = proc_end;
	// }
}
