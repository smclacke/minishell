------------------------------TO DO----------------------------

1) 

    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 

    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 

    handle exit codes

4) WAIT?

    minibleh:cat Makefile | grep pr | head -n 5 | cd file_not_exit
    minishell: cd: file_not_exit: No such file or directory
    cat: pr: No such file or directory
    cat: 5: No such file or directory
    cat: file_not_exit: No such file or directory
    head: cannot open 'file_not_exit' for reading: No such file or directory
    grep: 5: No such file or directory
    grep: file_not_exit: No such file or directory

    it should do just:

    bash: cd: file_not_exit: No such file or directory

6) WAIT?

    minibleh:cat Makefile | grep pr | head -n 5 | hello
    cat: pr: No such file or directory
    cat: 5: No such file or directory
    hello: command not found
    grep: 5: No such file or directory

    it should do:

    bash: hello: command not found

7) REDIR

    > file
    makefile error

8) REDIR

    minibleh:< does_not_exist
    makefile error

9) EXPORT OR EXPANDER

    export var=a
    export $var=test
    echo $var $a
    a test

10) EXPORT OR EXPANDER

    export var
    export var=test
    export
    var="test"

11) EXECUTE 

    bash does:

    dreijans@f0r1s11:~$ cat Makefile | cd file_not_exit
    bash: cd: file_not_exit: No such file or directory
    cat: Makefile: No such file or directory

    mine does:

    minibleh:cat Makefile | cd file_not_exit
    minishell: cd: file_not_exit: No such file or directory
    cat: file_not_exit: No such file or directory













----------------------------for sarah-------------------------

1) EXPANSION

    ./minishell
    $SHLVL

    bash: 2: command not found
    Needs to increment once per new shell session

    minibleh:$SHLVL
    1: command not found
    minibleh:./minishell
    minibleh:$SHLVL
    1: command not found

----------------------------------------------------------

2) PARSER

    "" 

    bash: : command not found

    ours:

    minibleh:""
    minibleh:dollar.c:86:8
        #5 0x4d27ff in expand_dollar /home/dreijans/Documents/ra        minibleh:> test | echo blabla
        ||
        index = [0], cmd = [echo]
        index = [0], str = [(null)]
        index = [0], meta = [(null)]
        next node

    export var=1 test=2
    echo $USER$var$USER$USER$USERtest$USER

    [username]1[username][username][username]

    ours:

    minibleh:echo $USER$var$USER$USER$USERtest$USER
    dreijans

----------------------------------------------------------

4) PARSING

    $
    bash: $: command not found

    ours:
    minibleh:$
    AddressSanitizer:DEADLYSIGNAL
    =================================================================
    ==1804020==ERROR: AddressSanitizer: SEGV on unknown address 0x0000004f17f0 (pc 0x000000420184 bp 0x000000000000 sp 0x7fff72ea8d50 T0)
    ==1804020==The signal is caused by a WRITE memory access.
        #0 0x420184 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) (/home/dreijans/Documents/rank3/minishell/minishell+0x420184)
        #1 0x49a095 in free (/home/dreijans/Documents/rank3/minishell/minishell+0x49a095)
        #2 0x4d02b1 in add_to_expand /home/dreijans/Documents/rank3/minishell/src/expander/expand_utils.c:27:2
        #3 0x4d3907 in dollar_bit /home/dreijans/Documents/rank3/minishell/src/expander/dollar_s_quotes.c:97:7
        #4 0x4d2d1f in dollar /home/dreijans/Documents/rank3/minishell/src/expander/expand_dollar.c:86:8
        #5 0x4d27ff in expand_dollar /home/dreijans/Documents/ra        minibleh:> test | echo blabla
        ||
        index = [0], cmd = [echo]
        index = [0], str = [(null)]
        index = [0], meta = [(null)]
        next node
        ||
        index = [1], cmd = [(null)]
        index = [1], str = [(null)]
        index = [1], meta = [>]        minibleh:> test | echo blabla
        ||
        index = [0], cmd = [echo]
        index = [0], str = [(null)]
        index = [0], meta = [(null)]
        next node
        ||
        index = [1], cmd = [(null)]
        index = [1], str = [(null)]
        index = [1], meta = [>]
        next node
        ||
        index = [2], cmd = [(null)]
        index = [2], str = [(null)]
        index = [2], meta = [(null)]
        next node
        ||
        index = [3], cmd = [(null)]
        index = [3], str = [(null)]
        index = [3], meta = [|]
        next node
        ||
        index = [4], cmd = [(null)]
        index = [4], str = [blabla]
        index = [4], meta = [(null)]
        next node
        NULL
        next node
        ||
        index = [2], cmd = [(null)]
        index = [2], str = [(null)]
        index = [2], meta = [(null)]
        next node
        ||
        index = [3], cmd = [(null)]
        index = [3], strecho blabla = [(null)]
        index = [3], meta = [|]
        next node
        ||
        index = [4], cmd = [(null)]
        index = [4], str = [blabla]
        index = [4], meta = [(null)]
        next node
        NULL
        #7 0x4d8a06 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:155:2
        #8 0x4cb5dd in main /home/dreijans/Documents/rank3/minishell/src/main.c:66:3
        #9 0x7fa677822d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
        #10 0x7fa677822e3f in __libc_start_main csu/../csu/libc-start.c:392:3
        #11 0x41f3d4 in _start (/home/dreijans/Documents/rank3/minishell/minishell+0x41f3d4)

    AddressSanitizer can not provide additional info.
    SUMMARY: AddressSanitizer: SEGV (/home/dreijans/Documents/rank3/minishell/minishell+0x420184) in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType)
    ==1804020==ABORTING
    make: *** [Makefile:93: run] Error 1

