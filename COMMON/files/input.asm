call 97:
jmp 2:
:97
push 1
pop [97]
push 0
pop [98]
push -1
pop [99]
call 98:
pop [100]
call 99:
ret
:2
jmp 3:
:98
push [98]
push [98]
mul
push 4
push [97]
mul
push [99]
mul
sub
sqrt
ret
:3
jmp 4:
:99
push [98]
push [100]
add
push 2
push [97]
mul
div
pop [120]
push [98]
push [100]
sub
push 2
push [97]
mul
div
pop [121]
push [120]
out
push [121]
out
ret
:4
hlt
