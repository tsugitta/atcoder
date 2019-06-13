package main

import (
	"fmt"
)

func solve(a int, b int) string {
	if (a*b)%2 == 0 {
		return "Even"
	}

	return "Odd"
}

func main() {
	var a, b int

	fmt.Scanf("%d %d", &a, &b)

	output := solve(a, b)

	fmt.Println(output)
}
