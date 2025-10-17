* SPICE NETLIST
***************************************
.SUBCKT circuit 4 5 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
D0 2 5 dn L=3.5e-07 W=1e-06 $X=6950 $Y=1600 $D=3
D1 3 4 dn L=3.5e-07 W=1e-06 $X=6950 $Y=4850 $D=3
M0 1 2 vdd! pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
M1 1 2 gnd! nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=8100 $D=3
M2 1 3 vdd! pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M3 1 3 gnd! nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
M4 0 vdd! 1 nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=8100 $D=3
.ENDS
***************************************
