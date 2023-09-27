/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_size.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 17:03:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/27 17:05:02 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @brief	
 * @param	
 * @param	
 * @return	
*/
int	start_token(char *input, int old_start)
{
	int 	j;
	char	*quote_type;

	j = 0;
	quote_type = NULL;
	while (input[old_start] && ft_isspace(input[old_start]))
		old_start++;
	j = old_start;
	while (input[old_start] && !ft_isspace(input[old_start]))
	{
		if (ft_ismeta(input[old_start]))
			return (j);
		if (ft_isquote(input[old_start]))
		{
			quote_type = which_quote(&input[old_start]);
			old_start += next_quote(&input[old_start], *quote_type);
		}
		old_start++;
	}
	return (j);
}

/**
 * @brief	
 * @param	
 * @param	
 * @return	
*/
int	len_token(char *input, int len)
{
	int		j;
	char	*quote_type;

	j = 0;
	quote_type = NULL;
	while (input[len] && ft_isspace(input[len]))
		len++;
	j = len;
	if (ft_ismeta(input[len]))
	{
		len += is_meta(&input[len]);
		len = len - j;
		return (len);
	}
	while (input[len] && !ft_isspace(input[len]) && !ft_ismeta(input[len]))
	{	
		if (ft_isquote(input[len]))
		{
			quote_type = which_quote(&input[len]);
			len += next_quote(&input[len], *quote_type);
		}
		len++;
	}
	len = len - j;
	return (len);	
}
