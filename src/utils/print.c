/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/23 16:19:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

void	print_expand_vals(t_expand *str)
{
	printf("input\t\t\t\t\t= [%s]\n", str->input);
	printf("dollar\t\t\t\t= [%s]\n", str->dollar);
	printf("expanded\t\t\t\t\t= [%s]\n", str->expanded);
	printf("------------------------------------------------------\n");
}

void	print_procs(t_procs *proc)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	printf("cmd = %s\n", proc->cmd);
	while (i < proc->hd_count)
	{
		printf("hd[] = %s\n", proc->hd[i]);
		i++;
	}
	while (k < proc->red_count)
	{
		printf("reds[] = %s\n", proc->redir[k]);
		k++;
	}
	while (j < proc->str_count)
	{
		printf("str[] = %s\n", proc->str[j]);
		j++;
	}
}

void	print_token_arr(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		printf("token_arr: [%i] [%s]\n", i, token[i]);
		i++;
	}
	printf("------------------------------------\n");
}

void	shelly_parser_print(t_parser *list)
{
	t_parser	*tmp_list;
	int			i;

	i = 0;
	tmp_list = list;
	while (tmp_list)
	{
		printf("[%i] parser_list->process = %p\n", i, tmp_list->process);
		tmp_list = tmp_list->next;
		i++;
	}
	printf("------------------------------------\n");
}

void	print_the_full_thing(t_parser *tokens)
{
	t_parser	*list;
	int			i;
	int			j;
	int			k;
	int			l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	list = tokens;
	while (list)
	{
		printf("[%i] parser_list->process = %p\n", i, list->process);
		printf("process->input %s\n", (char *)list->process->input);
		// printf("proc_count = %i\n", list->process->proc_count);
		// while (i < list->process->proc_count)
		// {
		// 	printf("[%i]\t ", i);
		// 	printf("cmd = %s\t", list->process->cmd);
		// 	while (i < list->process->hd_count)
		// 	{
		// 		printf("proc->hd = %s\n", list->process->hd[i]);
		// 		i++;
		// 	}
		// 	while (k < list->process->red_count)
		// 	{
		// 		printf("reds[k] = %s\n", list->process->redir[k]);
		// 		k++;
		// 	}
		// 	while (j < list->process->str_count)
		// 	{
		// 		printf("str[j] = %s\n", list->process->str[j]);
		// 		j++;
		// 	}
		// }
		list = list->next;
	}
}
