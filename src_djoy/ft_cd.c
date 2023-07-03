/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/03 15:57:33 by dreijans      ########   odam.nl         */
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
	// char	cwd[256];

	if (argv != NULL)
	{
		home_dir = getenv("HOME");
		// printf("%s\n", getcwd(cwd, sizeof(cwd)));
		if (home_dir == NULL)
			mini_error("getenv", errno);//custom message?
		// else
		if (access(argv, F_OK) == 0)
			chdir(argv);
		else
			mini_error("dir", errno);// change into custom
		// printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
}
