/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dd_quotes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:44:12 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/15 15:52:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"


// if single in double, keep quotes and still expand
static void	quote_dollar(t_expand *str, t_env **env)
{
	int		i;
	int		start;
	int		end;
	// char	*temp;

	i = 0;
	start = 0;
	end = 0;
	str->input = str->d_quote;
	str->input = first_bit(str);
	printf("str->expanded = %s\n", str->expanded);
	printf("str->input = %s\n", str->input);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, env, (i + 1));
		if (ft_issquote(str->input[i]))
		{
			printf("str->squote = %c\n", str->input[i]);
			i = squote_bit(str, i);
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, i);
		}
		if (!str->input[i])
			break ;
	}
}

int	dquote_bit(t_expand *str, t_env **env, int i)
{
	int		start;
	int		end;
	// char	*temp;

	start = i;
	end = 0;
	while(str->input[i])
	{
		if (ft_isdquote(str->input[i]))
		{
			end = i - 1;
			str->d_quote = ft_substr(str->input, start, end);
			printf("str->dquote = %s\n", str->d_quote);
			quote_dollar(str, env);
			return (i + 1);
		}
		i++;
	}
	str->d_quote = ft_substr(str->input, start, i - start);
	str->expanded = ft_strjoin(str->expanded, str->d_quote);
	return (i + 1);
}
