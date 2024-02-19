/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 16:33:38 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/19 21:06:35 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param lst parser linked list
 * @brief redirect heredoc in child process
 * @todo exit errors
 * @note change mini_error
*/
void	redirect_heredoc(t_parser *lst)
{
	if (dup2(lst->proc->hd_fd, STDIN_FILENO) == -1)
		mini_error(E_GENERAL, lst);
	if (close(lst->proc->hd_fd) == -1)
		mini_error(E_GENERAL, lst);
}

/**
 * @param read_line string containing line read.
 * @param file int with file fd.
 * @brief writes to the heredoc frees the read_line
*/
static void	write_to_file(t_parser *lst, char *readline, t_env **env, int file)
{
	if (lst && lst->hd_flag == 0) 
	{
		if (ft_isdollar(readline))
			readline = hd_expand(env, readline);
	}
	if (readline)
	{
		write(file, readline, ft_strlen(readline));
		free(readline);
	}
	write(file, "\n", 1);
}

/**
 * @param lst parser linked list
 * @brief opens a child proces where it writes to open heredoc
 * until all the delimiter are found 
 * waits for it to finish and exits.
 * with signals easier if we put this in child process
 * so parent can read exitstatus child to see if exited 
 * @todo
 * with CTRL+C/SIGNAL
 * exit codes
 * Norm it!
*/
static void	write_to_heredoc(t_procs *lst, t_env **env, char *file_name, int i)
{
	char	*read_line;
	pid_t	fork_pid;
	int		file;

	fork_pid = fork();
	if (fork_pid == -1)
		mini_error(E_GENERAL, lst->parser);
	if (fork_pid == 0)
	{
		handle_signals(HERE_DOC);
		file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file == -1)
		{
			// mini_error(E_USAGE, lst->proc->parser);
			exit(E_USAGE);//for time being exit seperate
		}
		while (i < lst->hd_count)
		{
			read_line = readline("heredoc> ");
			if (mini_strcmp(lst->hd[i], read_line) == 0)
			{
				free(read_line);
				exit (0);
			}
			else
				write_to_file(lst->parser, read_line, env, file);	
		}
		free(read_line);
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
 * @todo NORM IT
*/
static void	setup_heredoc(t_procs *lst, t_env **env, char *str)
{
	char		*number;
	int			i;

	i = 0;
	while (i < lst->hd_count)
	{
		number = ft_itoa(i);
		str = mini_strjoin("heredoc", number);
		write_to_heredoc(lst, env, str, i);
		lst->hd_fd = open(str, O_RDONLY);
		unlink(str);
		free(str);
		free(number);
		i++;
	}
	return ;
}

/**
 * @param lst parser linked list
 * @brief 
 * If there are multiple processes, iterate through proc_arrs
 * If there's only one process, handle its heredocs
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
 * @todo norm it
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
			for (int i = 0; i < head->proc_count; i++)
			{
				setup_heredoc(head->process[i], env, heredoc);
			}
		}
		else
			setup_heredoc(head->proc, env, heredoc);
		head = head->next;
	}
	return ;
}
