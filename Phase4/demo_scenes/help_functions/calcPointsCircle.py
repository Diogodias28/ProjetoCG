import math

# Função para calcular coordenadas x e z com base em r e alpha
def calc_coords(r, alpha):
    x = r * math.cos(alpha)
    z = r * math.sin(alpha)
    return round(x, 3), round(z, 3)


r = 2.193
alpha_values = [
    0, math.radians(18), math.radians(36), math.radians(54), math.radians(72),
    math.radians(90), math.radians(108), math.radians(126), math.radians(144), math.radians(162),
    math.radians(180), math.radians(198), math.radians(216), math.radians(234), math.radians(252),
    math.radians(270), math.radians(288), math.radians(306), math.radians(324), math.radians(342)
]

coords = [
    f'<point x="{calc_coords(r, alpha)[0]}" y="0" z="{calc_coords(r, alpha)[1]}" />'
    for alpha in alpha_values
]

for point in coords:
    print(point)
