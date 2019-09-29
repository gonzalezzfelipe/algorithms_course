with open('kargerMinCutAsEdges.txt', 'w') as _write:
    with open('kargerMinCut.txt') as _file:
        for line in _file.readlines():
            ints = list(map(int, line.rstrip('\t\n').split('\t')))
            for _int in ints[1:]:
                _write.write(f'{ints[0]},{_int}\n')
