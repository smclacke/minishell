/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/31 16:00:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// TOO LONGGGGGGG

/**
 * dollar could be cmd, str or file.. need to save which to return expanded 
 * back to correct var in parser struct
*/
char	*set_expand_string(t_parser *lst, t_expand *str, int *sign)
{
	t_parser		*tmp;

	tmp = lst;
	if (tmp->cmd)
	{
		if (ft_strnstr(tmp->cmd, "$", ft_strlen(tmp->cmd)))
		{
			*sign = 1;
			str->input = tmp->cmd;
		}
	}
	else if (tmp->str)
	{
		if (ft_strnstr(tmp->str, "$", ft_strlen(tmp->str)))
		{
			*sign = 2;
			str->input = tmp->str;
		}
	}
	else if (tmp->file)
	{
		if (ft_strnstr(tmp->file, "$", ft_strlen(tmp->file)))
		{
			*sign = 3;
			str->input = tmp->file;
		}
	}
	return (str->input);
}

/**
 * get first part of string, then loop through separating dollars and quotes...
*/
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

/**
 * adding expanded str back into correct parser struct var
*/
void	expand_dollar(t_parser *lst, t_env **env, t_expand *str)
{
	int			sign;

	sign = 0;
	str->input = set_expand_string(lst, str, &sign);
	if (sign == 1 || sign == 2 || sign == 3)
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
		else if (sign == 3)
		{
			lst->file = str->done;
			sign = 0;
		}
	}
}
