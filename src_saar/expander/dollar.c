/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/31 15:43:30 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*dollar(t_expand *str, t_env **env)
{
	(void)env;
	int		i = 0;

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

	return (str->done);
}

void	expand_dollar(t_parser *lst, t_env **env, t_expand *str)
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
