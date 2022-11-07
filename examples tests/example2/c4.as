.entry LOOP
.entry LENGTH
.extern L3
.extern W
	
MAIN:	mov S1.1 ,W
	add r2,STR
LOOP:	jmp W
	macro m1 
		mov 	S1.2,r3
		
		macro m2
			inc 	k
		endmacro
	endmacro
	m1
	m2
	prn	#-5
	sub 	r1,r4
	bne	L3
END:	hlt

