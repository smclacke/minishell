/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/12 16:01:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	init_type_struct(t_data_type *type)
{
	type->input = NULL;
	type->cmd = NULL;
	type->strs = NULL;
	type->meta = NULL;
	type->file = NULL;
	type->next = NULL;
}

t_data_type	*init_data(void)
{
	t_data_type		*data;

	data = (t_data_type *)malloc(sizeof(t_data_type));
	if (!data)
		exit(EXIT_FAILURE);
	init_type_struct(data);
	return (data);
}

char	*is_redirect(void *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (MOREMORE);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (LESSLESS);
	else if (ft_strcmp(input, MORE) == 0)
		return (MORE);
	else if (ft_strcmp(input, LESS) == 0)
		return (LESS);
	else if (ft_strcmp(input, PIPE) == 0)
		return (PIPE);
	return (NULL);
}

t_parser	*shelly_parser_print(t_parser *tokens)
{
	t_parser	*list;
	int			i;

	i = 0;
	list = tokens;
	while (list)
	{
		printf("parser list: index [%i] | node [%s]\n", i, list->input);
		i++;
		list = list->next;
	}
	return (tokens);
}
