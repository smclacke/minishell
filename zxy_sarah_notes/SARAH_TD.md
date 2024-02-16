------------------------------------------------------------------------
------------------------------------------------------------------------
------------------------------
------------------------------
------------------------------
------------------------------

*right here, right now*

**DO this**

- leaks

- errors

- STRESS TEST THE FUCK OUTTA IT

------------------------------
**THIS**
		echo $USER -- without any expansion, no leak, with expansion
		and execution, many env_list leaks and one sort_vars->copy_strs leak
		
	check once env_list leaks fixed if i still have leak..

	Direct leak of 6 byte(s) in 1 object(s) allocated from:
    #0 0x49a28d in malloc (/home/smclacke/Desktop/mini_check/minishell+0x49a28d)
    #1 0x4e2fff in ft_strdup (/home/smclacke/Desktop/mini_check/minishell+0x4e2fff)
    #2 0x4d1dfb in copy_strs /home/smclacke/Desktop/mini_check/src/parser/get_procs.c:82:27
    #3 0x4d1cc9 in get_strs /home/smclacke/Desktop/mini_check/src/parser/get_procs.c:123:4
    #4 0x4d09c0 in sort_vars /home/smclacke/Desktop/mini_check/src/parser/sort_procs.c:29:3
    #5 0x4d0826 in sort_each_proc /home/smclacke/Desktop/mini_check/src/parser/sort_procs.c:53:2
    #6 0x4cfde0 in handle_procs /home/smclacke/Desktop/mini_check/src/parser/parser.c:33:4
    #7 0x4cf538 in parse_tokens /home/smclacke/Desktop/mini_check/src/parser/parser.c:81:16
    #8 0x4cf40d in parse_input /home/smclacke/Desktop/mini_check/src/parser/parser.c:100:11
    #9 0x4cb420 in run_minishell /home/smclacke/Desktop/mini_check/src/main.c:28:10
    #10 0x4cb53f in main /home/smclacke/Desktop/mini_check/src/main.c:52:8
    #11 0x7f08f90a6d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

------------------------------
**THIS**
	-- hd when i test does not work correctly and then segfaults..

------------------------------
**THIS**
	no input a load of times then echo has leak....

minibleh:
minibleh:
minibleh:
minibleh:
minibleh:
minibleh:
minibleh:
minibleh:
minibleh:
minibleh:echo

[0] cmd = echo

[0] str_count = 0

[0] hd_count = 0

[0] red_count = 0

==23438==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 9 byte(s) in 9 object(s) allocated from:
    #0 0x49a28d in malloc (/home/smclacke/Desktop/mini_check/minishell+0x49a28d)
    #1 0x7f9b2f231bac in xmalloc (/lib/x86_64-linux-gnu/libreadline.so.8+0x39bac)

SUMMARY: AddressSanitizer: 9 byte(s) leaked in 9 allocation(s).
make: *** [Makefile:95: run] Error 1

------------------------------
------------------------------
------------------------------

**MAIN TO DO**

*TODO 1* US
 ---->>>>  ?? why we exiting??
EXAMPLE:
minibleh:<< eof
heredoc> hi
heredoc> hello
heredoc> exit
heredoc> eof
make: *** [Makefile:95: run] Error 1


*TODO 2*  ME
 ---->>>>> THIS LEAK... comes in here_doc and i think somewhere else too..
Direct leak of 33 byte(s) in 4 object(s) allocated from:
    #0 0x49a29d in malloc (/home/smclacke/Desktop/minishell/minishell+0x49a29d)
    #1 0x7fba8cca3bac in xmalloc (/lib/x86_64-linux-gnu/libreadline.so.8+0x39bac)

EXAMPLE:
minibleh:cat << eof
heredoc> $USER
heredoc> hehe
heredoc> $LESS$USER
heredoc> "$USER"
heredoc> '$USER'
heredoc> eof


*TODO 3* ME 	WHAT AM I DOING ABOUT MALLOC FUNC/PROTECTION??
 ------>> put ft_malloc into libft, use for all malloc in libft, 
		forget about protection hawhaw
		--->> add malloc func to libft with protection, change all malloc in libft, no longer need wrapers in main files..


*TODO 4* ME
 ---->> check and test here_doc expansion
 +++ -----> stress testing the expander + checking all for leaks

*TODO 6* US
SIGNALSSSSh
 ---> the file is a total mess....
 ---> check they really really work correctly in all situations 
 ---> heredoc still weird, two prompt with signal


*TODO 7* ME
EXPANSION
 ---> $? ***, test once exit codes are good


*TODO 8* ME
---> literally all errors


=================================================================
=================================================================
--------------------------------------------------------------------

=================================================================
=================================================================

**RANDOM NOTES ...**

------------------------------------------------------------------------
**IF THE SHIT SHOW HAS BEEN FIXED....**
JINGLE GLOBALS (:(:(:(:(:(:(::):):):):):):)

**TO DO**
**PROBLEM**
**FOOOOOOOOOK**

**THIS IS THE END YAY (not of minishell obvs, just my sanity) WOOOO**

my brain is fried and i hate this project :)

Holy mother of fuckidy fuck
here we gooo

// # define PROMPT BI_YELLOW"🍌🍌🍌🍌🍌🍌🍌🍌
	 Gutentag Fräulein Shelly, wie geht's?"RESET

mehmehmehmeh
     __
 .--()°'.'**ASK DJOYKE**
------------------------------

ACCESS = parser_list 	-> 		proc   ->		var
		parser list		proc struct process		var 
		t_parser		t_procs					token type || array


*ONE* explain the structure:  ++ how to access (example in main)

cmd <in <<hd str arg >out more strings | echo some | >out << hd1 << hd2 other ran wor

  -> proc_count = [2]		// == 3 processes

