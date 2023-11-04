/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/04 17:30:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo make it do the thing, norm it, leak proof it, comment it, error it
*/
static void	dollar_expand(t_expand *str, t_env **env)
{
	str->dollar = ft_strtrim(str->dollar, "$");
	if (!get_check_value(str, env))
		str->expanded = ft_strjoin(str->expanded, str->dollar);
	else
		str->dollar = NULL;
}

int	remove_dollar_bit(t_expand *str, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	while (str->input[i] && !is_dollar_or_quote(str->input[i]))
		i++;
	end = i - start;
	str->dollar = ft_substr(str->input, start, end);
	dollar_expand(str, env);
	return (i);
}


// dquote_expand

// squote_expand


