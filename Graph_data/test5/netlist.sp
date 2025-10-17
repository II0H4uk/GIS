* SPICE NETLIST
***************************************
.SUBCKT circuit 4 5 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
D0 2 5 dn
D1 3 4 dn
M0 1 2 vdd! pmos_h
M1 1 2 gnd! nmos_h
M2 1 3 vdd! pmos_h
M3 1 3 gnd! nmos_h
M4 0 vdd! 1 nmos_h
.ENDS
***************************************
