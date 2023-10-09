/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 19:45:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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

static char	*copy_quoteless(char *str, char *new, int q, int j)
{
	int		i;

	i = 0;
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
	new[j] = 0;
	return (new);
}

/**
 * @brief	finds matching sets of quotes, removes them leaving
 * 			everything inside those quotes intact
*/
static char	*remove_quotes(char *str)
{
	int		j;
	int		q;
	int		len;
	char	*new;

	j = 0;
	q = 0;
	len = len_quotes(str);
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		mini_error("malloc noped", errno);
	new = copy_quoteless(str, new, q, j);
	free (str);
	return (new);
}

/**
 * @brief	if cmd has quotes, check if there is a space inside,
 * 			if so it's invalid. for cmds and strs remove closed 
 * 			quotes and returns the new cmd string, don't remove 
 * 			in case of dollar in str, expand dollar separately
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
			{
				if (!ft_isdollar(list->str))
					list->str = remove_quotes(list->str);
			}
		}
		list = list->next;
	}
}
