/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/05 15:04:16 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/shelly.h"

/**
 * @todo comment
 * handle quotes without dollars, then handle any string with dollars
 * 	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
void	ft_expand(t_parser *tokens, t_env **env)
{
	t_parser	*tmp_tokens;
	t_expand	*str;

	tmp_tokens = tokens;
	str = (t_expand *)malloc(sizeof(*str));
	if (!str)
		return ;
	ft_bzero(str, sizeof(t_expand));
	expand_quotes(tmp_tokens);
	while (tmp_tokens)
	{
		expand_dollar(tmp_tokens, env, str);
		tmp_tokens = tmp_tokens->next;
	}
	free(str);
	free(tmp_tokens);
}
