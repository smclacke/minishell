/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/18 13:31:59 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/include/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

// # define PROMPT BI_YELLOW".~❃~."BI_PURPLE".~⚘~."BI_CYAN".~✿~."RESET

# define PROMPT "hey Djoyke $"
# define READ 0
# define WRITE 1

#endif