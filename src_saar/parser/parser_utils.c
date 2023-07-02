/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/02 10:08:16 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

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

// space, tab, \n, ;, comma, <, >, |, &
// tokens = words, keywords, In / Out redirectors, semicolons
// delimiters ;, |, &
