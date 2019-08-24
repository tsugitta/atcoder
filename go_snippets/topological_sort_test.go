package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestTopologicalSort(t *testing.T) {
	ts := TopologicalSort{}

	ts.init(5)
	ts.add(2, 1)
	ts.add(4, 0)
	ts.add(3, 2)
	ts.add(0, 3)

	res, _ := ts.sort()
	assert.Equal(t, res, []int{4, 0, 3, 2, 1})

	ts = TopologicalSort{}
	ts.init(3)
	ts.add(0, 1)
	ts.add(1, 2)
	ts.add(2, 0)

	_, loop := ts.sort()
	assert.Equal(t, loop, true)
}
