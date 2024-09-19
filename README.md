# Cellular-Automata-Research

![Cellular Automata Visualization](https://github.com/user-attachments/assets/9302271d-f1a2-40f6-b154-610cdc987623)

This repository focuses on the study and implementation of Cellular Automata (CA) with a particular emphasis on the (90-150)* rule vector. Cellular automata are mathematical models used to simulate complex systems through simple, local interactions.

## Overview

Cellular Automata (CAs) are discrete dynamical systems consisting of a grid of cells, each having a state from a finite set. The state of a cell at the next time step is determined by a local rule based on the current state of the cell and its neighbors.

## Research Abstract

In this work, we introduce a set of imperfect greedy algorithms designed to generate primitive polynomials of varying degrees over GF(2). Our methods specifically utilize the (90-150)* rule vectors. Building on the foundation of maximal length cellular automata (CAs), our algorithms aim to synthesize linear CAs that are highly likely to be of maximal length. Given that the characteristic polynomial of a maximal length CA is primitive, we propose that the characteristic polynomials derived from our synthesized CAs can be considered primitive.

### Definitions

- **Cellular Automata (CAs)**: Discrete dynamical systems consisting of a grid of cells, each having a state from a finite set. The state of a cell at the next time step is determined by a local rule based on the cell's current state and its neighbors.
- **Primitive Polynomials over GF(2)**: Irreducible polynomials that generate all non-zero elements of the field F<sub>2<sup>n</sup></sub>. A polynomial P(x) of degree n is primitive if the smallest positive integer m such that P(x) divides x<sup>m</sup> + 1 is m = 2<sup>n</sup> – 1.

## Algorithm Overview

We have implemented an algorithm for the (90-150)* rule vector to identify whether a CA is of maximal length. This algorithm confirms maximality without revisiting any p-configuration and generates all maximal CAs up to size 1000. The results are validated against existing computational tools.

### Key Findings

- **Efficiency**: Our algorithm provides improved computational efficiency (O(n) complexity) but may sacrifice some accuracy.
- **Limitations**: The current algorithm is imperfect and occasionally predicts maximal length sequences that are not maximal in practice. Squares of even grid size n predicted as maximal are often not maximal, highlighting the need for further refinement.

## Getting Started

To explore and run the CA simulations, clone this repository and follow the instructions provided in the documentation for setup and execution.

## Future Work

Future research will focus on:
- Enhancing the accuracy of the algorithms by incorporating additional patterns.
- Minimizing errors and improving the overall reliability of the algorithm.

## References

[Sumit Adak, Sukanta Das, (Imperfect) Strategies to Generate Primitive Polynomials over GF(2), Theoretical Computer Science, Volume 872, 2021, Pages 79–96](https://www.elsevier.com/locate/tcs)

