**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT, and during...**
HELLO WHAT DE FOOK
Gutentag Frälein Shelly, wie geht's?
dein computer, kein computer

---------------------------------------------------------------------------------
**CURRENT MESSAGES? UPDATES**

!! first arg + after pipe could be cmd or redirect.... :)
....  <out echo hello 
need to check all strings incase there are cmds, not always first/after pipe....
could give you something that NEEDS to be a cmd if not a file and then basically the other strings will just need to be checked.....................


-> cmd must be..
	first arg, after redirect or pipe... more? otherwise str


!! amount of tokens need to check attached redirects and quotes
changing this function, need to check quote funcs cause segfault :)
then do a meta check and separate those

!! split needs to handle quotes
!! split needs to handle redirects attached

---------------------------------------------------------------------------------

mehmehmehmeh

     __
 .--()°'.'
'|, . ,'
 !_-(_|\grep >
input: grep >
this is fucked
this is fucked
this is fucked
this is fucked
^C
➜  minishel

---------------------------------------------------------------------------------

IS QUITE LONGGGGGGGGGGGGGGGGG :))))))

// MAX = GOOD
// exit 9223372036854775807
// MIN = GOOD
// exit -9223372036854775808

// MORE THAN MAX = BAD
// exit 9223372036854775808
// exit 9223372036854775809
// exit 9223372036854775819

// LESS THAN MAX = GOOD
// exit 9223372036854775708
// exit 9223372036854775803

// MORE THAN MIN = BAD
// exit -9223372036854775810
// exit -9223372036854775809

// LESS THAN MIN = GOOD
// exit -9223372036854775805
// exit -9223372036854775706


**TO DOOOOOOS**

LEXER

// this is problem
<<
input: <<
&input: <<
is meta: 1
&input: <
is meta: 2


->>>>>>>>> SEPARATE FILES from redirects and attachments to pipes (lexer)
->>>>>>>>> SEPARATE QUOTES... need to talk to someone about quote handling cause its too much
->>>>>>>>> split the rest on spaces

PARSER
->>>>>>>>> what is the parser missing??
WHY ARENT THERE MORE TO DOOOOOOOOS....

OTHER
->>>>>>>>> errors ....
					-> cmd not found
					-> unclosed quotes
					-> pipe stuff
->>>>>>>>> figure out whether im going to use enums or not (probs not)
->>>>>>>>> where do i parser quote tokens??????? EXPAND THEM :):), or like parse between parser and expansion but like its good as one token for now and ill fix it at some point in the future

I think abc$abc, some<<something are both for the expander and ill leave them intact in the tokens


need to rethink a bit.... 

cmd or redirect...
as first or after pipe....
but this is ok, everything is ok

bash-3.2$ < out cat | cat > out2 -e
bash-3.2$ cat out2
Makefile$
README.md$
SARAH+tokens.md$
SARAH_TD.md$
heredoc_notes.md$
include$
micro_shell$
mini_src$
minishell$
obj$
obj_djoy$
obj_saar$
out$
sarah$
src_djoy$
src_saar$

---------------------------------------------------------------------------------
**TALK TO DJOYKE ABOUT THIS**

**ONE**
// i could check the exact behaviour of this and parse it to remove the unnecessary bits
// STILL NEED TO FIGURE OUT WHAT IM DOING WITH THIS, 
// PARSER REMOVES OR !!EXPANDER TAKES WHATS NECESSARY?!!
// JA WEETJE JE, DOE MAAR EVEN EXPADNER WANT ANDERS HEEFT HIJ BEST WEING OM TE DOEN

Gutentag Fräulein Shelly, wie geht's?echo abc$abc
lexer: 		~: echo
lexer: 		~: abc$abc
first->cmd: echo
second->str: abc$abc 


**TWO**
void	ft_echo(t_parser *lst)
{
	int	i;
	int	is_flag;


	i = 0;
	is_flag = 0;
	if (!lst->data_type->cmd)
		mini_error("lst->cmd", errno);
	lst = lst->next;
	while (lst)
	{
		if (ft_strcmp(lst->data_type->strs[i], "-n") == 0)
		{
			++is_flag;
			i++;
		}
		else
		{
			printf("%s ", lst->data_type->strs);
			i++;
		}
		lst = lst->next;
	}
	if (is_flag != 0)
		printf("\n");
}

void	ft_echo(t_parser *lst)
{
	int	i;
	int	is_flag;


	i = 0;
	is_flag = 0;
	if (!lst->data_type->cmd)
		mini_error("lst->cmd", errno);
	lst = lst->next;
	while (lst)
	{
		if (lst->data_type->strs)
		{
			if (ft_strcmp(lst->data_type->strs, "-n") == 0)
			{
				++is_flag;
				i++;
			}
			else
			{
				printf("%s ", lst->data_type->strs);
				i++;
			}
		}
		lst = lst->next;
	}
	if (is_flag != 0)
		printf("\n");
}

Echo was segfaulting, I edited the code a bit so that we look through the list for the strs
echo << some, then we need to handle the redirect correctly otherwise we will just skip it...


---------------------------------------------------------------------------------


**OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT**

---------------------------------------------------------------------------------
**NEW_STYLEEE YEAHHHHH**

//-----------------try out------------------//

typedef struct s_parser 
{
	struct s_parser		*data;
	struct s_parser		*next;
}	t_parser;


// typedef struct s_parser 
// {
// 	char **cmd_and_flags;   "ls", "-l"
//	char **redirections;    INPUT_R, OUPUT_R 
//	char **files;			"file_1" "file_2" 
// 	struct s_parser		*next;
// }	t_parser;


list->node[0]
if node[1] exists then further
if node[2] exists then further

example : minishell$> < file1 cmd1 | cmd2 >file2
if space 2 parts if no space 1 part.

linked list;
data[0] = **array[0] < [1] file1 [2] cmd [3] NULL
data[1] = **array[0] pipe [1] NULL
data[2] = **array[0] cmd [1] >outfile [2] NULL

---------------------------------------------------------------------------------

DJOYKE, YOUR STRCMP IS CAUSING THIS PROBLEM: (s1 || s2) NOT (s1 && s2)
........................
token->cmd->cmd = [e]
token->cmd->strs = [(null)]
[0] | input: [e] cmd_list->cmd: [e] | cmd_list->str: [(null)] | ----------------
||
index = [0], cmd = [e]
index = [0], str = [(null)]
NULL
----------------
cmd = [e]
expander: 		there's a builtin whoop
........................
token->cmd->cmd = [c]
token->cmd->strs = [(null)]
[0] | input: [c] cmd_list->cmd: [c] | cmd_list->str: [(null)] | ----------------
||
index = [0], cmd = [c]
index = [0], str = [(null)]
NULL
----------------
cmd = [c]
expander: 		there's a builtin whoop
........................

---------------------------------------------------------------------------------

