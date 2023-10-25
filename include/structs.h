/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 16:42:25 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/25 15:11:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define READ 0
# define WRITE 1

# define SUCCESS 0
# define ERROR -1

# define TRUE 1
# define FALSE 0

# define PIPE "|"
# define MORE ">"
# define MOREMORE ">>"
# define LESS "<"
# define LESSLESS "<<"
# define DOUBLE_Q "\""
# define SINGLE_Q "\'"


// EXITCODES
typedef enum e_exit
{
	E_USAGE = 0,
	E_GENERAL = 1,
	E_BUILTIN = 2,
	E_EXEC = 126,
	E_COMMAND_NOT_FOUND = 127,
	E_EXIT_INVALID_ARG = 128,
	E_FATAL_SIGNAL = 128,
	E_CTRL_C = 130,
	E_UNKNOWN = 225
}					t_exit;

/**
 * @brief	specifies the different variable types of tokens from the
 * 			lexer that are parsed and then given to the executor
 * @param	cmd: first string in each process without redirect char
 * @param	meta: pipe, more, less, moremore, lessless. 
 * 			**dollar is excluded and handled as a string
 * @param	file: in and out files; after more, less and moremore chars
 * @param	str:  limiter for here_doc (string after <<) and all other input
*/
typedef struct s_parser
{
	void				*input;
	char				*cmd;
	char				*meta;
	char				*file;
	char				*str;
	int					sign;
	int					flag;
	int					n_cmd;
	enum e_exit			exit_code;
	struct s_parser		*next;
}				t_parser;


typedef struct s_expand
{
	char	*input;
	char	*do_expand;
	char	*dont_expand;
	char	*env_val;
	char	*expanded;
}		t_expand;


typedef struct s_env
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env		*next;
	struct s_env		*previous;
	int					has_value;
}							t_env;


typedef struct s_execute
{
	int		fd_in;
	int		fork_pid;
	int		pipe_fd[2];
	char	**path;
	char	**env_array;
}				t_execute;

// replacing with above s_expand unless djoyke needs this
// typedef struct s_expand
// {
// 	char				*before_dollar;
// 	char				*var;
// 	char				*env_value;
// 	char				*comp_str;
// }							t_expand;

#endif
