/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/26 16:31:02 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	micro_execute(char **envp, t_parser *node)
{
	t_env	*env;

	env = micro_env_list(envp);
	micro_build_process(node, env);
}

/**
 * @param node linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief sets pipe to be reused in every child process
 * @todo change name into something else its not just setting pipes
*/
void	micro_build_process(t_parser *node, t_env *env)
{
	int	pipe_fd[2];
	int	fd_in;

	fd_in = 0;
	if (dup2(STDIN_FILENO, fd_in) == -1)
		micro_error("dup2", errno);
	while (node->cmd)
	{
		if (pipe(pipe_fd) == -1)
			micro_error("pipe", errno);
		micro_set_forks(node, env, fd_in, pipe_fd);
		if (dup2(pipe_fd[READ], fd_in) == -1)
			micro_error("dup2", errno);
		close(pipe_fd[READ]);
		node = node->next;
	}
}

/**
 * @param node linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
void	micro_set_forks(t_parser *node, t_env *env, int fd_in, int *pipe_fd)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		micro_error("fork", errno);
	if (fork_pid == 0)
		printf("children made\n");
	if (dup2(pipe_fd[READ], fd_in) == -1)
		micro_error("dup2", errno);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		micro_error("dup2", errno);
	micro_check_for_builtins(node, env);//bool?
	// check_for_heredoc //bool
	// check_meta_char //bool
	micro_find_path(env, node);
	close(fd_in);
	close(pipe_fd[WRITE]);
}

bool	micro_absolute_check(t_parser *node)
{
	if (!ft_strncmp(node->cmd, "/", 1) && access(node->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->cmd, "./", 2) && access(node->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->cmd, "../", 3) && access(node->cmd, F_OK) == 0)
		return (true);
	return (false);
}

/* finds the PATH and stores it in a struct as a 2D array*/
bool	parse_path(t_env *env, t_command *command)
{
	int		i;
	char	*temp_path;	

	i = 0;
	while (env->key[i])
	{
		if (ft_strncmp(&env->key[i], "PATH=", 5) == 0)
		{
			temp_path = ft_substr(&env->value[i], 0, ft_strlen(&env->value[i]));
			if (temp_path == NULL)
				mini_error ("malloc", errno);
			command->path = ft_split(temp_path, ':');
			if (command->path == NULL)
				mini_error ("malloc", errno);
			free (temp_path);
			if (command->path == NULL)
				mini_error ("malloc", errno);
			return (true);
		}
		i++;
	}
	return (false);
}

char	*micro_find_path(t_env *env, t_parser *node)
{
	char	*command;
	char	*ok_path;
	int		i;

	i = 0;
	if (!absolute_check(node->cmd) && parse_path(env, node))
	{
		while (input->path && input->path[i] != NULL)
		{
			command = ft_strjoin("/", input->command);
			if (command == NULL)
				mini_error("strjoin", errno);
			ok_path = ft_strjoin(input->path[i], command);
			if (ok_path == NULL)
				mini_error("strjoin", errno);
			free(command);
			if (access(ok_path, F_OK))
				return (ok_path);
			free(ok_path);
			i++;
		}
	}
	return (input->command);
}
