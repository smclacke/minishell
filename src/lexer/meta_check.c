/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 20:05:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/27 14:05:06 by smclacke      ########   odam.nl         */
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


// || (ft_strnstr(input, "|>""", 3))
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
		}
		if (meta_help(input[i]) == 3)
		{
			if (!input[i + 1] || (input[i + 1] && meta_help(input[i + 1] == 3)))
				return (syntax_error("near unexpected token 'newline'"));
		}
		i++;
	}
	return (1);
}
