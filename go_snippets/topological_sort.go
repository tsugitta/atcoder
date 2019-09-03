package go_snippets

type TopologicalSort struct {
	edges  [][]int
	sorted []int
	length []int // 入次数 0 のノードからそのノードまでの長さ
}

func (t *TopologicalSort) init(n int) {
	t.edges = make([][]int, n)
	t.length = make([]int, n)
}

func (t *TopologicalSort) add(from, to int) {
	t.edges[from] = append(t.edges[from], to)
}

// O(V + E)
func (t *TopologicalSort) sort() (res []int, isLoop bool) {
	inCount := make([]int, len(t.edges))

	for _, edgesForNode := range t.edges {
		for _, to := range edgesForNode {
			inCount[to]++
		}
	}

	// inCount が 0 のものの集合
	s := []int{}

	for node, in := range inCount {
		if in == 0 {
			s = append(s, node)
		}
	}

	for i := range t.length {
		t.length[i] = 1
	}

	for len(s) > 0 {
		popped := s[0]
		res = append(res, popped)
		s = s[1:len(s)]

		for _, to := range t.edges[popped] {
			if t.length[popped]+1 > t.length[to] {
				t.length[to] = t.length[popped] + 1
			}

			inCount[to]--

			if inCount[to] == 0 {
				s = append(s, to)
			}
		}
	}

	if len(res) != len(t.edges) {
		isLoop = true
		return
	}

	t.sorted = res

	return
}
