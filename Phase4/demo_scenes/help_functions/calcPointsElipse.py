import math

def calc_ellipse_coords(a, b, alpha):
    x = a * math.cos(alpha)
    z = b * math.sin(alpha)
    return round(x, 3), round(z, 3)

a = 3.5  
b = 2  

alpha_values = [
    0, math.radians(18), math.radians(36), math.radians(54), math.radians(72),
    math.radians(90), math.radians(108), math.radians(126), math.radians(144), math.radians(162),
    math.radians(180), math.radians(198), math.radians(216), math.radians(234), math.radians(252),
    math.radians(270), math.radians(288), math.radians(306), math.radians(324), math.radians(342)
]

coords = [
    f'<point x="{calc_ellipse_coords(a, b, alpha)[0]}" y="0" z="{calc_ellipse_coords(a, b, alpha)[1]}" />'
    for alpha in alpha_values
]

for point in coords:
    print(point)