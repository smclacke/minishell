/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 13:26:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*copy_back_and_free(char *new, char *str, int *j)
{
	new[(*j)] = '\0';
	str = ft_strcpy(str, new);
	return (str);
}

/**
 * @brief	buildt in protection
 * 			len is always given with one for the null, don't need to add here 
 * @todo	check the null malloc thingy...
*/
static char	*ft_char_malloc(int len)
{
	char	*var;

	var = (char *)malloc(sizeof(char) * len);
	if (!var)
	{
		printf("malloc noped oh no!\n");
		exit(EXIT_FAILURE);
	}
	return (var);
}

/**
 * @todo	errors NORMMMMMMMMM
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
 * 
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
	new = ft_char_malloc(ft_strlen(str) - 1);
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
	str = copy_back_and_free(new, str, &j);
	free(new);
}

static void	handle_hd_quote(t_parser *list)
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
