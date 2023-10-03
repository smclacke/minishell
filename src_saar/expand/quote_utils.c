/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/03 17:13:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	are there any quotes?
*/
int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief	are there spaces inside the quotation?
*/
int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief	length of string without any of the first quote type
 * 			but ec''h""o like = 4...
*/
int	len_quotes(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (is_same_quote(str[i], quote_type))
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

/**
 * while quote is not closed... remve/keep quotes
 * if quote is closed, renew process for many other quotes..
 * e""ch''o = echo :)
 * the next of the same is the closing quote...
 * ignore anything inside
*/

/**
 * @brief	removes type of quotations given in quote_type
*/
char	*remove_quotes(char *str, int len)
{
	int		i;
	int		j;
	char	*new;
	int		len;
	char	*quote_type;
	

	i = 0;
	j = 0;
	// len = len_wo_quotes(str, quote_type);
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (ft_isquote(str[i]))
			quote_type = which_quote(str[i]);
		if (is_same_quote(str[i], quote_type)) 
			i++;
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	new[j] = 0;
	return (new);
}
