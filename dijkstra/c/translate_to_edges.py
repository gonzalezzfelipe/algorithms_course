with open('dijkstraDataEdges.txt', 'w') as _write:
    with open('dijkstraData.txt') as _file:
        for line in _file.readlines():
            components = line.rstrip('\t\n').split('\t')
            from_ = components[0]
            for outgoing in components[1:]:
                if components:
                    _write.write(f'{from_},{outgoing}\n')
