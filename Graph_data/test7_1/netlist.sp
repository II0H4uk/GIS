* SPICE NETLIST
***************************************
.SUBCKT BigCircuit x1 x2 x3 x4 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 x2 1 vdd! gnd! NAND
D1 2 1 dn
X2 x3 3 vdd! gnd! NOT
X3 3 x4 4 vdd! gnd! NAND
X4 2 4 y1 vdd! gnd! NAND
.ENDS
***************************************
.SUBCKT NAND x1 x2 y vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
M0 y x1 vdd! pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
M1 y x2 vdd! pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=8100 $D=3
M2 y x1 1 nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M3 1 x2 gnd! nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
.ENDS
***************************************
.SUBCKT NOT x1 y1 vdd! gnd!
** N=4 EP=0 IP=0 FDC=0
M0 y1 x1 vdd! vdd! pmos_h
M1 y1 x1 gnd! gnd! nmos_h
.ENDS
***************************************