.entry LOOP
.entry LENGTH
.extern L3
.extern W
	
MAIN:	mov S1.1 ,W
	add r2,GAL
LOOP:	jmp W
	macro m1
		inc 	k
		mov 	S1.2,r3
	endmacro
	prn	#-5
	sub 	r1,r4
	m1
	bne	L2
END:	hlt
STR: 	.string "abcdef"
LENGTH: .data 6,-9,15
k:	.data 22
S1:	.struct 8,"ab" 
