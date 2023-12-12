/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 18:52:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/12 20:00:58 by smclacke      ########   odam.nl         */
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
		printf("TOOKENS: [%i] [%s]\n", i, token[i]);
		i++;
	}
}

// void	shelly_token_print(t_parser *list)
// {
// 	t_parser	*tmp_list;
// 	int			i;

// 	tmp_list = list;
// 	i = 0;
// 	while (tmp_list)
// 	{
// 		printf("[%i] tmp_list->process->str[i] = %s\n", i, tmp_list->process->str[i]);
// 		i++;
// 		tmp_list = tmp_list->next;
// 	}
// }

void	shelly_input_print(t_parser *list)
{
	int			i;
	t_parser	*tmp_list;

	i = 0;
	tmp_list = list;
	while (tmp_list)
	{
		printf("parser list: index [%i] | node [%s]\n", i, (char *)tmp_list->input);
		i++;
		tmp_list = tmp_list->next;
	}
}



// t_parser	*print_the_full_thing(t_parser *tokens)
// {
// 	t_parser	*list;
// 	int			i;

// 	i = 0;
// 	list = tokens;
// 	while (list)
// 	{
// 		// printf("input = %s\t", list->input);
	
// 		printf("[%i]\t ", i);
// 		printf("cmd = %s\t", list->cmd);
// 		printf("file = %s\t", list->file);
// 		printf("meta = %s\t", list->meta);
// 		printf("n_pipe = %i\t", list->n_pipe);
// 		printf("str = %s\n", list->str);
// 		// printf("hd_limit = %s\n", list->hd_limit);
		
// 		//  printf("n_cmd = %i\t", list->n_cmd);
// 		// printf("hd_fd = %i\n", list->hd_fd);
// 		i++;
// 		list = list->next;
// 	}
// 	return (tokens);
// }
