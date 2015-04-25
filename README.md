ArithmeticLanguage
==================

This is a toy language meant to be used as an example of creating a simple interpreter using lex/yacc.

In summary, this interpreter can compute any arithmetic operation expressed with +, -, \*, / and parenthesis. Similarly, double-quoted strings are allowed in the language. Though computations will take place for each line in the language, only lines preceeded with "print" will yield an *observable* result. There are no variables in the language or any other useful constructs.

Other language features have been explicitly omitted to keep the example useful but not *too* contrived. Comments are supported by placing a double-quoted string on its own line without a "print" statement.

Building
========

Run the following command (assuming you have lex, yacc, and cc installed):
```bash
$ make
```

Example
=======

An example script is as follows

```
1 + 3 * 3
"I act as a comment (though I'm parsed, I'm not observable)"
print "Test.. This works!"
print "Result 1 (should be 2): " @ 1+2*3/6 @ ", Result 2 (on same line. should be 16): " @ (8*2)+(3*4)*0
"some string that won't be displayed since we didn't print... But it still parses :D"
1*2/8 @ "same thing with this string and its results" @ 4
print "Nice print ..." @ 4 @ "... Done!"
```

