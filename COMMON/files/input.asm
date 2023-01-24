call 1001:
pop rxx
jmp 1000:
:1001
push 200
pop ryx
push 100
ret
:1000
push rxx
push ryx
add
out
