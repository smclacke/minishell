/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_s_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/12/04 16:52:15 by smclacke      ########   odam.nl         */
=======
/*   Updated: 2023/12/04 16:49:01 by dreijans      ########   odam.nl         */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	squote_bit(t_expand *str, char *input, int i)
{
	int		start;
	int		end;
	char	*tmp;
	char	*tmp_input;
	
	start = i;
	tmp = str->expanded;
	tmp_input = input;
	while (tmp_input[i])
	{
		if (ft_issquote(tmp_input[i]))
		{
			end = i - start;
			str->s_quote = ft_substr(tmp_input, start, end);
			if (!str->s_quote)
<<<<<<< HEAD
				mini_error("squote", errno);
			if (str->expanded)
=======
				return (0);
				// mini_error("squote", errno);
			if (!str->expanded)
				str->expanded = ft_strdup(str->s_quote);
			else
>>>>>>> main
				str->expanded = ft_strjoin(tmp, str->s_quote);
			else
				str->expanded = ft_strdup(str->s_quote);
			if (!str->expanded)
				mini_error("squote", errno);
			free(tmp);
			free(str->s_quote);
			return (i + 1);
		}
		i++;
	}
	free(str);
	return (i);
}

// static void	handle_dq(t_expand *str, t_env **env)
// {	
// 	(void)  env; // probs dont need you

// 	str->exit->exit_str = ft_itoa(str->exit->exit_code);
// 	str->expanded = ft_strjoin(str->expanded, str->exit->exit_str);
// }

/**
 * @todo make it do the thing, norm it, leak proof it, comment it, error it
*/
void	dollar_expand(t_expand *str, t_env **env)
{
	char		*tmp;

	tmp = str->expanded;
	str->tmp = ft_strtrim(str->dollar, "$");
	free(str->dollar);
	if (!str->tmp)
		return ;
	str->dollar = str->tmp;
	// if (ft_strcmp(str->dollar, "?") == 0)
	// 	handle_dq(str, env);
	if (get_check_value(str, env) == 0)
	{
		if (str->env_val)
		{
			if (tmp)
				str->expanded = ft_strjoin(tmp, str->env_val); // leakkkyyy
			else
				str->expanded = ft_strdup(str->env_val);
		}
		if (!str->expanded)
		{
			free(str->env_val);
			free(tmp);
			free(str->tmp);
			mini_error("dolllarrrr", errno);
		}
	}
	free(str->env_val);
	free(tmp);
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
	return (i);
}
