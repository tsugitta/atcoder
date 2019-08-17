package go_snippets

type TopologicalSort struct {
	edges   [][]int
	inCount []int
}

func (t *TopologicalSort) init(n int) {
	t.edges = make([][]int, n)
	t.inCount = make([]int, n)
}

func (t *TopologicalSort) add(from, to int) {
	t.edges[from] = append(t.edges[from], to)
}

func (t *TopologicalSort) sort() (res []int, isLoop bool) {
	// 全ての nodes の入次数をカウント O(E)
	for _, edgesForNode := range t.edges {
		for _, to := range edgesForNode {
			t.inCount[to]++
		}
	}

	// inCount が 0 のものの集合
	s := []int{}

	for node, in := range t.inCount {
		if in == 0 {
			s = append(s, node)
		}
	}

	for len(s) > 0 {
		popped := s[0]
		res = append(res, popped)
		s = s[1:len(s)]

		for _, to := range t.edges[popped] {
			t.inCount[to]--

			if t.inCount[to] == 0 {
				s = append(s, to)
			}
		}
	}

	if len(res) != len(t.edges) {
		isLoop = true
		return
	}

	return
}
