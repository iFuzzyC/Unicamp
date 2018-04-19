import argparse

from graph import DirectGraph

#receiving the file with the archs
parser = argparse.ArgumentParser()
parser.add_argument('-file', help='File containing the archs and costs')
name_file = parser.parse_args().file
assert name_file is not None, 'Please pass a proper file'

def remove_vals(lista, val):
    for i in range(len(lista)):
        while val in lista[i]: lista[i].remove(val)
    return lista
def find_negatives(lista):
    for arc in lista:
        if len(arc) > 3:
            if '-' in arc:
                arc.remove('-')
                arc[2] = -int(arc[2])
            else:
                arc[2] = "".join(arc[2:])
                arc.pop(3)
    return lista
#reading from the file
file = open(name_file, 'r')
graph = []
for line in file:
    graph.append(list(line))
graph = remove_vals(graph, '\n')
graph = find_negatives(graph)
print(graph)

dg = DirectGraph(graph)
dg.PrintsGraph()
# dg.Dijkstra()
# print('---Dijkstra---')
# dg.PrintShortPath()
# dg.FIFO()
# print('---FIFO---')
# dg.PrintShortPath()
dg.Floyd()