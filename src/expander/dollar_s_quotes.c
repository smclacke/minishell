/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_s_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/05 18:08:03 by smclacke      ########   odam.nl         */
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
				return (0);
			if (add_to_expand(str, str->s_quote) == -1)
			{
				printf("errorrrrrrr\n");
				return (-1);
			}
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
int	dollar_expand(t_expand *str, t_env **env)
{
	char		*tmp;

	str->tmp = ft_strtrim(str->dollar, "$");
	free(str->dollar);
	str->dollar = str->tmp;
	// if (ft_strcmp(str->dollar, "?") == 0)
	// 	handle_dq(str, env);
	tmp = str->expanded;
	if ((get_check_value(str, env) == 0) && str->env_val)
	{
		if (add_to_expand(str, str->env_val) == -1)
		{
			printf("errorrrrrrr\n");
			return (-1);
		}
	}
	if (!str->env_val)
		str->expanded = ft_strdup(" ");
	free(str->env_val);
	free(str->tmp);
	return (0);
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
	if (input[i] && expandable_str(input[i]))
	{
		while (input[i] && expandable_str(input[i]))
			i++;
		end = i - start;
		str->dollar = ft_substr(input, start, end);
		if (dollar_expand(str, env) == -1)
			return (-1);
	}
	else
	{
		if (add_to_expand(str, "$") == -1)
		{
			printf("errorrrrrrr\n");
			return (-1);
		}
	}
	return (i);
}
