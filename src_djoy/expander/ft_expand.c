/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/13 20:20:38 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param head parser linked list
 * @param sign int passed to check is string or command
 * @brief checks if string or command and sets str to content of parser node
 * 
 * dollar in double, remove quotes
 * dollar single, dont expand
 * dollar + -> up to quote
 * "$USER" = expanded user
 * '$USER' = $USER
 * $something"string" = expanded something, + string
 * $hello'<thing' = expanded hello + <thing
 * 
*/
char	*set_expand_string(t_parser *head, int *sign)
{
	char		*str;

	str = NULL;
	if (head->cmd != NULL)
	{
		if (ft_strnstr(head->cmd, "$", ft_strlen(head->cmd)))
		{
			*sign = 1;
			str = head->cmd;
		}
	}
	else if (head->str != NULL)
	{
		if (ft_strnstr(head->str, "$", ft_strlen(head->str)))
		{
			*sign = 2;
			str = head->str;
		}
	}
	return (str);
}

/**
 * @param head parser linked list
 * @param env environment linked list
 * @param exp expander struct
 * @brief checks parser node if command or string part has something
 * to expand. assign expanded string back to command or string part of node.
*/
void	expand_dollar(t_parser *head, t_env **env, t_expand *exp)
{
	int			len;
	int			sign;
	char		*str;

	sign = 0;
	str = set_expand_string(head, &sign);
	if (sign == 1 || sign == 2)
	{
		len = ft_strlen(str);
		str = dollar(str, env, exp, len);
		if (sign == 1)
		{
			head->cmd = str;
			sign = 0;
		}
		else if (sign == 2)
		{
			head->str = str;
			sign = 0;
		}
	}
}

/**
 * @param lst linked list from parser
 * @param env environment linked list
 * @brief checks if there's a meta or a builtin
 * @todo
 * check DJOYKE_TD.MD
*/
void	ft_expand(t_parser *lst, t_env **env)
{
	t_parser	*head;
	t_expand	*exp;
	t_execute	data;

	head = lst;
	exp = NULL;
	while (head)
	{
		expand_dollar(head, env, exp);
		head = head->next;
	}
	head = lst;
	// while (head)
	// {
	// 	init_execute_struct(&data, *env);
	// 	redirect(head, env, &data);
	// 	head = head->next;
	// }
	// head = lst;
	// while (head)
	// {
	// 	// check_for_meta(head);
	// 	if (check_for_env_builtin(head))
	// 		do_builtin(head, env);
	// 	head = head->next;
	// }
}

/*
	➜  minishell git:(djoyke) ✗ < hi.txt wc > outfile.txt 
	zsh: no such file or directory: hi.txt
	➜  minishell git:(djoyke) ✗ pwd
	/home/dreijans/Documents/rank3/minishell
	➜  minishell git:(djoyke) ✗ rm outfile.txt
	rm: cannot remove 'outfile.txt': No such file or directory
	➜  minishell git:(djoyke) ✗ cd src_djoy 
	➜  src_djoy git:(djoyke) ✗ < hi.txt wc |  > outfile.txt 
	zsh: no such file or directory: hi.txt
	➜  src_djoy git:(djoyke) ✗ rm outfile.txt   

		dreijans@f0r2s3:~$ < hi | echo hello
		hello
		dreijans@f0r2s3:~$ bash: hi: No such file or directory
		^C
		dreijans@f0r2s3:~$ < hi echo hello | echo hello
		hello
		bash: hi: No such file or directory

for check dir or file:
		//save fd somewhere
		//permissions (write read etc)

//do this in the child process

//if dir - `opendir`: Opens a directory stream.
- `readdir`: Reads a directory entry.
// */
// void	redirect_infile(t_parser *head, t_env **env, t_execute *data)
// {
// 	struct stat	file_stat;

// 	if (mini_strcmp(head->meta, "<") == 0)
// 	{
// 		head = head->next;
// 		if (access(head->file, F_OK) != 0)
// 		{
// 			ft_putstr_fd("minishell: ", STDOUT_FILENO);
// 			ft_putstr_fd(head->file, STDOUT_FILENO);
// 			ft_putstr_fd(":", STDOUT_FILENO);
// 			ft_putstr_fd(" No such file or directory\n", STDOUT_FILENO);
// 		}
// 		if (stat(head->file, &file_stat) == 0)
// 		{
// 			if (S_ISREG(file_stat.st_mode))
// 				data->infile_fd = open(head->file, O_RDWR);
// 			if (S_ISDIR(file_stat.st_mode))
// 				printf("[%s] is a directory\n", head->file);
// 			else
// 				printf("its not a file or directory");
// 		}
// 	}
// }

void	redirect_outfile(t_parser *head, t_env **env, t_execute *data)
{
	struct stat	file_stat;

	printf("entered redirect function\n");
	if (mini_strcmp(head->meta, ">") == 0)
	{
		printf("> found \n");
		head = head->next;
		if (access(head->file, F_OK) != 0)
		{
			printf("data->outfile = [%i]\n", data->outfile_fd);
			data->outfile_fd = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			printf("data->outfile = [%i]\n", data->outfile_fd);
			printf("[%s] is outfile created \n", head->file);
			if (data->outfile_fd == -1)
				printf("oeps\n");
		}
		if (stat(head->file, &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
			{
				printf("[%s] is a regular file\n", head->file);
				data->outfile_fd = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0644); // if it exists, we don't need to create
			}
			if (S_ISDIR(file_stat.st_mode))
				printf("[%s] is a directory\n", head->file);
			else
				printf("its not a directory\n");
		}
		if (dup2(data->outfile_fd, STDOUT_FILENO) == 0)
		{
			printf("dup2 outfile to ST_OUT went wrong\n");
			close(data->outfile_fd);
		}
	}
	if (dup2(data->outfile_fd, STDOUT_FILENO) == 0)
	{
		printf("dup2 outfile to ST_OUT went wrong\n");
		close(data->outfile_fd);
	}
	close(data->outfile_fd);
}
