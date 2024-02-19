/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 19:21:07 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/19 19:13:02 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// $? expanded = exit_code
// echo $? = 0 if success, just replace str with exit_code digit (probs itoa)
// void	check_exit(t_parser *tmp, t_expand *str, t_env **env)
// {
// 	if (tmp->proc->cmd)
// 	{
// 		if (ft_strcmp(tmp->proc->cmd, "$?") == 0)
// 		{
// 			free(tmp->proc->cmd);
// 			tmp->proc->cmd = ft_strdup("$?");
// 			if (!tmp->proc->cmd)
// 				malloc_error(tmp, NULL, NULL, 0);
// 		}
// 	}
// }

static int	ft_isunder(int c)
{
	if (c == '_')
		return (1);
	return (0);
}

int	ex_str(int c)
{
	if (ft_isalnum(c) || ft_isunder(c))
		return (1);
	return (0);
}

int	is_dollar_or_quote(int c)
{
	return (ft_dollar(c) || ft_isquote(c));
}
