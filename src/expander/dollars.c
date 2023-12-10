/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollars.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 17:51:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// static void	handle_dq(t_expand *str, t_env **env)
// {	
// 	(void)  env; // probs dont need you

// 	str->exit->exit_str = ft_itoa(str->exit->exit_code);
// 	str->expanded = ft_strjoin(str->expanded, str->exit->exit_str);
// }

static int	handle_no_env_val(t_expand *str)
{
	char	*tmp;

	tmp = NULL;
	if (str->expanded)
		tmp = ft_strjoin(str->expanded, "");
	else
		tmp = ft_strdup("");
	free(str->expanded);
	str->expanded = tmp;
	if (!str->expanded)
		return (-1);
	return (1);
}

int	dollar_expand(t_expand *str, t_env **env)
{
	// if (ft_strcmp(str->dollar, "$?") == 0)
	// {
	// 	handle_dq(str, env);
	// 	return (0);
	// }
	str->tmp = ft_strtrim(str->dollar, "$");
	free(str->dollar);
	str->dollar = str->tmp;
	if ((get_check_value(str, env) == 0) && str->env_val)
	{
		if (add_to_expand(str, str->env_val) == -1)
		{
			printf("errorrrrrrr\n");
			return (-1); // need proper error like
		}
	}
	if (!str->env_val)
	{
		if (handle_no_env_val(str) == -1)
			return (0);  // error if this comes back with -1
	}
	free(str->tmp);
	return (0);
}

static int	handle_one_dollar(t_expand *str)
{
	char	*tmp;

	tmp = NULL;
	if (str->expanded)
		tmp = ft_strjoin(str->expanded, "$");
	else
		tmp = ft_strdup("$");
	free(str->expanded);
	str->expanded = tmp;
	if (!str->expanded)
		return (-1);
	return (1);
}

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
			return (-1); // need proper error like
	}
	else if (!input[i])
	{
		if (handle_one_dollar(str) == -1)
			return (0); // error if this comes back with -1
	}
	return (i);
}
