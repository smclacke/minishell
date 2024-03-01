/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 18:01:59 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 21:50:59 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param file file str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @param lst parser linked list
 * @brief opens file and throws error if it doesnt exist
 * @note errno exit codes beacause it's a file
*/
static bool	file_dup(t_parser *lst, t_execute *data, char *file)
{
	data->in = open(file, O_RDONLY, 0644);
	if (data->in == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file);
		lst->exit_code = errno;
		return (false);
	}
	if (dup2(data->in, STDIN_FILENO) != -1)
		if (close(data->in) == -1)
			lst->exit_code = E_CLOSE;
	return (true);
}

/**
 * @param file file str
 * @param data struct containing fd's and 2d arrays needed for execution
 * @param lst parser linked list
 * @brief checks stats of the infile
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
*/
bool	redirect_infile(char *str, t_execute *data, t_parser *lst)
{
	if (access(str, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		lst->exit_code = errno;
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
*/
bool	redirect_outfile(char *str, t_execute *data, t_parser *lst)
{
	struct stat	file_stat;

	if (access(str, F_OK) != 0)
	{
		if (shelly_strcmp(str, "") == 0)
			return (redir_file_error(str, lst), false);
		data->out = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->out == -1)
			return (redir_error(lst, str));
	}
	if (stat(str, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			data->out = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->out == -1)
			return (redir_error(lst, str));
		if (S_ISDIR(file_stat.st_mode))
			return (dir_error(str, lst));
	}
	if (dup2(data->out, STDOUT_FILENO) != -1)
		if (close(data->out) == -1)
			lst->exit_code = E_CLOSE;
	return (true);
}

/**
 * @param str redir str
 * @param data execute struct
 * @brief appends to outfile instead of overwriting it
 * if file does not exist, it will be created. 
 * if it does exist, the output of command is appended 
 * to the end of the file, preserving the existing content.
*/
bool	redirect_append(char *str, t_execute *data, t_parser *lst)
{
	struct stat	file_stat;

	if (shelly_strcmp(str, "") == 0)
		return (redir_file_error(str, lst), false);
	if (access(str, F_OK) == 0 && access(str, W_OK) != 0)
	{
		write_permission_error(str, lst);
		return (false);
	}
	if (stat(str, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (dir_error(str, lst));
	}
	data->out = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->out == -1)
		redir_error(lst, str);
	if (dup2(data->out, STDOUT_FILENO) != -1)
		if (close(data->out) == -1)
			lst->exit_code = E_CLOSE;
	return (true);
}
