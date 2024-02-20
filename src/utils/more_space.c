/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   more_space.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 20:51:27 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/20 20:53:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int		get_strs_util(t_procs *proc, char **process, int i)
{
	if (!proc_redir(process[i]) && proc->cmd_flag != 0
			&& shelly_strcmp(process[i], PIPE) != 0)
			return (1);
	return (0);
}
