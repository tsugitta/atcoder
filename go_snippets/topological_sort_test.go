package go_snippets

import (
	"testing"
)

func TestTopologicalSort(t *testing.T) {
	assert := func(actual interface{}, expected interface{}) {
		if actual != expected {
			t.Fatalf("expected: %#v, actual: %#v", expected, actual)
		}
	}

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

	ts := TopologicalSort{}

	ts.init(5)
	ts.add(2, 1)
	ts.add(4, 0)
	ts.add(3, 2)
	ts.add(0, 3)

	res, _ := ts.sort()
	assert(equal(res, []int{4, 0, 3, 2, 1}), true)

	ts = TopologicalSort{}
	ts.init(3)
	ts.add(0, 1)
	ts.add(1, 2)
	ts.add(2, 0)

	_, loop := ts.sort()
	assert(loop, true)
}
