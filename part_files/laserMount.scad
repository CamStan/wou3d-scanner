use <fillet.scad>

/* Adapter to attach the Coherent laser mounting block onto the 
    main scanner hoop. 
    
    Stingray laser mount (p/n 1222896): https://www.coherent.com/drawings/Coherent%20StingRay%20Mount%20Drawings.PDF
*/

hoopTubeRadius = 25.4/2 + 0.3;  // radius of steel tube
hoopRadius = 18.75*25.4;        // radius of the whole hoop

holesRadius = 3.6/2 + 0.3;      // bolt holes

// model of the main hoop -- a torus
module scannerHoop()
{
    // torus
    rotate_extrude(convexity = 10, $fn = 100) 
        translate([hoopRadius, 0, 0])
            circle(r = hoopTubeRadius, $fn = 100);
}

// helper module to make a cube that is rounded in the corners on the X-Y plane
module roundedRectCube(width,length,thickness,cornerRadius)
{
    translate([0,0,thickness/2])
    hull()
    {
        locW = width/2-cornerRadius;
        locL = length/2-cornerRadius;
        for(x = [-locW,locW])
        {
            for(y = [-locL,locL])
            {
                $fn=50;
                translate([x,y,0]) cylinder(h=thickness,r=cornerRadius,center=true);
            }
        }
    }
}

// A model of the base of the Coherent mount part, which is a machined aluminum part
// This gives us either the bolt hole locations or a way to make a recess in the 
// 3D printed part
module coherentLaserMount(clearanceLength)
{
    baseWidth  = 31.4 + 0.3;
    baseLength = 50.8 + 0.3;
    baseThickness = 4.3;
    holesWidth = 25.4;
    holesLength = 43.2;
    //holesRadius = 3.6/2 + 0.3;
    cornerRadius = 0.167*25.4;
    
    //translate([0,0,baseThickness/2]) 
    union()
    {
        roundedRectCube(baseWidth,baseLength,baseThickness,cornerRadius);
        
        for(x = [-holesWidth/2,holesWidth/2])
        {
            for(y = [-holesLength/2,holesLength/2])
            {
                $fn=50;
                translate([x,y,0]) cylinder(h=clearanceLength,r=holesRadius,center=true);
            }
        }
    }
}

// Main part parameters
// flat top portion, with recessed tray
pWidth = 40.0;
pLength = 65.0 + 25;
pThickness = 9.0;
pCornerRadius = 6.0;
pRecess = 4.29;

// block portion that clamps onto the hoop
blockLength = 37.0;
blockThickness = 35.0;
gapWidth = 2.0;
boltPartWidth = 11;
boltPartThickness = 8;
boltHeadExtra = 1.9;

translate([0,0,pWidth/2])       // turn it on edge for printing
rotate([0,90,0])
difference()
{
    union()
    {
        difference()
        {
            // main tray
            translate([0,15,0]) roundedRectCube(pWidth,pLength,pThickness,pCornerRadius);
            // with recess for aluminum part
            translate([0,0,pThickness-pRecess]) coherentLaserMount(15);
        }
        fillet(r=3,steps=4)
        {
            // block to mount on hoop, offset to clear bolt holes and provide for optional offset of laser from focal point of camera
            translate([0,pLength/2,-blockThickness+pThickness]) roundedRectCube(pWidth,blockLength,blockThickness,pCornerRadius);
            // clamping screw part
    translate([0,pLength/2,pThickness-blockThickness-boltPartThickness/2]) cube([pWidth,boltPartWidth,boltPartThickness],center=true);
        }
    }
    // take out hoop
    #translate([0,-hoopRadius+pLength/2,-hoopTubeRadius+pThickness-pRecess]) scannerHoop();
    // and a little slice to give room for clamping
    translate([0,pLength/2,-blockThickness/2]) 
        cube([2*pWidth,gapWidth,blockThickness],center=true);
    // and some clamping bolt holes
    translate([pWidth/4,pLength/2,pThickness-blockThickness-boltPartThickness/2]) 
        rotate([90,0,0])
            cylinder(r=holesRadius,h=boltPartThickness*2,center=true,$fn=50);
    // bolt head
    translate([pWidth/4,pLength/2-boltPartWidth/2,pThickness-blockThickness-boltPartThickness/2]) 
        rotate([90,0,0])
            cylinder(r=holesRadius+boltHeadExtra,h=5,center=false,$fn=50);
    // nut
    translate([pWidth/4,pLength/2+boltPartWidth/2,pThickness-blockThickness-boltPartThickness/2])
        rotate([-90,0,0]) 
            cylinder(r=holesRadius+boltHeadExtra,h=5,center=false,$fn=50);
    // bolt
    translate([-pWidth/4,pLength/2,pThickness-blockThickness-boltPartThickness/2])
        rotate([90,0,0])
            cylinder(r=holesRadius,h=boltPartThickness*2,center=true,$fn=50);
    // bolt head
    translate([-pWidth/4,pLength/2-boltPartWidth/2,pThickness-blockThickness-boltPartThickness/2]) 
        rotate([90,0,0])
            cylinder(r=holesRadius+boltHeadExtra,h=5,center=false,$fn=50);
    // nut
    translate([-pWidth/4,pLength/2+boltPartWidth/2,pThickness-blockThickness-boltPartThickness/2])
        rotate([-90,0,0]) 
            cylinder(r=holesRadius+boltHeadExtra,h=5,center=false,$fn=50);
}


