/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:41 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/30 19:58:12 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"
#include <limits.h>

#define NO_SUCH_THING "minishell: cd: %s: No such file or directory\n"
#define NO_HOME "minishell: cd: HOME not set\n"

/**
 * @param env environment in linked list which is NULL
 * @param new node to be added to the list if list == NULL
 * @param str value of the old_pwd given as string
 * @param full NULL string to be filled with old_pwd=str
 * @brief assigns full and new to their values and adds them to
 * an empty list.
*/
static void	reassign_old_pwd(t_env **env, char *cwd)
{
	char	*full;
	t_env	*new;

	full = ft_strjoin("OLDPWD=", cwd);
	if (full == NULL)
		mini_error("malloc", errno);
	new = env_lstnew("OLDPWD", cwd, full, true);
	if (new == NULL)
		mini_error("malloc", errno);
	env_lstadd_back(env, new);
	if (env == NULL)
		mini_error("malloc", errno);
}

/**
 * @param env environment in linked list
 * @param str string containing old working directory string
 * @brief loops through environment till OLDPWD is found
 * changes env->value to value of str
 * @todo norm it
*/
static void	update_env(t_env **env, char *cwd, char *id)
{
	t_env	*node;

	node = env[0];
	while (node && mini_strcmp(id, node->key) != 0)
		node = node->next;
	if (node == NULL)
	{
		reassign_old_pwd(env, cwd);
		return ;
	}
	reassign_values(cwd, node);
}

void	home_dir(t_parser *lst, t_env **env)
{
	char		*home_dir;

	home_dir = ft_getenv(*env, "HOME");
	if (home_dir == NULL)
	{
		if (!lst->next)
		{
			dprintf(STDERR_FILENO, NO_HOME);
			return ;
		}
	}
	if (chdir(home_dir) == -1)
		no_such_file(lst);// fix this?
}

void	old_pwd(t_parser *lst, t_env **env)
{
	char		*old_pwd;

	old_pwd = ft_getenv(*env, "OLDPWD");
	if (old_pwd == NULL)
	{
		printf("yo OLDPWD NOT SET HAHAHAHHAHA\n");
		return ;
	}
	lst->str = old_pwd;
	if (chdir(lst->str) == -1)
		no_such_file(lst);// fix this?
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
 * @todo fix OLDPWD error message
*/
static void	access_change(t_env **env, t_parser *lst)
{
	char		cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (!lst || mini_strcmp(lst->str, "~") == 0)
	{
		home_dir(lst, env);
	}
	else if (mini_strcmp(lst->str, "-") == 0)
	{
		old_pwd(lst, env);
	}
	else if (access(lst->str, F_OK) == 0)
	{
		if (chdir(lst->str) == -1)
			no_such_file(lst);
	}
	else
	{
		dprintf(STDERR_FILENO, NO_SUCH_THING, lst->str);
		return ;
	}
	update_env(env, cwd, "OLDPWD");
	getcwd(cwd, PATH_MAX);
	update_env(env, cwd, "PWD");
}

/**
 * @param lst parsed linked list
 * @param env environment in linked list
 * @brief changes directory with an absolute and relative path as argument
 * @todo cd ~ home, cd (null) home, cd - old_pwd
*/
void	ft_cd(t_parser *lst, t_env **env)
{
	if (too_many_args(lst) == true)
		return ;
	lst = lst->next;
	access_change(env, lst);
}

