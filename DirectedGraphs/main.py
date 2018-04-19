import argparse
import pyglet
from pyglet import gl
from graph import Graph
from glGraph import glGraph

#creates window
width, height = 600, 400
window = pyglet.window.Window(width, height, caption='Primms Algorithm', resizable=True)
gl.glClearColor(1.0, 1.0, 1.0, 1.0)

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
G = glGraph(graph)
# G.CreateGraph(graph)
# tree, costs = G.SolvePrimm(initial_node=graph[0][0])
# print(tree, costs)

#get nodes
nodes = G.GetNodes()
print(nodes)

# label = pyglet.text.Label('A',font_name='Times New Roman',font_size=100,x=200, y=200, color=(0,0,0,255))
@window.event
def on_draw():
    gl.glPushMatrix()
    gl.glViewport(0, 0, window.width, window.height)
    gl.glMatrixMode(gl.GL_PROJECTION)
    gl.glLoadIdentity()
    gl.glOrtho(0, width, 0, height, -1, 1)
    gl.glMatrixMode(gl.GL_MODELVIEW)
    #
    window.clear()
    G.ShowNodes()
    #
    gl.glPopMatrix()

pyglet.app.run()