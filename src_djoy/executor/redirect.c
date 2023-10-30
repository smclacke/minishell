/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/30 16:38:30 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

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
 * @param node linked list
 * @brief checks arguments to find output or input redirect
 * @todo add append with O_APPEND and << 
*/
bool	check_redirect(t_parser *node)
{
	if (!node)
		return (false);
	if (mini_strcmp(node->meta, ">") == 0)
		return (true);
	else if (mini_strcmp(node->meta, "<<") == 0)
		return (true);
	else if (mini_strcmp(node->meta, "<") == 0)
		return (true);
	// else if (mini_strcmp(node->meta, "<<") == 0)
	// 	return (true); or add append to redirect_output
	else
		return (false);
}



	// else if (mini_strcmp(node->meta, ">>") == 0)
	// {
	// 	printf("append found");
	// 	return (true);
	// }
