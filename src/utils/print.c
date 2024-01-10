/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/10 21:04:50 by smclacke      ########   odam.nl         */
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

void	shelly_tokenlst_print(t_tokens *list)
{
	t_tokens	*tmp_list;
	int			i;

	i = 0;
	tmp_list = list;
	while (tmp_list)
	{
		printf("[%i] tokenlst process->node = [%s]\n", i, (char *)tmp_list->input);
		tmp_list = tmp_list->next;
		i++;
	}
	printf("------------------------------------\n");
}

void	shelly_parser_print(t_parser *list)
{
	int			i;
	t_parser	*tmp_list;

	i = 0;
	tmp_list = list;
	while (tmp_list)
	{
		while (tmp_list->process)
		{
			printf("[%i] parser_print list->process->node = [%s]\n", i, (char *)tmp_list->process->input);
			tmp_list->process = tmp_list->process->next;
			i++;
		}
		tmp_list = tmp_list->next;
	}
	printf("------------------------------------\n");
}
