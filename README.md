# CS225 Final Project

## Objective

Dijkstra's Algorithm: Find the shortest path and distance from a source vertex to every other vertex in the graph. In the context of our dataset, this represents the shortest flight path from a starting airport to every other airport in the dataset

Betweenness Centrality: Uses the Floyd-Warshall algorithm to find the Vertex which is most commonly on the shortest path from all other Vertices to all other Vertices. In the context of our dataset (airports and routes), this can be inferred as the airport which is most likely to be part of the shortest route between 2 other airports. 

To run this (which may take a long time!), see the "Main" section below. 

## Dataset

Both the airports and routes information can be found in the `datasets` folder under the names `airports.txt` and `routes.txt`, respectively.
Source: [Openflights](https://openflights.org/data.html)

## Main

1. `make main` to compile and link
2. `./main` to run Dijkstra's algorithm and Betweenness Centrality. Dijkstra's algorithm will find the shortest path from a randomly selected Vertex (airport) to every other Vertex in the dataset, as well as specifically outputting the shortest distance and full path to other two other randomly selected vertices. Betweenness Centrality will find the most central Vertex (airport) in the dataset

## Tests

1. `make test` to compile and link
2. `./test` to run all tests
