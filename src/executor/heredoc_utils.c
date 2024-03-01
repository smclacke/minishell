/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 16:33:38 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 21:13:47 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @brief redirect heredoc in child process
*/
void	redirect_heredoc(t_parser *lst)
{
	if (dup2(lst->proc->hd_fd, STDIN_FILENO) == -1)
		lst->exit_code = E_GENERAL;
	if (lst->proc->hd_fd != -1 && close(lst->proc->hd_fd) == -1)
		lst->exit_code = E_CLOSE;
}

/**
 * @param read_line string containing line read.
 * @param file int with file fd.
 * @brief writes to the heredoc until all delimiters are found
 * frees the read_line
*/
void	heredoc_proc(t_procs *lst, t_env **env, char *file_name, int i)
{
	char	*read_line;
	int		file;

	handle_signals(HERE_DOC);
	file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file == -1)
		exit(E_GENERAL);
	while (i < lst->hd_count)
	{
		read_line = readline("heredoc> ");
		if (mini_strcmp(lst->hd[i], read_line) == 0 || read_line == NULL)
		{
			if (close(file) == -1)
				lst->parser->exit_code = E_CLOSE;
			free(read_line);
			exit (EXIT_SUCCESS);
		}
		else
			write_to_file(lst->parser, read_line, env, file);
	}
	free(read_line);
}

/**
 * @param lst parser linked list
 * @param env environment linked list
 * @param file_name string containing file name
 * @param i int index
 * @brief opens a child proces where heredoc process is called
 * and exits with correct signals from the process 
 * waits for it to finish and exits.
*/
static void	write_to_heredoc(t_procs *lst, t_env **env, char *file_name, int i)
{
	pid_t	fork_pid;
	int		status;

	status = 0;
	fork_pid = fork();
	if (fork_pid == -1)
		lst->parser->exit_code = E_GENERAL;
	if (fork_pid == 0)
		heredoc_proc(lst, env, file_name, i);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(fork_pid, &status, 0);
	}
}

/**
 * @param lst parser linked list
 * @param str character string for name heredoc
 * @param env environment linked list
 * @brief makes name for heredoc by adding number of heredoc
 * to the name. unlinks, frees the string and the number.
*/
static void	setup_heredoc(t_procs *lst, t_env **env, char *str)
{
	char		*number;
	int			i;

	i = 0;
	while (i < lst->hd_count)
	{
		number = ft_itoa(i);
		if (number == NULL)
			exit(E_MALLOC);
		str = mini_strjoin("heredoc", number);
		write_to_heredoc(lst, env, str, i);
		if (lst->hd_fd != -1)
			close(lst->hd_fd);
		lst->hd_fd = open(str, O_RDONLY);
		if (lst->hd_fd == -1)
			exit(EXIT_FAILURE);
		free(str);
		free(number);
		i++;
	}
	return ;
}

/**
 * @param lst parser linked list
 * @param env environment linked list
 * @brief 
 * initializes one or multiple heredoc in parent process
 * INODE (files)
 * when opening file and writing to it it changes te position.
 * within that fd there's info about the position in the file 
 * until content ends.
 * file position.
 * within a file sets that to pos[3]. you start at pos[0], 
 * to read properly needs to be passed correctly
 * check these by using lseek(fd, 0, SEEK_CUR) before and 
 * after writing to the file.
*/
void	init_heredoc(t_parser *lst, t_env **env)
{
	t_parser	*head;
	char		*heredoc;
	int			i;

	head = lst;
	heredoc = NULL;
	i = 0;
	while (head)
	{
		if (head->multi_proc_b)
		{
			while (i < head->proc_count)
			{
				setup_heredoc(head->process[i], env, heredoc);
				i++;
			}
		}
		else
			setup_heredoc(head->proc, env, heredoc);
		head = head->next;
	}
	return ;
}
