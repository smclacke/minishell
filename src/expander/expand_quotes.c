/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/07 16:35:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*copy_back(char *new, char *str, int *j)
{
	new[(*j)] = '\0';
	str = ft_strcpy(str, new);
	if (!str)
		return (NULL);
	return (str);
}

/**
 * @todo	norm
 * @todo	maybe use mini struct and save some vars to help norm
 * @brief	minus one for malloc cause - 2 for quotes for str size then plus one
 * 			for null dus - 1 uiteindelijk
*/
static void	remove_quotes(char *str)
{
	int			i;
	int			j;
	int			q;
	char		*new;	

	i = 0;
	j = 0;
	q = 0;
	new = (char *)malloc(sizeof(ft_strlen(str) - 1));
	if (!new)
		return ; // malloc error
	while (str[i])
	{
		while (str[i] && !ft_isquote(str[i]))
			copy_and_increment(new, str, &i, &j);
		if (ft_isquote(str[i]))
		{
			q = quote_type(str[i]);
			i++;
			while (str[i] && str[i] != q)
				copy_and_increment(new, str, &i, &j);
			if (ft_isquote(str[i]) && str[i] == q)
				i++;
		}
	}
	str = copy_back(new, str, &j);
	free(new);
}

/**
 * @todo	norm
 * @brief	if cmd has quotes, check if there is a space inside,
 * 			if so it's invalid. for cmds and strs remove closed 
 * 			quotes and returns the new cmd string, don't remove 
 * 			in case of dollar in str, expand dollar separately
*/
void	expand_quotes(t_parser *tokens)
{
	t_parser	*list;
	int			i;

	list = tokens;
	i = 0;
	if (list->proc->cmd && check_quotes(list->proc->cmd))
	{
		if (!check_space(list->proc->cmd) && !ft_isdollar(list->proc->cmd))
			remove_quotes(list->proc->cmd);
	}
	if (list->proc->hd_count != 0)
	{
		// handle_hd()
		while (i < list->proc->hd_count)
		{
			if (check_quotes(list->proc->hd[i]) && (!ft_isdollar(list->proc->hd[i])))
			{
				list->hd_flag = 1;
				remove_quotes(list->proc->hd[i]);
			}
			i++;
		}
	}
	i = 0;
	if (list->proc->str_count != 0)
	{
		// handle_str()
		while (i < list->proc->str_count)
		{
			if (check_quotes(list->proc->str[i]) && (!ft_isdollar(list->proc->str[i])))
				remove_quotes(list->proc->str[i]);
			i++;
		}
	}
}
