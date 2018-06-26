.name "Chuck Norris"
.comment "Chuck Norris peut encercler ses ennemis. Tout seul."

		sti r1, %:mort, %1
		ld %1179648, r3
		ld %65536, r4
mort:	live %1
		sti r3, %:pam, %1
		add r3, r4, r3
pam:	fork %10
		live %16777216
		and r1, %0, r1
		zjmp %:mort







