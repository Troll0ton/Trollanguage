push 0
pop rxx
push 0
pop ryx
push 0
push rxx
push 100
add
je 1:
push rxx
push 1
add
pop rxx
push ryx
push 1
add
pop ryx
jmp 4:
:1
push ryx
push 1000
add
pop ryx
push rxx
push 1600
add
pop rxx
:4
push rxx
push ryx
add
out