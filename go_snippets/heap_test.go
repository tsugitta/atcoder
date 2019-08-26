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
	assert.Equal(t, 1, pq[0])
	assert.Equal(t, 1, heap.Pop(&pq))
	assert.Equal(t, 3, pq[0])
	assert.Equal(t, 3, heap.Pop(&pq))
}
