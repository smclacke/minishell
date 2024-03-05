/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:55:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/05 14:23:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	void	handle_reds(t_parser *list)
{
	int	i;

	i = 0;
	while (i < list->proc->red_count)
	{
		if (check_qs(list->proc->redir[i])
			&& (!ft_isdollar(list->proc->redir[i])))
			remove_quotes(list->proc->redir[i]);
		i++;
	}
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
		if (ft_strnstr(list->proc->str[i], "'~'", 3))
			list->proc->tilde = TRUE;
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
	if (list->proc->red_count != 0)
		handle_reds(list);
}
