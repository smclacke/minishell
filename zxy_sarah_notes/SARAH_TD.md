---------------------------------------------------------------------------------

**THIS IS THE END YAY (not of minishell obvs, just my sanity) WOOOO**

my brain is fried and i hate this project :)

Holy mother of fuckidy fuck
here we gooo

// # define PROMPT BI_YELLOW"🍌🍌🍌🍌🍌🍌🍌🍌
	 Gutentag Fräulein Shelly, wie geht's?"RESET

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


**SARAH, SHIT TO DO**

HELLO WHAT DE FOOK

Gutentag Frälein Shelly, wie geht's?
dein computer, kein computer

for in the future... don't change utils... ever. 

---------------------------------------------------------------------------------

===========================================
===========================================
===========================================

**TO DO**
**PROBLEM**
**FOOOOOOOOOK**

---->> check and test here_doc expansion

->> NORM: expand_quotes.c expand_utils.c

--->> add malloc func to libft with protection, change all malloc in
		libft, no longer need wrapers in main files..

-> export ls="ls -l"
	$ls - SHOULD WORK as ls -l, but im looking at cmd, and ls -l is not
		valid cmd.....

-> stress testing the expander + checking all for leaks

SIGNALSSSSh 
 ---> heredoc still weird, two prompt with signal

EXPANSION
 ---> $? ***, test once exit codes are good


***************************************************************************
***************************************************************************
***************************************************************************
**PROBLEEEEEEMMMMMM**


minibleh:cat << eof
heredoc> $USER
heredoc> hehe
heredoc> $LESS$USER
heredoc> "$USER"
heredoc> '$USER'
heredoc> eof

==978642==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 33 byte(s) in 4 object(s) allocated from:
    #0 0x49a29d in malloc (/home/smclacke/Desktop/minishell/minishell+0x49a29d)
    #1 0x7ff9abc22bac in xmalloc (/lib/x86_64-linux-gnu/libreadline.so.8+0x39bac)

SUMMARY: AddressSanitizer: 33 byte(s) leaked in 4 allocation(s).
hoi
hoi
AddressSanitizer:DEADLYSIGNAL
==978648==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x0000004dddc9 bp 0x7ffd73f086e0 sp 0x7ffd73f086e0 T0)
==978648==The signal is caused by a READ memory access.
==978648==Hint: address points to the zero page.
smclacke
hehe
-Rsmclacke
"smclacke"
'smclacke'
    #0 0x4dddc9 in ft_strlen (/home/smclacke/Desktop/minishell/minishell+0x4dddc9)
    #1 0x4de411 in ft_strjoin (/home/smclacke/Desktop/minishell/minishell+0x4de411)
    #2 0x4d869a in check_access /home/smclacke/Desktop/minishell/src/executor/execute.c:66:14
    #3 0x4d83f2 in mini_forks /home/smclacke/Desktop/minishell/src/executor/execute.c:106:15
    #4 0x4d9bfe in init_fork /home/smclacke/Desktop/minishell/src/executor/execute_utils_two.c:55:3
    #5 0x4d9f40 in pipeline /home/smclacke/Desktop/minishell/src/executor/execute_utils_two.c:103:4
    #6 0x4d88fe in build /home/smclacke/Desktop/minishell/src/executor/execute.c:135:2
    #7 0x4d887d in execute /home/smclacke/Desktop/minishell/src/executor/execute.c:157:2
    #8 0x4cb5dd in main /home/smclacke/Desktop/minishell/src/main.c:66:3
    #9 0x7ff9ab8e3d8f  (/home/smclacke/.capt/root/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)
    #10 0x7ff9ab8e3e3f in __libc_start_main (/home/smclacke/.capt/root/lib/x86_64-linux-gnu/libc.so.6+0x29e3f)
    #11 0x41f3d4 in _start (/home/smclacke/Desktop/minishell/minishell+0x41f3d4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/smclacke/Desktop/minishell/minishell+0x4dddc9) in ft_strlen
==978648==ABORTING

===========================================

**LEAKKKKSSSSSSS**




---------------------------------------------------------------------------------
=================================================================
=================================================================
=================================================================
=================================================================

**OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT**
=================================================================

minibleh:echo '$USER'
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
hd_limit = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = '$USER'
hd_limit = (null)
<!-- $USER -->
minibleh:exit
[0]	 cmd = exit	file = (null)	meta = (null)	str = (null)
hd_limit = (null)
exit

Direct leak of 6 byte(s) in 1 object(s) allocated from:
	malloc (/home/smclacke/Desktop/minishell/minishell+0x49a2ad)
    #1 0x4de6de in ft_substr (/home/smclacke/Desktop/minishell/minishell+0x4de6de)
    #2 0x4d2fb6 in squote_bit /home/smclacke/Desktop/minishell/src/expander/dollar_s_quotes.c:26:19
    #3 0x4d2a6b in dollar /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:74:8
    #4 0x4d24cb in expand_dollar /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:97:19
    #5 0x4d00c6 in ft_expand /home/smclacke/Desktop/minishell/src/expander/expand.c:53:3
    #6 0x4d82b1 in execute /home/smclacke/Desktop/minishell/src/executor/execute.c:150:2
    #7 0x4cb4e0 in main /home/smclacke/Desktop/minishell/src/main.c:61:3
    #8 0x7f7232160d8f  (/home/smclacke/.capt/root/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)

