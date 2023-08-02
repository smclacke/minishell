/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_execute.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/02 15:46:06 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

// void	micro_build(t_parser *node, t_env *env)
// {
// 	t_parser	*temp_node;
// 	int			fork_pid;

// 	temp_node = node;
// 	if (temp_node->cmd)
// 	{
// 		fork_pid = fork();
// 		if (fork_pid == -1)
// 			micro_error("fork", errno);
// 		if (fork_pid == 0)
// 			micro_check_for_builtin(node, env);
// 	}
// 	temp_node = temp_node->next;
// }

// /**
//  * @param node linked list containing commands and atributes
//  * @param env linked list containing environment
//  * @brief sets pipe to be reused in every child process
//  * @todo change name into something else its not just setting pipes
// */
// t_parser	*micro_build_process(t_parser *node, t_env *env)
// {
// 	int			pipe_fd[2];
// 	int			fd_in;
// 	t_parser	*temp_node;

// 	fd_in = 0;
// 	temp_node = node;
// 	if (dup2(STDIN_FILENO, fd_in) == -1)
// 		micro_error("dup2", errno);
// 	while (temp_node)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 			micro_error("pipe", errno);
// 		printf("are you here\n");
// 		micro_forks(node, env, fd_in, pipe_fd);
// 		if (dup2(pipe_fd[READ], fd_in) == -1)
// 			micro_error("dup2", errno);
// 		close(pipe_fd[READ]);
// 		temp_node = temp_node->next;
// 	}
// 	return (node);
// }

// /**
//  * @param node linked list containing commands and atributes
//  * @param env linked list containing environment
//  * @brief makes child process and executes in it
// */
// t_parser	*micro_forks(t_parser *node, t_env *env, int fd_in, int *pipe_fd)
// {
// 	int			fork_pid;
// 	t_parser	*temp_node;

// 	fork_pid = fork();
// 	temp_node = node;
// 	printf("fork_pid: %d\n", fork_pid);
// 	if (fork_pid == -1)
// 		micro_error("fork", errno);
// 	if (fork_pid == 0)
// 	{
// 		printf("children made\n");
// 		printf("here? 1\n");
// 		if (dup2(pipe_fd[READ], fd_in) == -1)
// 			micro_error("dup2", errno);
// 		close(pipe_fd[READ]); //needs error check
// 		if (dup2(STDOUT_FILENO, pipe_fd[WRITE]) == -1)
// 			micro_error("dup2", errno);
// 			printf("here? 2\n");
// 		micro_check_for_builtin(temp_node, env);//bool?
// 		printf("here? 3\n");
// 		// check_for_heredoc //bool
// 		// check_meta_char //bool
// 		// micro_find_path(env, node);
// 	}
// 	close(fd_in);
// 	close(pipe_fd[WRITE]);
// 	printf("here? 4\n");
// 	return (node);
// }

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
