/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/12 16:44:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param node parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks stats of the infile 
*/
bool	check_infile_stat(char *file, t_execute *data)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
		{
			data->in = open(file, O_RDWR, 0644);
			if (data->in == -1)
			{
				dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, file);
				// return (false);
			}
			if (dup2(data->in, STDIN_FILENO) == 0)
				close(data->in);
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			dprintf(STDERR_FILENO, DIR_MESSAGE, file);
			// return (false);
		}
		else if (!S_ISDIR(file_stat.st_mode) && !S_ISREG(file_stat.st_mode))
			dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, file);
			// return (false);
	}
	return (true);
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function 
 * @todo name the brief correctly
*/
bool	redirect_infile(t_procs *head, t_execute *data)
{
	if (mini_strcmp(head->redir[0], "<") == 0)
	{
		printf("hi\n");
		if (access(head->redir[1], F_OK) != 0)
		{
			dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, head->redir[1]);
			return (false);
		}
		if (check_infile_stat(head->redir[1], data) == false)
			return (false);
	}
	return (true);
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function
 * @todo check returns norm it hehe
 * name the brief correctly
*/
void	redirect_outfile(t_procs *head, t_execute *data)
{
	struct stat	file_stat;
		
	if (mini_strcmp(head->redir[0], ">") == 0)
	{
		if (access(head->redir[1], F_OK) != 0)
		{
			data->out = open(head->redir[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->out == -1)
				return ;
		}
		if (stat(head->redir[1], &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
				data->out = open(head->redir[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (S_ISDIR(file_stat.st_mode))
			{
				dprintf(STDERR_FILENO, DIR_MESSAGE, head->redir[1]);
				return ;
			}
		}
		if (dup2(data->out, STDOUT_FILENO) == 0)
			close(data->out);
		return ;
	}
	return ;
}

/**
 * @param head parser linked list
 * @param data execute struct
 * @brief appends to outfile instead of overwriting it
 * if file does not exist, it will be created. 
 * if it does exist, the output of command is appended 
 * to the end of the file, preserving the existing content.
 * @todo check the dprintf message and returns
*/
void	redirect_append(t_procs *head, t_execute *data)
{
	struct stat	file_stat;

	if (mini_strcmp(head->redir[0], ">>") == 0)
	{
		if (access(head->redir[1], F_OK) != 0)
		{
			data->out = open(head->redir[1], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->out == -1)
				return ;
		}
		if (stat(head->redir[1], &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
				data->out = open(head->redir[1], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (S_ISDIR(file_stat.st_mode))
				dprintf(STDERR_FILENO, "%s is a directory\n", head->redir[1]);
				// return ;
		}
		if (dup2(data->out, STDOUT_FILENO) == 0)
			close(data->out);
		return ;
	}
	return ;
}
