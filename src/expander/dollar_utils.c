/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/04 23:48:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// extra string ayyayyayya
int	save_extra_string(t_expand *str, int i)
{
	int	start;
	int	end;

	start = i;
	while (str->input[i] && !is_dollar_or_quote(str->input[i]))
		i++;
	end = i - start;
	str->string = ft_substr(str->input, start, end);
	str->expanded = ft_strjoin(str->expanded, str->string);
	return (i);
}

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
	printf("str->input = %s\n", str->input);
	while (str->input[i])
	{
		if (ft_dollar(str->input[i]))
			i = dollar_bit(str, env, (i + 1));
		// if (ft_issquote(str->input[i]))
		// {
		// 	i = squote_bit(str, i);
		// 	if (str->input[i] && !is_dollar_or_quote(str->input[i]))
		// 		i = save_extra_string(str, i);
		// }
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
			quote_dollar(str, env);
			return (i + 1);
		}
		i++;
	}
	str->d_quote = ft_substr(str->input, start, i - start);
	str->expanded = ft_strjoin(str->expanded, str->d_quote);
	return (i + 1);
}

// squote_expand
int	squote_bit(t_expand *str, int i)
{
	int		start;
	int		end;
	
	start = i;
	while (str->input[i])
	{
		if (ft_issquote(str->input[i]))
		{
			end = i - start;
			str->s_quote = ft_substr(str->input, start, end);	
			str->expanded = ft_strjoin(str->expanded, str->s_quote);
			return (i + 1);
		}
		i++;
	}
	return (i + 1);
}

/**
 * @todo make it do the thing, norm it, leak proof it, comment it, error it
*/
static void	dollar_expand(t_expand *str, t_env **env)
{
	str->dollar = ft_strtrim(str->dollar, "$");
	if (!get_check_value(str, env))
		str->expanded = ft_strjoin(str->expanded, str->dollar);
	else
		str->dollar = NULL;
}

int	dollar_bit(t_expand *str, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	while (str->input[i] && !is_dollar_or_quote(str->input[i]))
		i++;
	end = i - start;
	str->dollar = ft_substr(str->input, start, end);
	dollar_expand(str, env);
	return (i);
}
