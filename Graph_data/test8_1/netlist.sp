* SPICE NETLIST
***************************************
.SUBCKT BigCircuit x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 x3 x4 y1 vdd! gnd! Logic6
X1 x1 x2 x3 x4 y1 vdd! gnd! Logic6
X2 x1 x2 x3 x4 y1 vdd! gnd! Logic6
X3 x1 x2 x3 x4 y1 vdd! gnd! Logic6
.ENDS
***************************************
.SUBCKT Logic6 x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 x3 x4 y1 vdd! gnd! Logic5
X1 x1 x2 x3 x4 y1 vdd! gnd! Logic5
X2 x1 x2 x3 x4 y1 vdd! gnd! Logic5
X3 x1 x2 x3 x4 y1 vdd! gnd! Logic5
.ENDS
***************************************
.SUBCKT Logic5 x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 x3 x4 y1 vdd! gnd! Logic4
X1 x1 x2 x3 x4 y1 vdd! gnd! Logic4
X2 x1 x2 x3 x4 y1 vdd! gnd! Logic4
X3 x1 x2 x3 x4 y1 vdd! gnd! Logic4
.ENDS
***************************************
.SUBCKT Logic4 x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 x3 x4 y1 vdd! gnd! Logic3
X1 x1 x2 x3 x4 y1 vdd! gnd! Logic3
X2 x1 x2 x3 x4 y1 vdd! gnd! Logic3
X3 x1 x2 x3 x4 y1 vdd! gnd! Logic3
.ENDS
***************************************
.SUBCKT Logic3 x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 x3 x4 y1 vdd! gnd! Logic2
X1 x1 x2 x3 x4 y1 vdd! gnd! Logic2
X2 x1 x2 x3 x4 y1 vdd! gnd! Logic2
X3 x1 x2 x3 x4 y1 vdd! gnd! Logic2
.ENDS
***************************************
.SUBCKT Logic2 x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 x3 x4 y1 vdd! gnd! Logic1
X1 x1 x2 x3 x4 y1 vdd! gnd! Logic1
X2 x1 x2 x3 x4 y1 vdd! gnd! Logic1
X3 x1 x2 x3 x4 y1 vdd! gnd! Logic1
.ENDS
***************************************
.SUBCKT Logic1 x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 1 vdd! gnd! NotNot
X1 x2 x3 1 vdd! gnd! NAND
X2 x4 1 vdd! gnd! NotNot
X3 x1 2 vdd! gnd! NotNot
X4 x2 x3 2 vdd! gnd! NAND
X5 x4 2 vdd! gnd! NotNot
X6 x1 3 vdd! gnd! NotNot
X7 x2 x3 3 vdd! gnd! NAND
X8 x4 3 vdd! gnd! NotNot
X9 x1 4 vdd! gnd! NotNot
X10 x2 x3 4 vdd! gnd! NAND
X11 x4 4 vdd! gnd! NotNot
X12 1 2 y1 vdd! gnd! NAND
X13 3 4 y1 vdd! gnd! NAND
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