SUMMARY: AddressSanitizer: 6 byte(s) leaked in 1 allocation(s).
make: [Makefile:92: run] Error 1

=================================================================

/**
 * THIS DOESNT LEAK
 * minibleh:echo $USE
dollar = USE
env_val = (null)

minibleh:echo $USER
dollar = USER
env_val = smclacke
smclacke
minibleh:exit
exit

BUT
ONLY echo $USER DOES??!?

*/

=================================================================
minibleh:echo $USe
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
hd_limit = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = $USe
hd_limit = (null)

minibleh:exit
[0]	 cmd = exit	file = (null)	meta = (null)	str = (null)
hd_limit = (null)
exit

==2360819==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0x49a2ad in malloc (/home/smclacke/Desktop/minishell/minishell+0x49a2ad)
    #1 0x4de6de in ft_substr (/home/smclacke/Desktop/minishell/minishell+0x4de6de)
    #2 0x4de7cf in ft_strtrim (/home/smclacke/Desktop/minishell/minishell+0x4de7cf)
    #3 0x4d325e in dollar_expand /home/smclacke/Desktop/minishell/src/expander/dollar_s_quotes.c:46:13
    #4 0x4d3628 in dollar_bit /home/smclacke/Desktop/minishell/src/expander/dollar_s_quotes.c:75:2
    #5 0x4d299f in dollar /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:71:8
    #6 0x4d24cb in expand_dollar /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:97:19
    #7 0x4d00c6 in ft_expand /home/smclacke/Desktop/minishell/src/expander/expand.c:53:3
    #8 0x4d82b1 in execute /home/smclacke/Desktop/minishell/src/executor/execute.c:150:2
    #9 0x4cb4e0 in main /home/smclacke/Desktop/minishell/src/main.c:61:3
    #10 0x7fd4338aad8f  (/home/smclacke/.capt/root/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
make: *** [Makefile:92: run] Error 1


=================================================================

LOADS OF LEAKS
JUST SAVED ONE HERE FOR NOW

minibleh:echo "$USER'things'$LESS"
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
hd_limit = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = "$USER'things'$LESS"
hd_limit = (null)
smclacke'things'-R
minibleh:exit
[0]	 cmd = exit	file = (null)	meta = (null)	str = (null)
hd_limit = (null)
exit


Direct leak of 7 byte(s) in 1 object(s) allocated from:
    #0 0x49a2ad in malloc (/home/smclacke/Desktop/minishell/minishell+0x49a2ad)
    #1 0x4de6de in ft_substr (/home/smclacke/Desktop/minishell/minishell+0x4de6de)
    #2 0x4d2044 in save_extra_string /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:29:16
    #3 0x4d3afb in handle_double /home/smclacke/Desktop/minishell/src/expander/dd_quotes.c:52:8
    #4 0x4d37e5 in dquote_bit /home/smclacke/Desktop/minishell/src/expander/dd_quotes.c:71:4
    #5 0x4d2ccf in dollar /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:80:8
    #6 0x4d24cb in expand_dollar /home/smclacke/Desktop/minishell/src/expander/expand_dollar.c:97:19
    #7 0x4d00c6 in ft_expand /home/smclacke/Desktop/minishell/src/expander/expand.c:53:3
    #8 0x4d82b1 in execute /home/smclacke/Desktop/minishell/src/executor/execute.c:150:2
    #9 0x4cb4e0 in main /home/smclacke/Desktop/minishell/src/main.c:61:3
    #10 0x7f6930097d8f  (/home/smclacke/.capt/root/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)

SUMMARY: AddressSanitizer: 110 byte(s) leaked in 10 allocation(s).
make: *** [Makefile:92: run] Error 1
-----------------------------------------------------------------------------
===========================================
// EXPANSION YAY

// dollar handling, then dollar and quotes, then here_doc...
// then all the other bullshit edgecases

	// PROBLEM ONE
$USER$BRUH$USER
str before ret = $USER$BRUH$USER
str ret = smclackesmclackesmclacke
smclackesmclackesmclacke

	// PROBLEM TWO
 abc"$USER"something           NO WORKS   this should work	 BAD

	// PROBLEM THREE
-> abcsmclackesomething
but mine see's as str abc$USERsomething and $USERsomething = nope

	// PROBLEM FOUR
BASH   // this is technically bonus handling
echo "'$USER'"
'smclacke'

	// PROBLEM FIVE
// here_doc expansion............ :0 ...... :) ...........

**MAKE SURE BUILTINS ARE CHECKED CORRETLY**
-------------->  e"C"ho
Command 'eCho' not found
**APPARENTLY IT'S CASE SENSITIVE**

