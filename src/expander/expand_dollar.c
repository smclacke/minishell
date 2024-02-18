/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/18 17:34:28 by smclacke      ########   odam.nl         */
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

int	save_extra_string(t_expand *str, char *input, int i)
{
	int		start;
	int		end;
	int		len;
	char	*tmp;

	start = i;
	tmp = str->expanded;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	end = i;
	len = end - start;
	str->string = ft_substr(input, start, len);
	if (!str->string)
	{
		free(tmp);
		malloc_error(NULL, NULL, NULL, 0);
	}
	if (tmp && str->string)
	{
		str->expanded = ft_strjoin(tmp, str->string);
		if (!str->expanded)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free_strs(tmp, str->string);
	return (i);
}

int	first_bit(t_expand *str, char *input)
{
	int		i;

	i = 0;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	if (is_dollar_or_quote(input[i]))
	{
		if (i == 0)
			return (0);
		str->expanded = ft_substr(input, 0, i);
		if (!str->expanded)
			malloc_error(NULL, NULL, NULL, 0);
	}
	return (i);
}

void	dollar(t_expand *str, t_env **env)
{
	int		i;

	i = first_bit(str, str->input);
	while (str->input[i] && i >= 0)
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, str->input, env, (i + 1));
		if (ft_issquote(str->input[i]))
		{
			i = squote_bit(str, str->input, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
		if (ft_isdquote(str->input[i]))
		{
			i = dquote_bit(str, str->input, env, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
	}
}

void	expand_dollar(t_parser *lst, t_env **env)
{
	t_expand	str;
	t_parser	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	do_cmd(tmp, &str, env);
	do_strs(tmp, &str, env);
	do_hds(tmp, &str, env);
	do_reds(tmp, &str, env);
}
