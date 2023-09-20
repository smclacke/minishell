/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:45:59 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/20 20:09:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*which_quote(char *input)
{
	if (ft_strnstr(input, SINGLE_Q, 1))
		return (SINGLE_Q);
	else if (ft_strnstr(input, DOUBLE_Q, 1))
		return (DOUBLE_Q);
	return (0);
}

int	next_quote(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

bool	is_meta(char *input)
{
	if (ft_strnstr(input, MOREMORE, 2))
		return (true);
	else if (ft_strnstr(input, LESSLESS, 2))
		return (true);
	else if (ft_strnstr(input, MORE, 1))
		return (true);
	else if (ft_strnstr(input, LESS, 1))
		return (true);
	else if (ft_strnstr(input, PIPE, 1))
		return (true);
	return (false);
}

int	ft_ismeta(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_token(char *input)
{
	if (*input == '|')
		return (1);
	if (*input == '<')
	{
		if (!ft_strncmp(input, "<<", 2))
			return (1);
		return (2);
	}
	else if (*input == '>')
	{
		if (!ft_strncmp(input, ">>", 2))
			return (1);
		return (2);
	}
	return (0);
}
