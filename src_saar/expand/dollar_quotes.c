/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/11 15:40:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	is_dollar(int c)
{
	return (c == '$');
}

// char	*handle_dollar_qs(char *str)
// {
// 	printf("str = %s\n", str);
// 	return (str);
// }

// expand(char *str)

/***
 * when i check quotes
 * 
 * if quotes and !dollar, handle... 
 * 
*/

/**
 * for when dollar is inside quotes, remove the quotes...
 * if dollar inside, "$USER" remove, $USER"HELLO"
 * 
*/
// char	*fix_up(char *str)
// {
	
// }

/**
 * if !expand, fix up for return and immediately return str
 * 
 * if expand how to handle abc"$USER"hello ????????????
*/

int	sarah_expand_dollar(char *str)
{
	int		i = 0;
	int		quote;

	while (str[i])
	{
		while (str[i] && !is_dollar(str[i]))
		{
			if (ft_isquote(str[i]))
			{
				quote = quote_type(str[i]);
				if (quote == '\'')
					return (0);
				else
					return (1);
			}
			i++;
		}
	}
	return (1);
}


