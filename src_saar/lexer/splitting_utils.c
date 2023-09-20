/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:45:59 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/20 13:26:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	next_quote(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

// can i combine is_meta and is_token and just use one of these?

// int		ft_is_meta(int c)
// {
// 	return (c == '|');
// }

bool	is_meta(char *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (true);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (true);
	else if (ft_strcmp(input, MORE) == 0)
		return (true);
	else if (ft_strcmp(input, LESS) == 0)
		return (true);
	else if (ft_strcmp(input, PIPE) == 0)
		return (true);
	return (false);
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
