* SPICE NETLIST
***************************************
.SUBCKT BigCircuit x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 1 vdd! gnd! NAND
D1 2 1 dn
X2 x3 3 vdd! gnd! NOT
X3 3 x4 4 vdd! gnd! NAND
X4 2 5 y1 vdd! gnd! NAND
X5 4 5 vdd! gnd! NotNot
.ENDS
***************************************
.SUBCKT NAND x1 x2 y vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
M0 y x1 vdd! vdd! pmos_h
M1 y x2 vdd! vdd! pmos_h
M2 y x1 1 1 nmos_h
M3 1 x2 gnd! gnd! nmos_h
.ENDS
***************************************
.SUBCKT NotNot x1 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 1 vdd! gnd! NOT
X1 1 y1 vdd! gnd! NOT
.ENDS
***************************************
.SUBCKT NOT x1 y1 vdd! gnd!
** N=4 EP=0 IP=0 FDC=0
M0 y1 x1 vdd! vdd! pmos_h
M1 y1 x1 gnd! gnd! nmos_h
.ENDS
***************************************