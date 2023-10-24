/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/24 17:13:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*dollar(t_exp_dol *str, t_env **env)
{
	(void)env;
	int		i = 0;
	// quotes....

// $USER$USER

	str->unassed = check_first(str);
	while (str->unassed[i])
	{
		str->unassed = check_rest(str, env, i);
		if (!str->unassed)
			return (str->assed);
		i++;
	}

	print_exp_dol_vals(str);

	return (str->assed);
}

static void	expand_dollar(t_parser *lst, t_env **env, t_exp_dol *str)
{
	int			sign;

	sign = 0;
	str->unassed = set_expand_string(lst, str, &sign);
	if (sign == 1 || sign == 2)
	{
		str->assed = dollar(str, env);
		if (sign == 1)
		{
			lst->cmd = str->assed;
			sign = 0;
		}
		else if (sign == 2)
		{
			lst->str = str->assed;
			sign = 0;
		}
	}
}

void	ft_expand(t_parser *tokens, t_env **env)
{
	t_parser	*lst;
	t_exp_dol	*str;

	lst = tokens;
	str = (t_exp_dol *)malloc(sizeof(*str));
	if (!str)
		mini_error("malloc error exp_dol struct", errno);
	ft_bzero(str, sizeof(t_exp_dol));
	expand_quotes(lst);
	while (lst)
	{
		expand_dollar(lst, env, str);
		lst = lst->next;
	}
}
