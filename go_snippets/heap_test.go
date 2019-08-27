package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPQ(t *testing.T) {
	pq := NewPQ()

	pq.Push(3)
	pq.Push(1)
	assert.Equal(t, 1, pq.values[0])
	assert.Equal(t, 1, pq.Pop())
	assert.Equal(t, 3, pq.values[0])
	assert.Equal(t, 3, pq.Pop())
	assert.Equal(t, 0, pq.Len())
}
