/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 17:40:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/22 18:54:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * @todo	exit codes need to be set properly
 * @todo	tidy comments
*/

//	For the main:
// 	Ctrl-C: Displays a new prompt, exits with code 1.
// 	Ctrl-\: Has no effect.
static void	sig_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		// tmp->exit_code = 1;//whut
	}
}

// 	Ctrl-C: Exits the child process, displaying ^C, exits with code 130.
static void	sig_child_c(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

// 	Ctrl-\: Exits the child process, displaying ^\Quit, exits with code 131.
static void	sig_child_q(int signum)
{	
	if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit\n", 6);
		// tmp->exit_code = (signum + 128);// USE GLOBAL, and if that doesnt work use wait
	}	
}

//	For here_doc (input redirection):
// 	Ctrl-C: Displays the here_doc sign, exits with code 1.
// 	Ctrl-\: Has no effect.
static void	sig_hd(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		exit (130);
	}
}

/**
 * @todo doenst show ^C after trying to get out of cat
 * when ending herdoc withoud delimiter ^C exits herdoc does not execute anything eg cat << eof
 * ^D shows empty herdoc line and ends as if eof has been given.
*/
void	handle_signals(int proc)
{
	if (proc == PARENT)
	{
		signal(SIGINT, sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (proc == CHILD)
	{
		signal(SIGINT, sig_child_c);
		signal(SIGQUIT, sig_child_q);
	}
	if (proc == HERE_DOC)
	{
		signal(SIGINT, sig_hd);
		signal(SIGQUIT, SIG_IGN);
	}
}
