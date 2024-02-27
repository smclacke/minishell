/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 15:43:02 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/27 14:59:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
	int	i;

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

int	handle_dollars(t_parser *par, t_expand *str, t_env **env, int i)
{
	if (str->input[i + 1] && ft_isquest(str->input[i + 1]))
	{
		exit_exp(par, str);
		i = save_extra_string(str, str->input, (i + 2));
		return (i);
	}
	else
		i = dollar_bit(str, str->input, env, (i + 1));
	return (i);
}

void	dollar(t_parser *par, t_expand *str, t_env **env)
{
	int	i;

	i = first_bit(str, str->input);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = handle_dollars(par, str, env, i);
		if (ft_issquote(str->input[i]))
		{
			i = squote_bit(str, str->input, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
		if (ft_isdquote(str->input[i]))
		{
			i = dquote_bit(par, str, env, (i + 1));
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, str->input, i);
		}
		if (!ex_str(str->input[i]))
			i = save_extra_string(str, str->input, i);
	}
}

void	expand_dollar(t_parser *lst, t_env **env)
{
	t_expand	str;
	t_parser	*tmp;

	tmp = lst;
	do_cmd(tmp, &str, env);
	do_strs(tmp, &str, env);
	do_hds(tmp, &str, env);
	do_reds(tmp, &str, env);
}
