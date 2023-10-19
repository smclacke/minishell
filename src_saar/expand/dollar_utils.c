/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:18:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 20:20:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*check_if_expand(char *str)
{
	int		i;
	int		quote;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote = quote_type(str[i]);
			i++;
			while (str[i] && !ft_isquote(str[i]))
			{
				if (ft_dollar(str[i]) && quote == '\'')
					return (NULL);
				if (ft_dollar(str[i]) && quote == '\"')
					return (str);
				i++;
			}
		}
		i++;
	}
	return (str);
}

char	*set_expand_string(t_parser *lst, t_exp_dol *str, int *sign)
{
	t_parser		*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (ft_strnstr(tmp->cmd, "$", ft_strlen(tmp->cmd)))
			{
				*sign = 1;
				str->unassed = tmp->cmd;
			}
		}
		else if (tmp->str)
		{
			if (ft_strnstr(tmp->str, "$", ft_strlen(tmp->str)))
			{
				*sign = 2;
				str->unassed = tmp->str;
			}
		}
		tmp = tmp->next;
	}
	return (str->unassed);
}