-----------------------------------------------------------

5) EXPANSION
    export ls="ls -l"
    $ls

    Executes $ls to ls -l and executes it


------------------------------------------------------------

6) PARSER

    $LESS$VAR
    bash: -R: command not found

    ours:

    minibleh:$LESS$VAR
    =================================================================
    ==1804358==ERROR: LeakSanitizer: detected memory leaks

    Direct leak of 3 byte(s) in 1 object(s) allocated from:
        #0 0x49a29d in malloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a29d)
        #1 0x4de9c9 in ft_strdup (/home/dreijans/Documents/rank3/minishell/minishell+0x4de9c9)
        #2 0x4d0239 in add_to_expand /home/dreijans/Documents/rank3/minishell/src/expander/expand_utils.c:24:9
        #3 0x4d35df in dollar_expand /home/dreijans/Documents/rank3/minishell/src/expander/dollar_s_quotes.c:67:7
        #4 0x4d38d3 in dollar_bit /home/dreijans/Documents/rank3/minishell/src/expander/dollar_s_quotes.c:92:7
        #5 0x4d2d1f in dollar /home/dreijans/Documents/rank3/minishell/src/expander/expand_dollar.c:86:8
        #6 0x4d27ff in expand_dollar /home/dreijans/Documents/rank3/minishell/src/expander/expand_dollar.c:120:3
        #7 0x4d009c in ft_expand /home/dreijans/Documents/rank3/minishell/src/expander/expand.c:24:3
        #8 0x4d8a06 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:155:2
        #9 0x4cb5dd in main /home/dreijans/Documents/rank3/minishell/src/main.c:66:3
        #10 0x7f18ef93fd8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

    SUMMARY: AddressSanitizer: 3 byte(s) leaked in 1 allocation(s).

---------------------------------------------------------------------

7) PARSER
    ..
    bash: ..: command not found

    minibleh:..
    =================================================================
    ==1804519==ERROR: LeakSanitizer: detected memory    minishell: cd: file_not_exit: No such file or directory
        cat: pr: No such file or directory
        cat: 5: No such file or directory
        cat: file_not_exit: No such file or directory
        grep: 5: No such file or directory
        grep: file_not_exit: No such file or directory
        head: cannot open 'file_not_exit' for reading: No such file or directory
        #1 0x4de9c9 in ft_strdup (/home/dreijans/Documents/rank3/minishell/minishell+0x4de9c9)
        #2 0x4d0239 in add_to_expand /home/dreijans/Documents/rank3/minishell/src/expander/expand_utils.c:24:9
        #3 0x4d35df in dollar_expand /home/dreijans/Documents/rank3/minishell/src/expander/dollar_s_quotes.c:67:7
        #4 0x4d38d3 in dollar_bit /home/dreijans/Documents/rank3/minishell/src/expander/dollar_s_quotes.c:92:7
        #5 0x4d2d1f in dollar /home/dreijans/Documents/rank3/minishell/src/expander/expand_dollar.c:86:8but at all the other redirect tests it does fine.
        #6 0x4d27ff in expand_dollar /home/dreijans/Documents/rank3/minishell/src/expander/expand_dollar.c:120:3
        #7 0x4d009c in ft_expand /home/dreijans/Documents/rank3/minishell/src/expander/expand.c:24:3
        #8 0x4d8a06 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:155:2
        #9 0x4cb5dd in main /home/dreijans/Documents/rank3/minishell/src/main.c:66:3
        #10 0x7f18ef93fd8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

    SUMMARY: AddressSanitizer: 3 byte(s) leaked in 1 allocation(s).

8) PARSER

    hi Sarah! I was testing something that went wrong in redirect but when
    I print the parser linked list it looks a bit scrambled. our minishell only makes the file but doesnt echo.


        minibleh:> test | echo blabla
        ||
        index = [0], cmd = [echo]
        index = [0], str = [(null)]
        index = [0], meta = [(null)]
        index = [0], file = [(null)]
        next node
        ||
        index = [1], cmd = [(null)]
        index = [1], str = [(null)]
        index = [1], meta = [>]
        index = [1], file = [(null)]
        next node
        ||
        index = [2], cmd = [(null)]
        index = [2], str = [(null)]
        index = [2], meta = [(null)]
        index = [2], file = [test]
        next node
        ||
        index = [3], cmd = [(null)]
        index = [3], str = [(null)]
        index = [3], meta = [|]
        index = [3], file = [(null)]
        next node
        ||
        index = [4], cmd = [(null)]
        index = [4], str = [blabla]
        index = [4], meta = [(null)]
        index = [4], file = [(null)]
        next node
        NULL

9) PARSER

    scrambled parser list
    
    minibleh:< does_not_exist | echo blabla > test6
    minishell: does_not_exist: No such file or directory

    should do:

    bash: does: No such file or directory
    Creates file called "test6" with blabla as content

10) PARSER
    
    parser list is scrambled here

    minibleh:> test | echo blabla
    minibleh:

    should do:

    blabla
    Creates file called "test"
