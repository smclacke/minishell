/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/06 15:07:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	ft_expand(t_parser *tokens, t_env **env)
{
	t_parser	*tmp_tokens;
	t_expand	str;
	
	tmp_tokens = tokens;
	expand_quotes(tmp_tokens);
	while (tmp_tokens)
	{
		expand_dollar(tmp_tokens, &str, env);
		tmp_tokens = tmp_tokens->next;
	}
	free(tmp_tokens);
}
