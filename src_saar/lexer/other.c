/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   other.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/22 12:07:24 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/22 12:12:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// probably don't need these, just keeping incase they become useful

#include "../../include/sarah.h"

void	parse_space(char *input)
{
	while (ft_isspace(*input))
		input++;
}

char	**parse_input(char *input)
{
	char			**array;

	array = ft_split(input, ' ');
	return (array);
}

void	error_no_cmd(void)
{
	printf(PROMPT);   // necessary?
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(E_COMMAND_NOT_FOUND);
}

void	error_space(char *cmd)
{
	printf(PROMPT);   // necessary?
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(E_COMMAND_NOT_FOUND);
}
