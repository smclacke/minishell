/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/28 23:05:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief	length of string without any quotations
*/
int	len_wo_quotes(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
		{
			i++;
			len++;
		}
		if (str[i] && ft_isquote(str[i]))
			i++;
	}
	return (len);
}

/**
 * @brief	removes any/all quotations
*/
char	*remove_quotes(char *str, int len)
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
