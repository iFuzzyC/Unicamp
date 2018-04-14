
class Graph():
    def __init__(self):
        self.graph = dict()

    #adds connection to the graph
    def CreateGraph(self, graph):
        for i in range(len(graph)):
            self.AddConection(graph[i][0], graph[i][1], graph[i][2])

    def AddConection(self, nodeA, nodeB, cost):
        self.graph.setdefault(nodeA, []).append([nodeB, cost])
        self.graph.setdefault(nodeB, []).append([nodeA, cost])

    #given the set of nodes S, returns the archs and the costs of the possible archs
    #the possible archs are the ones that conect nodes in S to nodes not in S
    def FindArchs(self, S):
        archs, costs = [], []
        for node in S:
            info = self.graph[node]
            for i in range(len(info)):
                if info[i][0] not in S:
                    archs.append([node, info[i][0]])
                    costs.append(info[i][1])
        return archs, costs

    #find the arch with lowest cost in the given set
    def FindLowestArch(self, Archs, Costs):
        index = Costs.index(min(Costs))
        return Archs[index], Costs[index]

    #gives the minimum spanning tree using primms algorithm
    def SolvePrimm(self, initial_node):
        #declare tree, costs and S
        tree = []
        costs = []
        S = [initial_node]
        #check stop condition
        while len(S) != len(self.graph):
            #find possible archs and their costs
            Archs, Costs = self.FindArchs(S)
            #select the arch with lowest cost
            LowestArch, LowestCost = self.FindLowestArch(Archs, Costs)
            #append the arch to tree and saves the cost
            tree.append(LowestArch)
            costs.append(LowestCost)
            #update the set of nodes S
            S.append(LowestArch[1])
        return tree, costs