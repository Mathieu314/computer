SET r2, 0x82
ADD r1, r2, r3
SUB r4, r1, r3
STB r0, 0x01
LDB r5, 0x10
B 0x278
BEQ r1, r7, 0xf
IN r3, r2
