* SPICE NETLIST
***************************************
.SUBCKT circuit 5 6 7 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
D0 3 5 dn L=3.5e-07 W=1e-06 $X=6950 $Y=1600 $D=3
D1 4 6 dn L=3.5e-07 W=1e-06 $X=6950 $Y=4850 $D=3
D2 4 7 dn L=3.5e-07 W=1e-06 $X=6950 $Y=8100 $D=3
D3 8 4 dn L=3.5e-07 W=1e-06 $X=6950 $Y=11350 $D=3
M0 2 3 4 nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
M1 1 3 9 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=8100 $D=3
M2 0 2 3 nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
X0 8 9 vdd! gnd! NOTNOT
.ENDS
***************************************
.SUBCKT NOTNOT x1 y1 vdd! gnd!
** N=4 EP=0 IP=0 FDC=0
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