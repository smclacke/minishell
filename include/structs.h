/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 16:42:25 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/15 16:16:18 by smclacke      ########   odam.nl         */
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

# define PARENT 1
# define CHILD 2
# define HERE_DOC 3

# define CMD_X 1
# define STR_X 2
# define FILE_X 3

# define NOT_POSSIBLE "minishell: env: no such file or directory\n"
# define ERROR_MESSAGE ": positive numeric argument 255 or below required\n"
# define NO_SUCH_THING "minishell: cd: %s: No such file or directory\n"
# define NO_HOME "minishell: cd: HOME not set\n"
# define ARG_ERROR "minishell: %s: too many arguments\n"
# define TOO_MANY_ARG "exit\nminishell: exit: too many arguments\n"
# define INFILE_ERROR "minishell: %s: No such file or directory\n"
# define DIR_MESSAGE "minishell: %s: Is a directory\n"
# define DIR_FILE_MESSAGE "minishell: %s: No such file or directory\n"

// EXITCODES
typedef enum e_exit
{
	E_USAGE = 0,
	E_MALLOC = -1,
	E_GENERAL = 1,
	E_SYNTAX = 2,
	E_EXEC = 126,
	E_COMMAND_NOT_FOUND = 127,
	E_EXIT_INVALID_ARG = 128,
	E_FATAL_SIGNAL = 128,
	E_CTRL_C = 130,
	E_UNKNOWN = 225
}						t_exit;

/**
 * @brief	specifies the different variable types of tokens from the
 * 			lexer that are organised in mini sub arrays, parsed and then 
 * 			given to the executor as a link list of parser struct nodes
 * @param	cmd: first string in each process without redirect char
 * @param	str:  limiter for here_doc (string after <<) and all other input
 * @param	meta: pipe, more, less, moremore, lessless. 
 * 			**dollar is excluded and handled as a string
 * @param	file: in and out files; after more, less and moremore chars
 * @param	hd_limit: save the limiter string, check if it's quoted or not
 * @param	flag: useful util var
 * @param	hd_flag: 1 = quoted, quotes are removed but if flag is set, 
 * 			don't expand anything inside here_doc input for both
 * 			single and double quotes
*/
typedef struct s_tokens
{
	char 					**node;
	char					*cmd;
	char					**str;
	char					*meta;
	char					**file;
	char					**hd_limit;
	int						hd_flag;
	int						flag;
	struct s_tokens			*next;
}				t_tokens;

/**
 * going to be an array of token lists, one for each process
 * var are already organised in tokens struct
 * 
 * LIST AUCH ODER???
*/
typedef	struct	s_parser
{
	int						proc_count; // how any t_token processes there will be
	void					*input;
	struct s_tokens			*process; // one node parser, list tokens - one process
	struct s_parser			*next;
}							t_parser;


/**
 * THIS IS GOING TO BE PASSED TO THE EXECUTOR AND HAVE EVERYTHING INSIDE
 * @param	exit_code: enums to set exitcode at different
 * 			stages of process, saved to pass through the program
 * 
 * @todo exit stuff: what do we need?
 * @todo init hd_fd somewhere
*/
typedef struct s_input
{
	char					*exit_str;  //do we need all of these?  
	enum e_exit				exit_code;  //do we need all of these?
	int						exit_stat;  //do we need all of these?

	int						hd_fd; // check which struct this should below to
	t_parser				*parser;
}							t_input;





/**
 * comment on the way
*/
typedef struct s_expand
{
	char				*input;
	char				*tmp;
	char				*string;
	char				*dollar;
	char				*s_quote;
	char				*d_quote;
	char				*env_val;
	char				*expanded;
	char				*h_d;
	int					sign;
	struct s_parser		*exit;
}							t_expand;

/**
 * @brief	linked list containing the environment
 * @param	key: string containing the key part of the environment
 * @param	value: string containing the value part of the environment
 * @param	full: string containing full line of the environment
 * 			including semicolon.
 * @param	next: env struct pointing to the next node in the linked list
 * 			if no next then it points to NULL.
 * @param	has_value: int used as checkpoint if the key has a value
*/
typedef struct s_env
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env		*next;
	int					has_value;
}							t_env;

/**
 * @brief	struct containing variables needed for execution process
 * @param	fork_pid: int to store fork_pid in
 * @param	pipe_left: pipe used to read and write to in process
 * @param	pipe_right: pipe used to read and write to in process
 * @param	path: 2d array storing the path to a command.
 * @param	env_array: 2d array storing environment from environment linked list
 * @param	in: int storing fd for infile
 * @param	out: int storing fd for outfile
 * @param	count: int storing amount of commands in parser linked list
 * @param	fd: int storing a fd
*/
typedef struct s_execute
{
	pid_t				fork_pid;
	int					pipe_left[2];
	int					pipe_right[2];
	char				**path;
	char				**env_array;
	int					in;
	int					out;
	int					count;
	bool				error;
}							t_execute;

#endif
