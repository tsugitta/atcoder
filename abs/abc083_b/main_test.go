package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		n        int
		a        int
		b        int
		expected int
	}{
		{n: 20, a: 2, b: 5, expected: 84},
		{n: 10, a: 1, b: 2, expected: 13},
		{n: 100, a: 4, b: 16, expected: 4554},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.n, test.a, test.b); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
