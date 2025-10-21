* SPICE NETLIST
***************************************
.SUBCKT circuit bl bl_bar wl vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
M0 1 wl bl_bar nmos_h
M1 2 wl bl nmos_h
X2 1 2 vdd! gnd! NOT
X3 2 1 vdd! gnd! NOT
.ENDS
***************************************
.SUBCKT NOT x1 y1 vdd! gnd!
** N=4 EP=0 IP=0 FDC=0
M0 y1 x1 vdd! vdd! pmos_h
M1 y1 x1 gnd! gnd! nmos_h
.ENDS
***************************************