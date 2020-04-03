difference() {
    union() {
        cylinder(r=6.75/2, h=3, $fn=120);
        translate([-6, -1.25, 0]) cube([52,2.5,3]);
        hull() {
            translate([45, -2.5, 0]) cube([.5, 5, 3]);
            translate([52, 0, 0]) cylinder(r=.2, h=3, $fn=120);
        }
    }
    translate([0,0,1.1]) cylinder(r=4.85/2, h=2, $fn=12);
    translate([0,0,-.1]) cylinder(r=.75, h=4, $fn=120);
}
