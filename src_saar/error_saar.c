/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_saar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 11:52:11 by smclacke      #+#    #+#                 */
/*   Updated: 2023/06/30 12:03:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

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
