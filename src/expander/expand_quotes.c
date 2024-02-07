/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/07 18:18:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*copy_back(char *new, char *str, int *j)
{
	new[(*j)] = '\0';
	str = ft_strcpy(str, new);
	if (!str)
		return (NULL); // copy/malloc error
	return (str);
}

/**
 * @todo	norm
 * @todo	maybe use mini struct and save some vars to help norm
 * @brief	minus one for malloc cause - 2 for quotes for str size then plus one
 * 			for null dus - 1 uiteindelijk
*/
static void	remove_quotes(t_parser *list, char *str)
{
	char		*new;	

	list->i = 0;
	list->j = 0;
	list->q = 0;
	new = (char *)malloc(sizeof(ft_strlen(str) - 1));
	if (!new)
		return ; // malloc error
	while (str[list->i])
	{
		while (str[list->i] && !ft_isquote(str[list->i]))
			copy_and_increment(new, str, &list->i, &list->j);
		if (ft_isquote(str[list->i]))
		{
			list->q = quote_type(str[list->i]);
			list->i++;
			while (str[list->i] && str[list->i] != list->q)
				copy_and_increment(new, str, &list->i, &list->j);
			if (ft_isquote(str[list->i]) && str[list->i] == list->q)
				list->i++;
		}
	}
	str = copy_back(new, str, &list->j);
	free(new);
}

static	void	handle_hd(t_parser *list)
{
	int		i;

	i = 0;
	while (i < list->proc->hd_count)
	{
		if (check_qs(list->proc->hd[i]) && (!ft_isdollar(list->proc->hd[i])))
		{
			list->hd_flag = 1;
			remove_quotes(list, list->proc->hd[i]);
		}
		i++;
	}
}

static	void	handle_str(t_parser *list)
{
	int		i;

	i = 0;
	while (i < list->proc->str_count)
	{
		if (check_qs(list->proc->str[i]) && (!ft_isdollar(list->proc->str[i])))
			remove_quotes(list, list->proc->str[i]);
		i++;
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
	if (list->proc->cmd && check_qs(list->proc->cmd))
	{
		if (!check_space(list->proc->cmd) && !ft_isdollar(list->proc->cmd))
			remove_quotes(tokens, list->proc->cmd);
	}
	if (list->proc->hd_count != 0)
		handle_hd(list);
	if (list->proc->str_count != 0)
		handle_str(list);
}
