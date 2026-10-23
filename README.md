This is my own byte assembly emulator.8 bit processor. To run it you must first compile it to bytec then open termial/cmd and write bytec your assembly filename
Example "bytec main.asm".
Then it automaticly compile and run it.
Commands :
MOV to from - moves number to register or register to register.
PR what - prints number from register
Example 
MOV a 78
MOV d a
PR d 
it prints 78
In this emulator you can use 5 registers from a to e.
Numbers must be 8 bit (-128 to 127)
Please write issue if you have.
