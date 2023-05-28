import ezdxf
from ezdxf import colors

name_data = r'.\OutputData\pipeTrack2D.txt'

with open(name_data,'r') as f:
    lines = []
    dots = []
    n_lines,n_dots = map(int,f.readline().split())
    for _ in range (n_lines):
        lines.append(list(map(float, f.readline().split())))
    for _ in range (n_dots):
        dots.append(list(map(float, f.readline().split())))

def find_best_w (w):
    ws = list(ezdxf.lldxf.const.VALID_DXF_LINEWEIGHTS)
    for i in range (len(ws)-1):
        if ws[i] == w:
            return w
        if ws[i]< w <= ws[i+1] :
            return  ws[i+1]
    return ws[-1]
print(list(ezdxf.lldxf.const.VALID_DXF_LINEWEIGHTS))
in_name=r'.\InputData\stmConfig.dxf'
out_name=r'.\OutputData\stmConfig.dxf'
doc = ezdxf.readfile(in_name)
msp = doc.modelspace()
doc.header["$LWDISPLAY"] = 1

for line in lines:
    A = tuple(line[0:2])
    B = tuple(line[2:4])
    w = line[4]
    l = msp.add_line(A, B, dxfattribs={"color": colors.GREEN, 'lineweight': find_best_w (w)})
for dot in dots:
    center = tuple(dot[0:2])
    radius = dot[2]
    c = msp.add_circle(center, radius, dxfattribs={"color": colors.RED, })
doc.saveas(out_name)
