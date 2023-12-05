/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:41 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/04 17:50:15 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param env environment in linked list which is NULL
 * @param new node to be added to the list if list == NULL
 * @param str value of the old_pwd given as string
 * @param full NULL string to be filled with old_pwd=str
 * @brief assigns full and new to their values and adds them to
 * an empty list.
 * @todo exit codes
*/
static void	reassign_old_pwd(t_env **env, char *cwd, t_parser *head)
{
	char	*full;
	t_env	*new;

	full = ft_strjoin("OLDPWD=", cwd);
	if (full == NULL)
		mini_error("", "E_MALLOC", head);
	new = env_lstnew("OLDPWD", cwd, full, true);
	if (new == NULL)
		mini_error("", "E_MALLOC", head);
	env_lstadd_back(env, new);
	if (env == NULL)
		mini_error("", "E_MALLOC", head);
}

/**
 * @param env environment in linked list
 * @param str string containing old working directory string
 * @brief loops through environment till OLDPWD is found
 * changes env->value to value of str
*/
static void	update_env(t_env **env, char *cwd, char *id, t_parser *head)
{
	t_env	*node;

	node = env[0];
	while (node && mini_strcmp(id, node->key) != 0)
		node = node->next;
	if (node == NULL)
	{
		reassign_old_pwd(env, cwd, head);
		return ;
	}
	reassign_values(cwd, node, head);
}

/**
 * @param lst parser linked list
 * @param env environment in linked list
 * @brief stores home directory and changes to it
 * @todo do I need use no such file?
 * if !lst->next is uncommented it segfaults
 * do I need the if statement?
*/
void	home_dir(t_parser *lst, t_env **env)
{
	char		*home_dir;

	home_dir = ft_getenv(*env, "HOME");
	if (home_dir == NULL)
	{
		// if (!lst->next)//segfault
		// {
			dprintf(STDERR_FILENO, NO_HOME);
			return ;
		// }
	}
	if (chdir(home_dir) == -1)
		no_such_file(lst);
}

/**
 * @param lst parser linked list
 * @param env environment in linked list
 * @brief stores old working dir and changes to it
 * @todo do I need use no such file?
*/
void	old_pwd(t_parser *lst, t_env **env)
{
	char		*old_pwd;

	old_pwd = ft_getenv(*env, "OLDPWD");
	if (old_pwd == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return ;
	}
	lst->str = old_pwd;
	if (chdir(lst->str) == -1)
		no_such_file(lst);
}

/**
 * @param lst parsed linked list
 * @param env environment in linked list
 * @brief changes directory with an absolute and relative path as argument
 * checks access of lst->str, changes directory
 * changes enviroment PWD and OLDPWD.
 * gives custom error if access not found
 * @todo PATH_MAX not defined?
*/
void	ft_cd(t_parser *lst, t_env **env)
{
	char		cwd[PATH_MAX];
	t_parser	*head;

	head = lst;
	if (too_many_args(lst) == true)
		return ;
	lst = lst->next;
	getcwd(cwd, PATH_MAX);
	if (!lst || mini_strcmp(lst->str, "~") == 0)
		home_dir(lst, env);
	else if (mini_strcmp(lst->str, "-") == 0)
		old_pwd(lst, env);
	else if (access(lst->str, F_OK) == 0)
	{
		if (chdir(lst->str) == -1)
			no_such_file(lst);
	}
	else if (lst->str != NULL)
		no_such_file(lst);
	update_env(env, cwd, "OLDPWD", head);
	getcwd(cwd, PATH_MAX);
	update_env(env, cwd, "PWD", head);
	head->exit_code = E_USAGE;
}
