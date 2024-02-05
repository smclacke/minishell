/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 16:42:25 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/05 17:33:51 by smclacke      ########   odam.nl         */
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
# define HD_X 3
# define RED_X 4

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
 * @todo	check the count vars are correctly updated and saved per process
 * @brief	specifies the different variable types from the
 * 			lexer that are organised via the parser, then given to the 
 * 			executor in the form of a parser list, each node being
 * 			one process containing some or all of these proc struct vars
 * @param	proc_count: total number of processes (3 = 3)
 * @param	token_count: total number of tokens within each process
 * @param	cmd: first string in each process without redirect char
 * @param	str: array of all cmd args
 * @param	str_count: number of string args per process (3 = 3)
 * @param	redir: array of all < > >> in, out and truncate files, 
 * 			left in order as inputted. file after each meta characher included, 
 * 			error if no string after meta
 * @param	red_count: number of redir metas and files in array per process  (3 = 3)
 * @param	hd: array of all hd delimiters, ignoring hd meta itself
 * 				error if no string after hd meta
 * @param	hd_count: number of hd delimiters in array (3 = 3)
 * @param	hd_fd: var for djoyke, inited at -1
*/
typedef	struct s_procs
{
	int						proc_count;
	int						token_count;
	char					*cmd;
	int						cmd_flag;
	char					**str;
	int						str_count;
	char					**redir;
	int						red_count;
	char					**hd;
	int						hd_count;
	int						hd_fd;
	struct s_parser			*parser;
}			t_procs;

/**
 * @todo	check proc_size is correct while iterating through processes
 * @todo	exit stuff, what need to happen here?
 * @param	multi_proc_b: specifies whether there is only one process or multiple
 * @param	tokens: if only one process, can just use the token array
 * @param	proc_arrs: if multiple processes, use the array of processes
 * 
 * @param	start: used for creating proc_arrs
 * @param	proc_count: total number of processes (3 = 3)
 * 
 * @param	process: use to sort either tokens or proc_arrs into procs struct
 * 					similiar to just an input var
 * @param	proc: each node of the parser list is stored here, this way each node
 * 				parser->proc[0]->... accesses the procs struct with all vars
 * 				from that processes, can iterate through these proc nodes
 * @param	hd_flag: check if expansion in hd is necessary
*/
typedef	struct	s_parser
{
	bool					multi_proc_b;
	char					**tokens;
	char					***proc_arrs;

	int						start;
	int						proc_count;

	struct s_procs			**process;
	struct s_procs			*proc;
	int						hd_flag;

	char					*exit_str;
	enum e_exit				exit_code;
	int						exit_stat;

	struct s_parser			*next;
}							t_parser;

/**
 *  @todo	check what needs to be done with exit codes in expander
 *	@brief	simply a struct used to store and organise while expanding variables
*/
typedef struct s_expand
{
	char					*input;
	char					*tmp;
	char					*string;
	char					*dollar;
	char					*s_quote;
	char					*d_quote;
	char					*env_val;
	char					*expanded;
	char					*h_d;
	int						sign;
	int						pos;
	struct s_parser			*exit;
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
