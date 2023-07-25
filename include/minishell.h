/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 13:39:02 by smclacke      ########   odam.nl         */
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

typedef	struct	s_mini
{
	struct	t_parser	tokens;
	struct	t__env		environ;
}	t_mini;


//------------Minishell-----------//



//------------MICRO_SHELL----------//
//----Lexer----//

//----Parser----//
typedef struct s_parser 
{
	char				*word;
	char				*cmd;
	char				*redirect;
	struct t_lexer		*tokens;
}	t_parser;


//----Expander----//

//----Executor----//

#endif