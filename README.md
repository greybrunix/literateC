# literateC

**literateC** is a UNIX LL(1) parser for C89 literate Programming.

### Note
  **literateC** is not a compiler or a typesetting program,
it is just a translation parser to C and (La)TeX

  It was originaly meant to be a LR(1) canonical parser, but such is too
complex to build from scratch and is best done with assistance from tools
such as Lex and Yacc.

## Features

  * It produces a temporary LaTeX file with a one to one translation of
the source .ltc code;
  * It produces a temporary C file with necessary changes in
order to be compilable in C89;
  * By default it compiles the C code and produces a .dvi, .ps
or a .pdf file.
  * The temporary files are, by default, preserved but can be
optioned to not be stored, being deleted upon termination. 

## Usage

WIP - To be Developed

## Instalation

WIP - To be Developed

## Credits

   * bdg (greybrunix)

### Sources

   * Knuth, Donald; "On the Translation of Languages from
Left to Right"; Information and Control Vol.8, Issue 6, p607-639; 1965
   * Purple/Red/Green Dragon Book (any of which is helpful)
