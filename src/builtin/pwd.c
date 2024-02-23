/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:37 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/23 19:53:42 by dreijans      ########   odam.nl         */
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
	}
	else
		head->exit_code = E_GENERAL;
}
