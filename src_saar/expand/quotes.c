/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 18:29:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static void	increment(int *len, int *i)
{
	(*len)++;
	(*i)++;
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
			increment(&len, &i);
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
				increment(&len, &i);
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
static char	*remove_quotes(char *str)
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
		mini_error("malloc noped", errno);
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
		{
			new[j] = str[i];
			increment(&i, &j);
		}
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
			{
				new[j] = str[i];
				increment(&i, &j);
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
 * @brief	if cmd has quotes, check if there is a space inside,
 * 			if so it's invalid. for cmds and strs remove closed 
 * 			quotes and returns the new cmd string
*/
void	expand_quotes(t_parser *tokens)
{
	t_parser	*list;

	list = tokens;
	while (list)
	{
		if (list->cmd)
		{
			if (check_quotes(list->cmd))
			{
				if (!check_space(list->cmd))
					list->cmd = remove_quotes(list->cmd);	
			}
		}
		if (list->str)
		{
			if (check_quotes(list->str))
				list->str = remove_quotes(list->str);
		}
		list = list->next;
	}
}
