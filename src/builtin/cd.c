/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:41 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/29 17:23:07 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
static void	reassign_oft_pwd(t_env **env, char *str)
{
	char	*full;
	t_env	*new;

	full = ft_strjoin("OLDPWD=", str);
	printf("full = [%s]\n", full);
	if (full == NULL)
		mini_error("malloc", errno);
	new = env_lstnew("OLDPWD", str, full, (*env)->has_value);
	if (new == NULL)
		mini_error("malloc", errno);
	env_lstadd_back(env, new);
	if (env == NULL)
		mini_error("malloc", errno);
}

/**
 * @param env environment in linked list
 * @param str string containing new working directory string
 * @brief loops through environment till PWD is found
 * changes env->value to value of str
*/
static void	change_current_dir(t_env **env, char *str)
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
	free(head->value);
	head->value = str;
	key_equal = ft_strjoin(head->key, "=");
	new_full = ft_strjoin(key_equal, str);
	free(key_equal);
	free(head->full);
	head->full = new_full;
}

/**
 * @param env environment in linked list
 * @param str string containing old working directory string
 * @brief loops through environment till OLDPWD is found
 * changes env->value to value of str
*/
static void	change_old_dir(t_env **env, char *str)
{
	char	*key_equal;
	char	*new_full;
	t_env	*head;

	key_equal = NULL;
	new_full = NULL;
	head = *env;
	if (!env)
		reassign_oft_pwd(env, str);
	while (mini_strcmp ("OLDPWD", head->key) != 0)
	{
		head = head->next;
		if (head == NULL)
			return ;
	}
	reasing_value(str, head);
	key_equal = ft_strjoin(head->key, "=");
	new_full = ft_strjoin(key_equal, str);
	free(key_equal);
	free(head->full);
	head->full = new_full;
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
static void	access_change(t_env **env, t_parser *lst, char *o_d, char *c_d)
{
	char		*old_pwd;

	if (!lst->str)
		return ;
	else if (lst->str != NULL)
	{
		if (mini_strcmp(lst->str, "-") == 0)
		{
			old_pwd = ft_getenv(*env, "OLDPWD");
			lst->str = old_pwd;
		}
		if (access(lst->str, F_OK) == 0)
		{
			if (chdir(lst->str) == -1)
				no_such_file(lst, o_d);
			change_old_dir(env, o_d);
			change_current_dir(env, getcwd(c_d, 0));
		}
		else
		{
			dprintf(STDERR_FILENO, NO_SUCH_THING, lst->str);
			free(o_d);
		}
	}
}

/**
 * @param lst parsed linked list
 * @param env environment in linked list
 * @brief changes directory with an absolute and relative path as argument
*/
void	ft_cd(t_parser *lst, t_env **env)
{
	char		*old_work_dir;
	char		*cwd;
	char		*home_dir;

	if (check_args(lst) == true)
		return ;
	home_dir = ft_getenv(*env, "HOME");
	if (*env)
	{
		if (home_dir == NULL)
		{
			if (!lst->next)
				dprintf(STDERR_FILENO, NO_HOME);
		}
		cwd = NULL;
		old_work_dir = getcwd(cwd, 0);
		while (lst)
		{
			access_change(env, lst, old_work_dir, cwd);
			lst = lst->next;
		}
	}
}
