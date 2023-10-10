/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/10 21:02:08 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param head parser linked list
 * @param sign int passed to check is string or command
 * @brief checks if string or command and sets str to content of parser node
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

	head = lst;
	exp = NULL;
	while (head)
	{
		expand_dollar(head, env, exp);
		head = head->next;
	}
	head = lst;
	while (head)
	{
		check_for_meta(head);
		if (check_for_builtin(head))
			do_builtin(head, env);
		head = head->next;
	}
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

*/
void	redirect(t_parser *lst, t_env **env)
{
	//check if it' a file (for error code)
	//check if it's directory (for error code)
	//check if it's infile or outfile
	//permissions (write read etc)
	//check if infile exists throw error if it's not
	//if outfile make them all and store the fd's in new part of the node?
	// (parser->file != NULL)
	// {
	// 	write to parser->fd 
	// }
}
