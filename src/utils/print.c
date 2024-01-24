/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 13:17:01 by smclacke      ########   odam.nl         */
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
	while (index < proc->proc_count)
	{
		printf("[%i] cmd = %s\n", index, proc->process[index]->cmd);
		printf("--------------------------------------------------\n");
		printf("hd_count = %i\n", proc->process[index]->hd_count);
		while (i < proc->process[index]->hd_count)
		{
			printf("[%i] hd[%i] = %s\n", index, i, proc->process[index]->hd[i]);
			i++;
		}
		printf("--------------------------------------------------\n");
		printf("red_count = %i\n", proc->process[index]->red_count);
		while (k < proc->process[index]->red_count)
		{
			printf("[%i] reds[k] = %s\n", index, k, proc->process[index]->redir[k]);
			k++;
		}
		printf("--------------------------------------------------\n");
		printf("str_count = %i\n", proc->process[index]->str_count);
		while (j < proc->process[index]->str_count)
		{
			printf("[%i] str[j] = %s\n", index, j, proc->process[index]->str[j]);
			j++;
		}
		printf("--------------------------------------------------\n");
		index++;
	}
}
