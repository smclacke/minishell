/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/26 17:49:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*save_this(t_expand *str, int i)
{
	str->done = ft_substr(str->input, 0, i);
	if (!str->done) // if it fails or there wasnt anything before dollar
		return (str->input);
	str->input = ft_strtrim(str->input, str->done);
	// add str->before_dollar to assed as first bit of str
	return (str->input);
}

char	*expand_this(t_expand *str, t_env **env, int i)
{
	i++;
	while (str->input[i] && !ft_dollar(str->input[i]))
		i++;
	str->do_expand = ft_substr(str->input, 0, i);
	if (!str->do_expand)
		return (str->input);
	str->do_expand = ft_strtrim(str->input, "$");
	if (get_check_value(str, env))
		mini_error("bit fucked in expand_this()", errno);
	free (str->do_expand);
	printf("str->expanded = %s\n", str->expanded);
	str->done = ft_strjoin(str->done, str->expanded);
	printf("str->done = %s\n", str->done);
	// return input incase theres moreee
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