call 97:
jmp 2:
:97
push 0.00159265
pop [120]
push 0
pop [121]
push 0
push [120]
push 10
add
je 3:
push 100
pop [121]
jmp 4:
:3
:4
:5
push 0
push [120]
je 6:
push [121]
push 15
add
pop [121]
push [120]
push 1
sub
pop [120]
jmp 5:
:6
push 0
push [121]
je 7:
push [120]
push 56
sub
pop [120]
jmp 8:
:7
push 1800
pop [121]
:8
push [121]
out
push [121]
out
ret
:2
hlt
