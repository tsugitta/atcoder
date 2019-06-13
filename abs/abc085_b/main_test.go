package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		ds       []int
		expected int
	}{
		{ds: []int{10, 8, 8, 6}, expected: 3},
		{ds: []int{15, 15, 15}, expected: 1},
		{ds: []int{50, 30, 50, 100, 50, 80, 30}, expected: 4},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.ds); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
