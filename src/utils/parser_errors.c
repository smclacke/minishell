/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 16:13:00 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/16 17:38:55 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	malloc_error(t_parser *par, t_procs *proc, char **str, int flag)
{
	if (str)
		ft_free_arr(str);
	if (flag == 2 && par)
		ft_free_arr(*par->proc_arrs);
	if (flag == 1 && proc)
		free_procs(proc);
	if (proc)
		free(proc);
	if (par)
		free(par);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("malloc error\n", STDERR_FILENO);
	exit(E_MALLOC);
}