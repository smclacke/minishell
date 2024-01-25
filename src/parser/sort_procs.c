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

/**
 * @todo	norm
 * @todo	free proc_arr or tokens once sorted into proc struct
 * @todo	malloc protection 
 * @todo	bzeros?
*/
void	sort_each_proc(t_parser *parser, char **proc_arr, int i)
{
	int		token_count = ft_arrlen(proc_arr);

	parser->process = (t_procs **)malloc(sizeof(t_procs *));
	// wrap it up
	ft_bzero(parser->process, sizeof(t_procs));
	parser->process[i] = (t_procs *)malloc(sizeof(token_count + 1));
	// wrap it up
	ft_bzero(parser->process[i], sizeof(t_procs));
	// parser->process[i]->token_count = ft_arrlen(proc_arr);
	parser->process[i]->token_count = token_count;
	printf("token_count = %i\n", parser->process[i]->token_count);
	parser->process[i]->red_count = count_reds(proc_arr);
	printf("red_count = %i\n", parser->process[i]->red_count);
	parser->process[i]->str_count = count_strs(parser->process[i], proc_arr);
	printf("str_count = %i\n", parser->process[i]->str_count);
	parser->process[i]->hd_count = count_hds(proc_arr);
	printf("hd_count = %i\n", parser->process[i]->hd_count);
	// sort_vars(parser->process[i], proc_arr);
}
