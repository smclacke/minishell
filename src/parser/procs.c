/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/17 15:21:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*is_redirect(void *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (MOREMORE);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (LESSLESS);
	else if (ft_strcmp(input, MORE) == 0)
		return (MORE);
	else if (ft_strcmp(input, LESS) == 0)
		return (LESS);
	return (NULL);
}

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

/**
 * typedef struct s_tokens
{
	void					*input;
	char					*cmd;
	char					**str;
	char					*meta;
	char					*file;
	char					**hd_limit;
	int						hd_flag;
	int						flag;
	// struct s_tokens			*next;
}				t_tokens;

		// find strs
		// make list
		// add to vars
*/
static void	sort_proc(t_procs *proc, char **proc_arr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	// (void) proc;
	// printf("sort each process here\n");
	/**
	 * if meta, assign + file, otherwise cmd, then strs
	*/
	while (proc_arr[i])
	{
		printf("proc_arr[i] = [%i] %s\n", i, proc_arr[i]);
		if (is_redirect(proc_arr[i]))
		{
			proc->meta[j] = ft_strdup(proc_arr[i]);
			printf("proc->meta = %s\n", proc->meta[j]);
			j++;
		}
		i++;
	}
}

void	sort_each_proc(t_procs *proc, bool multi_proc)
{
	int		i;
	(void) proc;

	i = 0;
	if (multi_proc == true)
	{
		printf("\n");

		// while (proc->proc_arrs[i])
		// {
			// sort_proc(proc, proc->tokens);
		// 	i++;
		// }
		// return ;
	}
	else
	{
		// sort_proc(proc, proc->tokens);
		while (proc->tokens[i])
		{
			printf("meta = %s\n", proc->meta[i]);
			i++;
		}
	}
}
