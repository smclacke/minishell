/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/02 18:59:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

void	print_expand_vals(t_expand *str)
{
	printf("input\t\t\t\t\t= [%s]\n", str->input);
	printf("do_expand\t\t\t\t= [%s]\n", str->do_expand);
	printf("dont_expand\t\t\t\t= [%s]\n", str->dont_expand);
	printf("expanded\t\t\t\t\t= [%s]\n", str->expanded);
	printf("done\t\t\t\t\t= [%s]\n", str->done);
	printf("------------------------------------------------------\n");
}

void	shelly_print_list(t_parser *token)
{
	t_parser	*list;

	list = token;
	while (list)
	{
		printf("lexer list: [%s]\n", (char *)list->input);
		list = list->next;
	}
}

t_parser	*shelly_parser_print(t_parser *tokens)
{
	t_parser	*list;
	int			i;

	i = 0;
	list = tokens;
	while (list)
	{
		printf("parser list: index [%i] | node [%s]\n", i, (char *)list->input);
		i++;
		list = list->next;
	}
	return (tokens);
}

t_parser	*print_the_full_thing(t_parser *tokens)
{
	t_parser	*list;
	int			i = 0;

	list = tokens;
	while (list)
	{
		printf("[%i]\t ", i);
		// printf("input = %s\t", list->input);
		printf("cmd = %s\t", list->cmd);
		printf("file = %s\t", list->file);
		printf("meta = %s\t", list->meta);
		printf("str = %s\n", list->str);
		//  printf("n_cmd = %i\t", list->n_cmd);
		// printf("hd_fd = %i\n", list->hd_fd);
		i++;
		list = list->next;
	}
	return (tokens);
}
