/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/22 18:23:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

t_data_type		*handle_pipe(t_data_type *data, int *flag)
{
	data->meta = data->input;
	*flag = 0;
	return (data);
}

int	is_pipe(void *input)
{
	if (ft_strcmp(input, PIPE) == 0)
		return (1);
	return (0);
}

t_data_type	*init_data(t_parser *tokens)
{
	t_data_type		*data;

	data = (t_data_type *)malloc(sizeof(t_data_type));
	if (!data)
		exit(EXIT_FAILURE);
	ft_bzero(data, sizeof(t_data_type));
	tokens->data_type = tokens->input;
	data->input = tokens->data_type;
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
	// else if (ft_strcmp(input, PIPE) == 0) // don't know if i use this somewhere else
	// 	return (PIPE); // but so far not causing a problem
	// dont want to check pipe in parser so...
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
