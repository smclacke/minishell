/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 20:28:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/12 16:59:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	is_pipe(void *input)
{
	if (ft_strcmp(input, PIPE) == 0)
		return (1);
	return (0);
}

int		count_procs(char **tokens)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
			count++;
		i++;
	}
	return (count);
}
