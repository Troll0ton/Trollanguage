push 900
pop rxx
jmp 1:
:210
push 77
ret
:1
jmp 3:
:197
push 77
ret
:3
call 197:
call 210:
add
out
