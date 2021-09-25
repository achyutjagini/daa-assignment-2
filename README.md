# Dijkstra-in-C

<p align="center">
    <a href="https://github.com/thesuhas/Dijkstra-in-C/issues" alt="issues">
    <img alt="GitHub forks" src="https://img.shields.io/github/issues/thesuhas/Dijkstra-in-C"></a>
    <a href="https://github.com/thesuhas/Dijkstra-in-C/stargazers" alt="Stars">
    <img alt="GitHub stars" src="https://img.shields.io/github/stars/thesuhas/Dijkstra-in-C"></a>
    <img alt="Github license" src="https://img.shields.io/github/license/thesuhas/Dijkstra-in-C"></a>
    <a href="https://github.com/thesuhas/Dijkstra-in-C/contributors" alt="Contributors">
    <img src="https://img.shields.io/github/contributors/thesuhas/Dijkstra-in-C"/></a>

</p>
 
Dijkstra's Algorithm is used here to solve a **Single-Destination Shortest Path** problem to get the shortest path from all vertices in a graph to a given vertex.<br>
Done as part of the Design and Analysis of Algorithms Course (UE19CS251) at PES University, Bangalore.


## Input Format

The first line of the input file contains the number of vertices in the graph. <br>
The subsequent lines consist of: {Node} {vertex, weight of connection to vertex} where the pair of {vertex, weight} can be repeated for every other vertex in the graph. <br>
The last vertex (the highest numbered vertex) is taken as the Destination.<br>
[Sample Input File](adjacencylist.txt)


## Output Format

Each line of the output corresponds to: {Node} {Vertices in the path (including Node and Destination)} {Path Length} <br>
In case there is no path, "NO PATH" is printed

## How to Use

Clone this repository and run using the following command: `make -f makefile.mk`<br>
Input file can be changed in **line 57 in server.c** <br>

> fp = fopen("file_name.txt", "r");<br>

**Note 1:** To use the `make` command in windows, use Windows Subsystem for Linux<br>
**Note 2:** Uncomment the `display` function in `client.c` to see the graph that has been constructed.

