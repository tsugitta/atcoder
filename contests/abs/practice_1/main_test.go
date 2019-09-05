package main

import (
	"fmt"
	"testing"
)

func TestGenerateOutput(t *testing.T) {
	tests := []struct {
		a        int
		b        int
		c        int
		s        string
		expected string
	}{
		{a: 1, b: 2, c: 3, s: "foo", expected: "6 foo\n"},
		{a: -1, b: 0, c: 1, s: "", expected: "0 \n"},
	}

	for idx, test := range tests {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := generateOutput(test.a, test.b, test.c, test.s); actual != test.expected {
				t.Fatalf("expexted: %#v, actual: %#v", test.expected, actual)
			}
		})
	}
}
