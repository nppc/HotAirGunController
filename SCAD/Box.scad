$fn=50;

//Box();

/*
difference(){
    translate([0,10,-10.75])middlePlate();
    translate([8.3,-29.8,0]){
        cylinder(d=2,h=30,center=true);
        translate([0,0,-11.5])cylinder(d1=5,d2=2,h=2,center=true);
    }
    translate([-8.3,-29.8,0]){
        cylinder(d=2,h=30,center=true);
        translate([0,0,-11.5])cylinder(d1=5,d2=2,h=2,center=true);
    }
    translate([0,29,0])cylinder(d=2,h=11.8,center=true);
    translate([0.1,0,-0.3])Box();
    translate([-0.1,0,-0.3])Box();
    translate([0,-0.1,-0.3])Box();
    //translate([0,0.1,-0.3])Box();
}
*/
translate([0,10,-26])bottomPart();
//translate([-3.5,6,-25])color("GRAY")ACDC24V();

module Box(){
difference(){
    union(){
        difference(){
            union(){
                generalBox(21.5,64.5,21,4);
            }
            translate([0,0,-0.7])generalBox(19,62,20,2.6);

            // cutout for PowerJack
            translate([-17,-11,0.5])rotate([90,0,0])cylinder(d=11,h=30);

            // cutout for encoder pin
            translate([0.4,-23,9]){
                cylinder(d=7.2,h=20);
                translate([6,0,0])cube([2,4,3.5], center=true);
            }

            // Cutout for USB
            translate([0.5,-35,-4])cube([11.5,10,9], center=true);

        }
        // frame for OLED
        translate([0.4,-23+15+25/2+1,9.4])cube([10,27,1], center=true);
        
        // PCB holders
        translate([9,20,9.2-12]){
            rotate([90,0,0])cylinder(d=1.5,h=8,center=true);
            translate([0,-4,-0.75])cube([1,8,5]);
        }
        translate([-9,20,9.2-12]){
            rotate([90,0,0])cylinder(d=1.5,h=8,center=true);
            translate([-1,-4,-0.75])cube([1,8,5]);
        }
   }
    // cutout for OLED
    translate([0.4,-23+15+25/2+1,9]){
        
        cube([8,25,5], center=true);
        hull(){
            translate([0,0,3])cube([11,28,0.1], center=true);
            translate([0,0,2])cube([8,25,3], center=true);
        }
    }
    translate([0,10,-10.75])translate([-43/2,-8,0])DCDC_cover_part(43,50);

}
translate([8.3,-29.8,-5])case_mountinghole_corner();
translate([-8.3,-29.8,-5])rotate([0,0,-90])case_mountinghole_corner();
translate([0,29,0])rotate([0,0,180])case_mountinghole();

}



module generalBox(sx,sy,sz,diam){
    hull(){
        translate([(sx-diam)/2,(sy-diam)/2,0])generalBoxCylinder(sz,diam);
        translate([(-sx+diam)/2,(sy-diam)/2,0])generalBoxCylinder(sz,diam);
        translate([(sx-diam)/2,-(sy-diam)/2,0])generalBoxCylinder(sz,diam);
        translate([-(sx-diam)/2,-(sy-diam)/2,0])generalBoxCylinder(sz,diam);
    }
}

module generalBoxCylinder(hght,diam){
    cylinder(d=diam, h=hght-1,center=true);
    translate([0,0,(hght-1)/2])cylinder(d1=diam,d2=diam-1.2, h=1);
}

module case_mountinghole(){
    rotate([0,180,0])difference(){
        hull(){
            cylinder(d=4, h=10, center=true);
            translate([0,-2,0])cube([4,2,10], center=true);
        }
        translate([0,0,3])cylinder(d=1.8, h=9, center=true);
        translate([0,2,-8])rotate([45,0,0])cube([15,15,10], center=true);
    }
}

module case_mountinghole_corner(){
     rotate([0,180,0])difference(){
         hull(){
             cylinder(d=4, h=10, center=true);
             translate([0,-1,0])cube([4,2,10], center=true);
             translate([-1,0,0])cube([2,4,10], center=true);
         }
         translate([0,0,3])cylinder(d=1.8, h=8, center=true);
         translate([0,2,-8])rotate([45,0,-45])cube([15,15,10], center=true);
         // cut the corner
         translate([-2,-2,0])rotate([0,0,-45])cube([4,2,11], center=true);
     }
 }

module DCDC_cover_part(x,y){
    hull(){
        translate([0,0,-0.5])cube([x,y,0.5]);
        translate([3.5,4,4.75])cube([x-7,y-5,1]);
    }
}

module middlePlate(){
    difference(){
        union(){
            translate([0,0,-0.5])generalBox(36+7+2,87+2,1.5,3);
            translate([-43/2,-8,0])DCDC_cover_part(43,50);
            
        }
        translate([-43/2+1.5,-8+1.5,-1])DCDC_cover_part(40,46);
        translate([0,2,5.2+0.6])cube([17,30,2],center=true);

        translate([18,42,5.75])cylinder(d=4,h=10, center=true);
        translate([-18,42,5.75])cylinder(d=4,h=10, center=true);

        translate([18,42,0])cylinder(d=2,h=10, center=true);
        translate([-18,42,0])cylinder(d=2,h=10, center=true);
        translate([18,-42,0])cylinder(d=2,h=10, center=true);
    }
    //translate([-43/2,40,0])cube([3,3,3],center=true);
}

module bottomPart(){
    difference(){
        translate([0,0,0])generalBox(36+7+2+1.5,87+2+1.5,29,4);
        translate([0,0,1])generalBox(36+7,87,29,2);
        translate([0,0,14.8])generalBox(36+7+2+0.3,87+2+0.3,2,3);
        translate([-3.5,-50,1])cube([25,20,15],center=true);
        translate([16,50,0])rotate([90,0,0])cylinder(d=5.5,h=30);
    }
    translate([18,42,9.1])rotate([180,0,0])case_mountinghole();
    translate([-18,42,9.1])rotate([180,0,0])case_mountinghole();
    translate([18,-42,9.1])rotate([180,0,180])case_mountinghole();
}

module ACDC24V(){
    cube([36,77,27], center=true);
}