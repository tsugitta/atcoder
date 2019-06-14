package main

import (
	"fmt"
	"testing"
)

func TestSolve(t *testing.T) {
	cases := []struct {
		H        int
		W        int
		rows     []string
		expected int
	}{
		{
			4,
			6,
			[]string{
				"#..#..",
				".....#",
				"....#.",
				"#.#...",
			},
			8,
		},
		{
			8,
			8,
			[]string{
				"..#...#.",
				"....#...",
				"##......",
				"..###..#",
				"...#..#.",
				"##....#.",
				"#...#...",
				"###.#..#",
			},
			13,
		},
	}

	for idx, c := range cases {
		t.Run(fmt.Sprintf("%d", idx), func(t *testing.T) {
			if actual := solve(c.H, c.W, c.rows); actual != c.expected {
				t.Fatalf("expexted: %#v, actual: %#v", c.expected, actual)
			}
		})
	}
}
