.name "Chuck Norris"
.comment "Chuck Norris peut encercler ses ennemis. Tout seul."

		sti r1, %:mort, %1
		ld %32768, r3
		ld %8388608, r4
mort:	live %1
		sti r3, %:pam, %1
		add r3, r4, r3
pam:	lfork %10
		live %16777216
		and r1, %0, r2
		zjmp %:mort







