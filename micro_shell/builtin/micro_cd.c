/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/03 16:11:06 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param argv terminal given arguments (for now)
 * @brief changes directory with an absolute and relative path as argument
 * relative: cd src
 * absolute: cd src/bin/pannekoek/whatever
 * cd alone gives prompt back
 * cd jfhjvhs gives: cd: no such file or directory: jfhjvhs
 * change pwd 
 * change oldpwd
*/
void	micro_cd(t_parser *lst, t_env *env)
{
	char		*home_dir;
	char		*old_work_dir;
	char		*error;
	char		*cwd;
	t_env		**head;

	cwd = NULL;
	head = &env;
	if (env)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
			micro_error("getenv", errno);
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		old_work_dir = getcwd(cwd, sizeof(cwd));
		if (access(lst->str, F_OK) == 0)
			chdir(lst->str);
		else
		{
			error = ft_strjoin("minishell: cd: ", lst->str);
			micro_error(error, errno);
		}
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
