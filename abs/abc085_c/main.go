package main

import (
	"fmt"
)

func solve(N, Y int) string {
	max := 10000 * N
	min := 1000 * N

	if max < Y || min > Y {
		return "-1 -1 -1"
	}

	for x := 0; x <= N; x++ {
		max = 10000*x + 5000*(N-x)
		min = 10000*x + 1000*(N-x)

		if max == Y {
			return fmt.Sprintf("%d %d %d", x, N-x, 0)
		} else if min == Y {
			return fmt.Sprintf("%d %d %d", x, 0, N-x)
		} else if max < Y || min > Y {
			continue
		}

		numOfFiveMax := N - x
		numOfFiveMin := 0

		for numOfFiveMax-numOfFiveMin >= 2 {
			y := (numOfFiveMax + numOfFiveMin) / 2
			res := 10000*x + 5000*y + 1000*(N-x-y)

			if res == Y {
				return fmt.Sprintf("%d %d %d", x, y, N-x-y)
			} else if res < Y {
				numOfFiveMin = y
			} else {
				numOfFiveMax = y
			}
		}
	}

	return "-1 -1 -1"
}

func main() {
	var N, Y int

	fmt.Scan(&N)
	fmt.Scan(&Y)

	output := solve(N, Y)
	fmt.Println(output)
}
