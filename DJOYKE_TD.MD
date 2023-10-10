-----------$ expanding----------

builtin is not executing if:
 !_-(_|\echo abc$USER
[0]      cmd = echo     file = (null)   meta = (null)   str = (null)
[1]      cmd = (null)   file = (null)   meta = (null)   str = abc$USER
abc$USER compare_str = [USER]
before_dollar = [abc]
node->data->str = [abcdreijans]

 !_-(_|\echo $
[0]      cmd = echo     file = (null)   meta = (null)   str = (null)
[1]      cmd = (null)   file = (null)   meta = (null)   str = $
$ expander:             dolllaaaah

 !_-(_|\echo abc$i
[0]      cmd = echo     file = (null)   meta = (null)   str = (null)
[1]      cmd = (null)   file = (null)   meta = (null)   str = abc$i
abc$i compare_str = [i]
before_dollar = [abc]
node->data->str = [abc]
SEGFAULT

----------Make the executor expandable based on pipes--------

1) basic structure works
2) how do I want to expand it?
3) do I want to use 2 pipes and pass it on?


--------------------RANDOM-------------------------

1)Does Sarah or do I handle the passing of the quotes?
2) as soon as quotes are fixed 
    1) check exit and unset again for the quoted value etc
    2) check echo again
3) make bash script for easier testing


---------------BUILTIN------------------------------

review the checking of the builtins because its case sensitive

cd:

 * relative: cd src
 * absolute: cd src/bin/pannekoek/whatever TESTT!!!
 * 				cd alone gives prompt back
 * 				cd jfhjvhs gives: cd: no such file or directory: jfhjvhs
 * line 66: check if needs error message with exit
 * 			give prompt back, and endline?


-------------------$-----------------------

-----------------------------------------

echo $USER
dreijans

echo "$USER"
dreijans

------------------------------------------------

echo $ USER
$ USER

echo $"USER"
USER

-------------------------------------------------

echo $ U"SER"
$ USER

echo '$USER'
$USER

echo $'USER'
USER

echo $U'SER'
SER

"echo $USER"
echo minishell: command not found

'echo $USER'
echo $USER: command not found


-------------------------------------------------

echo abc$USER
abcdreijans

echo "abc$USER"
abcdreijans

-----------------------------------------------------

echo abc$i
abc

echo abc$
abc$

echo a$bc
a


---------------------METAA-------------------------------

1) infile <
2) outfile >
3) pipe |
4) append >>
5) heredoc <<

---------------------SARAH NOTES-------------------------------

hello lovely, it will all be ok soon... hopefully.. hehe

**DOLLAR QUOTES YAY**

when dollar in double remove quotes
when dollar in single take string literally

else, dollar + anything not quotes - expand
anything quoted = string to add as cmd arg

->>> $USER
expand = cmd = smclacke

dollar should also be seen as cmd after expansion
i.e. -> $USER
[0] cmd = smclacke

so that 
export hi=echo
-> $hi
[0] cmd = echo


export new_cmd=echo
$new_cmd hello djoyke
hello djoyke


export sarah=echo
export djoyke=echo
$sarah hello
hello
$djoyke hi
hi
$djoyke $sarah
echo
echo echo
echo
