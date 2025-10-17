* SPICE NETLIST
***************************************
.SUBCKT NAND x1 x2 vdd! gnd!
** N=4 EP=4 IP=32 FDC=8
M0 y x1 vdd! pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
M1 y x2 vdd! pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=8100 $D=3
M2 y x1 1 nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M3 1 x2 gnd! nmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
.ENDS
***************************************
