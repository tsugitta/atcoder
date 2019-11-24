package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestBipartiteMatching(t *testing.T) {
	bm := BipartiteMatching{}

	bm.init(5)

	bm.add(0, 1)
	bm.add(0, 2)
	bm.add(1, 3)
	bm.add(4, 3)

	res := bm.exec()

	assert.Equal(t, 2, res)

	match := []int{2, 3, 0, 1, -1}
	assert.Equal(t, match, bm.match)
}
