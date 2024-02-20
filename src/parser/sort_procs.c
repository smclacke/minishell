/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/20 16:49:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// norm
static	int	sort_vars(t_procs *proc, char **process)
{
	if (proc->cmd_flag == TRUE)
	{
		if (proc->str_count != 0)
		{
			proc->str = (char **)malloc(sizeof(char *)
					* (proc->str_count + 1));
			if (!proc->str)
				malloc_error(NULL, proc, NULL, 1);
		}
		if (get_strs(proc, process) == E_STOP)
			return (E_STOP);
	}
	else
	{
		proc->cmd = NULL;
		proc->str = NULL;
	}
	if (proc->red_count != 0)
	{
		if (get_reds(proc, process) == E_STOP)
			return (E_STOP);
	}
	else
		proc->redir = NULL;
	if (proc->hd_count != 0)
	{
		if (get_hds(proc, process) == E_STOP)
			return (E_STOP);
	}
	else
		proc->hd = NULL;
	return (0);
}

int	sort_each_proc(t_procs *proc, char **proc_arr)
{
	ft_bzero(proc, sizeof(t_procs));
	proc->token_count = ft_arrlen(proc_arr);
	if (proc->token_count == E_STOP)
		return (E_STOP);
	proc->red_count = count_reds(proc_arr);
	if (proc->red_count == E_STOP)
		return (E_STOP);
	proc->str_count = count_strs(proc, proc_arr);
	if (proc->str_count == E_STOP)
		return (E_STOP);
	proc->hd_count = count_hds(proc_arr);
	if (proc->hd_count == E_STOP)
		return (E_STOP);
	if (sort_vars(proc, proc_arr) == E_STOP)
		return (E_STOP);
	return (0);
}

static	void	token_while(t_parser *proc, char **str)
{
	int		i;
	int		pi;
	int		p_size;

	i = 0;
	pi = 0;
	p_size = 0;
	while (str[i])
	{
		proc->start = i;
		while (str[i] && !is_pipe(str[i]))
			i++;
		p_size = ft_abs(i - proc->start);
		proc->proc_arrs[pi] = (char **)malloc(sizeof(char *) * (p_size + 1));
		if (!proc->proc_arrs)
			malloc_error(proc, NULL, str, 2);
		if (!make_proc_arr(proc, pi, p_size))
			general_error("error parsing input");
		proc->proc_arrs[pi][p_size] = NULL;
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
		{
			i++;
			pi++;
		}
	}
}

int	get_procs(t_parser *proc)
{
	proc->proc_arrs = (char ***)malloc(sizeof(char **)
			* (proc->proc_count + 1));
	if (!proc->proc_arrs)
		malloc_error(proc, NULL, NULL, 0);
	token_while(proc, proc->tokens);
	return (1);
}
