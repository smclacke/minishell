/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/09 19:47:41 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param lst linked list from parser
 * @brief checks if there's a meta or a builtin
 * sarah parses the word i need to check if the word requires an action:
 * "user" = user (word), "$user" = djoyke (action), '$user' = $user (word)
 * >>
 * >
 * @todo
 * bash-3.2$ cat $djoyke
 * cat: haaa: No such file or directory
 * cat: ggg: No such file or directory (is moeilijk maybe not)
 * 		cat $USER
 * 
 * 		char ** =	[0] cat
 * 					[1] $USER
 * 					[2] NULL
 * 
 * 		expanding handles [1]$USER (could be djoyke etc or nothing)
 * 		if it's nothing char ** after expanding should look like
 * 
 * 		char ** = [0] cat
 * 		[1] NULL
 *		give that to execve
 *		
 *		or:
 * 		
 *		char ** = [0] cat
 *				  [1] djoyke
 *				  [2] NULL
 *
 * 		[1] $USER get's removed not overwritten! (memcpy)
 * 		[2] NULL get's moved up!
 * 		
 * 		➜  ~ echo $USER
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0	
 * 		➜  ~ echo ${USER}
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0
 * 		➜  ~ echo "$USER"
 * 		dreijans
 * 		➜  ~ echo $?
 * 		0
 * 		➜  ~
 * 
 * 		bash-3.2$ echo hi > outfile
 * 		bash-3.2$ cat outfile
 * 		hi
 * 			
 * builtin needs to be redirected to outfile
 * does this mean that if a process ended correctly 
 * it needs to return 0? as in EXIT_SUCCESS?
 * if >>$USER no expanding user it's a delimiter now
*/
void	ft_expand(t_parser *lst, t_env **env)
{
	t_parser	*head;
	t_expand	*exp;
	int			len;

	head = lst;
	exp = NULL;
	while (head)
	{
		if (head->str != NULL)
		{
			len = ft_strlen(head->str);
			dollar(head, env, exp, len);
		}
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

//check if it' a file (for error code)
//check if it's directory (for error code)
//permissions (write read etc)
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
in executor would translate to if 
(parser->file != NULL)
{
	write to parser->fd 
}
*/
void	redirect(t_parser *lst, t_env **env)
{
	//check
}
