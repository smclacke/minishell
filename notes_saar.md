<br/><br/>

## (03/07)

<br/>

### **lexer:** takes *cmd arugments, separates into tokens, puts into linked list

### **parser:** parse linked list and make a AST to pass to the expander...

<br/>

**metas:** pipe, ampersand, semicolon, less-than, more-than, left parenthesis, right parenthesis, <br/>
dollar, backquote, backslash, single quote, double quote, newline, space and tab

**delimiter:**  whatever is after <<
try delimiter with and without quotes!!! (ole note)

<< + DELIMITER

**redirects:** more-than/less-than and pipe, double more-than/less-than

** handle: ** dollars, $?, ctrl-C, ctrl-D, ctrl-\

** tokenize the builtins ** echo ( + -n), cd (relative/abso path), pwd, export, unset, env, exit

• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence

• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)


<br/>

tokenise based on quotes, spaces and meta characters

so since quotes and spaces are meta in linux shell, just tokenise metas...


!!!! remember Djoyke needs to handle absolute paths, and relatives
!!!! specify if double or single quotes by, maybe, token for single, token for double.. or is that 
part of the parsing tree?


get lexer (so far working) then add in prompt, getting that working, then start seeing if it works correctly with all symbols, flags, quotes etc etc etc etc etccccccccc

