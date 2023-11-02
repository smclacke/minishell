/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_expand.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/02 21:03:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo all of this shitt...
*/



/**
 * @todo how to use both these but in my loopyyloopy
*/
static char	*save_input(t_expand *str, int i)
{
	str->done = ft_substr(str->input, 0, i);
	if (!str->done)
		return (str->input);
	str->input = ft_strtrim(str->input, str->done);
	return (str->input);
}

// dollar_expand
char	*dollar_expand(char *str)
{
	int		i;

	i = 0;
	
	str->input = save_input(str, i);
	return (str->input);
}

// // dollar_expand
// char	*dollar_expand(char *str)
// {
	
// }

char	*save_dollar(t_expand *str, int i)
{
	str->do_expand =

	// expand_dollar() 
	// return rest of input
}

char	*check_first(t_expand *str)
{
	int		i = 0;
	
	while (str->input[i] && !ft_dollar(str->input[i])\
		&& !ft_isquote(str->input[i]))
		i++;
	if (ft_dollar(str->input[i]) || ft_isquote(str->input[i]))
		str->input = save_input(str, i);
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