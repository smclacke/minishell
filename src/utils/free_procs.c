/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 22:51:10 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/26 19:06:07 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

static void	free_reds(t_procs *proc)
{
	int	i;

	i = 0;
	while (i < proc->red_count)
	{
		free(proc->redir[i]);
		i++;
	}
	free(proc->redir);
}

static void	free_hds(t_procs *proc)
{
	int	i;

	i = 0;
	while (i < proc->hd_count)
	{
		free(proc->hd[i]);
		i++;
	}
	free(proc->hd);
}

static void	free_str(t_procs *proc)
{
	int	i;

	i = 0;
	while (i < proc->str_count)
	{
		free(proc->str[i]);
		i++;
	}
	free(proc->str);
}

void	free_procs(t_procs *proc)
{
	if (proc == NULL)
		return ;
	if (proc->cmd)
		free(proc->cmd);
	if (proc->str_count != 0)
		free_str(proc);
	if (proc->hd_count != 0)
		free_hds(proc);
	if (proc->red_count != 0)
		free_reds(proc);
	free(proc);
}

void	free_util(t_parser *list, char ***arrs, char **arr, char *str)
{
	if (str)
		free(str);
	if (arr)
		ft_free_arr(arr);
	if (arrs)
		free(arrs);
	if (list)
		free(list);
}
