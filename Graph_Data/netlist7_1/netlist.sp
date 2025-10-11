* SPICE NETLIST
***************************************
.SUBCKT circuit vdd gnd Adr<0> wl Data<0>
** N=4 EP=4 IP=32 FDC=8
M0 0 Adr<0> gnd pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M1 2 wl 1 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M2 4 wl 3 pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M3 1 0 Data<0> pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
M4 3 Adr<0> Data<0> pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
R5 0 vdd 100 L=3.5e-07 W=1e-06 $[rnpoly] $X=11200 $Y=11350 $D=3
C6 2 gnd pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
C7 4 gnd pmos_h L=3.5e-07 W=1e-06 $X=11200 $Y=11350 $D=3
.ENDS
***************************************