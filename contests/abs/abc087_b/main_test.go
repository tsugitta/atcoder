package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		a        int
		b        int
		c        int
		x        int
		expected int
	}{
		{a: 2, b: 2, c: 2, x: 100, expected: 2},
		{a: 5, b: 1, c: 0, x: 150, expected: 0},
		{a: 30, b: 40, c: 50, x: 6000, expected: 213},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.a, test.b, test.c, test.x); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
