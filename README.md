# RPN calculator
It interprets given expressions written in Reverse Polish Notation (RPN).

Compile with\
`$ make`

Run with\
`$ ./interp`

Available commands:
- `print` *rpn-expr*\
Evaluate *rpn-expr* and write result on the standard output.\
Note: each symbol must be separated with at least one space.
- `assign` *rpn-expr* `to` *var*\
Evaluate *rpn-expr* and assign its value to *var* variable.\
Note: *var* must consist of at most 7 characters and must not include whitespace characters. It musn't cover the name of built-in functions too.
- `clear`\
Removes all assigned variables from the variables' environment.
- `exit`\
Quits program.

Built-in functions and operators:
- `+`
- `-`
- `*`
- `/`
- `modulo`
- `min`
- `max`
- `log`
- `pow`
- `abs`
- `sgn`
- `floor`
- `ceil`
- `frac`
- `sin`
- `cos`
- `atan`
- `acot`
- `ln`
- `exp`
