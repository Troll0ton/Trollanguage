call 97:
jmp 2:
:97
in
pop [97]
push 1
pop [98]
:3
push [97]
push 0
ja 5:
push 0
jmp 6:
:5
push 1
:6
push 0
je 4:
push [98]
push [97]
mul
pop [98]
push [97]
push 1
sub
pop [97]
jmp 3:
:4
push [98]
out
ret
:2
hlt
