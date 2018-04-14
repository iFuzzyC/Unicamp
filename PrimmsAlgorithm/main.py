import argparse
from graph import Graph

#receiving the file with the archs
parser = argparse.ArgumentParser()
parser.add_argument('-file', help='File containing the archs and costs')
name_file = parser.parse_args().file
assert name_file is not None, 'Please pass a proper file'

def remove_vals(lista, val):
    for i in range(len(lista)):
        while val in lista[i]: lista[i].remove(val)
    return lista

#reading from the file
file = open(name_file, 'r')
graph = []
for line in file:
    graph.append(list(line))
graph = remove_vals(graph, ' ')
graph = remove_vals(graph, '\n')

#creating the graph
G = Graph()
G.CreateGraph(graph)
tree, costs = G.SolvePrimm(initial_node=graph[0][0])
print(tree, costs)