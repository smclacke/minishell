/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 14:56:46 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors
*/

int	is_meta_no_pipe(char *input)
{
	if (ft_strnstr(input, MOREMORE, 2))
		return (2);
	else if (ft_strnstr(input, LESSLESS, 2))
		return (2);
	else if (ft_strnstr(input, MORE, 1))
		return (1);
	else if (ft_strnstr(input, LESS, 1))
		return (1);
	return (0);
}

/**
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
t_parser	*handle_pipe(t_parser *data, int *flag)
{
	t_parser	*tmp;

	data->meta = data->input;
	if (!data->next)
		// mini_error("syntax error near expected token 'TOKEN'", E_SYNTAX);
		return (0);
	tmp = data->next;
	if (ft_strcmp(tmp->input, PIPE) == 0)
		// mini_error("syntax error near expected token 'TOKEN'", E_SYNTAX);
		return (0);
	*flag = 0;
	return (data);
}

int	is_pipe(void *input)
{
	if (ft_strcmp(input, PIPE) == 0)
		return (1);
	return (0);
}

char	*is_redirect(void *input)
{
	if (ft_strcmp(input, MOREMORE) == 0)
		return (MOREMORE);
	else if (ft_strcmp(input, LESSLESS) == 0)
		return (LESSLESS);
	else if (ft_strcmp(input, MORE) == 0)
		return (MORE);
	else if (ft_strcmp(input, LESS) == 0)
		return (LESS);
	return (NULL);
}
