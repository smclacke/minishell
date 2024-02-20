/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 17:40:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/20 18:29:34 by dreijans      ########   odam.nl         */
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
	// t_parser		*tmp;

	// tmp = NULL;
	if (signum == SIGINT)
	{
		// rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		// tmp->exit_code = 1;
	}
}

// 	Ctrl-C: Exits the child process, displaying ^C, exits with code 130.
static void	sig_child_c(int signum)
{
	// t_parser		*tmp;

	// tmp = NULL;
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		// tmp->exit_code = (signum + 128);
	}
}

// 	Ctrl-\: Exits the child process, displaying ^\Quit, exits with code 131.
static void	sig_child_q(int signum)
{	
	// t_parser		*tmp;

	// tmp = NULL;
	if (signum == SIGQUIT)
	{
		printf("Quit\n");
		// tmp->exit_code = (signum + 128);
	}
}

//	For here_doc (input redirection):
// 	Ctrl-C: Displays the here_doc sign, exits with code 1.
// 	Ctrl-\: Has no effect.
static void	sig_hd(int signum)
{
	// t_parser		*tmp;

	// tmp = NULL;
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		// lst->exit_code = E_GENERAL;
		exit(E_GENERAL);
	}
}

/**
 * @todo doenst show ^C after trying to get out of cat
*/
void	handle_signals(int proc)
{
	struct termios	term;

	if (proc == PARENT)
	{
		signal(SIGINT, sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (proc == CHILD)
	{
		tcgetattr(STDIN_FILENO, &term);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, sig_child_c);
		signal(SIGQUIT, sig_child_q);
	}
	if (proc == HERE_DOC)
	{
		tcgetattr(STDIN_FILENO, &term);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, sig_hd);
		signal(SIGQUIT, SIG_IGN);
	}
}
