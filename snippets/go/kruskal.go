package go_snippets

// コストを考えない Kruskal
func GetMinEdgeList(edgeList [][]int) [][]int {
	uf := NewUnionFind(len(edgeList))

	minEdgeList := make([][]int, len(edgeList))
	for i := range minEdgeList {
		minEdgeList[i] = make([]int, 0)
	}

	for u, uTos := range edgeList {
		for _, v := range uTos {
			if u > v || uf.same(u, v) {
				continue
			}

			minEdgeList[u] = append(minEdgeList[u], v)
			minEdgeList[v] = append(minEdgeList[v], u)
			uf.merge(u, v)
		}
	}

	return minEdgeList
}
