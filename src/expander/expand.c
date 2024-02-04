/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/04 16:33:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// int	find_strs(t_parser *tmp, t_expand *str, int i)
// {
// 	if (tmp->proc->str_count != 0)
// 	{
// 		while (tmp->proc->str[i])
// 		{
// 			if (ft_strnstr(tmp->proc->str[i], "$", ft_strlen(tmp->proc->str[i])))
// 				set_input_and_sign(str, tmp->proc->cmd, STR)
// 		}
// 	}
// 	return (i);
// }

// int	find_hds(t_parser *tmp, t_expand *str, int i)
// {
// 	return (i);
// }

// int	find_reds(t_parser *tmp, t_expand *str, int i)
// {
	
// }

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
