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
// static	void	sort_vars(t_procs *proc, char **process)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		l;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	l = 0;
// 	proc->cmd_flag = 0;
// 	proc->str = (char **)malloc(sizeof(char *) * (proc->str_count + 1));
// 	proc->redir = (char **)malloc(sizeof(char *) * (proc->red_count + 1));
// 	proc->hd = (char **)malloc(sizeof(char *) * (proc->hd_count + 1));
// 	while (process[i])
// 	{
// 		if (proc_redir(process[i]))
// 		{
// 			if (!process[i + 1])
// 			{
// 				printf("error\n");
// 				return ;
// 			}
// 			if (proc_redir(process[i]) == 2)
// 			{
// 				proc->hd[l] = process[i];
// 				proc->hd[l + 1] = process[i + 1];
// 				l += 2;
// 			}
// 			else
// 			{
// 				proc->redir[k] = process[i];
// 				proc->redir[k + 1] = process[i + 1];
// 				k += 2;
// 			}
// 			i += 2;
// 		}
// 		else if (proc->cmd_flag != 1)
// 		{
// 			proc->cmd_flag = 1;
// 			proc->cmd = process[i];
// 			i += 1;
// 		}
// 		while (process[i] && proc_redir(process[i]) == 0 && proc->cmd_flag != 0)
// 		{
// 			proc->str[j] = process[i];
// 			i++;
// 			j++;
// 		}
// 	}
// }



// void	sort_each_proc(t_parser *parser, t_procs *proc, char **proc_arr, int i)
// {
// 	int		j = 0;
// 	while (proc_arr[j])
// 	{
// 		printf("proc_arr[j] = %s\n", proc_arr[j]);
// 		j++;
// 	}
// 	parser->process = (t_procs **)malloc(sizeof(t_procs *));
// 	// bzero process
// 	parser->process[i] = (t_procs *)malloc(sizeof(t_procs));
// 	// bzero
// 	proc = parser->process[i];
// 	// int		j = 0;
// 	// while (proc_arr[j])
// 	// {
// 	// 	printf("proc_arr in sort = %s\n", proc_arr[j]);
// 	// 	j++;
// 	// }
// 	proc->token_count = ft_arrlen(proc_arr);
// 	proc->red_count = count_reds(proc_arr);
// 	proc->str_count = count_strs(proc, proc_arr);
// 	proc->hd_count = count_hds(proc_arr);
// 	sort_vars(proc, proc_arr);
// 	parser->process[i] = proc;		
// }

/**
 * @todo	norm
 * @todo	free proc_arr or tokens once sorted into proc struct
 * @todo	malloc protection 
 * @todo	bzeros?
*/
void	sort_each_proc(t_parser *parser, t_procs *proc, char **proc_arr, int i)
{
	int		token_count = ft_arrlen(proc_arr);
	int		red_count = count_reds(proc_arr);
	int		str_count = count_strs(proc_arr);
	int		hd_count = count_hds(proc_arr);

	// printf("token = %i\n red = %i\n str = %i\n hd = %i\n", token_count, red_count, str_count, hd_count);

	// proc = (t_procs **)malloc(sizeof(token_count + 1));
	// // wrap it up
	// ft_bzero(parser->process, sizeof(t_procs));

	// proc = (t_procs *)malloc(sizeof(t_procs));
	// // wrap it up
	// ft_bzero(proc, sizeof(t_procs));


	// proc[i]->token_count = ft_arrlen(proc_arr);

	parser->process = (t_procs **)malloc(sizeof(parser->proc_count + 1));
	parser->process[i] = (t_procs *)malloc(sizeof(token_count + 1));

	proc = parser->process[i];

	proc->token_count = token_count;
	printf("token_count = %i\n", proc->token_count);

	proc->red_count = red_count;
	printf("red_count = %i\n", proc->red_count);

	proc->str_count = str_count;
	printf("str_count = %i\n", proc->str_count);

	proc->hd_count = hd_count;
	printf("hd_count = %i\n", proc->hd_count);
	// sort_vars(proc, proc_arr);
	parser->process[i] = proc;
}
