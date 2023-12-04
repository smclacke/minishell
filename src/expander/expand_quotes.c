/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 16:44:27 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo errors NORMMMMMMMMM
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/

static void	remove_quotes(char *str)
{
	int			i;
	int			j;
	int			q;
	size_t		len;
	char		*new;	

	i = 0;
	j = 0;
	q = 0;
	len = (ft_strlen(str) - 2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		// mini_error("malloc noped", errno);
		return ;
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
			if (ft_isquote(str[i]) && str[i] == q)
				i++;
		}
	}
	new[j] = '\0';
	str = ft_strcpy(str, new);
	free(new);
}

static void		handle_hd_quote(t_parser *list)
{
	if (check_quotes(list->hd_limit))
	{
		list->hd_flag = 1;
		if (!ft_isdollar(list->hd_limit))
			remove_quotes(list->hd_limit);
	}
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
		if (list->cmd && check_quotes(list->cmd))
		{
			if (!check_space(list->cmd) && !ft_isdollar(list->cmd))
				remove_quotes(list->cmd);
		}
		else if (list->str || list->hd_limit)
		{
			if (list->hd_limit)
				handle_hd_quote(list);
			else if (list->str)
			{
				if (check_quotes(list->str) && (!ft_isdollar(list->str)))
						remove_quotes(list->str);
			}
		}
		list = list->next;
	}
}
