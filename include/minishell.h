/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:20:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/25 13:55:23 by smclacke      ########   odam.nl         */
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



//------------MICRO_SHELL----------//
//----Lexer----//

//----Parser----//
typedef struct s_parser 
{
	char				*word;
	char				*cmd;
	char				*redirect;
	struct s_lexer		*tokens;
}	t_parser;


//----Expander----//

//----Executor----//
typedef struct s_env
{
	char				*key;
	char				*value;
	// char				full;
	struct s_env		*next;
	struct s_env		*previous;
}							t_env;


//------------Minishell-----------//

/**
 * everything that we share
 * add our structs that hold the info that we need to share/for minishell as a whole 
*/
typedef	struct	s_mini
{
	struct	s_parser	tokens;
	struct	s_env		environ;
}	t_mini;


#endif