/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_size.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:03:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 20:00:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	start_token(char *input, int old_start)
{
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	return (old_start);
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
	{
		len += is_meta(&input[len]);
		len = len - tmp;
		return (len);
	}
	while (input[len] && !space_or_meta(input[len]))
	{
		if (ft_isquote(input[len]))
		{
			quote_type = which_quote(&input[len]);
			len += next_quote(&input[len], *quote_type);
		}
		len++;
	}
	len = len - tmp;
	return (len);
}
