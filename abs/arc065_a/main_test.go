package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	tests := []struct {
		S        string
		expected bool
	}{
		{S: "erasedream", expected: true},
		{S: "dreameraser", expected: true},
		{S: "dremaerer", expected: false},
		{S: "", expected: false},
		{S: "dreame", expected: false},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(test.S); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
