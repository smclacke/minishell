/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 17:34:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	add_to_expand(t_expand *str, char *copy_str)
{
	char	*tmp;

	if (!copy_str)
		return (-1);
	if (str->expanded)
		tmp = ft_strjoin(str->expanded, copy_str);
	else
		tmp = ft_strdup(copy_str);
	free(str->expanded);
	str->expanded = tmp;
	free(copy_str);
	if (!str->expanded)
		return (-1);
	return (0);
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
	str->env_val = NULL;
	while (head)
	{
		if (shelly_strcmp(str->dollar, head->key) == 0)
		{
			if (!head->value)
				return (1);
			len = ft_strlen(head->value);
			str->env_val = ft_substr(head->value, 0, len);
			if (!str->env_val)
			{
				free(str->env_val);
				return (1);
			}
			return (0);
		}
		head = head->next;
	}
	return (1);
}

static void	set_input_and_sign(t_expand *str, char *input_type, int type)
{
	str->sign = type;
	str->input = input_type;
}

int	set_expand_string(t_parser *lst, t_expand *str)
{
	t_parser	*tmp;

	str->sign = 0;
	str->input = NULL;
	tmp = lst;
	if (!tmp)
		return (0);
	if (tmp->cmd && ft_strnstr(tmp->cmd, "$", ft_strlen(tmp->cmd)))
	{
		set_input_and_sign(str, tmp->cmd, CMD_X);
		return (1);
	}
	else if (tmp->str && ft_strnstr(tmp->str, "$", ft_strlen(tmp->str)))
	{
		set_input_and_sign(str, tmp->str, STR_X);
		return (1);
	}
	else if (tmp->file && ft_strnstr(tmp->file, "$", ft_strlen(tmp->file)))
	{
		set_input_and_sign(str, tmp->file, FILE_X);
		return (1);
	}
	return (0);
}
