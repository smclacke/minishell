/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/31 15:41:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*expand_this(t_expand *str, t_env **env, int i)
{
	i++;
	while (str->input[i] && !ft_dollar(str->input[i]))
		i++;
	str->do_expand = ft_substr(str->input, 0, i);
	if (!str->do_expand)
		return (str->input);
	str->do_expand = ft_strtrim(str->input, "$");
	printf("str->do_expand HERE = %s\n", str->do_expand);
	str->input = ft_strtrim(str->input, "$");
	str->input = ft_strtrim(str->input, str->do_expand);
	printf("str->input HERE = %s\n", str->input);
	if (get_check_value(str, env))
		mini_error("bit fucked in expand_this()", errno); // this fails with two dollars
	free (str->do_expand);
	printf("epxanded = %s\n", str->expanded);
	printf("done = %s\n", str->done);
	str->done = ft_strjoin(str->done, str->expanded);
	printf("str->done = %s\n", str->done);
	printf("str->input = %s\n", str->input);
	return (str->input);
}

char	*check_rest(t_expand *str, t_env **env, int i)
{
	while (str->input[i] && !ft_dollar(str->input[i]))
		i++;
	if (ft_dollar(str->input[i]))
	{
		str->input = expand_this(str, env, i);
		if (!str->input)
			return (NULL);
	}
	if (!str->input)
		return (NULL);
	return (str->input);
}

char	*save_this(t_expand *str, int i)
{
	str->done = ft_substr(str->input, 0, i);
	if (!str->done)
		return (str->input);
	str->input = ft_strtrim(str->input, str->done);
	return (str->input);
}

char	*check_first(t_expand *str)
{
	int		i = 0;
	
	while (str->input[i] && !ft_dollar(str->input[i]))
		i++;
	if (ft_dollar(str->input[i]))
		str->input = save_this(str, i);
	return (str->input);
}
