hsep = 9.5;
hrad = 3.1/2;
mrad = 3.68/2;  // #6 wood screws

pwidth = 20;
plength = 20;
pthick = 6;

// very quick design for an endstop micro-switch mount
// section that screws to scanner
difference()
{
        $fn=100;
        cube([plength,plength,pthick]);
        for(y=[pwidth/2-hsep/2,pwidth/2+hsep/2])
        {
            hull()
            {
                translate([plength-1.5*hrad*2,y-1,0]) cylinder(h=pthick*2.5,r=mrad,center=true);
                translate([plength-1.5*hrad*2,y+1,0]) cylinder(h=pthick*2.5,r=mrad,center=true);
            }
        }
}
rotate([0,45,0]) translate([-20,0,0]) difference()
{
        $fn=100;
        cube([plength,pwidth,pthick]);
        for(y=[pwidth/2-hsep/2,pwidth/2+hsep/2])
        {
            #translate([1.5*hrad*2,y,0]) cylinder(h=pthick*2.5,r=hrad,center=true);
        }
}