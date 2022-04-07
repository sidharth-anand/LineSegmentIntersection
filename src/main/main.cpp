#include <iostream>
#include <fstream>
#include <vector>

#include <math/rational.h>

#include <geometry/point.h>
#include <geometry/linesegment.h>
#include <geometry/intersection.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <input-file> <output-file>\n";
        return 1;   
    }

    LineSegmentR line;
    std::ifstream infile(argv[1]);

    std::vector<LineSegmentR> lines;

    while (infile >> line)
        lines.push_back(line);

    auto events = bentleyOttmann(lines);
    std::ofstream outfile(argv[2]);

    for (const auto &event : events)
    {
        outfile << event.first << ": ";
        for (const auto &line : event.second)
            outfile << *line << ", ";

        outfile << "\n";
    }

    return 0;
}