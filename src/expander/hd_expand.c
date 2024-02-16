/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hd_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 09:29:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/16 19:29:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static	int	save_first(t_expand *str, char *input)
{
	int		i;

	i = 0;
	while (input[i] && !ft_dollar(input[i]))
		i++;
	if (ft_dollar(input[i]))
	{
		str->expanded = ft_substr(input, 0, i);
		if (!str->expanded)
			malloc_error(NULL, NULL, NULL, 0);
	}
	return (i);
}

static int	handle_hd_input(t_expand *str, char *read_line, int i)
{
	int	start;
	int	end;

	start = i;
	while (read_line[i] && !ft_dollar(read_line[i]))
		i++;
	end = i - start;
	str->string = ft_substr(read_line, start, end);
	if (!str->string)
		malloc_error(NULL, NULL, NULL, 0);
	if (add_to_expand(str, str->string) == -1)
		general_error("expansion failure");
	return (i);
}

char	*hd_expand(t_env **env, char *read_line)
{
	t_expand		*str;
	int				i;

	str = (t_expand *)malloc(sizeof(*str));
	if (!str)
		malloc_error(NULL, NULL, NULL, 0);
	ft_bzero(str, sizeof(t_expand));
	i = save_first(str, read_line);
	while (read_line[i])
	{
		if (ft_dollar(read_line[i]))
			i = dollar_bit(str, read_line, env, (i + 1));
		if (read_line[i] && !ft_dollar(read_line[i]))
			i = handle_hd_input(str, read_line, i);
	}
	read_line = str->expanded;
	free(str);
	return (read_line);
}
