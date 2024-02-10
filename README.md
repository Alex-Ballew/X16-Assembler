# C-X16 Assembler Project History

My favorite project (currently) while a student at Western Washington Univeristy in the Computer Science Major. This project was given to me and my fellow students by professor See-Mong Tan while in his Computer Systems I class.

## C-X16 Assembler

The xas.c file is an assembler for the X16, which can write and compile assembler code written in X16 assembler into binary objects that could be load an run by an emulator.

<b>**NOTE: Instuction.c and Instruction.h were provided by professor See-Mong, but everything else is my own creation (bits.c, bits.h, xas.c) **</b>

### Test file example, the following test loops
 
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

### Output file and explanation:

The file produced by the example has a series of 16-bit words stored in Big Endian format. The first word is 0x3000, the location to load the program. It is always that value, since our assembler only produces users programs. Then there are 5 instructions for (add, ..., halt) followed by two 16-bit data values of 42 and 10 respectively (bit values are formatted for readability).

<pre>
0011 0000 0000 0000 
0001 0010 0010 1010
0010 0000 0000 0101
1111 0000 0010 0001
0001 0010 0111 1111
0000 0100 0000 0001
0100 1111 1111 1011
1111 0000 0010 0101
0000 0000 0010 1010
0000 0000 0000 1010
</pre>

