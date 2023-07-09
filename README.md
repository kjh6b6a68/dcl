# dcl
 
This is a program inspired by the program from Dennis Ritchie and Brian Kernighan's book "The C Programming Language", chapter 5, section 12.  
I made this program to get a better understanding of recursive descent parser.

#### Difference between my program and the program from the book
* The program from the book only parses declarations in which no function has parameters, but my program can parse those that have them.
* The program from the book uses `ungetch()` function, but I felt that is not needed and dirty so I didn't use it.
* My program has more elaborated error messages.

#### How to execute
It reads a single declaration from the standard input and prints its meaning in plain english.
