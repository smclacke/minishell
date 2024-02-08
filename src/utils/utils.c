/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/08 17:33:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * norrrrrmmmmmmmmm 
 */
void	free_procs(t_procs *proc)
{
	int			i;

	if (proc == NULL)
		return ;
	i = 0;
	if (proc->cmd)
		free(proc->cmd);
	if (proc->str_count != 0)
	{
		while (i < proc->str_count)
		{
			free(proc->str[i]);
			i++;
		}
	}
	i = 0;
	if (proc->hd_count != 0)
	{
		while (i < proc->hd_count)
		{
			free(proc->hd[i]);
			i++;
		}
	}
	i = 0;
	if (proc->red_count != 0)
	{
		while (i < proc->red_count)
		{
			free(proc->redir[i]);
			i++;
		}
	}
}

/**
 * norrrrrmmmmmmmmm 
 */
void	free_parser(t_parser *procs)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	while (procs)
	{
		tmp = procs->next;
		if (procs->tokens)
			ft_free_arr(procs->tokens);
		if (procs->proc_arrs)
		{
			while (i < procs->proc_count)
			{
				ft_free_arr(procs->proc_arrs[i]);
				i++;
			}
			free(procs->proc_arrs);
		}
		if (procs->process)
			free(procs->process);
		if (procs->proc)
		{
			free_procs(procs->proc);
			free(procs->proc);
		}
		free(procs);
		procs = tmp;
	}
	free(procs);
}

void	free_util(t_parser *list, t_procs *proc, char **arr, char *str)
{
	if (str)
		free(str);
	if (arr)
		ft_free_arr(arr);
	if (proc)
		free(proc);
	if (list)
		free(list);
}
