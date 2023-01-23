push 5
pop rxx
push 10
pop ryx
:2
push 0
push rxx
je 3:
push rxx
push 1
sub
pop rxx
push ryx
push 1
add
pop ryx
jmp 2:
:3
push ryx
out