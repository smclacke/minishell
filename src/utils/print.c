/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 19:43:41 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * @todo	comment out all
*/
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

void	print_expand_vals(t_expand *str)
{
	printf("input\t\t\t\t\t= [%s]\n", str->input);
	printf("dollar\t\t\t\t= [%s]\n", str->dollar);
	printf("expanded\t\t\t\t\t= [%s]\n", str->expanded);
	printf("------------------------------------------------------\n");
}

void	print_proc_arrs(t_parser *parser)
{
	int		i = 0;

	printf("proc count = %i\n", parser->proc_count);
	while (i <= parser->proc_count)
	{
		int		j = 0;
		int		proc_size = ft_arrlen(parser->proc_arrs[i]);
		while (j <= proc_size)
		{
			printf("proc_arrs[%i][%i] = %s\n", i, j, parser->proc_arrs[i][j]);
			j++;
		}
		i++;
	}
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
	printf("--------------------------------------------------\n");
	printf("hd_count = %i\n", proc->hd_count);
	while (i < proc->hd_count)
	{
		printf("hd[%i] = %s\n", i, proc->hd[i]);
		i++;
	}
	printf("--------------------------------------------------\n");
	printf("red_count = %i\n", proc->red_count);
	while (k < proc->red_count)
	{
		printf("reds[%i] = %s\n", k, proc->redir[k]);
		k++;
	}
	printf("--------------------------------------------------\n");
	printf("str_count = %i\n", proc->str_count);
	while (j < proc->str_count)
	{
		printf("str[%i] = %s\n", j, proc->str[j]);
		j++;
	}
	printf("--------------------------------------------------\n");
}

void	print_parser(t_parser *proc)
{
	int	i;
	int	j;
	int	k;
	int	index;

	i = 0;
	j = 0;
	k = 0;
	index = 0;
	printf("--------------------------------------------------\n");
	printf("proc_count = %i\n", proc->proc_count);
	printf("--------------------------------------------------\n");
	printf("proc->cmd = %s\n", proc->proc[0].cmd);
	printf("--------------------------------------------------\n");
	while (index <= proc->proc_count)
	{
		printf("hd_count = %i\n", proc->proc[index].hd_count);
		while (i < proc->proc[index].hd_count)
		{
			printf("[%i] hd[%i] = %s\n", index, i, proc->proc[index].hd[i]);
			i++;
		}
		printf("--------------------------------------------------\n");
		printf("red_count = %i\n", proc->proc[index].red_count);
		while (k < proc->proc[index].red_count)
		{
			printf("[%i] reds[%i] = %s\n", index, k, proc->proc[index].redir[k]);
			k++;
		}
		printf("--------------------------------------------------\n");
		printf("str_count = %i\n", proc->proc[index].str_count);
		while (j < proc->proc[index].str_count)
		{
			printf("[%i] str[%i] = %s\n", index, j, proc->proc[index].str[j]);
			j++;
		}
		printf("--------------------------------------------------\n");
		index++;
	}
}
