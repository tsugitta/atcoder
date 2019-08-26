package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSegmentTree(t *testing.T) {
	st := &SegmentTree{}

	vs := []int{1, 2, 3, 4, 5, -1}
	st.init(vs, int(1e18))

	assert.Equal(t, -1, st.query(0, len(vs)))
	assert.Equal(t, 1, st.query(0, 2))
	assert.Equal(t, 3, st.query(2, 4))
}
