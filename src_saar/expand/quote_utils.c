/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 17:54:11 by smclacke      ########   odam.nl         */
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

static int	quote_type(int str)
{
	if (str == '\'')
		return ('\'');
	else if (str == '\"')
		return ('\"');
	return (0);
}

/**
 * @brief	length of string without the quotes that are going to be removed
 * 			encounter a quote, find matching, remove both, keep everything
 * 			inside those quotes intact
*/
static int	len_quotes(char *str)
{
	int	i;
	int	q;
	int	len;

	i = 0;
	q = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
		{
			len++;
			i++;
		}
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
			{
				len++;
				i++;
			}
		}
		if (ft_isquote(str[i]) && str[i] == q)
			i++;
	}
	return (len);
}

/**
 * @brief	finds matching sets of quotes, removes them leaving
 * 			everything inside those quotes intact
*/
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		q;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	q = 0;
	len = len_quotes(str);
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		mini_error("malloc noped", STDERR_FILENO);
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
		{
			new[j] = str[i];
			i++;
			j++;
		}
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
			{
				new[j] = str[i];
				i++;
				j++;
			}
		}
		if (ft_isquote(str[i]) && str[i] == q)
			i++;
	}
	free (str);
	new[j] = 0;
	return (new);
}
