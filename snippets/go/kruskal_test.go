package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestKruskal(t *testing.T) {
	N := 10

	edges := make([][]int, N)
	for i := range edges {
		edges[i] = make([]int, 0, N-1)

		for j := 0; j < N; j++ {
			if j == i {
				continue
			}

			edges[i] = append(edges[i], j)
		}
	}

	minEdges := GetMinEdgeList(edges)
	edgesCt := 0

	for _, iEdges := range minEdges {
		for range iEdges {
			edgesCt++
		}
	}

	assert.Equal(t, N-1, edgesCt/2)
}
