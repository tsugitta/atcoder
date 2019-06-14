package main

import (
	"fmt"
)

func solve(H, W int, rows []string) int {
	h := make([][]int, H)
	v := make([][]int, H)

	for i := 0; i < H; i++ {
		h[i] = make([]int, W)
		v[i] = make([]int, W)
	}

	for i := 0; i < H; i++ {
		ct := 0
		for j := 0; j < W; j++ {
			if rows[i][j] == '#' {
				ct = 0
			} else {
				ct++
			}

			h[i][j] = ct
		}

		ct = 0
		for j := W - 1; j >= 0; j-- {
			if rows[i][j] == '#' {
				ct = 0
			} else {
				ct++
			}

			h[i][j] += ct
		}
	}

	for j := 0; j < W; j++ {
		ct := 0
		for i := 0; i < H; i++ {
			if rows[i][j] == '#' {
				ct = 0
			} else {
				ct++
			}

			v[i][j] = ct
		}

		ct = 0
		for i := H - 1; i >= 0; i-- {
			if rows[i][j] == '#' {
				ct = 0
			} else {
				ct++
			}

			v[i][j] += ct
		}
	}

	max := 0

	for i := 0; i < H; i++ {
		for j := 0; j < W; j++ {
			res := h[i][j] + v[i][j] - 3

			if res > max {
				max = res
			}
		}
	}

	return max
}

func main() {
	var H, W int

	fmt.Scan(&H)
	fmt.Scan(&W)

	rows := make([]string, H)

	for i := 0; i < H; i++ {
		fmt.Scanf("%s", &rows[i])
	}

	output := solve(H, W, rows)

	fmt.Println(output)
}
