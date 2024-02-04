/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/04 21:00:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param	env expander struct
 * @param	exp environmet linked list
 * @brief	checks environment value of string to be expanded
 * 			if there is no value it free's the comp_str and env_value.
 * @return	1 if there is no value, 0 if value is found and assigned
 * @todo	triple check protection, norm and sooo when less tired
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

/**
 * @todo	check the comment
 * @todo	substr protection
 * @todo	strjoin protection
 * @brief	string after closed quotes that needs to be added to expanded string
*/
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
	// if (!str->string)
	// {
	// 	free(tmp);
	// 	return (0);
	// }
	if (tmp && str->string)
		str->expanded = ft_strjoin(tmp, str->string);
	free(tmp);
	free(str->string);
	return (i);
}

/**
 * @todo	substr protection
 * @brief	before any dollar or quotes, just save the string
*/
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
			return (0);
	}
	return (i);
}

/**
 * @todo	fix this, leaks, norm, test test test...
 * @todo	did i do this? -> write version (or have func for here_doc and only edit that bit)
 * @brief	get first part of string, then loop through separating dollars and quotes...
*/
void	dollar(t_expand *str, t_env **env)
{
	int		i;

	i = first_bit(str, str->input);
	while (str->input[i])
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

/**
 * @todo 	error handling
 * @todo	comment
*/
void	expand_dollar(t_parser *lst, t_expand *str, t_env **env)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	tmp = lst;
	if (!tmp)
		return ; // error oder??
	do_cmd(tmp, str, env);
	do_strs(tmp, str, env);
	do_hds(tmp, str, env);
	do_reds(tmp, str, env);
}
