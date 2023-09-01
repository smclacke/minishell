**SARAH, SHIT TO DO AFTER MICRO SHELLY, DONT FORGETTTTTTTTTT, and during...**

Gutentag Frälein Shelly, wie geht's?
dein computer, kein computer

---------------------------------------------------------------------------------
**CURRENT TO DO'S:**

HELLLLOOOOOO
please just ignore quotes for now cause it's setting me back massively...
handle errors, handle flags, put flag in node with cmd to send to executor
come back to quotes when stronger and more slept

~~ MICROSHELLY ~~
-> usable?

~~ERRORS~~
-> cmd not found
-> unclosed quotes
-> pipe stuff

~~FLAGS~~
///// Djoyke:
-> flags are just strings, im sending them the same as any other str :)
-> if echo and str after is -n, then dont just print -n, but remove newline, thats all
-> otherwise cmd put whatever after is given to execve and will be handled
-> pipes and redirects are important but other than that, we just give the input to executor

~~QUOTES~~
---> try using old ft_split, split on spaces, if quote found, stop splitting
---> add separately the part of the array from s or d quotes and then return to splitting on spaces
---> this way, I need to check the whole word for quotes and fix the a"something" problem


---------------------------------------------------------------------------------
**FUTURE TO DOS::**

*Lexer*

-> send good tokens to parser


*Parser*

->	some<<something 
->	<<something
				bash-3.2$ some<<something
				> something
				bash: some: command not found
				bash-3.2$ some<<something
				> hello
				> some
				> something
				bash: some: command not found
				bash-3.2$ <<something
				> some
				> something
				bash-3.2$

*Other*


---------------------------------------------------------------------------------
**TALK TO DJOYKE ABOUT THIS**

Gutentag Fräulein Shelly, wie geht's?echo abc$abc
lexer: 		~: echo
lexer: 		~: abc$abc
first->cmd: echo
second->str: abc$abc 

// i could check the exact behaviour of this and parse it to remove the unnecessary bits

+++++++++++

Gutentag Fräulein Shelly, wie geht's?/usr/bin/cd some thing
lexer: 		~: /usr/bin/cd
lexer: 		~: some
lexer: 		~: thing
first->abso: /usr/bin/cd
second->str: some
second->str: thing
Gutentag Fräulein Shelly, wie geht's?/bin/echo some thing
lexer: 		~: /bin/echo
lexer: 		~: some
lexer: 		~: thing
first->abso: /bin/echo
second->str: some
second->str: thing

IM GOING TO GIVE YOU AN ABSO PATH IN THE STRUCT, STILL NEED TO CHECK IF ITS THE CORRECT 
ABSO PATH, ECHO WORKS, CD DOESN'T, ETC ETC., USE EXECVE FOR THESE BECAUSE USING
THE ENV PATH FOR THESE NOT OUR BUILDINS
// I COULD CHECK THESE PATHS AND ONLY GIVE YOU VALID ONES

+++++++++++++++++++++

djoyke... maybe use a static function once in a while.... please

+++++++++++++++++++++++++=


t_expand	*micro_expand(char **envp, t_parser *node)
{
	// t_env	    *env;
    t_expand    *expand;

    (void) envp;
	expand = NULL;
	// env = micro_env_list(envp);
	while (node)
	{
        shelly_expand_lstadd_back(&expand, init_expand_list(node));
		node = node->next;
	}
	return (expand);
}


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

//-----------------try out------------------//


