/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dd_quotes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:44:12 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/15 21:22:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// '$USER'hello
// find quote to quote
// hello is handled after separately
// dont remove quotes, but expand thing inside
// static int	squote_in_dquote_bit(t_expand *str, char *input, t_env **env, int i)
// {
// 	int	start;
// 	int	end;
// 	int	j;

// 	j = 0;
// 	start = i;
// 	i++;
// 	while (input[i] && !ft_issquote(input[i]))
// 		i++;
// 	end = i - start;
// 	printf("start = %d, end = %d\n", start, end);
// 	str->s_quote = ft_substr(input, start, end);
// 	printf("str->s_quote = %s\n", str->s_quote);
// 	if (str->s_quote && ft_isdollar(str->s_quote))
// 	{
// 		start = 1;
// 		while (str->s_quote[j] && !is_dollar_or_quote(str->s_quote[j]))
// 			j++;
// 		end = j - start;
// 		str->dollar = ft_substr(str->s_quote, start, end);
// 		dollar_expand(str, env);
// 	}
// 	return (i + 1);
// }

static char	*save_first_bit(t_expand *str, char *input, int i)
{
	str->tmp = ft_substr(input, 0, i);
	if (!str->tmp)
		return (input);
	input = ft_strtrim(input, str->tmp);
	str->expanded = ft_strjoin(str->expanded, str->tmp);
	return (input);
}

static char *first_str_bit(t_expand *str, char *input)
{
	int	i = 0;

	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	if (is_dollar_or_quote(input[i]))
		input = save_first_bit(str, input, i);
	return (input);
}

// something'$USER'hello ->
// get first bit - > something
// if single quote...
// '$USER'hello
// send '$USER' to next func, handle hello with save_extra_string,,,, ret pos
static void	quote_dollar(t_expand *str, char *input, t_env **env)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	input = first_str_bit(str, input);
	while (input[i])
	{
		if (ft_dollar(input[i]))
			i = dollar_bit(str, input, env, (i + 1));
		if (ft_issquote(input[i]))
		{
			str->s_quote = ft_substr(input, i, (i + 1));
			str->expanded = ft_strjoin(str->expanded, str->s_quote);
			printf("str->expanded = %s\n", str->expanded);
			// if (!str->expanded) // will need to add proper protection...
			// {
			// 	printf("noope\n");
			// }
			i++;
		}
		if (input[i] && !is_dollar_or_quote(input[i]))
			i = save_extra_string(str, input, i);
		if (!input[i])
			break ;
	}
}

// "something'$USER'hello" - > something'$USER'hello
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
			end = i - 1;
			str->d_quote = ft_substr(input, start, end);
			printf("str->d_quote = %s\n", str->d_quote);
			quote_dollar(str, str->d_quote, env);
			return (i + 1);
		}
		i++;
	}
	return (0);
}
