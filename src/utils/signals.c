/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 17:40:06 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/07 16:05:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * SIGINT	
 * SIGQUIT
 * SIG_IGN	signal is ignored
 * 
 * Ctrl-D: is no signal. 
 * Ctrl-D tells the terminal that it should register a EOF on standard input, 
 * which bash interprets as a desire to exit
*/

	// For the main:
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
		// set exit code to 1
	}
}

	// 	Ctrl-C: Exits the child process, displaying ^C, exits with code 130.
static void	sig_child_c(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		// set exit code to 130 (signum + 128)
	}
	
}

	// 	Ctrl-\: Exits the child process, displaying ^\Quit, exits with code 131.
static void	sig_child_q(int signum)
{	
	if (signum == SIGQUIT)
	{
		printf("Quit\n"); // why do we exit here without exiting?
		// set exit code to 131 (signum + 128)
	}
}

	// For here_doc (input redirection):
	// 	Ctrl-C: Displays the here_doc sign, exits with code 1.
	// 	Ctrl-\: Has no effect.
static void	sig_hd(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		exit(1);
	}
}

void	handle_signals(int proc)
{
	struct termios	term;

	// tcgetattr(STDIN_FILENO, &term);
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	if (proc == PARENT)
	{
		signal(SIGINT, sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (proc == CHILD)
	{
		tcgetattr(STDIN_FILENO, &term);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, sig_child_c);
		signal(SIGQUIT, sig_child_q);
	}
	else if (proc == HERE_DOC)
	{
		tcgetattr(STDIN_FILENO, &term);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, sig_hd);
		signal(SIGQUIT, SIG_IGN);
	}
}

// in parent? - main
// in child? - func
// in here_doc? - func

// when signals in child, ignore in parent

