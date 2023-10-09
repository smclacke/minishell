/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:48:44 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/09 19:10:37 by dreijans      ########   odam.nl         */
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
void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		printf("Current working directory: %s\n", path);
		free(path);
	}
	else
		mini_error("getcwd()", errno);
}
