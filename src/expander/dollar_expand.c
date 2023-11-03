/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_expand.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/03 18:57:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo all of this shitt...
*/



/**
 * @todo how to use both these but in my loopyyloopy
*/
static char	*save_first_input(t_expand *str, int i)
{
	str->expanded = ft_substr(str->input, 0, i);
	if (!str->expanded)
		return (str->input);
	str->input = ft_strtrim(str->input, str->expanded);
	return (str->input);
}

static void	dollar_expand(t_expand *str, char *dollar)
{
	str->expanded = dollar;
	// just expand the strrrrrrrrrrrr
}

// dollar_expand
char	*remove_dollar_bit(t_expand *str)
{
	int		i;

	i = 0;
	while (str->input[i] && !ft_dollar(str->input[i])\
		&& !ft_isquote(str->input[i]))
		i++;
	if (ft_dollar(str->input[i]) || ft_isquote(str->input[i]))
	{
		str->dollar = ft_substr(str->input, 0, i);
		if (!str->dollar)
			mini_error("some thing is wrong", errno);
	}
	str->input = ft_strtrim(str->input, str->dollar);
	if (!str->input)
		return (NULL);
	dollar_expand(str, str->dollar);
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

// dquote_expand

// squote_expand

// call save_this on expanded strs to add them to done_str, 
// and ret left over input to dollar()

// is dollar or quote func....

// int		is_dollar_or_quote(int c)
// {
	
// }


// char	*expandable(t_expand *str)
// {
// 	int		i = 1;

// 	while (str->input[i] && !ft_dollar(str->input[i])\
// 		&& !ft_isquote(str->input[i]))
// 		i++;
// 	if (ft_dollar(str->input[i]) || ft_isquote(str->input[i]))
// 		str->do_expand = 
// }