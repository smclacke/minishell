/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/27 17:06:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

t_data	*handle_pipe(t_data *data, int *flag)
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
	return (NULL);
}

t_data	*init_data(t_parser *tokens)
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	ft_bzero(data, sizeof(t_data));
	tokens->data = tokens->input;
	data->input = tokens->data;
	return (data);
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
