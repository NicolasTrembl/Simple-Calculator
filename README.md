# A simple calculator


## Order of Operations :

This calculator evaluates expressions following the **PEMDAS** order of operation :

1. Function ($cos, sin, tan, \\sqrt{\~}, ...$)
2. Exponent
3. Division / Multiplication
4. Addition / Substraction


## Tokenizing

Each valid element is tokenized as one of the following :

| Element   | Description           | Example           | | Element     | Description           | Example           |
| -------   | -----------           | :-----:           |-| -------     | -----------           | :-----:           |
| NUMBER    | Any number            | $123.4$           | | COS         | Cosine                | $cos\~a$           |
| PLUS      | Addition              | $a+b$             | | TAN         | Tangent               | $tan\~a$           |
| UMINUS    | Unary subtraction     | $-a$              | | SQRT        | Square Root           | $\\sqrt{a}$        |
| BMINUS    | Binary subtration     | $a-b$             | | LOG         | Logarithm             | $log\~a$           |
| MULTIPLY  | Multiplication        | $a\\times a$       | | LN          | Natural Log           | $ln\~a$            |
| DIVIDE    | Division              | $\\frac{a}{b}$     | | PI          | Constant pi           | $\\pi$             |
| POWER     | Exponent              | $a^b$             | | E           | Constant e            | $e$               |
| SIN       | Sine                  | $sin\~a$           | | PARENTHESIS | Parenthesis or bracket| $(\~[\~$ & $\~]\~)$   |


## translation to **postfix** notation

> [!NOTE]
> As the expression is translated to a *postfix* notation, the priority of operation is unambiguous and there is no need of parenthesis

*Postfix* notation places the operator after the arguments while the regular *infix* notation places it in between

For example :

| Infix                 | Postfix           |
| :---:                 | :-----:           |
| $a + b$               | $ab+$             |
| $(a+b)\\times(c/d)+e$  | $ab+cd/\\times e+$ |

## Evaluation 

*Postfix* allows for a very simple evaluation from left to right using only a stack and a small buffer

For exemple :

We want to evaluate $5+4\\times 2$
which translates to *postfix* as : $2\~4\\times 5+$ 

| Steps     | 0                                                                                                                             | 1                                                                                                                              | 2                                                                                                                               | 3                                                                                                                          | 4                                                                                                                           | 5                                                                                                                            | 6
| :---:     | :---:                                                                                                                         | :-:                                                                                                                            | :-:                                                                                                                             | :-:                                                                                                                        | :-:                                                                                                                         | :-:                                                                                                                          | :-:
| **Stack** | <table><tr><td>$2$</td></tr><tr><td>$4$</td></tr><tr><td>$\times$</td></tr><tr><td>$5$</td></tr><tr><td>$+$</td></tr></table> | <table><tr><td>$\~$</td></tr><tr><td>$4$</td></tr><tr><td>$\times$</td></tr><tr><td>$5$</td></tr><tr><td>$+$</td></tr></table> | <table><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$\times$</td></tr><tr><td>$5$</td></tr><tr><td>$+$</td></tr></table> | <table><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$8$</td></tr><tr><td>$5$</td></tr><tr><td>$+$</td></tr></table> | <table><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$5$</td></tr><tr><td>$+$</td></tr></table> | <table><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$+$</td></tr></table> | <table><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$\~$</td></tr><tr><td>$13$</td></tr></table>  
| **Buffer**| <table><td>$\~$</td><td>$\~$</td></table>                                                                                     | <table><td>$2$</td><td>$\~$</td></table>                                                                                       | <table><td>$2$</td><td>$4$</td></table>                                                                                         | <table><td>$\~$</td><td>$\~$</td></table>                                                                                  | <table><td>$8$</td><td>$\~$</td></table>                                                                                    | <table><td>$8$</td><td>$5$</td></table>                                                                                      | <table><td>$\~$</td><td>$\~$</td></table>


At step $3$ and $6$, when there is an operator, we can just evaluate it with the value in the buffer and put he result back in the stack

## TODO next :

While it work as it is, there is a lot of room for improvement :

 - [ ] Commenting the code
 - [ ] Add an 'How to use' section to this readme 
 - [ ] Adding error support
 - [ ] Cleaning the code for the stack
 - [ ] Adding more functions
 - [ ] Improving the interface

And maybe : 
 - [ ] Adding support for unknown numbers