package main

import (
	"fmt"
)

func generateOutput(a int, b int, c int, s string) string {
	return fmt.Sprintf("%d %s\n", a+b+c, s)
}

func main() {
	var a, b, c int
	var s string

	fmt.Scanf("%d", &a)
	fmt.Scanf("%d %d", &b, &c)
	fmt.Scanf("%s", &s)

	output := generateOutput(a, b, c, s)

	fmt.Println(output)
}
