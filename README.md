# C-X16 Assembler Project History

My favorite project (currently) while a student at Western Washington Univeristy in the Computer Science Major. This project was given to me and my fellow students by professor See-Mong Tan while in his Computer Systems I class.

## C-X16 Assembler

The xas.c file is an assembler for the X16, which can write and compile assembler code written in X16 assembler into binary objects that could be load an run by an emulator. 

<b>**Important Note: The assembler is in file xas.c, I wrote some of the other files (bits.c) and did some of the code in the other files, however most of the code in these other files were provided by professor See-Mong. These files take infomation provided by me from xas (all my code) and fill in the binary instruction via emit_ calls **</b>

### How to run/returns: ###

The xas.c program accepts exactly one argument, the name of the assembler file to process, and produces the output file a.obj. However, for the purpose of demonstration I've modified the code such that it will not only produce the file a.obj, but also print the contents (the 16 bit instructions) to the terminal. Moreover, the program will return 0 on success, 1 if no file was specified, 2 for any other error messages.

<b>Compile with:</b>
<pre> make </pre>

<b>To run:</b>
<pre>./xas test/[filename].x16s</pre>


### Test file example, the following test loops:
 
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

The file produced by the example has a series of 16-bit words stored in Big Endian format. The first word is 0x3000, the location to load the program. It is always that value, since our assembler only produces users programs. Then there are 7 instructions for (add, ..., halt) followed by two 16-bit data values of 42 and 10 respectively (bit values are formatted for readability).

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

