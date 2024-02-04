/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/04 20:55:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	ft_expand(t_parser *tokens, t_env **env)
{
	t_parser	*tmp_tokens;
	t_expand	str;

	(void) str;
	(void) env;

	tmp_tokens = tokens;
	// expand_quotes(tmp_tokens); // need to fix this too...
	while (tmp_tokens)
	{
		// printf("tmp_tokens = %s\n", tmp_tokens->proc->cmd);
		expand_dollar(tmp_tokens, &str, env);
		tmp_tokens = tmp_tokens->next;
	}
	// free(tmp_tokens);
}
