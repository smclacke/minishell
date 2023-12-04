/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hd_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 09:29:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 10:17:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// if the limiter was NOT in qoutes, call expander on head_doc readline input
// regardless of the quotes, dollars are ALWAYS being expanded if limit not in quotes
// dont need to do anything with the quotes here

// look for dollars, if found, check if expandable var, add to expanded


char		*hd_expand(t_env **env, char *read_line)
{
	t_expand		*str;
	int				i;

	str = (t_expand *)malloc(sizeof(*str));
	if (!str)
		mini_error("malloc error expand dollar HD", errno);
	ft_bzero(str, sizeof(t_expand));
	i = first_bit(str, read_line);
	while (read_line[i])
	{
		if (ft_dollar(read_line[i]))
			i = dollar_bit(str, read_line, env, (i + 1));
	}
	read_line = str->expanded;
	free(str);
	return (read_line);
}