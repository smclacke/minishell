/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_execute.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/03 17:30:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	micro_execute(char **envp, t_parser *lst)
{
	t_env	*env;

	env = micro_env_list(envp);
	micro_build(lst, env);
}

void	micro_build(t_parser *lst, t_env *env)
{
	printf("cmd = [%s]\n", lst->cmd);
	printf("builtin = [%s]\n", lst->cmd);
	if (lst->cmd)
		micro_check_for_builtin(lst, env);

}

/**
 * @param lst linked list
 * @param env string or char to compare with
 * @brief checks arguments to find meta_chars: 
 * $, >>, <<, >, <, |
 * @todo 
 * 1) needs to be passed to actual process,
 * 2) MAYBE MAKE IT A BOOL?
*/
void	micro_check_for_meta(t_parser *lst)
{
	if (lst->meta == NULL)
		micro_error("meta", errno);
	if (micro_strcmp(lst->meta, "$") == 0)
		printf("dolllaaaah\n");
	else if (micro_strcmp(lst->meta, ">>") == 0)
		printf("Output Append\n");
	else if (micro_strcmp(lst->meta, "<<") == 0)
		printf("here doc\n");
	else if (micro_strcmp(lst->meta, ">") == 0)
		printf("output Redirect\n");
	else if (micro_strcmp(lst->meta, "<") == 0)
		printf("Input Redirect\n");
	else if (micro_strcmp(lst->meta, "|") == 0)
		printf("pipe\n");
}
