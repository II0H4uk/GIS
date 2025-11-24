* SPICE NETLIST
***************************************
.SUBCKT circuit x1 y1 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
X0 x1 y1 vdd! gnd! NOT
X1 x1 y1 vdd! gnd! NOT
.ENDS
***************************************
.SUBCKT NOT x1 y1 vdd! gnd!
** N=4 EP=0 IP=0 FDC=0
M0 y1 x1 vdd! vdd! pmos_h
M1 y1 x1 gnd! gnd! nmos_h
.ENDS
***************************************