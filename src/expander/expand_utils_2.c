/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 19:21:07 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/27 14:16:43 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param	env expander struct
 * @param	exp environmet linked list
 * @brief	checks environment value of string to be expanded
 * 			if there is no value it free's the comp_str and env_value.
 * @return	1 if there is no value, 0 if value is found and assigned
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
				malloc_error(NULL, NULL, NULL, 0);
			}
			return (0);
		}
		head = head->next;
	}
	return (1);
}

void	exit_exp(t_parser *par, t_expand *str)
{
	char	*tmp;
	char	*exit_code;

	exit_code = ft_itoa(par->exit_code);
	if (!exit_code)
		malloc_error(NULL, NULL, NULL, 0);
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, exit_code);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		tmp = ft_strdup(exit_code);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free(str->expanded);
	str->expanded = tmp;
	free(exit_code);
	if (!str->expanded)
		general_error("expansion failure");
}

static int	ft_isunder(int c)
{
	if (c == '_')
		return (1);
	return (0);
}

int	ex_str(int c)
{
	if (ft_isalnum(c) || ft_isunder(c) || ft_isquest(c))
		return (1);
	return (0);
}

int	is_dollar_or_quote(int c)
{
	return (ft_dollar(c) || ft_isquote(c));
}
