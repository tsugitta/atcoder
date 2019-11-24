package go_snippets

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestGetPatternIndices(t *testing.T) {
	for _, pair := range []struct {
		s        string
		p        string
		expected []int
	}{
		{s: "abcab", p: "ab", expected: []int{0, 3}},
		{s: "abcabcd", p: "xxx", expected: nil},
		{s: "abcde", p: "abcde", expected: []int{0}},
		{s: "aaaaa", p: "a", expected: []int{0, 1, 2, 3, 4}},
	} {
		res := getPatternIndices(pair.s, pair.p)
		assert.Equal(t, pair.expected, res)
	}
}
