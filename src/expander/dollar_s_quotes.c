/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_s_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 10:06:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
			free(str->s_quote); // check
			return (i + 1);
		}
		i++;
	}
	return (i); // error
}

/**
 * @todo make it do the thing, norm it, leak proof it, comment it, error it
*/
void	dollar_expand(t_expand *str, t_env **env)
{
	str->tmp = ft_strtrim(str->dollar, "$");
	free(str->dollar);
	if (!str->tmp)
		return ;
	str->dollar = str->tmp;
	if (!get_check_value(str, env))
	{
		if (!str->expanded)
			str->expanded = str->env_val;
		else
			str->expanded = ft_strjoin(str->expanded, str->env_val);
	}
	printf("dollar = %s\n", str->dollar);
	printf("env_val = %s\n", str->env_val);
	free(str->tmp);
}

/**
 * dollar_bit, if dollar not in quotations
*/
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
	str->env_val = NULL;
	return (i);
}
