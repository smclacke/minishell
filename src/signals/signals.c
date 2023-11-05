/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 17:40:06 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/05 18:34:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * SIGINT	
 * SIGQUIT
 * SIG_DFL	default signal handling
 * SIG_IGN	signal is ignored
 * 
 * Ctrl-D: is no signal. 
 * Ctrl-D tells the terminal that it should register a EOF on standard input, 
 * which bash interprets as a desire to exit
 * 
 * 
	For the main:
		Ctrl-C: Displays a new prompt, exits with code 1.
		Ctrl-\: Has no effect.

	For here_doc (input redirection):
		Ctrl-C: Displays the here_doc sign, exits with code 1.
		Ctrl-\: Has no effect.

	For child processes (e.g., cat):
		Ctrl-C: Exits the child process, displaying ^C, exits with code 130.
		Ctrl-\: Exits the child process, displaying ^\Quit, exits with code 131.
*/

static void	sig_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		// set exit code to 1
	}
}

// static void	sig_child(void)
// {
// 	// if sigint, exit(130)
// 	// if sigdfl, exit(131)
	
// }

// static void	sig_hd(void)
// {
// 	// sigint, display here_doc sign, exit(1)
// }

void	handle_signals(int proc)
{
	if (proc == 1)
	{
		signal(SIGINT, sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	// else if (proc == CHILD)
	// {
	// 	signal(SIGINT, sig_child);
	// 	signal(SIGQUIT, sig_child);
	// }
	// else if (proc == HERE_DOC)
	// {
	// 	signal(SIGINT, sig_hd);
	// 	signal(SIGQUIT, SIG_IGN);
	// }
}

// in parent? - main
// in child? - func
// in here_doc? - func

// when signals in child, ignore in parent

