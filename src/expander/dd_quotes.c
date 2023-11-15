/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dd_quotes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:44:12 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/15 16:27:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	squote_in_dquote_bit(t_expand *str, int i)
{
	int	start;
	int	end;
	int	j;

	j = 0;
	start = i;
	while (str->input[i] && !ft_issquote(str->input[i]))
		i++;
	end = i - start;
	str->s_quote = ft_substr(str->input, start, end);
	start = 1;
	if (str->s_quote && ft_isdollar(str->s_quote))
	{
		while (str->s_quote[j] && !is_dollar_or_quote(str->s_quote[j]))
			j++;
		end = j - start;
		str->dollar = ft_substr(str->s_quote, start, end);
		dollar_expand(str, env);
		return (j);
	}
	return (i + 1);
}
// where is the bits inside the single quotes that arent to do with the dollaR?
// will this work?
// am i spiraling?

// if single in double, keep quotes and do expand
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
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, env, (i + 1));
		if (ft_issquote(str->input[i]))
		{
			i = squote_in_dquote_bit(str, i);
			if (str->input[i] && !is_dollar_or_quote(str->input[i]))
				i = save_extra_string(str, i);
		}
		if (!str->input[i])
			break ;
	}
}

/**
 * why return, why substr and strjoin there? this func doesnt make sense...
*/
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
			quote_dollar(str, env);
			// return (i + 1); // should i be returning here...?
		}
		i++;
	}
	str->d_quote = ft_substr(str->input, start, i - start);
	str->expanded = ft_strjoin(str->expanded, str->d_quote);
	return (i + 1);
}
