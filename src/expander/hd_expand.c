/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hd_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 09:29:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 16:57:34 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/shelly.h"

// if the limiter was NOT in qoutes, call expander on head_doc readline input
// regardless of the quotes, dollars are ALWAYS being expanded if limit not in quotes
// dont need to do anything with the quotes here

// look for dollars, if found, check if expandable var, add to expanded

static	int	save_first(t_expand *str, char *input)
{
	int		i;

	i = 0;
	while (input[i]&& !ft_dollar(input[i]))
		i++;
	if (ft_dollar(input[i]))
	{
		str->expanded = ft_substr(input, 0, i);
		if (!str->expanded)
			return (0);
	}
	return (i);
}

char		*hd_expand(t_env **env, char *read_line)
{
	t_expand		*str;
	int				i;
	int				start;
	int				end;

	str = (t_expand *)malloc(sizeof(*str));
	if (!str)
		return (0);
		// mini_error("malloc error expand dollar HD", errno);
	ft_bzero(str, sizeof(t_expand));
	i = save_first(str, read_line);
	start = 0;
	end = 0;
	while (read_line[i])
	{
		if (ft_dollar(read_line[i]))
			i = dollar_bit(str, read_line, env, (i + 1));
		if (read_line[i] && !ft_dollar(read_line[i]))
		{	
			start = i;
			while (read_line[i] && !ft_dollar(read_line[i]))
				i++;
			end = i - start;
			str->string = ft_substr(read_line, start, end);
			if (!str->string)
				return (NULL);
			if (str->expanded)
			{
				str->expanded = ft_strjoin(str->expanded, str->string);
				if (!str->expanded)
					return (NULL);
			}
			else
			{
				str->expanded = ft_strdup(str->string);
				if (!str->expanded)
					return (NULL);
			}
		}
	}
	read_line = str->expanded;
	free(str);
	return (read_line);
}
