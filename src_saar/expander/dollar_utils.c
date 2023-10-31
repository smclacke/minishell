/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:18:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 19:39:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo don't think this is necessary anymore...
*/
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

