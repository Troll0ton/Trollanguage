call 97:
jmp 2:
:97
push 0
pop [120]
push [120]
push 20
ja 5:
push 0
jmp 6:
:5
push 1
:6
push 0
je 3:
push 666
pop [121]
jmp 4:
:3
push 777
pop [121]
:4
push [121]
out
ret
:2
hlt
