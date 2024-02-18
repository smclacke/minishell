/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 16:13:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/18 19:54:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	syntax_error(char *str)
{
	printf("minishell: %s\n", str);
	exit(E_SYNTAX);
}

void	general_error(char *str)
{
	printf("minishell: %s\n", str);
	exit(E_GENERAL);
}

void	malloc_error(t_parser *par, t_procs *proc, char **str, int flag)
{
	if (str)
		ft_free_arr(str);
	if (flag == 2 && par)
		ft_free_arr(*par->proc_arrs);
	if (flag == 1 && proc)
		free_procs(proc);
	if (flag == 3 && par)
	{
		if (par->proc_arrs)
			ft_free_arr(*par->proc_arrs);
		if (par->proc)
			free_procs(par->proc);
	}
	if (proc)
		free(proc);
	if (par)
		free(par);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("malloc error\n", STDERR_FILENO);
	exit(E_MALLOC);
}
