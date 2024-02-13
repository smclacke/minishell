/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_this.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/13 17:17:20 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/13 17:20:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../shelly.h"

int	expand_this(t_expand *str, char *exable, t_env **env)
{
	str->input = ft_strdup(exable);
	if (!str->input)
		return (-1); // malloc error, stop
	str->expanded = NULL;
	dollar(str, env);
	if (!str->expanded)
		return (-1);
	exable = str->expanded;
	if (!exable)
		return (-1);
	return (0);
}
