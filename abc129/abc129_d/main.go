package main

import (
	"fmt"
	"bufio"
	"os"
)

var rdr = bufio.NewReaderSize(os.Stdin, 1000000)

func readLine() string {
	buf := make([]byte, 0, 1000000)

	for {
		l, p, e := rdr.ReadLine()
		if e != nil {
			panic(e)
		}

		buf = append(buf, l...)

		if !p {
			break
		}
	}

	return string(buf)
}

func solve(H, W int, rows []string) int {
	h := make([][]int, H)
	v := make([][]int, H)

	for i := 0; i < H; i++ {
		h[i] = make([]int, W)
		v[i] = make([]int, W)
	}

	for i := 0; i < H; i++ {
		ct := 0
		from := 0
		for j := 0; j <= W; j++ {
			if j == W || rows[i][j] == '#' {
				for k := from; k < j; k++ {
					h[i][k] = ct
				}
			}

			if j == W {
				continue
			}

			if rows[i][j] == '#' {
				h[i][j] = 0
				ct = 0
				from = j+1
			} else {
				ct++
			}
		}
	}

	for j := 0; j < W; j++ {
		ct := 0
		from := 0
		for i := 0; i <= H; i++ {
			if i == H || rows[i][j] == '#' {
				for k := from; k < i; k++ {
					v[k][j] = ct
				}
			}

			if i == H {
				continue
			}

			if rows[i][j] == '#' {
				v[i][j] = 0
				ct = 0
				from = i+1
			} else {
				ct++
			}
		}
	}

	max := 0

	for i := 0; i < H; i++ {
		for j := 0; j < W; j++ {
			res := h[i][j] + v[i][j] - 1

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
		rows[i] = readLine()
	}

	output := solve(H, W, rows)

	fmt.Println(output)
}
