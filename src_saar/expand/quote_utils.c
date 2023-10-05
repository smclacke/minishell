/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 16:34:53 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/04 15:36:39 by smclacke      ########   odam.nl         */
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
 * encounter quote, find matching, remove those
 * encounter quote....
 * till end of str
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
	printf("len = %i\n", len);
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
			printf("q = %i\n", q);
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


/**
 * @brief	length of string without any of the first quote type
 * 			but ec''h""o like = 4...
*/
// int	len_quotes(char *str)
// {
// 	int		len;
// 	int		i;
// 	char	*quote_type;

// 	len = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_isquote(str[i]))
// 		{
// 			quote_type = which_quote(&str[i]);
// 			i++;
// 		}
// 		if (is_same_quote(str[i], quote_type))
// 			i++;
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

/**
 * this doesn't work
 * to do:
 * fix it
*/

/**
 * @brief	removes type of quotations given in quote_type
*/
// char	*remove_quotes(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*new;
// 	char	*quote_type;
	

// 	i = 0;
// 	j = 0;
// 	len = len_quotes(str);
// 	new = (char *)malloc(sizeof(char) * (len + 1));
// 	while (str[i])
// 	{
// 		if (ft_isquote(str[i]))
// 		{
// 			quote_type = which_quote(&str[i]);
// 			i++;
// 		}
// 		if (is_same_quote(str[i], quote_type)) 
// 			i++;
// 		new[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	new[j] = 0;
// 	return (new);
// }


/**
 * while quote is not closed... remve/keep quotes
 * if quote is closed, renew process for many other quotes..
 * e""ch''o = echo :)
 * the next of the same is the closing quote...
 * ignore anything inside
*/

/**
 * what am i actually doing?
 * 
 * find matching quote
 * get rid of those quotes
 * next quote
 * find matching quote
 * get rid of those quotes
 * 
*/