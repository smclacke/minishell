/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:12:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/25 14:47:46 by dreijans      ########   odam.nl         */
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
 * @todo do we actually need OLDPWD and PWD bash doesnt have it
*/
void	ft_cd(t_parser *lst, t_env **env)
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
void	access_and_change(t_env **env, t_parser *lst, char *o_d, char *c_d)
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
			change_old_dir(env, o_d);
			change_current_dir(env, getcwd(c_d, sizeof(c_d)));
		}
		else
			printf("cd: no such file or directory: %s\n", lst->str);
	}
}

/**
 * @param env environment in linked list
 * @param str string containing old working directory string
 * @brief loops through environment till OLDPWD is found
 * changes env->value to value of str
 * @todo decide if I want to keep env->full
 * else need to update that everytime I update my environment
*/
void	change_old_dir(t_env **env, char *str)
{
	char	*key_equal;
	char	*new_full;
	t_env	*new;
	char	*full;
	t_env	*head;

	key_equal = NULL;
	new_full = NULL;
	new = NULL;
	full = NULL;
	head = *env;
	if (!env)
		reassign_old_pwd(env, new, str, full);
	while (mini_strcmp ("OLDPWD", head->key) != 0)
	{
		head = head->next;
		if (head == NULL)
			return ;
	}
	head->value = str;
	key_equal = ft_strjoin(head->key, "=");
	new_full = ft_strjoin(key_equal, str);
	head->full = new_full;
}

/**
 * @param env environment in linked list
 * @param str string containing new working directory string
 * @brief loops through environment till PWD is found
 * changes env->value to value of str
 * @todo decide if I want to keep env->full
 * else need to update that everytime I update my environment
*/
void	change_current_dir(t_env **env, char *str)
{
	char	*key_equal;
	char	*new_full;
	t_env	*head;

	key_equal = NULL;
	new_full = NULL;
	head = *env;
	while (mini_strcmp ("PWD", head->key) != 0)
	{
		head = head->next;
		if (head == NULL)
			return ;
	}
	head->value = str;
	key_equal = ft_strjoin(head->key, "=");
	new_full = ft_strjoin(key_equal, str);
	head->full = new_full;
}

void	reassign_old_pwd(t_env **env, t_env *new, char *str, char *full)
{
	full = ft_strjoin("OLDPWD=", str);
	if (full == NULL)
		mini_error("malloc", errno);
	new = env_lstnew("OLDPWD", str, full);
	if (new == NULL)
		mini_error("malloc", errno);
	env_lstadd_back(env, new);
	if (env == NULL)
		mini_error("malloc", errno);
}
