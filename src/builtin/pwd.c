/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:37 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/19 21:57:36 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param path string passed as NULL that needs to be filled in this function
 * @brief get's current working firectory
 * @return node made
 * @todo needs exit codes?
*/
void	ft_pwd(t_parser *head)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		printf("Current working directory: %s\n", path);
		free(path);
		head->exit_code = E_USAGE;
	}
	else
		mini_error(E_USAGE, head);
}
