/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/10 17:36:26 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

void	ft_execute(char **envp, t_parser *lst)
{
	t_env	*env;

	env = env_list(envp);
	// print_env_list(env);
	build_process(lst, env);
}

void	build_process(t_parser *lst, t_env *env)
{
	int			fork_pid;
	int			fd_in;
	int			pipe_fd[2];

	fd_in = 0;
	if (dup2(STDIN_FILENO, fd_in) == -1)
		mini_error("dup2", errno);
	if (!lst)
		mini_error("list", errno);
	while (lst)
	{
		if (lst->next)
		{
			fork_pid = fork();
			if (fork_pid == -1)
				mini_error("fork", errno);
			if (fork_pid == 0)
			{
				if (pipe(pipe_fd) == -1)
					mini_error("pipe", errno);
				printf("build_process:		have to get a kindergarten\n");
				mini_forks(lst, env, fd_in, pipe_fd, fork_pid);
				if (dup2(pipe_fd[READ], fd_in) == -1)
				{
					printf("build process:		you came back huh\n");
					mini_error("1.... dup2", errno);
				}
				// close(pipe_fd[READ]);
				// close(pipe_fd[WRITE]);
		}
		else// Parent process - Wait for the child process to finish
			waitpid(fork_pid, NULL, 0); // Properly wait for child process
		}
		lst = lst->next;
	}
	close(pipe_fd[READ]);
	//if redirect found for outfile dup read end to outfile 
	// close(pipe_fd[WRITE]);
}

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
t_parser	*mini_forks(t_parser *lst, t_env *env, int fd_in, int *pipe_fd, int fork_pid)
{
	char	*executable;

	(void) env;
	if (fork_pid == 0)
	{
		printf("mini_forks:		children made\n");
		if (dup2(pipe_fd[READ], fd_in) == -1)
			mini_error(" 2.... dup2", errno);
		close(pipe_fd[READ]); //needs error check
		if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
			mini_error(" 3..... dup2", errno);
		close(pipe_fd[WRITE]);
		executable = 
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
bool	parse_path(t_env *env, t_parser *node)
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
				micro_error ("malloc", errno);
			env->path = ft_split(temp_path, ':');
			if (env->path == NULL)
				micro_error ("malloc", errno);
			free (temp_path);
			if (env->path == NULL)
				micro_error ("malloc", errno);
			return (true);
		}
		i++;
	}
	return (false);
}

char	*find_path(t_env *env, t_parser *node)
{
	char	*command;
	char	*ok_path;
	int		i;

	i = 0;
	if (!micro_absolute_check(node) && micro_parse_path(env, node))
	{
		while (env->path && env->path[i] != NULL)
		{
			command = ft_strjoin("/", node->str);
			if (command == NULL)
				micro_error("strjoin", errno);
			ok_path = ft_strjoin(env->path[i], command);
			if (ok_path == NULL)
				micro_error("strjoin", errno);
			free(command);
			if (access(ok_path, F_OK))
				return (ok_path);//it's a command;
			if (!acces(ok_path, F_OK))
				return(node->str)//its just a string;
			free(ok_path);
			i++;
		}
	}
	return (node->cmd);
}

/* checks if the path acces with access() for the first command */
char	*check_access(t_env *env, t_parser *node)
{
	char	*ok_path;
	char	*command;
	int		i;

	i = 0;
	if (!absolute_check(node->abso) && parse_path(env, node))
	{
		while (env->path && env->path[i] != NULL)
		{
			command = ft_strjoin("/", node->abso);
			if (command == NULL)
				ft_error("malloc", errno);
			ok_path = ft_strjoin(env->path[i], command);
			if (command == NULL)
				ft_error("malloc", errno);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		command_error(node->cmd, errno);//of node->str?
	}
	return (node->cmd);//of node->str?
}

//1) check if str is a command or just a string by parsing path into env and checking if it's valid.
//2) if  it's not a command it needs to be treated as a string
//2) feed that into execve
