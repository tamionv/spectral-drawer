# Spectral Graph Drawer

This program takes, as input, a graph, and outputs a drawing of that graph, drawn using the *spectral projection* technique. I read about this technique in the paper "Drawing graphs by eigenvectors: theory and practice", by Y. Koren, published in "Computers & Mathematics with Applications", Vol. 49, Issues 11-12, June 2005. 

## Basic theory

These ideas are taken from the previously mentioned paper. In essence, given a graph G = (V, E), where V = {1, ..., n}, what we want is to find coordinates (x_1, y_1), ..., (x_n, y_n) such that:

1. The vectors (x_1, ..., x_n) and (y_1, ..., y_n) are perpendicular.
2. These two vectors have 0 mean.
3. The sum of the squares of the lengths of the graph edges, when the vertices are put at these coordinates, is minimised.

It turns out that it is optimal to select the two vectors to be the eigenvectors of the Laplacian matrix that correspond to the smallest two eigenvalues that differ from 0. This is computed using an iterative method, described in the paper.

## Building and running

To build the project, run the `make` command. The executable produced is called `main.exe` -- this is the graph drawing executable.

## Input format

The input is as follows:

```
n m
a1 b1
...
am bm
```

This input represents a graph with V = {1, ..., n}, with edges E = { {a1, b1}, ..., {am, bm}}.

For the code to work, the graph *must be connected*.

## Output format

The output is a 512x512 pgm image.

## Examples

The folder `graphs` contains some example graphs. To make all the examples, use the `make examples` command. This will create all the examples, putting the results in the `img` folder. To make a particular example, such as, for instance, `img/platonic1.pgm`, just use `make img/platonic1.pgm`.

## Author and maintainer

This code is written and maintained by <tamionv@gmail.com>.
