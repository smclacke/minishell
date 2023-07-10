/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:48:44 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/04 17:11:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* 
	get's current working directory 
	research pwd behavior when given NULL
*/
void	ft_pwd(char *path)
{
	path = getcwd(path, sizeof(NULL));
	if (path != NULL)
		printf("Current working directory: %s\n", path);
	else
		mini_error("getcwd()", errno);
}
