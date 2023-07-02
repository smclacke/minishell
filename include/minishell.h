/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/02 15:47:35 by SarahLouise   ########   odam.nl         */
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

# define PROMPT BI_YELLOW".~❃~."BI_PURPLE".~⚘~."BI_CYAN".~✿~."RESET


# define PROMPT "hey Djoyke $"
# define READ 0
# define WRITE 1





// Colours
# define RESET "\033[0m"
# define RED "\033[1;91m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"
# define BLUE "\033[1;94m"
# define PURPLE "\033[1;95m"
# define CYAN "\033[1;96m"
# define WHITE "\033[1;97m"
# define BLACK "\033[1;90m"
// Bold
# define B_BLACK "\e[1;30m"
# define B_RED "\e[1;31m"
# define B_GREEN "\e[1;32m"
# define B_YELLOW "\e[1;33m"
# define B_BLUE "\e[1;34m"
# define B_PURPLE "\e[1;35m"
# define B_CYAN "\e[1;36m"
# define B_WHITE "\e[1;37m"
// Bold high intensity
# define BI_BLACK "\e[1;90m"
# define BI_RED "\e[1;91m"
# define BI_GREEN "\e[1;92m"
# define BI_YELLOW "\e[1;93m"
# define BI_BLUE "\e[1;94m"
# define BI_PURPLE "\e[1;95m"
# define BI_CYAN "\e[1;96m"
# define BI_WHITE "\e[1;97m"

#endif