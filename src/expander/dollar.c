/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/04 17:30:34 by smclacke      ########   odam.nl         */
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

static char	*remove_first_bit(t_expand *str)
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
 * @todo fix this
 * 
 * og_str ....... iterate
 * if dollar/quote/NULL
 * substr + strjoin everything before found thing ^ into snd_str
 * look at OG_str .... iterate until found thing ^
 * what is the first thing?
 * call function on it, return 
*/
char	*dollar(t_expand *str, t_env **env)
{
	int		i = 0;

	str->input = remove_first_bit(str);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = remove_dollar_bit(str, env, (i + 1));


		// if quote, call find next quote immediately... ?

		// if (D_QUOTE)
			// D_DUOTE_expand, ret pos, i
		// if (S_QUOTE)
			// S_QUOTE EXPAND, ret pos, i
		if (!str->input)
			return (str->expanded);
	}
	return (str->expanded);
}

