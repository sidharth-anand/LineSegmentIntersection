import re
import sys

def export_svg(filename, segments, intersections):
    scale = 256.0
    margin = 2.1
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
            '<rect x="%d" y="%d" width="%d" height="%d" fill="black"/>\n'
            % (
                -int(margin * scale),
                -int(margin * scale),
                int(margin * scale * 2),
                int(margin * scale * 2),
            )
        )

        if segments:
            fw('<g stroke="yellow" stroke-opacity="0.25" stroke-width="1">\n')
            for v0, v1 in segments:
                fw(
                    '<line x1="%.4f" y1="%.4f" x2="%.4f" y2="%.4f" />\n'
                    % (v0[0] * scale, -v0[1] * scale, v1[0] * scale, -v1[1] * scale)
                )
            fw("</g>\n")
        if intersections:
            fw(
                '<g fill="yellow" fill-opacity="0.25" stroke="white" stroke-opacity="0.5" stroke-width="1">\n'
            )
            for v0 in intersections:
                fw(
                    '<circle cx="%.4f" cy="%.4f" r="2"/>\n'
                    % (v0[0] * scale, -v0[1] * scale)
                )
            fw("</g>\n")

        fw("</svg>")


def read_segments(infile):
    f = open(infile, 'r')

    segments = []

    for segment in f.readlines():
        points = re.findall('(-?[0-9]*/[0-9]*)', segment)
        for i in range(len(points)):
            frac = points[i].split('/')
            points[i] = float(frac[0]) / float(frac[1])

        segments.append(((points[0], points[1]), (points[2], points[3])))

    return segments

def read_intersections(outfile):
    f = open(outfile, 'r')

    intersections = []

    for intersection in f.readlines():
        intersection = intersection.split(': ')[0]
        points = re.findall('(-?[0-9]*/[0-9]*)', intersection)
        for i in range(len(points)):
            frac = points[i].split('/')
            points[i] = float(frac[0]) / float(frac[1])

        intersections.append((points[0], points[1]))

    return intersections


def main():
    if len(sys.argv) != 3:
        print("Usage: visualize.py <input file> <output file>")
        exit(1)

    segments = read_segments(sys.argv[1])
    intersections = read_intersections(sys.argv[2])

    export_svg('intersections', segments, intersections)

if __name__ == '__main__':
    main()