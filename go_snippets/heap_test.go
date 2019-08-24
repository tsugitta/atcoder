package go_snippets

import (
	"container/heap"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPQ(t *testing.T) {
	pq := PQ{}
	heap.Init(&pq)

	heap.Push(&pq, 3)
	heap.Push(&pq, 1)
	assert.Equal(t, pq[0], 1)
	assert.Equal(t, heap.Pop(&pq), 1)
	assert.Equal(t, pq[0], 3)
	assert.Equal(t, heap.Pop(&pq), 3)
}
