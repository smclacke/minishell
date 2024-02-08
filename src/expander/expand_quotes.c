/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/08 21:00:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static void	increment(int *len, int *i)
{
	(*len)++;
	(*i)++;
}

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

static	void	handle_hd(t_parser *list)
{
	int		i;

	i = 0;
	while (i < list->proc->hd_count)
	{
		if (check_qs(list->proc->hd[i]) && (!ft_isdollar(list->proc->hd[i])))
		{
			list->hd_flag = 1;
			remove_quotes(list->proc->hd[i]);
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
			remove_quotes(list->proc->str[i]);
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
			remove_quotes(list->proc->cmd);
	}
	if (list->proc->hd_count != 0)
		handle_hd(list);
	if (list->proc->str_count != 0)
		handle_str(list);
}
