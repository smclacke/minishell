/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 19:21:07 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/20 14:58:45 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	exit_exp(t_parser *par, t_expand *str)
{
	char	*tmp;
	char	*exit_code;

	exit_code = ft_itoa(par->exit_code);
	if (!exit_code)
		malloc_error(NULL, NULL, NULL, 0);
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, exit_code);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		tmp = ft_strdup(exit_code);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free(str->expanded);
	str->expanded = tmp;
	free(exit_code);
	if (!str->expanded)
		general_error("expansion failure");
}

static int	ft_isunder(int c)
{
	if (c == '_')
		return (1);
	return (0);
}

int	ex_str(int c)
{
	if (ft_isalnum(c) || ft_isunder(c))
		return (1);
	return (0);
}

int	is_dollar_or_quote(int c)
{
	return (ft_dollar(c) || ft_isquote(c));
}
