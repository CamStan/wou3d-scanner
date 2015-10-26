// washer

// for scanner main rotating hoop
//rout = 15.0/2;
//rin = 10.5/2;
//height = 2.0;

// for power supply spacer washers
rout = 14.0/2;
rin = 5.0/2;
height = 0.34*25.4;


$fn=100;
difference()
{
	cylinder(h=height,r=rout);
	#translate([0,0,-height/2]) cylinder(h=2*height,r=rin);
}