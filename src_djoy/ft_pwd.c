/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:48:44 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/03 17:31:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* get's current working directory */
void	ft_pwd(char *path)
{
	path = getcwd(path, sizeof(NULL));
	if (path != NULL)
		printf("Current working directory: %s\\n", path);
	else
		mini_error("getcwd()", errno);
}

//give it a struct so I can store the outcome in another?
// ➜  Minishell git:(djoyke) ✗ ./djoyke pwd
// getcwd(): Result too large
