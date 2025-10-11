* SPICE NETLIST
***************************************

.SUBCKT pmos_h
** N=4 EP=0 IP=0 FDC=0
.ENDS
***************************************
.SUBCKT Circuit Vdd! g
** N=4 EP=4 IP=32 FDC=8
M0 Vdd! Vdd! g pmos_h
M1 Vdd! Vdd! g pmos_h
X0 1 1 g B
X1 g Vdd! A
X2 1 1 g B
.ENDS
***************************************
.SUBCKT A g Vdd!
** N=4 EP=0 IP=0 FDC=0
D0 g 1 pmos_h
D1 g 1 pmos_h
M0 Vdd! 1 pmos_h
.ENDS
***************************************
.SUBCKT B a b c
** N=4 EP=0 IP=0 FDC=0
M0 a a c pmos_h
M1 b b c pmos_h
.ENDS
***************************************