package main

import (
	"fmt"
)

func min(a, b int) int {
	if a < b {
		return a
	}

	return b
}

func solve(a, b, c, x int) int {
	res := 0

	for i := 0; i <= min(a, x/500); i++ {
		for j := 0; j <= min(b, (x-500*i)/100); j++ {
			if c >= (x-500*i-100*j)/50 {
				res++
			}
		}
	}

	return res
}

func main() {
	var a, b, c, x int

	fmt.Scanf("%d\n%d\n%d\n%d", &a, &b, &c, &x)

	output := solve(a, b, c, x)

	fmt.Println(output)
}
