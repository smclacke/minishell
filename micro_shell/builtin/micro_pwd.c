/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_pwd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:48:44 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/26 16:51:29 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param path string passed as NULL that needs to be filled in this function
 * @brief get's current working firectory
 * @return node made
 * @todo also print the old one OLDPWD=/Users/dreijans/Documents/Rang 3/Minishell
 * needs exit status
*/
void	micro_pwd(char *path)
{
	path = getcwd(path, sizeof(NULL));
	if (path != NULL)
		printf("Current working directory: %s\n", path);
	else
		micro_error("getcwd()", errno);
}
