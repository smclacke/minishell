/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dd_quotes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:44:12 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/29 13:33:26 by smclacke      ########   odam.nl         */
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
		str->tmp = ft_substr(input, 0, i);
		str->expanded = ft_strjoin(str->expanded, str->tmp);
		free(str->tmp);
		if (!str->expanded)
			return (0);
	}
	return (i);
}

static void	handle_double(t_expand *str, char *input, t_env **env)
{
	int		i;
	int		start;

	i = first_str_bit(str, input);
	start = 0;
	while (input[i])
	{
		if (ft_dollar(input[i]))
			i = dollar_bit(str, input, env, (i + 1));
		if (ft_issquote(input[i]))
		{
			start = i;
			i++;
			while (!ft_issquote(input[i]))
				i++;
			str->tmp = ft_substr(input, start, i);
			str->expanded = ft_strjoin(str->expanded, str->tmp);
			free(str->tmp);
		}
		i++;
		if (input[i] && !is_dollar_or_quote(input[i]))
			i = save_extra_string(str, input, i);
		if (!input[i])
			break ;
	}
}

int	dquote_bit(t_expand *str, char *input, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	while(input[i])
	{
		if (ft_isdquote(input[i]))
		{
			end = i - start;
			str->d_quote = ft_substr(input, start, end);
			handle_double(str, str->d_quote, env);
			return (i + 1);
		}
		i++;
	}
	return (i); //error
}
