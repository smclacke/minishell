/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/17 16:25:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param head parser linked list
 * @param sign int passed to check is string or command
 * @brief checks if string or command and sets str to content of parser node
*/
static t_exp_dol	*set_expand_string(t_parser *head, int *sign)
{
	t_exp_dol		*str;

	str = NULL;
	if (head->cmd != NULL)
	{
		if (ft_strnstr(head->cmd, "$", ft_strlen(head->cmd)))
		{
			*sign = 1;
			str->unassed = head->cmd;
		}
	}
	else if (head->str != NULL)
	{
		if (ft_strnstr(head->str, "$", ft_strlen(head->str)))
		{
			*sign = 2;
			str->unassed = head->str;
		}
	}
	printf("unassed = %s\n", str->unassed);
	return (str);
}

/**
 * @param head parser linked list
 * @param env environment linked list
 * @param exp expander struct
 * @brief checks parser node if command or string part has something
 * to expand. assign expanded string back to command or string part of node.
*/
static void	expand_dollar(t_parser *head, t_env **env)
{
	// int			len;
	int			sign;
	t_exp_dol	*str;
	(void)	env;

	sign = 0;
	// init_exp_dol_struct(str);
	str = set_expand_string(head, &sign);
	// if (sign == 1 || sign == 2)
	// {
	// 	len = ft_strlen(str);
	// 	str = dollar(str, env, exp, len);
	// 	if (sign == 1)
	// 	{
	// 		head->cmd = str;
	// 		sign = 0;
	// 	}
	// 	else if (sign == 2)
	// 	{
	// 		head->str = str;
	// 		sign = 0;
	// 	}
	// }
}


/**
 * @param lst linked list from parser
 * @param env environment linked list
 * @brief checks if there's a meta or a builtin
*/
void	ft_expand(t_parser *lst, t_env **env)
{
	t_parser	*head;

	head = lst;
	while (head)
	{
		expand_dollar(head, env);
		head = head->next;
	}
	head = lst;
	while (head)
	{
		check_for_meta(head);
		if (check_for_builtin(head))
			do_builtin(head, env);
		head = head->next;
	}
}
