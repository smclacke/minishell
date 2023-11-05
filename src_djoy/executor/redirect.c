/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/05 16:27:50 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

#define DIR_MESSAGE "minishell: %s: Is a directory\n"
#define DIR_FILE_MESSAGE "minishell: %s: No such file or directory\n"

/**
 * @param node parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks stats of the infile 
*/
bool	check_infile_stat(t_parser *node, t_execute *data)
{
	struct stat	file_stat;

	if (stat(node->file, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
		{
			data->in = open(node->file, O_RDWR, 0644);
			if (data->in == -1)
			{
				dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, node->file);
				return (false);
			}
			if (dup2(data->in, STDIN_FILENO) == 0)
				close(data->in);
		}
		if (S_ISDIR(file_stat.st_mode))
			dprintf(STDERR_FILENO, DIR_MESSAGE, node->file);
		else if (!S_ISDIR(file_stat.st_mode) && !S_ISREG(file_stat.st_mode))
			dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, node->file);
	}
	return (true);
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function 
*/
bool	redirect_infile(t_parser *head, t_execute *data)
{

	if (mini_strcmp(head->meta, "<") == 0)
	{
		if (head->next)
			head = head->next;
		if (access(head->file, F_OK) != 0)
		{
			dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, head->file);
			return (false);
		}
		if (check_infile_stat(head, data) == false)
			return (false);
	}
	return (true);
}

/**
 * @param head parser linked list
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for redirects enters redirect function
*/
void	redirect_outfile(t_parser *head, t_execute *data)
{
	struct stat	file_stat;

	if (mini_strcmp(head->meta, ">") == 0)
	{
		if (head->next)
			head = head->next;
		if (access(head->file, F_OK) != 0)
		{
			data->out = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->out == -1)
				return ;
		}
		if (stat(head->file, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
				data->out = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (S_ISDIR(file_stat.st_mode))
				dprintf(STDERR_FILENO, DIR_MESSAGE, head->file);
		}
		if (dup2(data->out, STDOUT_FILENO) == 0)
			close(data->out);
		return ;
	}
	return ;
}

/**
 * @param node linked list
 * @brief checks arguments to find output or input redirect
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
	else if (mini_strcmp(node->meta, ">>") == 0)
		return (true);
	else
		return (false);
}

/**
 * @param head parser linked list
 * @param data execute struct
 * @brief appends to outfile instead of overwriting it
 * if file does not exist, it will be created. 
 * if it does exist, the output of command is appended 
 * to the end of the file, preserving the existing content.
*/
void	redirect_append(t_parser *head, t_execute *data)
{
	struct stat	file_stat;

	if (mini_strcmp(head->meta, ">>") == 0)
	{
		if (head->next)
			head = head->next;
		if (access(head->file, F_OK) != 0)
		{
			data->out = open(head->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->out == -1)
				return ;
		}
		if (stat(head->file, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
				data->out = open(head->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (S_ISDIR(file_stat.st_mode))
				dprintf(STDERR_FILENO, "[%s] is a directory\n", head->file);
		}
		if (dup2(data->out, STDOUT_FILENO) == 0)
			close(data->out);
		return ;
	}
	return ;
}

