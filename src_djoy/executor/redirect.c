/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/27 18:55:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
// #include <dirent.h>

#define INFILE_ERROR "minishell: %s: No such file or directory\n"

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function
 * @todo
 * check all the prints no needed prints no
 * if dir - `opendir`: Opens a directory stream.
 * readdir`: Reads a directory entry.
 * check how to do last else statement when exiting from a builtin
 *  * check how to do else statement at the end when exiting from a builtin
 * 	// else
	// 	exit(1); only when we figure out how to exit from a builtin use this :)
 * when infile does not exist dont continue opening files thats for in
 * 
*/
void	redirect_infile(t_parser *head, t_execute *data)
{
	struct stat	file_stat;

	if (mini_strcmp(head->meta, "<") == 0)
	{
		head = head->next;
		if (access(head->file, F_OK) != 0)
			dprintf(STDERR_FILENO, INFILE_ERROR, head->file);
		if (stat(head->file, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
			{
				data->in = open(head->file, O_RDWR, 0644);
				if (data->in == -1)
					mini_error("open infile", errno);
				if (dup2(data->in, STDIN_FILENO) == 0)
					close(data->in);
			}
			if (S_ISDIR(file_stat.st_mode))
				dprintf(STDERR_FILENO, "[%s] is a directory\n", head->file);
			else if (!S_ISDIR(file_stat.st_mode) && !S_ISREG(file_stat.st_mode))
				dprintf(STDERR_FILENO, "its not a file or directory\n");
		}
	}
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function
 * @todo
 * if dir - `opendir`: Opens a directory stream.
 * readdir`: Reads a directory entry.
 * check how to do else statement at the end when exiting from a builtin
 * 	// else
	// 	exit(1); only when we figure out how to exit from a builtin use this :)
 * 
*/
void	redirect_outfile(t_parser *head, t_execute *data)
{
	struct stat	file_stat;

	if (mini_strcmp(head->meta, ">") == 0)
	{
		head = head->next;
		if (access(head->file, F_OK) != 0)
		{
			data->out = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->out == -1)
				mini_error("open outfile", errno);
		}
		if (stat(head->file, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
				data->out = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (S_ISDIR(file_stat.st_mode))
				dprintf(STDERR_FILENO, "[%s] is a directory\n", head->file);
		}
		if (dup2(data->out, STDOUT_FILENO) == 0)
			close(data->out);
		return ;
	}
}

/**
 * @param lst parser linked list
 * @brief opens a child proces where it writes to open heredoc
 * until all the delimiter are found 
 * waits for it to finish and exits.
 * @todo
 * with signals easier if we put this in child process
 *  so parent can read exitstatus child to see if exited 
 * with CTRL+C/SIGNAL
*/
static void	write_to_heredoc(t_parser *lst, char *file_name)
{
	char	*read_line;
	pid_t	fork_pid;
	int		file;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error("fork", errno);
	if (fork_pid == 0)
	{
		file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (1)
		{
			printf("hello from write to heredoc\n");
			read_line = readline("< ");
			if (mini_strcmp(lst->str, read_line) != 0)
			{
				write(file, read_line, ft_strlen(read_line));
				write(file, "\n", 1);
				free(read_line);
			}
			else if (mini_strcmp(lst->str, read_line) == 0)
			{
				free(read_line);
				exit (0);
			}
		}
	}
	else
	{
		waitpid(fork_pid, NULL, 0);
	}
}

/**
 * @param lst parser linked list
 * @brief redirect heredoc in child process
 * @todo
 * norm proof
*/
void	redirect_heredoc(t_parser *lst)
{
	if (mini_strcmp(lst->meta, "<<") == 0)
	{
		printf("hi from redirect heredoc\n");
		lst = lst->next;
		if (dup2(lst->hd_fd, STDIN_FILENO) == -1)
			mini_error("dup2", errno);
		if (close(lst->hd_fd) == -1)
			mini_error("close", errno);
	}
}

/**
 * @param lst parser linked list
 * @brief initializes one or multiple heredoc in parent process
 * @todo
 * norm proof
 * heredoc = ft_strjoin("/temp/heredoc", number);// or heredoc
 * INODE (into files deeeep)
 * when opening file and writing to it it changes te position.
 * within that fd there's info about the position in the file until content ends.
 * file position.
 * hi within a file sets that to pos[3]. you start at pos[0], 
 * to read properly needs to be passed correctly
 * check these by using lseek(fd, 0, SEEK_CUR) before and after writing to the file.
*/
void	init_heredoc(t_parser *lst)
{
	t_parser	*head;
	char		*heredoc;
	int			i;
	char		*number;

	head = lst;
	heredoc = NULL;
	i = 0;
	while (head)
	{

		if (mini_strcmp(head->meta, "<<") == 0)
		{
			i++;
			head = head->next;
			if (head->str != NULL)
			{
				number = ft_itoa(i);
				heredoc = ft_strjoin("heredoc", number);
				write_to_heredoc(head, heredoc);
				head->hd_fd = open(heredoc, O_RDONLY);
				unlink(heredoc);
				free(heredoc);
				free(number);
			}
		}
		head = head->next;
	}
	return ;
}

	// else if (mini_strcmp(node->meta, ">>") == 0)
	// {
	// 	printf("append found");
	// 	return (true);
	// }
