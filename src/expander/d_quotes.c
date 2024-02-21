/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   d_quotes.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:44:12 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/21 18:29:29 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	first_str_bit(t_expand *str, char *input)
{
	int	i;

	i = 0;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	if (is_dollar_or_quote(input[i]))
	{
		if (i == 0)
			return (0);
		str->tmp = ft_substr(input, 0, i);
		if (!str->tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		str->tmp = ft_strdup(input);
		if (!str->tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	if (add_to_expand(str, str->tmp) == -1)
		general_error("expansion failure");
	return (i);
}

static int	add_single_quote(t_expand *str, char *c)
{
	char	*tmp;

	tmp = NULL;
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, c);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		tmp = ft_strdup(c);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free(str->expanded);
	str->expanded = tmp;
	if (!str->expanded)
		general_error("expansion failure");
	return (0);
}

static int	handle_double(t_expand *str, char *input, t_env **env)
{
	int		i;
	// int		start;

	i = first_str_bit(str, input);
	// start = 0;
	while (input[i])
	{
		if (ft_dollar(input[i]))
			i = dollar_bit(str, input, env, (i + 1));
		if (input[i] && ft_issquote(input[i]))
		{
			if (add_single_quote(str, "\'"))
				general_error("expansion failure");
			i++;
		}
		if (input[i] && !is_dollar_or_quote(input[i]))
			i = save_extra_string(str, input, i);
		if (!input[i])
			break ;
	}
	return (0);
}

int	dquote_bit(t_expand *str, char *input, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	while (input[i])
	{
		if (ft_isdquote(input[i]))
		{
			end = i - start;
			str->d_quote = ft_substr(input, start, end);
			if (!str->d_quote)
				malloc_error(NULL, NULL, NULL, 0);
			if (handle_double(str, str->d_quote, env) == -1)
				general_error("expansion failure");
			free(str->d_quote);
			return (i + 1);
		}
		i++;
	}
	general_error("expansion failure");
	return (0);
}
