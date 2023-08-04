/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/04 15:24:29 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

void	ft_execute(char **envp, t_parser *lst)
{
	t_env	*env;

	env = env_list(envp);
	build_process(lst, env);
}

void	build_process(t_parser *lst, t_env *env)
{
	int			fork_pid;
	int			fd_in;
	int			pipe_fd[2];

	// printf("execute:		cmd = [%s]\n", lst->cmd);
	// printf("execute:		builtin = [%s]\n", lst->cmd);
	// printf("execute:		meta = [%s]\n", lst->meta);
	// printf("execute:		str = [%s]\n", lst->str);
	fd_in = 0;
	if (dup2(STDIN_FILENO, fd_in) == -1)
		mini_error("dup2", errno);
	if (!lst)
		mini_error("list", errno);
	while (lst)
	{
		if (lst->cmd)
		{
			fork_pid = fork();
			if (fork_pid == -1)
				mini_error("fork", errno);
			if (fork_pid == 0)
			{
				if (pipe(pipe_fd) == -1)
					mini_error("pipe", errno);
				printf("build_process:		have to get a kindergarten\n");
				mini_forks(lst, env, fd_in, pipe_fd);
				if (dup2(pipe_fd[READ], fd_in) == -1)
				{
					printf("build process:		you came back huh\n");
					mini_error("dup2", errno);
				}
				close(pipe_fd[READ]);
			}
		}
		lst = lst->next;
	}
}

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
t_parser	*mini_forks(t_parser *lst, t_env *env, int fd_in, int *pipe_fd)
{
	int			fork_pid;
	t_parser	*temp_lst;

	fork_pid = fork();
	temp_lst = lst;
	(void) env;
	printf("mini_forks:			fork_pid[%d]\n", fork_pid);
	if (fork_pid == -1)
		mini_error("fork", errno);
	if (fork_pid == 0)
	{
		printf("mini_forks:		children made\n");
		if (dup2(pipe_fd[READ], fd_in) == -1)
			mini_error("dup2", errno);
		close(pipe_fd[READ]); //needs error check
		if (dup2(STDOUT_FILENO, pipe_fd[WRITE]) == -1)
			mini_error("dup2", errno);
		// mini_find_path(env, lst);
	}
	close(fd_in);
	close(pipe_fd[WRITE]);
	close(pipe_fd[READ]);
	return (lst);
}

// bool	micro_absolute_check(t_parser *node)
// {
// 	if (!ft_strncmp(node->cmd, "/", 1) && access(node->cmd, F_OK) == 0)
// 		return (true);
// 	if (!ft_strncmp(node->cmd, "./", 2) && access(node->cmd, F_OK) == 0)
// 		return (true);
// 	if (!ft_strncmp(node->cmd, "../", 3) && access(node->cmd, F_OK) == 0)
// 		return (true);
// 	return (false);
// }

/* finds the PATH and stores it in a struct as a 2D array*/
// bool	micro_parse_path(t_env *env, t_parser *node)
// {
// 	int		i;
// 	char	*temp_path;	

// 	i = 0;
// 	while (env->key[i])
// 	{
// 		if (ft_strncmp(&env->key[i], "PATH=", 5) == 0)
// 		{
// 			temp_path = ft_substr(&env->value[i], 0, ft_strlen(&env->value[i]));
// 			if (temp_path == NULL)
// 				micro_error ("malloc", errno);
// 			node->path = ft_split(temp_path, ':');
// 			if (node->path == NULL)
// 				micro_error ("malloc", errno);
// 			free (temp_path);
// 			if (node->path == NULL)
// 				micro_error ("malloc", errno);
// 			return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }

// char	*micro_find_path(t_env *env, t_parser *node)
// {
// 	char	*command;
// 	char	*ok_path;
// 	int		i;

// 	i = 0;
// 	if (!micro_absolute_check(node) && micro_parse_path(env, node))
// 	{
// 		while (node->path && node->path[i] != NULL)
// 		{
// 			command = ft_strjoin("/", node->cmd);
// 			if (command == NULL)
// 				micro_error("strjoin", errno);
// 			ok_path = ft_strjoin(node->path[i], command);
// 			if (ok_path == NULL)
// 				micro_error("strjoin", errno);
// 			free(command);
// 			if (access(ok_path, F_OK))
// 				return (ok_path);
// 			free(ok_path);
// 			i++;
// 		}
// 	}
// 	return (node->cmd);
// }
