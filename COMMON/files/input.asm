push 100
pop rxx
jmp 1000:
:1001
push 777
pop ryx
ret
:1000
push rxx
push ryx
add
out
