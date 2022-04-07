import sys
import poly_point_isect  

def segments_rotate(s, angle):
    from math import sin, cos
    si = sin(angle)
    co = cos(angle)

    def point_rotate(x, y):
        return (x * co - y * si,
                x * si + y * co)

    s = [(point_rotate(*p0), point_rotate(*p1)) for (p0, p1) in s]

    return s

def isect_segments(s):
    ret = poly_point_isect.isect_segments(s)
    return tuple(sorted(set(ret)))


def isect_segments__naive(s):
    ret = poly_point_isect.isect_segments__naive(s)
    return tuple(sorted(set(ret)))

def isect_segments_compare(s):
    if 1:
        yield (s, isect_segments(s), isect_segments__naive(s), "")
    else:
        from math import radians
        angle_deg = 45.0
        angle_rad = radians(angle_deg)
        s_rotate = segments_rotate(s, angle_rad)
        yield (s_rotate, isect_segments(s_rotate), isect_segments__naive(s_rotate), "")

def export_svg(filename, segments, intersections):
    scale = 512.0
    margin = 1.1
    with open(filename + ".svg", "w", encoding="utf-8") as f:
        fw = f.write
        fw('<?xml version="1.0" encoding="UTF-8"?>\n')
        fw(
            '<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1 Tiny//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11-tiny.dtd">\n'
        )
        fw(
            '<svg version="1.1" '
            'width="%d" height="%d" '
            'viewBox="%d %d %d %d" '
            'xmlns="http://www.w3.org/2000/svg">\n'
            % (
                # width, height
                int(margin * scale * 2),
                int(margin * scale * 2),
                # viewBox
                -int(margin * scale),
                -int(margin * scale),
                int(margin * scale * 2),
                int(margin * scale * 2),
            )
        )

        fw(
            '<rect x="%d" y="%d" width="%d" height="%d" fill="white"/>\n'
            % (
                -int(margin * scale),
                -int(margin * scale),
                int(margin * scale * 2),
                int(margin * scale * 2),
            )
        )

        if segments:
            fw('<g stroke="black" stroke-opacity="0.25" stroke-width="1">\n')
            for v0, v1 in segments:
                fw(
                    '<line x1="%.4f" y1="%.4f" x2="%.4f" y2="%.4f" />\n'
                    % (v0[0] * scale, -v0[1] * scale, v1[0] * scale, -v1[1] * scale)
                )
            fw("</g>\n")
        if intersections:
            fw(
                '<g fill="red" fill-opacity="1.0" stroke="white" stroke-opacity="1.0" stroke-width="1">\n'
            )
            for v0 in intersections:
                fw(
                    '<circle cx="%.4f" cy="%.4f" r="2"/>\n'
                    % (v0[0] * scale, -v0[1] * scale)
                )
            fw("</g>\n")

        fw("</svg>")


def load_input_data(name):
    return __import__(name).data


# Path to input data (segments): First arg
# Path to output data (intersections): Second arg
input_segments = load_input_data(sys.argv[1])
for s_alt, ix_final, ix_naive, ix_id in isect_segments_compare(input_segments):
    export_svg("result" + ix_id, s_alt, ix_final)

