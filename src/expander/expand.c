/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/04 17:17:41 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * adding expanded str back into correct parser struct var
 * @todo comment
*/
static void	expand_dollar(t_parser *lst, t_env **env, t_expand *str)
{
	str->input = set_expand_string(lst, str);
	if (str->sign == 1 || str->sign == 2 || str->sign == 3)
	{
		str->expanded = dollar(str, env);
		if (!str->expanded)
			mini_error("str->expanded noped", errno);
		if (str->sign == 1)
		{
			lst->cmd = str->expanded;
			str->sign = 0;
		}
		else if (str->sign == 2)
		{
			lst->str = str->expanded;
			str->sign = 0;
		}
		else if (str->sign == 3)
		{
			lst->file = str->expanded;
			str->sign = 0;
		}
	}
}

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
}
