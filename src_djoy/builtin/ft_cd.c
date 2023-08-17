/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/17 21:39:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param lst parsed linked list
 * @param env environment in linked list
 * @brief changes directory with an absolute and relative path as argument
 * relative: cd src
 * absolute: cd src/bin/pannekoek/whatever TESTT!!!
 * 				cd alone gives prompt back
 * 				cd jfhjvhs gives: cd: no such file or directory: jfhjvhs
 * line 66: check if needs error message with exit
 * 			give prompt back, and endline?
*/
void	ft_cd(t_parser *lst, t_env *env)
{
	char		*home_dir;
	char		*old_work_dir;
	char		*cwd;

	cwd = NULL;
	old_work_dir = NULL;
	if (env)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
			mini_error("getenv", errno);
		old_work_dir = getcwd(cwd, sizeof(cwd));
		while (lst)
		{
			access_and_change(env, lst, old_work_dir, cwd);
			lst = lst->next;
		}
	}
}

/**
 * @param lst environment in linked list
 * @param env parsed linked list
 * @param opwd string containing old working directory
 * @param cwd string containing new working directory
 * @brief checks acces of lst->str, changes directory
 * changes enviroment PWD and OLDPWD.
 * gives custom error if access not found
 * cd: no such file or directory: %s\n", lst->str
*/
void	access_and_change(t_env *env, t_parser *lst, char *opwd, char *cwd)
{
	char		*error;

	if (lst->str != NULL)
	{
		if (access(lst->str, F_OK) == 0)
		{
			if (chdir(lst->str) == -1)
			{
				error = ft_strjoin("minishell: cd: ", lst->str);
				mini_error(error, errno);
			}
			change_old_dir(env, opwd);
			change_current_dir(env, getcwd(cwd, sizeof(cwd)));
		}
		if (access(lst->str, F_OK) == -1)
		{
			printf("cd: no such file or directory: %s\n", lst->str);
		}
	}
}

/**
 * @param env environment in linked list
 * @param str string containing old working directory string
 * @brief loops through environment till OLDPWD is found
 * changes env->value to value of str
*/
void	change_old_dir(t_env *env, char *str)
{
	while (mini_strcmp ("OLDPWD", env->key) != 0)
	{
		env = env->next;
		if (env == NULL)
			return ;
	}
	env->value = str;
}

/**
 * @param env environment in linked list
 * @param str string containing new working directory string
 * @brief loops through environment till PWD is found
 * changes env->value to value of str
*/
void	change_current_dir(t_env *env, char *str)
{
	while (mini_strcmp ("PWD", env->key) != 0)
	{
		env = env->next;
		if (env == NULL)
			return ;
	}
	env->value = str;
}
