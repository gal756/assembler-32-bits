.entry LOOP
.entry LENGTH
.extern L3
.extern W
	
MAIN:	mov S1.1 ,W
	add r2,STR
	m1
LOOP:	jmp W
	macro m1
		inc 	k
		mov 	S1.2,r3
	endmacro
	prn	#-5
	sub 	r1,r4
	bne	L3
END:	hlt
