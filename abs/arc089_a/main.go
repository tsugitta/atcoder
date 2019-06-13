package main

import (
	"fmt"
)

func abs(x int) int {
	if x < 0 {
		return -x
	}

	return x
}

func solve(ps []Position) bool {

	curr := Position{
		t: 0,
		x: 0,
		y: 0,
	}

	next := ps[0]

	i := -1

	for {
		diff := abs(next.x-curr.x) + abs(next.y-curr.y)
		tDiff := next.t - curr.t

		if diff > tDiff || diff%2 != tDiff%2 {
			return false
		}

		i++

		if i+1 > len(ps)-1 {
			break
		}

		curr = ps[i]
		next = ps[i+1]
	}

	return true
}

type Position struct {
	t int
	x int
	y int
}

func main() {
	var N int
	fmt.Scan(&N)

	ps := make([]Position, N)
	for i := 0; i < N; i++ {
		fmt.Scanf("%d %d %d", &ps[i].t, &ps[i].x, &ps[i].y)
	}

	res := solve(ps)

	if res {
		fmt.Println("Yes")
	} else {
		fmt.Println("No")
	}
}
