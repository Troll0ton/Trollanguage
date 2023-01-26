# Trollanguage
My own language

## Overview
This work is the final project of the last semester, which includes most of the previous work.
It is an assembly from the compiler and the processor, which was made earlier.
The compiler is able to convert code written in MY programming language into assembler code, which is subsequently executed by MY processor.
To compile and execute YOUR program, you need to put it in a text file. (input.txt)
~~~
Trollanguage/frontend/files/input.txt
~~~

## Execute the programm:
~~~
COMPILATION - compile.bat (frontend.exe, backend.exe)
EXECUTION - proc.bat (asm.exe, cpu.exe)
~~~

## Comand line arguments

-absent-

## Supported code:
-simple operations: +, -, *, /, ^, sin, cos, ln, tg, sqrt;
-variable (ATTENTION!!! This version of project supports only single letter variables: a, x and others)
-assignment operator: 
~~~
x=100+56*y^3
~~~
-conditional operator: 
~~~
if(x+1221) y=56
~~~
-conditional operator with else: 
~~~
                                  if(x+1221) y=56
                                  else y=89
~~~                                  
-cycles: 
~~~
while(x) x=x-1
~~~
-comparison operators: >, <, ~ (this is ==):
~~~
if((x)>(20)) y=78
~~~
-"body" structure:   
 ~~~
                     if(x+1221){
                     z=y+90
                     m=78
                     }
~~~
~~~
                     while(u){
                     u=u+1
                     y=y+89
                     } 
~~~
-function initialization: 
~~~
                           funct a (){
                           t=32
                           z=989
                           m (this means, that this function RETURNS this value)
                           }
~~~

-function using: 
~~~
x=f()+78
~~~

-print ans scan functions:
~~~
scan(x)
print(y+909)
~~~


### Unit tests
All supported operations are shown in the examples.
~~~
Trollanguage/frontend/files/...
~~~

## Documentation

-absent-

**Troll0ton corporation** 
