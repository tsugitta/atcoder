package go_snippets

type BipartiteMatching struct {
	edges [][]int
	match []int
	used  []bool
}

func (b *BipartiteMatching) init(n int) {
	b.edges = make([][]int, n)
	b.match = make([]int, n)

	for i := range b.match {
		b.match[i] = -1
	}
}

func (b *BipartiteMatching) add(from, to int) {
	b.edges[from] = append(b.edges[from], to)
	b.edges[to] = append(b.edges[to], from)
}

func (b *BipartiteMatching) dfs(v int) bool {
	b.used[v] = true

	for _, u := range b.edges[v] {
		w := b.match[u]
		if w == -1 || !b.used[w] && b.dfs(w) {
			b.match[u] = v
			b.match[v] = u
			return true
		}
	}

	return false
}

func (b *BipartiteMatching) exec() int {
	res := 0

	for v := 0; v < len(b.edges); v++ {
		if b.match[v] == -1 {
			b.used = make([]bool, len(b.edges))

			if b.dfs(v) {
				res++
			}
		}
	}

	return res
}