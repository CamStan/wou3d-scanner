// Z motor mount for 3D printer
// By Brayden Morse (age 12)

$fn=100;
rotate([90,0,0])
union()
{
difference()
{
translate([-4.5,0,0])
    cube([52,42,42+10.5]);
translate([0,-1,-5])
    cube([42,44,42+10.5]);

translate([21,21,36])
   cylinder(h=10+10.5,d=25); 

    translate([36.5,36.5,0])
        cylinder(h=50+10.5,d=3.3);

    translate([36.5,5.5,0])
        cylinder(h=50+10.5,d=3.3);
    
    translate([5.5,36.5,0])
        cylinder(h=50+10.5,d=3.3);
    
    translate([5.5,5.5,0])
        cylinder(h=50+10.5,d=3.3);

    //translate([1.995693,21,39])
    //#cylinder(h=20+10.5,d=8.005);
}
//rotate([90,0,0])
difference()
{
    translate([-14,0,0])
        cube([10,42,4]);
translate([-9,6,-1])
    cylinder(h=30,d=4);
translate([-9,33,0])
    cylinder(h=30,d=4);
}
// 19.004307mm for space motor and 8mm rod
// 57mm for wood block X
// 26mm for wood block Y
// 31mm for steper motor holes
//rotate([90,0,0])
difference()
{
translate([47,0,0])
    cube([10,42,4]);
translate([52,6,0])
    cylinder(h=30,d=4);
translate([52,33,0])
    cylinder(h=30,d=4);
}
//rotate([90,0,0])
//difference()
//{
//translate([1.995693,21,39])
//    cylinder(h=10,d=14);
//translate([1.995693,21,39])
//    cylinder(h=10,d=8.005);
//
//translate([1.995693,18,44])
//    rotate([90,0,0])
//        cylinder(h=5,d=2);
////translate([1.995693,18,44]) $fn=5;
//    rotate([90,0,0])
//        cylinder(h=2.3,d=5.3);
//}
}
