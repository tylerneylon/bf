# brainf*ck interpreter

Because it's fun to write small Turing complete interpreters :)

## Example usage

Run `make bf` to compile. To interpret a bf source file, such as `hello.bf`:

    ./bf hello.bf

or

    ./bf -d hello.bf

which sends debug info to stderr.

## What it is

`bf` is an interpreter of the brainf*ck language.

Brainf*ck is a Turing-complete language with only 8 command symbols,
listed here:

    +-<>[],.

There is a good summary of the language on
[the brainf*ck wikipedia page](http://en.wikipedia.org/wiki/Brainfuck#Commands).

## Sample input

Here are the complete contents of a hello world program, copied
from wikipedia and included with this repo as `hello.bf`:

    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++
    ..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

You can slightly visualize the control flow since
the `[` and `]` characters form a loop that helps efficiently
set data values for ASCII codes of the characters in the string
`Hello World!`.

## Debug output

Below is an edited sampling of the `stderr` output from a run
of `./bf -d hello.bf`

    --- 0 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
    ^
    Data:
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0
        ^
    --- 1 step done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
     ^
    Data:
        1,   0,   0,   0,   0,   0,   0,   0,   0,   0
        ^
    --- 2 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
      ^
    Data:
        2,   0,   0,   0,   0,   0,   0,   0,   0,   0
        ^
    
    (skipping steps)
    
    --- 10 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
              ^
    Data:
       10,   0,   0,   0,   0,   0,   0,   0,   0,   0
        ^
    --- 11 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
               ^
    Data:
       10,   0,   0,   0,   0,   0,   0,   0,   0,   0
        ^
    --- 12 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                ^
    Data:
       10,   0,   0,   0,   0,   0,   0,   0,   0,   0
             ^
    --- 13 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                 ^
    Data:
       10,   1,   0,   0,   0,   0,   0,   0,   0,   0
             ^
    
    (skipping steps)
    
    --- 318 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                           ^
    Data:
        1,  70, 100,  30,  10,   0,   0,   0,   0,   0
             ^
    --- 319 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                            ^
    Data:
        1,  70, 100,  30,  10,   0,   0,   0,   0,   0
        ^
    --- 320 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                             ^
    Data:
        0,  70, 100,  30,  10,   0,   0,   0,   0,   0
        ^
    --- 321 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                              ^
    Data:
        0,  70, 100,  30,  10,   0,   0,   0,   0,   0
        ^
    --- 322 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                               ^
    Data:
        0,  70, 100,  30,  10,   0,   0,   0,   0,   0
             ^
    --- 323 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                                ^
    Data:
        0,  71, 100,  30,  10,   0,   0,   0,   0,   0
             ^
    --- 324 steps done ---
    Source point:
    ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+
                                                 ^
    Data:
        0,  72, 100,  30,  10,   0,   0,   0,   0,   0
             ^
    
    (etc; there are 390 steps in total for hello.bf)

The last-listed step (step 325) is a `.` character, which
means to output whichever character is being pointed to in
the data array. In this case, it's number 72, which is the
ASCII code of character `H`, so we finally print out the
"H" in "Hello World!"


