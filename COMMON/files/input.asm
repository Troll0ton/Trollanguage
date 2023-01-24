call 97:
jmp 2:
:120
push 900
ret
:2
jmp 4:
:121
push 100
ret
:4
jmp 6:
:97
push 900
pop rxx
call 120:
call 121:
add
out
ret
:6
