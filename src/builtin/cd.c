/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:41 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/29 21:35:41 by dreijans      ########   odam.nl         */
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
*/
static void	reassign_old_pwd(t_env **env, char *cwd, t_parser *head)
{
	char	*full;
	t_env	*new;

	full = mini_strjoin("OLDPWD=", cwd);
	new = env_lstnew("OLDPWD", cwd, full, true);
	if (new == NULL)
		head->exit_code = E_MALLOC;
	env_lstadd_back(env, new);
	if (env == NULL)
		head->exit_code = E_MALLOC;
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

	node = *env;
	while (node && ft_strncmp(id, node->key, ft_strlen(id) + 1) != 0)
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
*/
void	home_dir(t_parser *lst, t_env **env)
{
	char		*home_dir;

	home_dir = ft_getenv(*env, "HOME");
	if (home_dir == NULL)
	{
		write(STDERR_FILENO, NO_HOME, 29);
		lst->exit_code = E_GENERAL;
		return ;
	}
	if (chdir(home_dir) == -1)
		no_such_file(home_dir, lst);
}

/**
 * @param lst parser linked list
 * @param env environment in linked list
 * @brief stores old working dir and changes to it
*/
void	old_pwd(char *str, t_env **env, t_parser *lst)
{
	char		*old_pwd;

	old_pwd = ft_getenv(*env, "OLDPWD");
	if (old_pwd == NULL)
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 31);
		lst->exit_code = E_GENERAL;
		return ;
	}
	str = old_pwd;
	if (chdir(str) == -1)
		no_such_file(str, lst);
}

/**
 * @param lst parsed linked list
 * @param env environment in linked list
 * @brief changes directory with an absolute and relative path as argument
 * checks access of lst->str, changes directory
 * changes enviroment PWD and OLDPWD.
 * gives custom error if access not found
*/
void	ft_cd(t_parser *lst, t_env **env)
{
	char		cwd[PATH_MAX];

	if (too_many_args(lst) == true)
		return ;
	getcwd(cwd, PATH_MAX);
	if (lst->proc->str_count == 0 || mini_strcmp(lst->proc->str[0], "~") == 0)
		home_dir(lst, env);
	else if (mini_strcmp(lst->proc->str[0], "-") == 0)
		old_pwd(lst->proc->str[0], env, lst);
	else if (access(lst->proc->str[0], F_OK) == 0)
	{
		if (chdir(lst->proc->str[0]) == -1)
			no_such_file(lst->proc->str[0], lst);
	}
	else if (lst->proc->str[0] != NULL)
		no_such_file(lst->proc->str[0], lst);
	if (lst->exit_code == 0)
	{
		update_env(env, cwd, "OLDPWD", lst);
		getcwd(cwd, PATH_MAX);
		update_env(env, cwd, "PWD", lst);
	}
}
