push 5
pop rxx
:2
push 0
push rxx
je 3:
push rxx
push 1
sub
pop rxx
jmp 2:
:3
push rxx
out