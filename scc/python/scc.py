import sys
from collections import deque

import numpy as np


sys.setrecursionlimit(15000)


class Edge:

    def __init__(self, from_, to):
        self.from_ = from_
        self.to = to


class Node:

    def __init__(self, id):
        self.id = id
        self.upstream = set()
        self.downstream = set()

        self.seen = False
        self._scc_label = None

    def __hash__(self):
        return id


class DAG:

    def __init__(self):
        self.edges = set()
        self.nodes = dict()

    @property
    def n(self):
        return len(self.nodes)

    @property
    def m(self):
        return len(self.edges)

    @classmethod
    def from_edges(cls, filename):
        """Read filename containing edges to init graph."""
        self = cls()
        with open(filename, 'r') as _file:
            for line in _file.readlines():
                nodes = [int(x) for x in line.rstrip('\n').rstrip(' ').split(' ')]
                self.edges.add(Edge(*nodes))
                for node in nodes:
                    if not node in self.nodes:
                        self.nodes[node] = Node(node)
                self.nodes[nodes[0]].downstream.add(nodes[1])
                self.nodes[nodes[1]].upstream.add(nodes[0])
        return self


    def clear_seen(self):
        for _, node in self.nodes.items():
            node.seen = False


def dfs(dag, start, backwards=False, leader=None, finish_time=None):
    dag.nodes[start].seen = True
    dag.nodes[start]._scc_label = leader

    up_or_down = 'upstream' if backwards else 'downstream'

    for node in getattr(dag.nodes[start], up_or_down):
        if not dag.nodes[node].seen:
            dfs(dag, node, backwards=backwards,
                leader=leader, finish_time=finish_time)
    if finish_time is not None:
        finish_time.append(start)


def label_scc(dag):
    finish_time = deque()

    # First backwards, dont care about leader
    for node in dag.nodes:
        if not dag.nodes[node].seen:
            dfs(dag, node, backwards=True, finish_time=finish_time)

    dag.clear_seen()
    # Then forwards, using leader
    for node in reversed(finish_time):
        if not dag.nodes[node].seen:
            leader = node
            dfs(dag, node, leader=leader)


if __name__ == '__main__':
    dag = DAG.from_edges('../c/SCC.txt')
    label_scc(dag)
    import pdb; pdb.set_trace()
