/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 16:33:38 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/04 16:42:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @brief redirect heredoc in child process
 * @todo norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
void	redirect_heredoc(t_parser *lst)
{
	if (mini_strcmp(lst->meta, "<<") == 0)
	{
		lst = lst->next;
		if (dup2(lst->hd_fd, STDIN_FILENO) == -1)
			mini_error("dup2", "E_GENERAL", lst);
			// mini_error("dup2", errno);
		if (close(lst->hd_fd) == -1)
			mini_error("close", "E_GENERAL", lst);
			// mini_error("close", errno);
	}
}

/**
 * @param read_line string containing line read.
 * @param file int with file fd.
 * @brief writes to the heredoc frees the read_line
*/
static void	write_to_file(char *read_line, int file)
{
	write(file, read_line, ft_strlen(read_line));
	write(file, "\n", 1);
	free(read_line);
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
 * @todo norm proof, djoyke changed some things regarding mini_error
 * 			parser is not made yet so can't use mini_error function
*/
static void	write_to_heredoc(t_parser *lst, char *file_name)
{
	char	*read_line;
	pid_t	fork_pid;
	int		file;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error("fork", "E_GENERAL", lst);
		// mini_error("fork", errno);
	if (fork_pid == 0)
	{
		handle_signals(HERE_DOC);
		file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (1)
		{
			read_line = readline("heredoc> ");
			if (mini_strcmp(lst->str, read_line) != 0)
				write_to_file(read_line, file);
			else if (mini_strcmp(lst->str, read_line) == 0)
			{
				free(read_line);
				exit (0);
			}
		}
	}
	else
		waitpid(fork_pid, NULL, 0);
}

/**
 * @param lst parser linked list
 * @param str character string for name heredoc
 * @param i int containing number of heredoc
 * @brief makes name for heredoc by adding number of heredoc
 * to the name. unlinks, frees the string and the number.
*/
static void	setup_heredoc(t_parser *lst, char *str, int i)
{
	char		*number;

	number = ft_itoa(i);
	str = ft_strjoin("heredoc", number);
	write_to_heredoc(lst, str);
	lst->hd_fd = open(str, O_RDONLY);
	unlink(str);
	free(str);
	free(number);
}

/**
 * @param lst parser linked list
 * @brief initializes one or multiple heredoc in parent process
 * INODE (files)
 * when opening file and writing to it it changes te position.
 * within that fd there's info about the position in the file 
 * until content ends.
 * file position.
 * hi within a file sets that to pos[3]. you start at pos[0], 
 * to read properly needs to be passed correctly
 * check these by using lseek(fd, 0, SEEK_CUR) before and 
 * after writing to the file.
*/
void	init_heredoc(t_parser *lst)
{
	t_parser	*head;
	char		*heredoc;
	int			i;

	head = lst;
	heredoc = NULL;
	i = 0;
	while (head)
	{
		if (mini_strcmp(head->meta, "<<") == 0)
		{
			i++;
			if (head->next)
				head = head->next;
			if (head->str != NULL)
				setup_heredoc(head, heredoc, i);
		}
		head = head->next;
	}
	return ;
}
