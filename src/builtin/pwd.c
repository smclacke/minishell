/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:23:37 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/04 15:58:32 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param path string passed as NULL that needs to be filled in this function
 * @brief get's current working firectory
 * @return node made
 * @todo needs exit status
 * dprintf?
 * @todo	norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
// void	ft_pwd(void)
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
		// mini_error("getcwd()", errno);
		//should it be 1?
		mini_error("", "E_GENERAL", head);
}
