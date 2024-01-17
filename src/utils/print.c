/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/17 17:36:28 by smclacke      ########   odam.nl         */
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

void	print_procs(t_procs *procs)
{
	t_procs	*list;
	
	list = procs;
	while (list)
	{
		printf("proc list = %s\n", (char *)list->input);
		list = list->next;
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

t_parser	*print_the_full_thing(t_parser *tokens)
{
	t_parser	*list;
	int			i;
	int			j;

	i = 0;
	j = 0;
	list = tokens;
	while (list)
	{
		printf("[%i]\t ", i);
		printf("cmd = %s\t", list->process->cmd);
		while (list->process->str[j])
		{
			printf("str = %s\t", list->process->str[j]);
			j++;
		}
		printf("meta = %s\t", list->process->meta);
		printf("file = %s\n", list->process->file);
		i++;
		list = list->next;
	}
	return (tokens);
}
