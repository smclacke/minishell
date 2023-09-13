**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT, and during...**

Gutentag Frälein Shelly, wie geht's?
dein computer, kein computer

---------------------------------------------------------------------------------
**CURRENT MESSAGES? UPDATES**

HELLOHELLOHELLOHELLO 11/09/23, and it works ::)

LETS SIMPLIFY SO I HAVE SOMETHING THAT ACTUALLY WORKS.... WOOW AMAZING IDEA......

MESSAGE TO DJOYKE:
im sorry this is going to be horrible to read, but it all works now with metas,  cmd after pipe, files after redirects,,, :') after << we are looking for a delimiter which is just a string that we need to compare the input from the command line to to see if we should end the here_doc or not, i can add a delimiter var if you like or ill leave it as a string, just let me know cause that would be really easy to add if it would make life easier for you :slightly_smiling_face: 

 !_-(_|\echo some | thing >> in < input > more more | more < thigns
[0] | cmd = echo | file = (null) | meta = (null) | strs = (null)
[1] | cmd = (null) | file = (null) | meta = (null) | strs = some
[2] | cmd = (null) | file = (null) | meta = | | strs = (null)
[3] | cmd = thing | file = (null) | meta = (null) | strs = (null)
[4] | cmd = (null) | file = (null) | meta = >> | strs = (null)
[5] | cmd = (null) | file = in | meta = (null) | strs = (null)
[6] | cmd = (null) | file = (null) | meta = < | strs = (null)
[7] | cmd = (null) | file = input | meta = (null) | strs = (null)
[8] | cmd = (null) | file = (null) | meta = > | strs = (null)
[9] | cmd = (null) | file = more | meta = (null) | strs = (null)
[10] | cmd = (null) | file = (null) | meta = (null) | strs = more
[11] | cmd = (null) | file = (null) | meta = | | strs = (null)
[12] | cmd = more | file = (null) | meta = (null) | strs = (null)
[13] | cmd = (null) | file = (null) | meta = < | strs = (null)
[14] | cmd = (null) | file = thigns | meta = (null) | strs = (null)


integrating the new parser into your srcs on my branch was fine, but now we need
some changes, e.g. ft_echo is trying to iterate through a list of strings but it now needs to iterate through the whole list and while there are strings, do the thing

---------------------------------------------------------------------------------

**TO DOOOOOOS**

LEXER
->>>>>>>>> SEPARATE FILES from redirects and attachments to pipes (lexer)
->>>>>>>>> SEPARATE QUOTES... need to talk to someone about quote handling cause its too much
->>>>>>>>> split the rest on spaces

PARSER
->>>>>>>>> what is the parser missing??
->>>>>>>>> should dollar just be a string or no?

OTHER
->>>>>>>>> errors ....
					-> cmd not found
					-> unclosed quotes
					-> pipe stuff
->>>>>>>>> figure out whether im going to use enums or not (probs not)
->>>>>>>>> where do i parser quote tokens???????

I think abc$abc, some<<something are both for the expander and ill leave them intact in the tokens


---------------------------------------------------------------------------------
**TALK TO DJOYKE ABOUT THIS**

**ONE**
// i could check the exact behaviour of this and parse it to remove the unnecessary bits
// STILL NEED TO FIGURE OUT WHAT IM DOING WITH THIS, PARSER REMOVES OR EXPANDER TAKES WHATS NECESSARY?

Gutentag Fräulein Shelly, wie geht's?echo abc$abc
lexer: 		~: echo
lexer: 		~: abc$abc
first->cmd: echo
second->str: abc$abc 

**TWO**
I'll give you cmds, files and strs, do you want delimiter vars as well for after << ??



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


