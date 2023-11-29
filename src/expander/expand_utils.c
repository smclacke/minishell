/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/29 16:19:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/shelly.h"

int	is_dollar_or_quote(int c)
{
	return (ft_dollar(c) || ft_isquote(c));
}

/**
 * @param env expander struct
 * @param exp environmet linked list
 * @brief checks environment value of string to be expanded
 * if there is no value it free's the comp_str and env_value.
 * @return 1 if there is no value, 0 if value is found and assigned
 * @todo triple check protection, norm and sooo when less tired
*/
int	get_check_value(t_expand *str, t_env **env)
{
	t_env	*head;
	int		len;

	head = *env;
	if (!str->dollar || !head->key)
		return (1);
	while (head)
	{
		if (mini_strcmp(str->dollar, head->key) == 0)
		{
			if (!head->value)
				return (1);
			len = ft_strlen(head->value);
			str->env_val = ft_substr(head->value, 0, len);
			if (!str->env_val)
				return (1);
			str->dollar = str->env_val;
			return (0);
		}
		head = head->next;
	}
	return (1);
}

/**
 * @todo commmennntttt
*/
char	*set_expand_string(t_parser *lst, t_expand *str)
{
	t_parser		*tmp;

	tmp = lst;
	str->sign = 0;
	if (tmp->cmd && ft_strnstr(tmp->cmd, "$", ft_strlen(tmp->cmd)))
	{
		str->sign = 1;
		str->input = tmp->cmd;
	}
	else if (tmp->str && ft_strnstr(tmp->str, "$", ft_strlen(tmp->str)))
	{
		str->sign = 2;
		str->input = tmp->str;
	}
	else if (tmp->file && ft_strnstr(tmp->file, "$", ft_strlen(tmp->file)))
	{
		str->sign = 3;
		str->input = tmp->file;
	}
	return (str->input);
}
