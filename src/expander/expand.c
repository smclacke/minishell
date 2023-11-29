/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/29 17:19:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo comment
*/
void	ft_expand(t_parser *tokens, t_env **env)
{
	t_parser	*lst;
	t_expand	*str;

	lst = tokens;
	str = (t_expand *)malloc(sizeof(*str));
	if (!str)
		mini_error("malloc error expand struct", errno);
	ft_bzero(str, sizeof(t_expand));
	expand_quotes(lst);
	while (lst)
	{
		expand_dollar(lst, env, str);
		lst = lst->next;
	}
	free(str);
}
