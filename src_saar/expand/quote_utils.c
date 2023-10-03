/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/03 15:24:50 by smclacke      ########   odam.nl         */
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
*/
int	len_wo_quotes(char *str, char *quote_type)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		while (!is_same_quote(str[i], quote_type))
		{
			len++;
			i++;
		}
		i++;
	}
	return (len);
}

/**
 * @brief	removes all quotations CHANGE TO REMOVE SPECIFIC TYPE OF QUOTE
*/
char	*remove_quotes(char *str, int len, char *quote_type)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (ft_isquote(str[i]))
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
