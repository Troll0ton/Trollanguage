push 8
pop rxx
push 0
pop ryx
push 0
push rxx
push 10
add
je 1:
push 100
pop ryx
jmp 2:
:1
:2
:3
push 0
push rxx
je 4:
push ryx
push 15
add
pop ryx
push rxx
push 1
sub
pop rxx
jmp 3:
:4
push 0
push ryx
je 5:
push rxx
push 56
sub
pop rxx
jmp 6:
:5
push 1800
pop ryx
:6
push ryx
push 88
sub
out