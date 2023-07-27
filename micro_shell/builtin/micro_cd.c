/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/27 14:18:44 by dreijans      ########   odam.nl         */
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
*/
void	micro_cd(t_parser *node, t_env *env)//list instead argv
{
	char	*home_dir;
	char	*error;
	char	*cwd;

	cwd = NULL;
	if (node)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
			mini_error("getenv", errno);
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		if (access(node->str, F_OK) == 0)
		{
			// getcwd()..?
			while (env)
			{
				if (ft_strncmp ("OLDPWD=", env->key, 6)
				{
					
				}
				env = env->next;
			}
			chdir(node->str);
		}
		else
		{
			error = ft_strjoin("minishell: cd: ", node->str);
			mini_error(error, errno);
		}
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
