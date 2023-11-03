/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_expand.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/03 22:28:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo make it do the thing, norm it, leak proof it, comment it, error it
*/

static char	*save_first_input(t_expand *str, int i)
{
	str->expanded = ft_substr(str->input, 0, i);
	if (!str->expanded)
		return (str->input);
	str->input = ft_strtrim(str->input, str->expanded);
	return (str->input);
}

char	*remove_first_bit(t_expand *str)
{
	int		i = 0;
	
	while (str->input[i] && !ft_dollar(str->input[i])\
		&& !ft_isquote(str->input[i]))
		i++;
	if (ft_dollar(str->input[i]) || ft_isquote(str->input[i]))
		str->input = save_first_input(str, i);
	return (str->input);
}




static void	dollar_expand(t_expand *str, t_env **env)
{
	str->dollar = ft_strtrim(str->dollar, "$");
	if (!get_check_value(str, env))
		str->expanded = ft_strjoin(str->expanded, str->dollar);
	else
		str->dollar = NULL;
}

// dollar_expand
int	remove_dollar_bit(t_expand *str, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	while (str->input[i] && !ft_dollar(str->input[i])\
		&& !ft_isquote(str->input[i]))
		i++;
	if (ft_dollar(str->input[i]) || ft_isquote(str->input[i]))
		end = i;
	else 
		end = i;
	str->dollar = ft_substr(str->input, start, end);
	dollar_expand(str, env);
	return (i);
}


// dquote_expand

// squote_expand

// call save_this() on expanded strs to add them to done_str, 
// and ret left over input to dollar()


// is dollar or quote func....
// int		is_dollar_or_quote(int c)
// {
	
// }
