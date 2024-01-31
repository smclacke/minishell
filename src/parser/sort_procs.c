/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_procs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 16:47:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/25 14:45:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo	protect all mallocs
 * @todo	if no str/redir/hd, free the memory
 * @todo	norm - if red // make red arr func(), if hd // make hd arr func ().... 
*/
static	void	sort_vars(t_procs *proc, char **process)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	proc->cmd_flag = 0;
	proc->str = (char **)malloc(sizeof(char *) * (proc->str_count + 1));
	proc->redir = (char **)malloc(sizeof(char *) * (proc->red_count + 1));
	proc->hd = (char **)malloc(sizeof(char *) * (proc->hd_count + 1));
	while (process[i])
	{
		if (proc_redir(process[i]))
		{
			if (!process[i + 1])
			{
				printf("error 1\n");
				return ;
			}
			if (proc_redir(process[i]) == 2)
			{
				proc->hd[l] = process[i];
				proc->hd[l + 1] = process[i + 1];
				l += 2;
			}
			else
			{
				proc->redir[k] = process[i];
				proc->redir[k + 1] = process[i + 1];
				k += 2;
			}
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
	// process[i + 1] = NULL;
}

/**
 * @todo	norm
 * @todo	free proc_arr or tokens once sorted into proc struct
 * @todo	malloc protection 
 * @todo	bzeros?
*/
void	sort_each_proc(t_procs *proc, char **proc_arr)
{
	// t_procs		*proc_tmp;
	int			token_count = ft_arrlen(proc_arr);
	int			red_count = count_reds(proc_arr);
	int			str_count = count_strs(proc_arr);
	int			hd_count = count_hds(proc_arr);

	printf("where?\n");
	// proc[i] = (t_procs *)malloc(sizeof(t_procs));

	// proc_tmp = proc;

	proc->token_count = token_count;
	printf("->token_count = %i\n", proc->token_count);

	proc->red_count = red_count;
	printf("->red_count = %i\n", proc->red_count);

	proc->str_count = str_count;
	printf("->str_count = %i\n", proc->str_count);

	proc->hd_count = hd_count;
	printf("->hd_count = %i\n", proc->hd_count);

	sort_vars(proc, proc_arr);
	// print_procs(proc);
	// proc = proc_tmp;
	// free(proc_tmp);
}
