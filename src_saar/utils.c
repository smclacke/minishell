/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/02 21:53:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

// void	free_data(t_data *data)
// {
// 	t_data	*tmp;

// 	while (data)
// 	{
// 		tmp = data->next;
// 		free (data->cmd);
// 		free (data->meta);
// 		free (data->file);
// 		free (data->str);
// 		free (data);
// 		data = tmp;
// 	}
// }

void	free_tokens(t_parser *tokens)
{
	t_parser	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		// free_data(tokens->data);
		free (tokens);
		tokens = tmp;
	}
}
