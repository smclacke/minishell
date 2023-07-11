/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/11 14:59:19 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/*
	cd with only a relative or absolute path
	relative: cd src
	absolute: cd src/bin/pannekoek/whatever
	cd alone gives prompt back
	cd jfhjvhs gives: cd: no such file or directory: jfhjvhs	
*/
void	ft_cd(char *argv)
{
	char	*home_dir;
	char	*error;
	// char	*cwd;

	// cwd = NULL;
	if (argv != NULL)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
			mini_error("getenv", errno);
		// printf("%s\n", getcwd(cwd, sizeof(cwd)));
		if (access(argv, F_OK) == 0)
		{
			// getcwd()..?
			chdir(argv);
		}
		else
		{
			error = ft_strjoin("minishell: cd: ", argv);
			mini_error(error, errno);
		}
		// printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
	// printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
