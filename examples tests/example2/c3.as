.entry LOOP
.entry LENGTH
.extern L3
.extern W
	
MAIN:	mov S1.1 ,W
	add r2,STR
LOOP:	jmp W
	macro m1 m2
		inc 	k
		mov 	S1.2,r3
	endmacro
	m1
	prn	#-5
	sub 	r1,r4
	bne	L3
END:	hlt

