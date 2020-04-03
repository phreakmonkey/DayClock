module rtext(st) {
    width = 104;
    thickness = 4;
    len = width / 2;
    chars = len(st) + 1;
    degrees = 180;
    ang = degrees/chars;

    #rotate(degrees/2) {
        for (i = [1: chars]) {
            linear_extrude(thickness)
              translate([len*sin(i*ang), len*cos(i*ang), 0])
                rotate(-ang*i)
                  text(st[i-1],size=5);
        }
    }
}

module servo_mount() {
  difference() {
    cube([3,33,18]);
    translate([-.2,4.5,3]) cube([5,23,12]);
    translate([-.2,2.5,9]) rotate([0,90,0]) cylinder(r=.7,h=5,$fn=64);
    translate([-.2,29.5,9]) rotate([0,90,0]) cylinder(r=.7,h=5,$fn=64);
  }
}

// ARC:
difference() {
    union() {
        cylinder(r=60, h=3, $fn=180);
        for (i=[0: 25.7: 180]) {
            rotate([0,0,i]) translate([0, -.5, 0]) cube([60, 1, 4]);
        }
    }
    translate([0,0,-.1]) cylinder(r=50, h=5, $fn=180);
    translate([-61,-61,-.1]) cube([122, 61, 4]);
}

translate([11.25, 9,0]) rotate([0, -90, 90]) servo_mount();

translate([-60, -9, 0]) cube([40, 10, 3]);
translate([10, -9, 0]) cube([50, 10, 3]);

// TEXT:
rtext("SUN                               ");
rtext("    MON                      ");
rtext("          TUE                     ");
rtext("                    THU           ");
rtext("                           FRI      ");
rtext("                             SAT ");
#translate([-7,52,0])
  linear_extrude(4) text("WED", size=5);

