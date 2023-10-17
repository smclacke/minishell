/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:18:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 19:32:11 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// put in libft...
int	is_dollar(char c)
{
	return (c == '$');
}

char	*check_if_expand(char *str)
{
	int		i;
	int		quote;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote = quote_type(str[i]);
			i++;
			while (str[i] && !ft_isquote(str[i]))
			{
				if (is_dollar(str[i]) && quote == '\'')
					return (NULL);
				if (is_dollar(str[i]) && quote == '\"')
					return (str);
				i++;
			}
		}
		i++;
	}
	return (str);
}

char	*set_expand_string(t_parser *lst, t_exp_dol *str, int *sign)
{
	t_parser		*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (ft_strnstr(tmp->cmd, "$", ft_strlen(tmp->cmd)))
			{
				*sign = 1;
				str->unassed = tmp->cmd;
			}
		}
		else if (tmp->str)
		{
			if (ft_strnstr(tmp->str, "$", ft_strlen(tmp->str)))
			{
				*sign = 2;
				str->unassed = tmp->str;
			}
		}
		tmp = tmp->next;
	}
	return (str->unassed);
}

// bool	check_for_builtin(t_parser *node)
// {
// 	if (!node)
// 		return (false);
// 	if (mini_strcmp(node->cmd, "exit") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->cmd, "echo") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->cmd, "cd") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->cmd, "pwd") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->cmd, "export") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->cmd, "unset") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->cmd, "env") == 0)
// 		return (true);
// 	else
// 		return (false);
// }

// bool	check_for_meta(t_parser *node)
// {
// 	if (!node)
// 		return (false);
// 	else if (mini_strcmp(node->meta, ">>") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->meta, "<<") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->meta, ">") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->meta, "<") == 0)
// 		return (true);
// 	else if (mini_strcmp(node->meta, "|") == 0)
// 		return (true);
// 	else
// 		return (false);
// }
