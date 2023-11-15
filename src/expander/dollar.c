/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/15 21:02:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*save_first_input(t_expand *str, char *input, int i)
{
	str->expanded = ft_substr(input, 0, i);
	if (!str->expanded)
		return (input);
	input = ft_strtrim(input, str->expanded);
	return (input);
}

char	*first_bit(t_expand *str, char *input)
{
	int		i = 0;
	
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	if (is_dollar_or_quote(input[i]))
		input = save_first_input(str, input, i);
	return (input);
}

/**
 * get first part of string, then loop through separating dollars and quotes...
 * @todo fix this, leaks, norm, test test test...
 * write version (or have func for here_doc and only edit that bit)
*/
char	*dollar(t_expand *str, t_env **env)
{
	int		i = 0;

	str->input = first_bit(str, str->input);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, str->input, env, (i + 1));
		if (ft_issquote(str->input[i]))
		{
			i = squote_bit(str, str->input, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
		if (ft_isdquote(str->input[i]))
			i = dquote_bit(str, str->input, env, (i + 1));
		if (!str->input[i])
			return (str->expanded);
	}
	return (str->expanded);
}
