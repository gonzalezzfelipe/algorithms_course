import random


class Counter(dict):

    def add(self, key, value=1):
        if key in self:
            self[key] += value
        else:
            self[key] = value

    def remove(self, key):
        return self.pop(key)

    def merge(self, other):
        for key, value in other.items():
            if key in self:
                self[key] += value
            else:
                self.add(key)
                self[key] += value - 1


def readfile(filename):
    graph = {}
    with open(filename, 'r') as _file:
        for line in _file:
            nodes = line.rstrip('\n').rstrip('\t').split('\t')
            actual_node = int(nodes[0])
            counter = Counter()
            for adjacent_node in nodes[1:]:
                counter.add(int(adjacent_node))
            graph[actual_node] = counter
    return graph


min_cut = 1000000000
for run in range(40000):
    graph = readfile('kargerMinCut.txt')
    while len(graph) > 2:
        node = random.choice(tuple(graph))
        other = random.choice(tuple(graph[node]))
        # Merge nodes "node" and "other":
        for adjacent_node in graph[other]:
            value = graph[adjacent_node].remove(other)
            graph[adjacent_node].add(node, value=value)
        graph[node].merge(graph[other])
        graph[node].remove(node)
        graph.pop(other)
    key, value = graph.keys()
    min_cut = min(min_cut, graph[key][value])

print(min_cut)
