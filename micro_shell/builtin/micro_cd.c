/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/27 17:12:32 by dreijans      ########   odam.nl         */
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
void	micro_cd(t_parser *node, t_env *env)
{
	char	*home_dir;
	char	*new_old_pwd;
	char	*temp_old_pwd;
	char	*error;
	char	*cwd;

	(void) env;
	cwd = NULL;
	if (node)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
			micro_error("getenv", errno);
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		if (access(node->str, F_OK) == 0)
		{
			while (env)
			{
				if (ft_strncmp ("OLDPWD=", env->key, 6))
				{
					new_old_pwd = getcwd(cwd, sizeof(cwd));
					temp_old_pwd = env->value; 
					env->value = new_old_pwd;
					free(temp_old_pwd);
				}
				env = env->next;
			}
			chdir(node->str);
		}
		else
		{
			error = ft_strjoin("minishell: cd: ", node->str);
			micro_error(error, errno);
		}
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
