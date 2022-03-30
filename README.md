# Line Segment Intersection via Bentley-Ottmann Algorithm

**Course:** CS F364 - Design and Analysis of Algorithm

## Group Members

 - Sidharth Anand (2019A7PS1203H)
 - Yashaswi Yenugu (2019A71210H)
 - Akhil Macherla (2019A71211H)
 - Aryan Arora (2019A7PS1204H)

## Implementation of Algorithm

Details regarding the nuances of the algorithm, functions utilized and general workflow can be viewed via Doxygen documentation.

## Building and Running

Working and running of the project can be performed by CMake.

Following are the commands and their respective functionalities:-

Build the project with
```
cmake -P build.cmake -DCMAKE_BUILD_TYPE=Release
```

Use `-DCMAKE_BUILD_UNIT_TESTS` and `-DCMAKE_BUILD_DOCUMENTATION` to turn building building unit tests and documentation on/off

The built doxygen documentation can be found in the docs directory and is also hosted [here](https://sidharth-anand.github.io/LineSegmentIntersection/).

## Testing

Shown below are some of the test cases our algorithm was run against, with varying number and types of line segments - each returning unique set of intersections. Attached below are some of the results:-

- Grid 1
- Grid 2
- Ampersand Sign
- Scribble Plot
- Spiral Plot
- Monkey Face Plot

### Grid 1

![Test A](/img/test_isect_crosshatch_01.svg)

### Grid 2

![Test B](/img/test_isect_crosshatch_03.svg)

### Ampersand Sign

![Test C](/img/test_isect_scatter_01.svg)

### Scribble Plot

![Test D](/img/test_isect_scribble_01.svg)

### Spiral Plot

![Test E](/img/test_isect_spiro_01.svg)

### Monkey Face Plot

![Test F](/img/test_isect_suzzane.svg)

## Performance Analysis

To verify how effective our algorithm is computationally, we compare the performance of our algorithm with the brute force approach. We also compare the graph with (n+k)logn plot, to show the similarity of both.

![plot]()

### Results

We observe that our algorithm severely overperforms the brute force, and is similar to the (n+k)logn plot. Thus, emperically establishing the complexity of our algorithm:

        T(n, k) ε O((k+n)logn)
