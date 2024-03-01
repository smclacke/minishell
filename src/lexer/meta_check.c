/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 20:05:11 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 18:28:31 by smclacke      ########   odam.nl         */
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

static	int	check_metas(char *input, int i)
{
	if (!input[i] || (input[i]
			&& meta_help(input[i]) == 3))
		return (syntax_error("near unexpected token 'newline'"));
	else
	{
		if ((input[i] && ft_isspace(input[i])
				&& (input[i + 1] && meta_help(input[i + 1]) != 0))
			|| !input[i + 1])
			return (syntax_error("near unexpected token 'newline'"));
		if (meta_help(input[i + 1]) != 0 && meta_help(input[i + 2]) != 0)
			return (syntax_error("near unexpected token 'newline'"));
		while (input[i] && ft_isspace(input[i]))
		{
			i++;
			if (meta_help(input[i]) == 1 || meta_help(input[i]) == 2)
				return (syntax_error("near unexpected token 'newline'"));
		}
	}
	return (i);
}

static	int	check_pipe(char *input, int i)
{
	if (!input[i] || (input[i]
			&& meta_help(input[i] == 3)))
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
			i = check_metas(input, (i + 1));
			if (i == E_STOP)
				return (E_STOP);
		}
		if (meta_help(input[i]) == 3)
		{
			i = check_pipe(input, (i + 1));
			if (i == E_STOP)
				return (E_STOP);
		}
		i++;
	}
	return (1);
}
