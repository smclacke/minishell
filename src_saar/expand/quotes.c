/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/10 13:36:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
char	*remove_quotes(char *str)
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

static	void	dollar_quotes(t_parser *tokens)
{
	t_parser	*list;

	list = tokens;
	while (list)
	{
		if (list->str)
		{
			if (check_quotes(list->str) && ft_isdollar(list->str))
				list->str = handle_dollar_qs(list->str);
		}
		else if (list->cmd)
		{
			if (check_quotes(list->cmd && ft_isdollar(list->cmd)))
				list->cmd = handle_dollar_qs(list->cmd);
		}
		list = list->next;
	}
}

/**
 * @brief	if cmd has quotes, check if there is a space inside,
 * 			if so it's invalid. for cmds and strs remove closed 
 * 			quotes and returns the new cmd string, don't remove 
 * 			in case of dollar in str, expand dollar separately
*/
static void	cmd_str_quotes(t_parser *tokens)
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
		else if (list->str)
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

void	expand_quotes(t_parser *tokens)
{
	cmd_str_quotes(tokens);
	// dollar_quotes(tokens);
}
