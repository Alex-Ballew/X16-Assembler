# C-X16 Assembler Project History

My favorite project (currently) while a student at Western Washington Univeristy in the Computer Science Major. This project was given to me and my fellow students by professor See-Mong Tan while in his Computer Systems I class.

## C-X16 Assembler

The following is an assembler for the X16, which can write and compile assembler code written in X16 assembler into binary objects that could be load an run by an emulator.

### Test file example, the following test loops written in assembly
 
<pre>begin:
        add %r1, %r0, $10 <br>
start1:
        ld  %r0, star
        putc
        add %r1, %r1, $-1
        brz stop
        jsr start1
stop:
        halt
star:
        val $42    # ASCII 42 is the * charactger
newline:
        val $10    # ASCII 10 is the \n character </pre>

### Output file would include:
<pre>
0001 0010 0010 1010
0010 0000 0000 0101
1111 0000 0010 0001
0001 0010 0111 1111
0000 0100 0000 0001
0100 1111 1111 1011
1111 0000 0010 0101
0000 0000 0010 1010
</pre>

