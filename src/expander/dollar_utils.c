/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/15 23:15:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	save_extra_string(t_expand *str, char *input, int i)
{
	int	start;
	int	end;
	int	len;

	start = i;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	end = i;
	len = end - start;
	str->string = ft_substr(input, start, (len + 1));
	str->expanded = ft_strjoin(str->expanded, str->string);
	return (i);
}

int	squote_bit(t_expand *str, char *input, int i)
{
	int		start;
	int		end;
	
	start = i;
	while (input[i])
	{
		if (ft_issquote(input[i]))
		{
			end = i - start;
			str->s_quote = ft_substr(input, start, end);	
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
void	dollar_expand(t_expand *str, t_env **env)
{
	str->dollar = ft_strtrim(str->dollar, "$");
	if (!get_check_value(str, env))
		str->expanded = ft_strjoin(str->expanded, str->dollar);
	else
		str->dollar = NULL;
}

int	dollar_bit(t_expand *str, char *input, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	while (input[i] && !is_dollar_or_quote(input[i]))
		i++;
	end = i - start;
	str->dollar = ft_substr(input, start, end);
	dollar_expand(str, env);
	return (i);
}
