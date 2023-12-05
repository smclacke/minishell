/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/05 18:06:20 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/shelly.h"

int		add_to_expand(t_expand *str, char *copy_str)
{
	char	*tmp;

	if (!copy_str)
		return (-1);
	tmp = str->expanded;
	if (tmp)
		str->expanded = ft_strjoin(tmp, copy_str);
	else
		str->expanded = ft_strdup(copy_str);
	free(copy_str);
	free(tmp);
	if (!str->expanded)
		return (-1);
	return (0);
}

/**
 * specifically for checking the values after dollar sign
 * need to check if expandable if not another dollar, quote or space
*/
int	expandable_str(int c)
{
	if (!is_dollar_or_quote(c) && !ft_isspace(c))
		return (1);
	return (0);
}

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
				return (1);
			return (0);
		}
		head = head->next;
	}
	return (1);
}

/**
 * @todo commmennntttt
*/
int	set_expand_string(t_parser *tmp, t_expand *str)
{
	str->sign = 0;
	str->input = NULL;
	if (!tmp)
		return (0);
	if (tmp->cmd && ft_strnstr(tmp->cmd, "$", ft_strlen(tmp->cmd)))
	{
		str->sign = CMD_X;
		str->input = tmp->cmd;
		return (1);
	}
	else if (tmp->str && ft_strnstr(tmp->str, "$", ft_strlen(tmp->str)))
	{
		str->sign = STR_X;
		str->input = tmp->str;
		return (1);
	}
	else if (tmp->file && ft_strnstr(tmp->file, "$", ft_strlen(tmp->file)))
	{
		str->sign = FILE_X;
		str->input = tmp->file;
		return (1);
	}
	return (0);
}
