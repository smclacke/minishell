<br/><br/>

## (03/07)

<br/>

### **lexer:** takes *cmd arugments, separates into tokens, puts into linked list

### **parser:** parse linked list and make a AST to pass to the expander...

<br/>

**metas:** pipe, ampersand, semicolon, less-than, more-than, left parenthesis, right parenthesis, <br/>
dollar, backquote, backslash, single quote, double quote, newline, space and tab

**delimiters:**  semi-colon, pipe, ampersand


**redirects:** more-than/less-than, pipe... anymore?

<br/>

tokenise based on quotes, spaces and meta characters

so since quotes and spaces are meta in linux shell, just tokenise metas...
