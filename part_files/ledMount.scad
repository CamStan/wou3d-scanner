use <fillet.scad>

/* Adapter to attach a camera to the hoop.  Attachment is via the normal
    1/4" - 20 screw as on normal tripods.  
    
    Copied over the laserMount code and modifying from there (yes, would have
    been better to put common code in a separate module :-)
*/

hoopTubeRadius = 25.4/2 - 0.02;  // radius of steel tube
hoopRadius = 18.75*25.4;        // radius of the whole hoop

holesRadius = 3.6/2 + 0.3;      // bolt holes

// model of the main hoop -- a torus
module scannerHoop()
{
    // torus
    rotate_extrude(convexity = 10, $fn = 200) 
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

// Main part parameters
// flat top portion, with recessed tray
pWidth = 70.0;
pLength = 50.0 + 37.0/2 + 17.0 - 27;
pThickness = 9.0;
pCornerRadius = 6.0;
pRecess = 6;

// block portion that clamps onto the hoop
blockLength = 37.0;
blockThickness = 35.0;
gapWidth = 2.0;
boltPartWidth = 11;
boltPartThickness = 8;
boltHeadExtra = 1.9;

//translate([0,0,pWidth/2])       // turn it on edge for printing
//rotate([0,90,0])
difference()
{
    union()
    {
        // main tray
        translate([0,-(pLength/2-blockLength/2),0]) roundedRectCube(pWidth,pLength,pThickness,pCornerRadius);
        fillet(r=3,steps=4)
        {
            // block to mount on hoop, offset to clear bolt holes and provide for optional offset of laser from focal point of camera
            translate([0,0,-blockThickness+pThickness]) roundedRectCube(pWidth,blockLength,blockThickness,pCornerRadius);
            // clamping screw part
    translate([0,0,pThickness-blockThickness-boltPartThickness/2]) cube([pWidth,boltPartWidth,boltPartThickness],center=true);
        }
    }
    // take out hoop
    #translate([0,0,-hoopRadius-hoopTubeRadius+pThickness-pRecess]) rotate([90,0,0]) scannerHoop();
    // make clamp over hoop corrugated (it won't curve with the torus though)
    // to try to increase clamping strength
    translate([0,0,-1.0-hoopTubeRadius+pThickness-pRecess])
        for( i = [0:18:360] )
        {
            rotate([i,0,0]) translate([0,hoopTubeRadius,0]) cube([pWidth*1.1,2.1,1.5],center=true);
        }
    // and a little slice to give room for clamping
    translate([0,0,-blockThickness/2]) 
        cube([2*pWidth,gapWidth,blockThickness],center=true);
        
        
    // and some clamping bolt holes
    for( j = [-1.5,-0.5,0.5,1.5] )
    {
        xpos = j*pWidth/4;
        // bolt
        translate([xpos,0,pThickness-blockThickness-boltPartThickness/2]) 
            rotate([90,0,0])
                cylinder(r=holesRadius,h=boltPartThickness*2,center=true,$fn=50);
        // bolt head
        translate([xpos,0-boltPartWidth/2,pThickness-blockThickness-boltPartThickness/2]) 
            rotate([90,0,0])
                cylinder(r=holesRadius+boltHeadExtra,h=5,center=false,$fn=50);
        // nut
        translate([xpos,0+boltPartWidth/2,pThickness-blockThickness-boltPartThickness/2])
            rotate([-90,0,0]) 
                cylinder(r=holesRadius+boltHeadExtra,h=5,center=false,$fn=50);
    }
    
    // holes for 1/4"-20 bolt to secure led mounting plate
    translate([-20.5,-30,-pThickness/2]) cylinder(r=0.25*25.4/2+0.3,h=pThickness*2,$fn=50);
    translate([20.5,-30,-pThickness/2]) cylinder(r=0.25*25.4/2+0.3,h=pThickness*2,$fn=50);
}


