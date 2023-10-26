/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/26 17:47:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*dollar(t_expand *str, t_env **env)
{
	(void)env;
	int		i = 0;
	// quotes....

// $USER$USER

	str->input = check_first(str);
	while (str->input[i])
	{
		str->input = check_rest(str, env, i);
		if (!str->input)
			return (str->expanded);
		i++;
	}
	if (!str->input)
		return (0);
	// print_expand_vals(str);
	printf("str->expanded = %s\n", str->expanded);
	printf("str->done = %s\n", str->done);

	return (str->done);
}

static void	expand_dollar(t_parser *lst, t_env **env, t_expand *str)
{
	int			sign;

	sign = 0;
	str->input = set_expand_string(lst, str, &sign);
	if (sign == 1 || sign == 2)
	{
		str->done = dollar(str, env);
		if (sign == 1)
		{
			lst->cmd = str->done;
			sign = 0;
		}
		else if (sign == 2)
		{
			lst->str = str->done;
			sign = 0;
		}
	}
}

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
