/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:03:30 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/26 19:57:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

bool	is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	shelly_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

int	start_token(char *input, int old_start)
{
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	return (old_start);
}

static	int	meta_found(char *input, int len, int tmp)
{
	len += is_meta(&input[len]);
	len = len - tmp;
	return (len);
}

int	len_token(char *input, int len)
{
	int		tmp;
	char	*quote_type;

	tmp = 0;
	quote_type = NULL;
	while (input[len] && ft_isspace(input[len]))
		len++;
	tmp = len;
	if (ft_ismeta(input[len]))
		return (meta_found(input, len, tmp));
	while (input[len] && !space_or_meta(input[len]))
	{
		if (ft_isquote(input[len]))
		{
			quote_type = which_quote(&input[len]);
			if (next_quote(&input[len], *quote_type) == E_STOP)
				return (E_STOP);
			len += next_quote(&input[len], *quote_type);
		}
		len++;
	}
	len = len - tmp;
	return (len);
}
