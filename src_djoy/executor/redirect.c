/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:25:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/25 14:30:39 by dreijans      ########   odam.nl         */
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
		// else
		// 	exit(1); only when we figure out how to exit from a builtin use this :)
	}
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function
 * @todo
 * if dir - `opendir`: Opens a directory stream.
 * readdir`: Reads a directory entry.
 * check how to do last else statement when exiting from a builtin
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
	// else
	// 	exit(1); only when we figure out how to exit from a builtin use this :)
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for heredoc
 * @todo
 * open directory to put all the heredoc files in `opendir`: Opens a directory stream.
 * readdir`: Reads a directory entry.
 * how do I pass herdoc properly into childprocess for eg cat to read?
 * NO MULTIPLES? multiples dont work now
*/
void	heredoc(t_parser *lst, t_execute *data)
{
	t_parser	*head;
	char		*read_line;
	char		*heredoc;
	int			i;
	char		*number;

	head = lst;
	read_line = NULL;
	heredoc = NULL;
	i = 0;
	while (head)
	{
		if (mini_strcmp(head->meta, "<<") == 0)
		{
			printf("heredoc found\n");
			i++;
			head = head->next;
			if (head->str != NULL)
			{
				number = ft_itoa(i);
				heredoc = ft_strjoin("heredoc", number);
				data->hdoc_fd = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
				free(heredoc);
				free(number);
			}
			while (1)
			{
				read_line = readline(PROMPT);
				if (mini_strcmp(head->str, read_line) != 0)
				{
					write(data->hdoc_fd, read_line, ft_strlen(read_line));
					write(data->hdoc_fd, "\n", 1);
				}
				if (mini_strcmp(head->str, read_line) == 0)
				{
					free(read_line);
					if (dup2(data->hdoc_fd, STDIN_FILENO) == -1)// do you need STD_IN?
						mini_error("dup2", errno);
					return ;
				}
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
