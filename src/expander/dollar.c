/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/04 22:44:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*save_first_input(t_expand *str, int i)
{
	str->expanded = ft_substr(str->input, 0, i);
	if (!str->expanded)
		return (str->input);
	str->input = ft_strtrim(str->input, str->expanded);
	return (str->input);
}

char	*first_bit(t_expand *str)
{
	int		i = 0;
	
	while (str->input[i] && !is_dollar_or_quote(str->input[i]))
		i++;
	if (is_dollar_or_quote(str->input[i]))
		str->input = save_first_input(str, i);
	return (str->input);
}

/**
 * get first part of string, then loop through separating dollars and quotes...
 * @todo fix this, leaks, norm, test test test...
 * write version (or have func for here_doc and only edit that bit)
*/
char	*dollar(t_expand *str, t_env **env)
{
	int		i = 0;

	str->input = first_bit(str);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, env, (i + 1));
		if (ft_issquote(str->input[i]))
		{
			i = squote_bit(str, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, i);
		}
		if (ft_isdquote(str->input[i]))
			i = dquote_bit(str, env, (i + 1));
		if (!str->input)
			return (str->expanded);
	}
	return (str->expanded);
}
