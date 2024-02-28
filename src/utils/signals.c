/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 17:40:06 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/28 14:52:26 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * @param signum int with signal value
 * @brief called when the parent process receives a SIGINT signal.
 * It replaces the current readline input 
 * with an empty string, starts a new line,
 * and redisplay the prompt.
*/
static void	sig_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @param signum int with signal value
 * @brief Signal handler for the child process.
 * called when the child process receives a SIGINT signal.
 * It simply outputs a newline character to STDOUT_FILENO
*/
static void	sig_child_c(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @param signum int with signal value
 * @brief Signal handler for the child process.
 * called when the child process receives a SIGQUIT signal.
 * It outputs the message "Quit" to STDERR_FILENO.
*/
static void	sig_child_q(int signum)
{
	if (signum == SIGQUIT)
		write(STDERR_FILENO, "Quit\n", 6);
}

/**
 * @param signum The signal number.
 * @brief Signal handler for here_doc (input redirection).
 * called when the here_doc process receives a signal.
 */
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
 * @param proc The type of process (PARENT, CHILD, or HERE_DOC).
 * @brief Sets signal handlers for different process types.
 * sets signal handlers for different process types:
 * - For the parent process: 
 * SIGINT is handled by `sig_parent`, and SIGQUIT is ignored.
 * - For the child process: 
 * SIGINT is handled by `sig_child_c`, and SIGQUIT is handled by `sig_child_q`.
 * - For the here_doc process: 
 * SIGINT is handled by `sig_hd`, and SIGQUIT is ignored.
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
