/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/04 11:04:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	free_expand_struct(t_expand *str)
{
	if (str->input)
		free(str->input);
	if (str->tmp)
		free(str->tmp);
	if (str->string)
		free(str->string);
	if (str->dollar)
		free(str->dollar);
	if (str->s_quote)
		free(str->s_quote);
	if (str->d_quote)
		free(str->d_quote);
	if (str->env_val)
		free(str->env_val);
	if (str->expanded)
		free(str->expanded);
	if (str->h_d)
		free(str->h_d);
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
	free(str);
}
