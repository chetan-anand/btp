User Instruction
--------------------------------------------------

(DAG Generator)
dag_gen.cpp
----------------------------------------------------
g++ dag_gen.cpp
./a.out > test.ip
Input:
Number of testcases:
Number of nodes:
Number of child:

Output files:
test.ip
graph1.gv (DOT file)

-----------------------------------------------------------------------------------

Configuration generator
--------------------------------------------------
g++ configuration_gen.cpp
./a.out > configuration.ip

Computing cost of node Generator
------------------------------------------------
g++ weight.cpp
./a.out > weight.ip


Now only we have to run heuristics code
------------------------------------------------
g++ HEFT.cpp
g++ CPOP.cpp
g++ CMB-CP-CVP.cpp
g++ CMB-CVP.cpp
g++ CM-CVP.cpp
g++ WaveFrontMethod.cpp
./a.out


In the out put 1st column will be number of nodes, scheduling length and scheduling cost.
--------------------------------------------------------------------------------------------------------------


DAG Visualisation
-----------------------------------------------------------------------------
The dag_gen.cpp also generate the dot file corressponding to the generated DAG.
So you can generate the png image of the graph by following command.

COMMAND: dot -Tpng graph1.gv -o test1.png
