/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/13 21:20:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	is_dollar(char c)
{
	return (c == '$');
}

char	*sarah_expand_dollar(char *str)
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
				if (is_dollar(str[i]) && quote == '\'')
					return (NULL);
				if (is_dollar(str[i]) && quote == '\"')
				{
					str = remove_quotes(str);
					return (str);
				}
				i++;
			}
		}
		i++;
	}
	return (str);
}


