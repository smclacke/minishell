/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_saar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/06/30 12:36:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

// ft_isquote

// double or single quote
// quotes open or no
// delimiters

char	*check_empty(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		error_no_cmd();
	while (cmd[i])
	{
		if (ft_isspace(cmd[0]))
			error_space(cmd);
		if (ft_isspace(cmd[i] && ft_isspace(cmd[i - 1])
				&& ft_isspace(cmd[i + 1])))
			error_space(cmd);
		if (ft_isspace(cmd[i]) && (ft_isspace(cmd[i + 1])
				|| cmd[i + 1] == '\0'))
			error_space(cmd);
		i++;
	}
	return (cmd);
}


// Meta characters: SPACE, TAB, NEWLINE, ;, (, ), <, >, |, &.
// Types of tokens: words, keywords, In / Out redirectors, and semicolons.

// Delimiters ";", "|", "&".
