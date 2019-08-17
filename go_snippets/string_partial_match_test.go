package go_snippets

import (
	"testing"
)

func TestGetPatternIndices(t *testing.T) {
	for _, pair := range []struct {
		s        string
		p        string
		expected []int
	}{
		{s: "abcab", p: "ab", expected: []int{0, 3}},
		{s: "abcabcd", p: "xxx", expected: []int{}},
		{s: "abcde", p: "abcde", expected: []int{0}},
		{s: "aaaaa", p: "a", expected: []int{0, 1, 2, 3, 4}},
	} {
		res := getPatternIndices(pair.s, pair.p)

		equal := func(a, b []int) bool {
			if len(a) != len(b) {
				return false
			}
			for i, v := range a {
				if v != b[i] {
					return false
				}
			}
			return true
		}

		if !equal(res, pair.expected) {
			t.Errorf("in: %s, expected: %v, actual: %v", pair.s, pair.expected, res)
		}
	}
}
