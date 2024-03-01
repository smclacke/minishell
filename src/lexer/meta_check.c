/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 20:05:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 14:51:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	meta_help(int c)
{
	if (c == '<')
		return (1);
	if (c == '>')
		return (2);
	if (c == '|')
		return (3);
	return (0);
}

static	int	check_pipe(char *input, int i)
{
	if (!input[i + 1] || (input[i + 1]
			&& meta_help(input[i + 1] == 3)))
		return (syntax_error("near unexpected token 'newline'"));
	else
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (meta_help(input[i]) == 3 || !input[i])
			return (syntax_error("near unexpected token 'newline'"));
	}
	return (i);
}

int	meta_check(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (meta_help(input[i]) == 1 || meta_help(input[i]) == 2)
		{
			if (!input[i + 1] || (input[i + 1]
					&& meta_help(input[i + 1]) == 3))
				return (syntax_error("near unexpected token 'newline'"));
			else
			{
				while (input[i] && ft_isspace(input[i]))
					i++;
				if (meta_help(input[i]) != 0 || !input[i])
					return (syntax_error("near unexpected token 'newline'"));
			}
		}
		if (meta_help(input[i]) == 3)
		{
			i = check_pipe(input, i);
			// if (!input[i + 1] || (input[i + 1]
			// 		&& meta_help(input[i + 1] == 3)))
			// 	return (syntax_error("near unexpected token 'newline'"));
			// else
			// {
			// 	while (input[i] && ft_isspace(input[i]))
			// 		i++;
			// 	if (meta_help(input[i]) == 3 || !input[i])
			// 		return (syntax_error("near unexpected token 'newline'"));
			// }
		}
		i++;
	}
	return (1);
}
