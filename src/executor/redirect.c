/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/23 22:44:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param file file str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @param lst parser linked list
 * @brief opens file and throws error if it doesnt exist
 * @todo 
 * norm it
*/
static bool	file_dup(t_parser *lst, t_execute *data, char *file)
{
	data->in = open(file, O_RDWR, 0644);
	if (data->in == -1)
	{
		redir_file_error(file, lst);
		return (false);
	}
	if (dup2(data->in, STDIN_FILENO) == 0)
		close(data->in);
	return (true);
}

/**
 * @param file file str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @param lst parser linked list
 * @brief checks stats of the infile
 * @todo 
 * norm it
*/
static bool	check_infile_stat(char *file, t_execute *data, t_parser *lst)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
		{
			if (file_dup(lst, data, file) == false)
				return (false);
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			dir_error(file, lst);
			return (false);
		}
		else if (!S_ISDIR(file_stat.st_mode) && !S_ISREG(file_stat.st_mode))
		{
			redir_file_error(file, lst);
			return (false);
		}
	}
	return (true);
}

/**
 * @param str redir str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks for infile and opens it 
 * @todo replace dprintf
*/
bool	redirect_infile(char *str, t_execute *data, t_parser *lst)
{
	if (access(str, F_OK) != 0)
	{
		redir_file_error(str, lst);
		return (false);
	}
	if (check_infile_stat(str, data, lst) == false)
		return (false);
	else
		return (true);
}

/**
 * @param str redir str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief creates and opens outfile
 * @todo replace dprintfs
*/
bool	redirect_outfile(char *str, t_execute *data, t_parser *lst)
{
	struct stat	file_stat;

	if (access(str, F_OK) != 0)
	{
		data->out = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->out == -1)
			return (false);
	}
	if (stat(str, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			data->out = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (S_ISDIR(file_stat.st_mode))
		{
			dir_error(str, lst);
			return (false);
		}
	}
	if (dup2(data->out, STDOUT_FILENO) == 0)
		close(data->out);
	return (true);
}

/**
 * @param str redir str
 * @param data execute struct
 * @brief appends to outfile instead of overwriting it
 * if file does not exist, it will be created. 
 * if it does exist, the output of command is appended 
 * to the end of the file, preserving the existing content.
 * @todo 
 * check the replace dprintf 
 * check returns
*/
bool	redirect_append(char *str, t_execute *data, t_parser *lst)
{
	struct stat	file_stat;

	if (access(str, F_OK) == 0 && access(str, W_OK) != 0)
	{
		write_permission_error(str, lst);
		return (false);
	}
	if (stat(str, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			dir_error(str, lst);
			return (false);
		}
	}
	data->out = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->out == -1)
		return (false);
	if (dup2(data->out, STDOUT_FILENO) == 0)
		close(data->out);
	return (true);
}
