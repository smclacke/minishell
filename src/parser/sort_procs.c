/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/14 15:02:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	sort_vars(t_procs *proc, char **process)
{
	if (proc->cmd_flag == TRUE)
	{
		if (proc->str_count != 0)
		{
			proc->str = (char **)malloc(sizeof(char *)
					* (proc->str_count + 1));
			if (!proc->str)
			{
				free_procs(proc);
				return ;//malloc error
			}
		}
		get_strs(proc, process);
	}
	else
	{
		proc->cmd = NULL;
		proc->str = NULL;
	}
	if (proc->red_count != 0)
		get_reds(proc, process);
	else
		proc->redir = NULL;
	if (proc->hd_count != 0)
		get_hds(proc, process);
	else
		proc->hd = NULL;
}

void	sort_each_proc(t_procs *proc, char **proc_arr)
{
	ft_bzero(proc, sizeof(t_procs));
	proc->token_count = ft_arrlen(proc_arr);
	proc->red_count = count_reds(proc_arr);
	proc->str_count = count_strs(proc, proc_arr);
	proc->hd_count = count_hds(proc_arr);
	sort_vars(proc, proc_arr);
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
			free_util(proc, proc->proc_arrs, str, NULL); // malloc error, but no return
		if (!make_proc_arr(proc, pi, p_size))
			return ;// error
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
		return (free (proc), 0);// malloc error
	token_while(proc, proc->tokens);
	return (1);
}
