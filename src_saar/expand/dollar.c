/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:18 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/24 17:25:05 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

char	*save_this(t_exp_dol *str, int i)
{
	str->assed = ft_substr(str->unassed, 0, i);
	if (!str->assed) // if it fails or there wasnt anything before dollar
		return (str->unassed);
	str->unassed = ft_strtrim(str->unassed, str->assed);
	// add str->before_dollar to assed as first bit of str
	return (str->unassed);
}

char	*expand_this(t_exp_dol *str, t_env **env, int i)
{
	// printf
	str->expand_this = ft_substr(str->unassed, 0, i);
	if (!str->expand_this)
		return (str->unassed);
	str->unassed = ft_strtrim(str->unassed, str->expand_this);
	get_check_value(str, env);
	// now expand, add to assed, then empty expand_this
	// printf("unassed in func = %s\n", str->unassed);
	return (str->unassed);
}

char	*check_first(t_exp_dol *str)
{
	int		i = 0;
	
	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
		i++;
	if (ft_dollar(str->unassed[i]))
		str->unassed = save_this(str, i);
	return (str->unassed);
}

char	*check_rest(t_exp_dol *str, t_env **env, int i)
{
	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
		i++;
	if (ft_dollar(str->unassed[i]))
	{
		str->unassed = expand_this(str, env, i);
		// if (!str->unassed)
		// 	return (NULL);
	}
	// printf("unassed after  = %s\n", str->unassed);
	return (str->unassed);
}