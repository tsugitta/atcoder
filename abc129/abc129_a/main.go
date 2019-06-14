package main

import (
	"fmt"
	"sort"
)

func solve(P, Q, R int) int {
	s := []int{P, Q, R}
	sort.Ints(s)
	return s[0] + s[1]
}

func main() {
	var P, Q, R int

	fmt.Scanf("%d %d %d", &P, &Q, &R)

	output := solve(P, Q, R)

	fmt.Println(output)
}
