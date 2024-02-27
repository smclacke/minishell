/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollars.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/27 15:00:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static int	handle_no_env_val(t_expand *str)
{
	char	*tmp;

	tmp = NULL;
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, "");
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		tmp = ft_strdup("");
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free(str->expanded);
	str->expanded = tmp;
	if (!str->expanded)
		return (-1);
	return (1);
}

int	dollar_expand(t_expand *str, t_env **env)
{
	str->tmp = ft_strtrim(str->dollar, "$");
	if (!str->tmp)
		malloc_error(NULL, NULL, NULL, 0);
	free(str->dollar);
	str->dollar = str->tmp;
	if ((get_check_value(str, env) == 0) && str->env_val)
	{
		if (add_to_expand(str, str->env_val) == -1)
			general_error("expansion failure");
	}
	if (!str->env_val)
	{
		if (handle_no_env_val(str) == -1)
			general_error("expansion failure");
	}
	free(str->tmp);
	return (0);
}

static int	handle_one_dollar(t_expand *str)
{
	char	*tmp;

	tmp = NULL;
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, "$");
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		tmp = ft_strdup("$");
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free(str->expanded);
	str->expanded = tmp;
	if (!str->expanded)
		general_error("expansion failure");
	return (1);
}

int	dollar_bit(t_expand *str, char *input, t_env **env, int i)
{
	int		start;
	int		end;

	start = i;
	end = 0;
	if (input[i] && ex_str(input[i]))
	{
		while (input[i] && ex_str(input[i]))
			i++;
		end = i - start;
		str->dollar = ft_substr(input, start, end);
		if (!str->dollar)
			malloc_error(NULL, NULL, &input, 0);
		if (dollar_expand(str, env) == -1)
			general_error("expansion failure");
	}
	else if (!input[i])
	{
		if (handle_one_dollar(str) == -1)
			general_error("expansion failure");
	}
	return (i);
}
