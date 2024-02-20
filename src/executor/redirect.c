/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/20 21:36:26 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param file file str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @brief checks stats of the infile
 * @todo 
 * replace dprintf 
 * norm it
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
				return (false);
			}
			if (dup2(data->in, STDIN_FILENO) == 0)
				close(data->in);
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			dprintf(STDERR_FILENO, DIR_MESSAGE, file);
			return (false);
		}
		else if (!S_ISDIR(file_stat.st_mode) && !S_ISREG(file_stat.st_mode))
		{
			dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, file);
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
bool	redirect_infile(char *str, t_execute *data)
{
	if (access(str, F_OK) != 0)
	{
		dprintf(STDERR_FILENO, DIR_FILE_MESSAGE, str);
		return (false);
	}
	if (check_infile_stat(str, data) == false)
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
bool	redirect_outfile(char *str, t_execute *data)
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
			dprintf(STDERR_FILENO, DIR_MESSAGE, str);
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
bool	redirect_append(char *str, t_execute *data)
{
	struct stat	file_stat;

	if (access(str, F_OK) == 0 && access(str, W_OK) != 0)
	{
		dprintf(STDERR_FILENO, "%s no writing permissions\n", str);
		return (false);
	}
	if (stat(str, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			dprintf(STDERR_FILENO, "%s is a directory\n", str);
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