echo "some 'hi thing"
some 'hi thing


HAWHAWHAW
HEHE

minishell: < file 'ec"h"o' | < in c'd'f'g'f'd's's'"" >> something
cmd with quotes = 'ec"h"o'
len = 4
cmd with quotes = c'd'f'g'f'd's's'""
len = 8
[0]	 cmd = (null)	file = (null)	meta = <	str = (null)
[1]	 cmd = (null)	file = file	meta = (null)	str = (null)
[2]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[3]	 cmd = (null)	file = (null)	meta = |	str = (null)
[4]	 cmd = (null)	file = (null)	meta = <	str = (null)
[5]	 cmd = (null)	file = in	meta = (null)	str = (null)
[6]	 cmd = cdfgfdss	file = (null)	meta = (null)	str = (null)
[7]	 cmd = (null)	file = (null)	meta = >>	str = (null)
[8]	 cmd = (null)	file = something	meta = (null)	str = (null)



Current :)

wtf>> | hellllo"some thing"wtttfff >thing > thing > > thing
no_tokens: 11
start = 0
start = 3
start = 6
start = 8
start = 35
start = 36
start = 42
start = 44
start = 50
start = 52
start = 54
lexer list: [wtf]
lexer list: [>>]
lexer list: [|]
lexer list: [hellllo"some thing"wtttfff]
lexer list: [>]
lexer list: [thing]
lexer list: [>]
lexer list: [thing]
lexer list: [>]
lexer list: [>]
lexer list: [thing]
[0]	 cmd = wtf	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = >>	str = (null)
[2]	 cmd = (null)	file = (null)	meta = |	str = (null)
[3]	 cmd = (null)	file = (null)	meta = (null)	str = hellllo"some thing"wtttfff
[4]	 cmd = (null)	file = (null)	meta = >	str = (null)
[5]	 cmd = (null)	file = thing	meta = (null)	str = (null)
[6]	 cmd = (null)	file = (null)	meta = >	str = (null)
[7]	 cmd = (null)	file = thing	meta = (null)	str = (null)
[8]	 cmd = (null)	file = (null)	meta = >	str = (null)
[9]	 cmd = (null)	file = (null)	meta = >	str = (null)
[10]	 cmd = (null)	file = (null)	meta = (null)	str = thing

---------------------------------------------------------------------------------
**25/09:**

-> amount_tokens() in token_size.c, normed, cleaner and commented

-> LEAKSSSSSSS

-> TEST TEST TEST

-> EXPANSION LET'S FUCKING GOOOOOO

---------------------------------------------------------------------------------

-> fix the new quote shit in lexer: (last to do notes before this shit show:)
		!! amount of tokens need to check attached redirects and quotes
		changing this function, need to check quote funcs cause segfault :)
		then do a meta check and separate those

		!! split needs to handle quotes
		!! split needs to handle redirects attached

-> add meta separatation in lexer
-> check that quotes are whole: abd"bull"shit = is one token
-> cry
-> find problems
-> cry some more

---------------------------------------------------------------------------------

**ALL THE FUN ARG SHIT** ja? nee? ja? nee? ik weet het niet meeeeer

**EXAMPLE**
<out echo hello 
 -> hello

**EXAMPLE**
<infile cat | cat >out = works

**EXAMPLE**
echo hello | cat >outfile
cat infile
 -> hello
echo hello | >outfile
cat infile

**EXAMPLE**
echo hello | cat >outfile
cat infile
 -> hello
echo hello | >outfile
cat infile
// nothing in infile anymore, but also doesn't echo hello since stdout is redirected and no cmd for infile...

**EXAMPLE**
echo hello | >outfile
cat infile
echo hello | <infile
cat infile
echo hello | cat <infile
cat infile
cat Makefile | cat <infile
cat infile

// put the makefile into the infile, then run cat Makefile | <infile, Makefile is still in the infile

-> cmd can only be:
	first arg, after redirect or pipe... more? otherwise str
-> first arg can be cmd, or infile or here_doc
-> atfer pipe, can be cmd in/out file (but pipe wont actually do anything without a cmd after it, other than just making the out file)

**EXAMPLE**
echo hello <<something >out
> what
> is
> happening
> something
cat out
 -> hello

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

echo >> things
no_tokens: 4
start = 0
start = 5
start = 8
start = 14
lexer list: [echo]
lexer list: [>>]
lexer list: [things]
lexer list: []
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = >>	str = (null)
[2]	 cmd = (null)	file = things	meta = (null)	str = (null)
[3]	 cmd = (null)	file = (null)	meta = (null)	str = 
expander: 		there's a builtin whoop


echo some|thing
no_tokens: 2
start = 0
start = 5
lexer list: [echo]
lexer list: [some|]
[0]	 cmd = echo	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = some|
expander: 		there's a builtin whoop
some|    


ecommmm|hello
no_tokens: 1
start = 0
lexer list: [ecommmm|hello]
[0]	 cmd = ecommmm|hello	file = (null)	meta = (null)	str = (null)
     _

