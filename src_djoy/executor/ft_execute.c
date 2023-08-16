/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:13:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/16 15:10:43 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

void	ft_execute(char **envp, t_parser *lst)
{
	t_env	*env;
	char	**array_env;
	int		i;

	i = 0;
	env = env_list(envp);
	array_env = list_to_string(env);
	// while (array_env[i] != NULL)
	// {
	// 	printf("array = [%s]\n", array_env[i]);
	// 	i++;
	// }
	// // print_env_list(env);
	// printf("----------------------------------------\n");
	// print_list_full(env);
	build(lst, env, array_env);
}

t_fd	*init_fd_struct(void)
{
	t_fd	*fd;

	fd = (t_fd *)malloc(sizeof(t_fd));
	if (!fd)
		mini_error("malloc", errno);
	fd->fd_in = 0;
	fd->fork_pid = 0;
	fd->pipe_fd[READ] = 0;
	fd->pipe_fd[WRITE] = 0;
	return (fd);
}


void	build(t_parser *lst, t_env *env, char **array_env)
{
	t_fd	*fd;

	fd = init_fd_struct();
	if (dup2(STDIN_FILENO, fd->fd_in) == -1)
		mini_error("dup2", errno);
	if (!lst)
		mini_error("list", errno);
	while (lst)
	{
		if (lst->next)
		{
			fd->fork_pid = fork();
			if (fd->fork_pid == -1)
				mini_error("fork", errno);
			if (fd->fork_pid == 0)
			{
				if (pipe(fd->pipe_fd) == -1)
					mini_error("pipe", errno);
				printf("build_process:		have to get a kindergarten\n");
				mini_forks(lst, env, fd, array_env);
				if (dup2(fd->pipe_fd[READ], fd->fd_in) == -1)
				{
					printf("build process:		you came back huh\n");
					mini_error("1 dup2", errno);
				}
				// close(fd->pipe_fd[READ]);
				// close(fd->pipe_fd[WRITE]);
		}
		else// Parent process - Wait for the child process to finish
			waitpid(fd->fork_pid, NULL, 0); // Properly wait for child process
		}
		lst = lst->next;
	}
	close(fd->pipe_fd[READ]);
	//if redirect found for outfile dup read end to outfile 
	// close(pipe_fd[WRITE]);
}

//int dup2(int oldfd, int newfd);

/**
 * @param lst linked list containing commands and atributes
 * @param env linked list containing environment
 * @brief makes child process and executes in it
*/
t_parser	*mini_forks(t_parser *lst, t_env *env, t_fd *fd, char **array_env)
{
	char	*executable;

	printf("fd_in = [%d]\n", fd->fd_in);
	printf("pipe_fd = [%d]\n", fd->pipe_fd[READ]);

	if (fd->fork_pid == 0)
	{
		printf("mini_forks:		children made\n");
		if (dup2(fd->pipe_fd[READ], fd->fd_in) == -1)
		{
			printf("hier 1 ??\n");
			mini_error(" 2.... dup2", errno);
		}
		printf("fd_in = [%d]\n", fd->fd_in);
		printf("pipe_fd = [%d]\n", fd->pipe_fd[READ]);
		if (close(fd->pipe_fd[READ]) == -1)
		{
			mini_error("close", errno);
		}
		if (dup2(fd->pipe_fd[WRITE], STDOUT_FILENO) == -1)
		{
			printf("hier 2??\n");
			mini_error(" 3..... dup2", errno);
		}
		puts("huehue");
		close(fd->pipe_fd[WRITE]);
		executable = check_access(env, lst);
		printf("executble = [%s]\n", executable);
		if (access(executable, X_OK) == -1)
		{
			printf("hier 3??\n");
			mini_error(executable, errno);
		}
		if (execve(executable, &lst->str, array_env) == -1)//but does this only give cat and not the next in the list?
		{
			printf("of hier?\n");
			mini_error(lst->str, errno);
		}
	}
	close(fd->fd_in);
	close(fd->pipe_fd[WRITE]);
	close(fd->pipe_fd[READ]);
	return (lst);
}

bool	absolute_check(t_parser *node)
{
	if (!node->abso)
		return (false);
	if (!ft_strncmp(node->abso, "/", 1) && access(node->abso, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->abso, "./", 2) && access(node->abso, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->abso, "../", 3) && access(node->abso, F_OK) == 0)
		return (true);
	return (false);
}

/* finds the PATH and stores it in a struct as a 2D array*/
bool	parse_path(t_env *env, t_parser *node)
{
	int		i;
	char	*temp_path;

	(void)node;
	i = 0;
	while (env->key[i])
	{
		if (ft_strncmp(&env->key[i], "PATH=", 5) == 0)
		{
			temp_path = ft_substr(&env->value[i], 0, ft_strlen(&env->value[i]));
			if (temp_path == NULL)
				mini_error ("malloc", errno);
			env->path = ft_split(temp_path, ':');
			if (env->path == NULL)
				mini_error ("malloc", errno);
			free (temp_path);
			if (env->path == NULL)
				mini_error ("malloc", errno);
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
	if (!absolute_check(node) && parse_path(env, node))
	{
		while (env->path && env->path[i] != NULL)
		{
			command = ft_strjoin("/", node->str);
			if (command == NULL)
				mini_error("strjoin", errno);
			ok_path = ft_strjoin(env->path[i], command);
			if (ok_path == NULL)
				mini_error("strjoin", errno);
			free(command);
			if (access(ok_path, F_OK))
				return (ok_path);//it's a command;
			if (!access(ok_path, F_OK))
				return(node->str);//its just a string;
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
	if (!absolute_check(node) && parse_path(env, node))
	{
		while (env->path && env->path[i] != NULL)
		{
			command = ft_strjoin("/", node->abso);
			if (command == NULL)
				mini_error("malloc", errno);
			ok_path = ft_strjoin(env->path[i], command);
			if (command == NULL)
				mini_error("malloc", errno);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		mini_error(node->cmd, errno);//of node->str?
		// command_error(node->cmd, errno);//of node->str?
	}
	return (node->cmd);//of node->str?
}

//1) check if str is a command or just a string by parsing 
// path into env and checking if it's valid.
//2) if  it's not a command it needs to be treated as a string
//2) feed that into execve
