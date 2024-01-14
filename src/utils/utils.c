/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/14 18:58:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

bool	is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	shelly_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

// void	free_parser(t_parser *tokens)
// {
// 	t_parser	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		free (tokens);
// 		tokens = tmp;
// 	}
// }

// void	free_tokens(t_tokens *tokens)
// {
// 	t_tokens	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		free (tokens);
// 		tokens = tmp;
// 	}
// }
