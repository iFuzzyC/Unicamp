
class Node():


    def __init__(self, name):
        """Class for a node in a Directed Graph."""
        self.name = name
        self.connections = []
        self.costs = []
        self.count = 0


    def AddConnection(self, node, cost):
        """Adds a connection to the node."""
        self.connections.append(node)
        self.costs.append(int(cost))

    def SetDistance(self, dist):
        """Set the distance for a node."""
        self.distance = dist

    def SetPred(self, pred):
        """Set predecessor for a node."""
        self.pred = pred

    def AddCount(self):
        """Adds one to variable count."""
        self.count += 1

    def SetLabel(self, label):
        """Sets the label of the node."""
        self.label = label

class DirectGraph():
    def __init__(self, graph):
        """Class for a Directed Graph."""
        self.graph = graph
        self._CreateArcs()

    def PrintsGraph(self):
        """Prints nodes, arcs and costs."""
        for no in self._NodeGenerator():
            print('Name {}, Connected to {} with costs {}'.format(no.name, no.connections, no.costs))

    def PrintShortPath(self):
        """Prints the shortest path found with FIFO or Dijkstra."""
        for key in self.nodes:
            print('Node {} has predecessor {}'.format(key, self.nodes[key].pred))

    def Dijkstra(self, initial_node='A'):
        """Performs Dijkstra algorithm."""
        #initiating the variables
        S = []
        for node in self._NodeGenerator():
            node.SetDistance(100000000)    
        self.nodes[initial_node].SetDistance(0)
        self.nodes[initial_node].SetPred(0)
        while len(S) < len(self.nodes):
            #create complementary to S node set
            S_line = self._DefineS_line(S)
            #chooses node with least distance
            node_i = self._LeastDistanceNode(S_line)
            #updates the distance from adjacent nodes
            self._UpdateAdjacentNodes(node_i)
            #adds node to list
            S.append(node_i)

    def FIFO(self, initial_node='A'):
        """Performs the FIFO algorithm"""
        for key in self.nodes:
            self.nodes[key].SetDistance(100000000)    
        self.nodes[initial_node].SetDistance(0)
        self.nodes[initial_node].SetPred(0)
        S = [initial_node]
        while len(S) > 0:
            node_i = S[0]
            L = self._UpdateAdjacentNodes(node_i, FIFO=True)
            for node in L:  
                if node not in S:   
                    S.append(node)
            #update the counts
            self._UpdateCounts(S)
            #checks for negative cycle
            if self._NegativeCycle(len(self.nodes)):
                raise ValueError('Algorithm terminated! Negative Cycle detected!')
            S.remove(node_i)

    def Floyd(self):
        """Performs Floyd All-Pairs algorithm"""
        self._SetNodesLabels()
        disMatrix, predMatrix = self._FloydMatrices()
        C = self._FindUpperBound()
        print(C)
        n = len(disMatrix)
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if disMatrix[i][j] > disMatrix[i][k] + disMatrix[k][j] and disMatrix[i][k] < n*C:
                        disMatrix[i][j] = disMatrix[i][k] + disMatrix[k][j]
                        predMatrix[i][j] = predMatrix[k][j]
                #detects negative cycle        
                if disMatrix[i][i] < 0:
                    raise ValueError('Algorithm terminated! Negative Cycle detected!')
            #detects negative cycle
            if disMatrix.min() < -n*C:
                raise ValueError('Algorithm terminated! Negative Cycle detected!')
        print('---Distance Matrix---')
        print(disMatrix)
        print('---Predecessors Matrix---')
        print(predMatrix)

    def _CreateArcs(self):
        """Creates the arcs of the graph"""
        self.nodes = {}
        for arc in self.graph:
            if arc[0] not in self.nodes:
                self.nodes[arc[0]] = Node(arc[0])
            if arc[1] not in self.nodes:
                self.nodes[arc[1]] = Node(arc[1])
            self.nodes[arc[0]].AddConnection(self.nodes[arc[1]].name, cost=arc[2])

    def _NodeGenerator(self):
        """Generator that returns the node classes"""
        for key in self.nodes:
            yield self.nodes[key]

    def _DefineS_line(self, S):
        """given a set of nodes S defines the complementary"""
        S_line = []
        for node_name in self.nodes:
            if node_name not in S:
                S_line.append(node_name)
        return S_line

    def _LeastDistanceNode(self, S):
        """given a set S of nodes return the node with the least distance"""
        least_node = 0
        if len(S) > 0:
            least_node = S[0]
            for node_name in S:
                if self.nodes[node_name].distance < self.nodes[least_node].distance:
                    least_node = node_name
        return least_node

    def _UpdateAdjacentNodes(self, current_node, FIFO=False):
        """Updates adjacent nodes for the Dijkstra or FIFO algorithm"""
        FIFO_list = []
        node_c = self.nodes[current_node]
        for i in range(len(node_c.connections)):
            node_i = node_c.connections[i]
            if self.nodes[node_i].distance > node_c.distance + node_c.costs[i]:
                self.nodes[node_i].SetDistance(node_c.distance + node_c.costs[i])
                self.nodes[node_i].SetPred(current_node)
                if FIFO:
                    FIFO_list.append(node_i)
        if FIFO:
            return FIFO_list

    def _UpdateCounts(self, S):
        """Update the counts for every node, used in FIFO"""
        for node in S:
            self.nodes[node].AddCount()

    def _NegativeCycle(self, n):
        """Checks if the count surpass maximum value n. used in FIFO"""
        for node in self._NodeGenerator():
            if node.count > n:
                return True
        return False

    def _SetNodesLabels(self):
        """Set labels for every node, used in Floyd"""
        i = 0
        for node in self._NodeGenerator():
            node.SetLabel(i)
            i += 1

    def _FloydMatrices(self):
        """Creates the initial matrices for Floyd"""
        import numpy as np
        dim = len(self.nodes)
        D = np.inf*np.ones((dim, dim))
        P = np.chararray((dim, dim))
        P[:] = '-'
        #set 0 on the diagonal
        for i in range(dim):
            D[i][i] = 0
        #seting the arcs that already exists
        for node in self._NodeGenerator():
            for i in range(len(node.connections)):
                D[node.label][self.nodes[node.connections[i]].label] = node.costs[i]
                P[node.label][self.nodes[node.connections[i]].label] = node.name
        return D, P

    def _FindUpperBound(self):
        """Given a network find the upper bound for the costs, used in Floyd"""
        C = -10000
        for node in self._NodeGenerator():
            if len(node.costs) > 0:
                if C < max(node.costs):
                    C = max(node.costs)
        return C + 10
