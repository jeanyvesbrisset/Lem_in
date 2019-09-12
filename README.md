# Lem_in
42 Project

A project that takes a ants colony and helps it navigate in a given maze using path-finding and max flow algorithms.
The ants can move at the same time (steps), the goal is to do it in less steps as possible, of course, there can't be two ants in the same room at the same time. (See example bellow)

Choosed algorithm: Edmund-Karps (includes BFS and DFS)

To compile, run 'make'. This will compile 'lem-in'. Execute with a map as a parameter in standard input.

> ./lem-in < map_example

Input format example:\

2 ---> number of ants\
##start --> defines the start room\
A 10 10\
B 10 10\
##end ---> defines the end room\
C 10 10\
A-B -----> defines a tube\
B-C\

Output format example:\

L1-A --> first ant goes in room B\
L1-C, L2-A ---> first ant goes in room C (end), second ant in room B\
L2-C --> second ant goes in room C\
