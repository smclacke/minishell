/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/04 19:29:59 by smclacke      ########   odam.nl         */
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

// dquote_expand
int	dquote_bit(t_expand *str, t_env **env, int i)
{
	int		start;
	int		end;
	int		dq_start;
	
	start = i;
	dq_start = 0;
	while (str->input[i])
	{
		if (ft_isdquote(str->input[i]))
		{
			end = i - start;
			str->d_quote = ft_substr(str->input, start, end);
			str->d_quote = remove_quotes(str->input);
			printf("str->d_quote = %s\n", str->d_quote);
		}
		// 	end = i - start;
		// 	str->d_quote = ft_substr(str->input, start, end);
		// 	str->d_quote = first_bit(str);
		// 	while (str->d_quote[dq_start])
		// 	{
		// 		if (ft_dollar(str->d_quote[dq_start]))
		// 		{
		// 			dq_start = dollar_bit(str, env, dq_start);
		// 			str->d_quote = ft_substr(str->d_quote, dq_start, (ft_strlen(str->d_quote) - dq_start));
		// 		}
		// 		dq_start++;
		// 	}
		// 	str->expanded = ft_strjoin(str->expanded, str->d_quote);
		// 	return (i + 1);
		// }
		i++;
	}
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
