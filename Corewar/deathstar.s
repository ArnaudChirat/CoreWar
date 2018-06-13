.name "Deathstar"
.comment "Fear is the path to the dark side. Fear leads to anger; anger leads to hate; hate leads to suffering. I sense much fear in you."

sti r1, %:live, %1
ld %0, r2
ld %19660800, r3
fork %:f1
live: live %1
	fork %:f2
	 and r3, %0, r3
	 zjmp %:live
f1:	st r2, -42
	st r2, -51
	st r2, -60
	st r2, -69
	st r2, -78
	st r2, -87
	st r2, -96
	st r2, -105
	st r2, -114
	st r2, -123
	st r2, -132
	st r2, -141
	st r2, -150
	st r2, -159
	st r2, -168
	st r2, -177
	st r2, -186
	st r2, -195
	st r2, -204
	st r2, -213
	st r2, -222
	st r2, -231
	st r2, -240
	st r2, -249
	st r2, -258
	st r2, -267
	st r2, -276
	st r2, -285
	st r2, -294
	st r2, -303
	st r2, -312
	st r2, -321
	st r2, -330
	zjmp %:f1
#f2: st r1, 6
#	live %42
#	lfork %800	
#	st r1, 6
#	live %42
#	lfork %1600
#	st r1, 6
#	live %42
#	lfork %2400
#	st r1, 6
#	live %42
#	lfork %3200
f2:	st r1, 6
	live %42
	add r3, r2, r2
	and	r2, %4294901760, r2
	or r2, %1108, r2
	st r2, 6
	lfork %200
	add r15, r15, r15
	zjmp %:f2