[0] cmd = cmd				// == process[0] cmd

[0] str_count = 4			// == 4 string args not including cmd str
[0] strs[0] = str
[0] strs[1] = arg
[0] strs[2] = more
[0] strs[3] = strings

[0] hd_count = 2			// == 1 here_doc
[0] hd[0] = <<
[0] hd[1] = hd

[0] red_count = 4			// == 2 redirects
[0] reds[0] = <
[0] reds[1] = in
[0] reds[2] = >
[0] reds[3] = out
--------------------------------------------------

[1] cmd = echo				// == process[1] cmd

[1] str_count = 1			// == 1 string args not including cmd str
[1] strs[0] = some

[1] hd_count = 0

[1] red_count = 0
--------------------------------------------------

[2] cmd = other				// == process[2] cmd

[2] str_count = 2			// == 2 string args not including cmd str
[2] strs[0] = ran
[2] strs[1] = wor

[2] hd_count = 4			// == 2 here_doc
[2] hd[0] = <<
[2] hd[1] = hd1
[2] hd[2] = <<
[2] hd[3] = hd2

[2] red_count = 2			// == 1 redirect
[2] reds[0] = >
[2] reds[1] = out
--------------------------------------------------

**SECOND EXAMPLE**
< in > out | echo something | << hd1 << hd2 cmd str
  -> proc_count = [2]


[0] cmd = (null)

[0] str_count = 0

[0] hd_count = 0

[0] red_count = 4
[0] reds[0] = <
[0] reds[1] = in
[0] reds[2] = >
[0] reds[3] = out
--------------------------------------------------

[1] cmd = echo

[1] str_count = 1
[1] strs[0] = something

[1] hd_count = 0

[1] red_count = 0
--------------------------------------------------

[2] cmd = cmd

[2] str_count = 1
[2] strs[0] = str

[2] hd_count = 4
[2] hd[0] = <<
[2] hd[1] = hd1
[2] hd[2] = <<
[2] hd[3] = hd2

[2] red_count = 0


*TWO*
----- ask djoyke what counts she wants, i think easier to use << hd == 2
		then iterate hd_count to find meta and eof, since same array...
proc_count = 0				= 1 process
hd_count = 2				= 1 hd
[0] hd[0] = <<
[0] hd[1] = eof

red_count = 4				= 2 redirects
[0] reds[0] = >
[0] reds[1] = out_file
[0] reds[2] = <
[0] reds[3] = in_file

str_count = 4				= 4 cmd args
[0] str[0] = something
[0] str[1] = string
[0] str[2] = and
[0] str[3] = things

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
=================================================================
=================================================================
-----------------------------------------------------------------

**OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT****OLD SHIT**

=================================================================
=================================================================
=================================================================

**ASK DJOYKE**
------------------------------

ACCESS = parser_list 	-> 		proc   ->		var
		parser list		proc struct process		var 
		t_parser		t_procs					token type || array


*ONE* explain the structure:  ++ how to access (example in main)

cmd <in <<hd str arg >out more strings | echo some | >out << hd1 << hd2 other ran wor

  -> proc_count = [2]		// == 3 processes

[0] cmd = cmd				// == process[0] cmd

[0] str_count = 4			// == 4 string args not including cmd str
[0] strs[0] = str
[0] strs[1] = arg
[0] strs[2] = more
[0] strs[3] = strings

[0] hd_count = 2			// == 1 here_doc
[0] hd[0] = <<
[0] hd[1] = hd

[0] red_count = 4			// == 2 redirects
[0] reds[0] = <
[0] reds[1] = in
[0] reds[2] = >
[0] reds[3] = out
--------------------------------------------------

[1] cmd = echo				// == process[1] cmd

[1] str_count = 1			// == 1 string args not including cmd str
[1] strs[0] = some

[1] hd_count = 0

[1] red_count = 0
--------------------------------------------------

[2] cmd = other				// == process[2] cmd

[2] str_count = 2			// == 2 string args not including cmd str
[2] strs[0] = ran
[2] strs[1] = wor

[2] hd_count = 4			// == 2 here_doc
[2] hd[0] = <<
[2] hd[1] = hd1
[2] hd[2] = <<
[2] hd[3] = hd2

[2] red_count = 2			// == 1 redirect
[2] reds[0] = >
[2] reds[1] = out
--------------------------------------------------

**SECOND EXAMPLE**
< in > out | echo something | << hd1 << hd2 cmd str
  -> proc_count = [2]


[0] cmd = (null)

[0] str_count = 0

[0] hd_count = 0

[0] red_count = 4
[0] reds[0] = <
[0] reds[1] = in
[0] reds[2] = >
[0] reds[3] = out
--------------------------------------------------

[1] cmd = echo

[1] str_count = 1
[1] strs[0] = something

[1] hd_count = 0

[1] red_count = 0
--------------------------------------------------

[2] cmd = cmd

[2] str_count = 1
[2] strs[0] = str

[2] hd_count = 4
[2] hd[0] = <<
[2] hd[1] = hd1
[2] hd[2] = <<
[2] hd[3] = hd2

[2] red_count = 0


*TWO*
----- ask djoyke what counts she wants, i think easier to use << hd == 2
		then iterate hd_count to find meta and eof, since same array...
proc_count = 0				= 1 process
hd_count = 2				= 1 hd
[0] hd[0] = <<
[0] hd[1] = eof

red_count = 4				= 2 redirects
[0] reds[0] = >
[0] reds[1] = out_file
[0] reds[2] = <
[0] reds[3] = in_file

str_count = 4				= 4 cmd args
[0] str[0] = something
[0] str[1] = string
[0] str[2] = and
[0] str[3] = things

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

