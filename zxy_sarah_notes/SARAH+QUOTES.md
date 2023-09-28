**Quote Expansion**

bash = 

echo "something << hello >in"
something << hello >in

--------------> Is it the case that all strs (in my struct)
		can just lose their quotes..? for all cases?

--------------> what else do we need to do with the quotes??

- **SINGLE QUOTES**

    - preserves literal value of each character
    - a single quote may not occur between single quotes, even when 	preceded by a backslash GOOD

- **DOUBLE QUOTES**

    - double quote can be quoted within double quotes by preceding it with a backslash DON'T HANDLE THIS
    - preserve the literal value of all characters within the quotes
    - EXCEPT FOR ‘$’

- **DOLLAR**

        - BUT subject = Handle " (double quote) which should prevent the shell from interpreting the meta characters in the quoted sequence except for $ (dollar sign).
=== // dollar in or out DOUBLE quotes should still be dollar
=== // dollar in SINGLE quotes should not be dollar:
echo '$USER'
$USER



meta characters have special meaning and need to be quoted if representing itself


	**COMMAND QUOTATIONS**
:):):)

"wc -l" < file somthing | << eof
[0]	 cmd = "wc -l"	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = <	str = (null)
[2]	 cmd = (null)	file = file	meta = (null)	str = (null)
[3]	 cmd = (null)	file = (null)	meta = (null)	str = somthing
[4]	 cmd = (null)	file = (null)	meta = |	str = (null)
[5]	 cmd = (null)	file = (null)	meta = <<	str = (null)
[6]	 cmd = (null)	file = (null)	meta = (null)	str = eof


wc -l < file something | << eof
[0]	 cmd = wc	file = (null)	meta = (null)	str = (null)
[1]	 cmd = (null)	file = (null)	meta = (null)	str = -l
[2]	 cmd = (null)	file = (null)	meta = <	str = (null)
[3]	 cmd = (null)	file = file	meta = (null)	str = (null)
[4]	 cmd = (null)	file = (null)	meta = (null)	str = something
[5]	 cmd = (null)	file = (null)	meta = |	str = (null)
[6]	 cmd = (null)	file = (null)	meta = <<	str = (null)
[7]	 cmd = (null)	file = (null)	meta = (null)	str = eof


< Makefile wc -l
234
< Makefile "wc -l"
wc -l: command not found
< Makefile "wc"
 234  639 6115

================

 < Makefile "echo"

 < Makefile "echo -n"
echo -n: command not found


