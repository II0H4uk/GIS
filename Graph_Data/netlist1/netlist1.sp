* SPICE NETLIST
***************************************

.SUBCKT pmos_h
** N=4 EP=0 IP=0 FDC=0
.ENDS
***************************************
.SUBCKT reduce8h s1 d1 g1 b1
** N=4 EP=4 IP=32 FDC=8
M0 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=6950 $Y=1600 $D=3
M1 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=6950 $Y=4850 $D=3
M2 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=6950 $Y=8100 $D=3
M3 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=6950 $Y=11350 $D=3
M4 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=1600 $D=3
M5 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=4850 $D=3
M6 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=8100 $D=3
M7 d1 g1 s1 b1 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
.ENDS
***************************************
