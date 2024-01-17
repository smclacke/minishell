/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/17 17:56:32 by smclacke      ########   odam.nl         */
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

// static void	sort_proc(t_procs *proc)
// {
// 	int		cmd_flag;

// 	cmd_flag = 0;
// 	while (proc->input)
// 	{
// 		printf("here\n");
// 		exit(EXIT_FAILURE);
// 		if (proc_redir(proc->input))
// 		{
// 			proc->input = proc->meta;
// 			proc->input = proc->next;
// 			proc->input = proc->file;
// 		}
// 		else if (cmd_flag == 0)
// 		{
// 			cmd_flag = 1;
// 			proc->input = proc->cmd;
// 		}
// 		// else if (cmd_flag != 0)
// 		// 	proc->input = proc->str;
// 		proc->input = proc->next;
// 	}
// }

static	int	count_strs(char **process)
{
	int		i;
	int		cmd_flag;
	int		count;

	i = 0;
	cmd_flag = 0;
	count = 0;
	printf("process[i] = %s\n", process[i]);
	while (process[i])
	{
		if (proc_redir(process[i]))
			i += 2;
		if (cmd_flag != 1)
		{
			cmd_flag = 1;
			i += 1;
		}
		while (process[i] && proc_redir(process[i]) == 0 && cmd_flag != 0)
			count++;
		i++;
	}
	return (count);
}

// if if or if else??
// NEED TO REMOVE THE STR STRS BEFORE ADDINGG EVERYTING IN LIST
// ADD STR STRS TO LIST HERE...
static	void	make_str_array(t_procs *proc, char **process)
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
			i += 2;
		else if (cmd_flag != 1)
		{
			cmd_flag = 1;
			i += 1;
		}
		while (process[i] && proc_redir(process[i]) == 0 && cmd_flag != 0)
		{
			proc->str[j] = process[i];
			i++;
			j++;
		}
		// i++;
	}
}

/**
 * !!!! already got separate nodes in list but want strs in array....
*/
void	sort_each_proc(t_procs *proc, bool multi_proc)
{
	(void) proc;
	
	int		i;
	t_procs	*new_list;
	t_procs	*new_node;

	i = 0;
	new_list = (t_procs *)malloc(sizeof(t_procs));
	ft_bzero(new_list, sizeof(t_procs));
	// ignore cmds, save strs in array, then make lists...
	if (multi_proc == true)
	{
		while(proc->proc_arrs[i])
		{
		// add str strs to str var then give that back as one token...
			make_str_array(proc, proc->proc_arrs[i]);
			i++;
		}
		i = 0;
		while (proc->proc_arrs[i])
		{
			new_node = proc_listnew(proc->proc_arrs[i]);
			proc_listadd_back(&new_list, new_node);
			new_list = new_list->next;
			i++;
		}
	}
	else
	{
		// add str strs to str var then give that back as one token...
		// make_str_array(proc, proc->tokens);
		while (proc->tokens[i])
		{
			printf("proc->token[i] = %s\n", proc->tokens[i]);
			new_node = proc_listnew(proc->tokens[i]);
			proc_listadd_back(&new_list, new_node);
			new_list = new_list->next;
			i++;
		}
		print_procs(new_list);
	}
	// sort_proc(proc);
}
