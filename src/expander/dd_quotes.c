/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dd_quotes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:44:12 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/29 12:55:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// static char	*save_first_bit(t_expand *str, char *input, int i)
// {
// 	str->tmp = ft_substr(input, 0, i);
// 	if (!str->tmp)
// 		return (input);
// 	input = ft_strtrim(input, str->tmp);
// 	str->expanded = ft_strjoin(str->expanded, str->tmp);
// 	return (input);
// }

static int	first_str_bit(t_expand *str, char *input, int i)
{
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	if (is_dollar_or_quote(input[i]))
	{
		str->expanded = ft_strjoin(str->expanded, str->input);
		if (!str->expanded)
			return (0);
	}
	return (i);
}

static void	handle_double(t_expand *str, char *input, t_env **env, int i)
{
	i = first_str_bit(str, input, i);
	printf("input[i] = %c\n", input[i]); // lost my input...
	while (input[i])
	{
		if (ft_dollar(input[i]))
			i = dollar_bit(str, input, env, (i + 1));
		if (ft_issquote(input[i]))
		{
			str->s_quote = ft_substr(input, i, 1);
			str->expanded = ft_strjoin(str->expanded, str->s_quote);
			i++;
		}
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
			printf("d_quote full = %s\n", str->d_quote);
			handle_double(str, str->d_quote, env, i);
			return (i + 1);
		}
		i++;
	}
	return (i); //error
}
