// https://atcoder.jp/contests/abc137/tasks/abc137_e

package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N := io.NextInt()
	M := io.NextInt()
	P := io.NextInt()

	edges := make([][]int, M)

	for i := 0; i < M; i++ {
		A := io.NextInt()
		B := io.NextInt()
		C := io.NextInt()

		edges[i] = []int{
			A,
			B,
			C,
		}
	}

	fromToEdges := make([][][]int, N+1)
	for i := range fromToEdges {
		fromToEdges[i] = make([][]int, 0)
	}

	toFromEdges := make([][][]int, N+1)
	for i := range toFromEdges {
		toFromEdges[i] = make([][]int, 0)
	}

	for _, e := range edges {
		fromToEdges[e[0]] = append(fromToEdges[e[0]], []int{e[1], e[2]})
		toFromEdges[e[1]] = append(toFromEdges[e[1]], []int{e[0], e[2]})
	}

	goalReachableNodes := map[int]bool{}

	var addGoalReachableNodes func(currentNode int)
	addGoalReachableNodes = func(currentNode int) {
		// already added
		if goalReachableNodes[currentNode] {
			return
		}

		goalReachableNodes[currentNode] = true

		edges := toFromEdges[currentNode]
		for _, edge := range edges {
			addGoalReachableNodes(edge[0])
		}
	}

	addGoalReachableNodes(N)

	// 各 node へのスコアの最大値
	scoreMap := map[int]int{}

	var dfs func(node, score, visited int) bool
	dfs = func(node int, score int, visited int) bool {
		_, included := scoreMap[node]

		if included {
			if score > scoreMap[node] {
				if visited > len(fromToEdges) {
					return true
				}

				scoreMap[node] = score
			} else {
				return false
			}
		}

		visited++
		scoreMap[node] = score

		edges := fromToEdges[node]

		for _, edge := range edges {
			nextScore := score + edge[1] - P
			nextNode := edge[0]

			if !goalReachableNodes[nextNode] {
				continue
			}

			if dfs(nextNode, nextScore, visited) {
				return true
			}
		}

		return false
	}

	infinity := dfs(1, 0, 0)

	if infinity {
		io.Println(-1)
		return
	}

	io.Println(Max(scoreMap[N], 0))
}

// ベルマンフォードに帰着
func solve2(io *Io, d *Io) {
	N := io.NextInt()
	M := io.NextInt()
	P := io.NextInt()

	type Edge struct {
		from int
		to   int
		cost int
	}

	edges := make([]Edge, M)

	for i := 0; i < M; i++ {
		A := io.NextInt()
		B := io.NextInt()
		C := io.NextInt()

		edges[i] = Edge{
			from: A,
			to:   B,
			cost: -(C - P), // 最短経路問題にするためマイナスをかける
		}
	}

	fromToEdges := make([][]int, N+1)
	toFromEdges := make([][]int, N+1)

	for _, e := range edges {
		fromToEdges[e.from] = append(fromToEdges[e.from], e.to)
		toFromEdges[e.to] = append(toFromEdges[e.to], e.from)
	}

	var addReachableNodes func(node int, edges [][]int, reachableMap map[int]bool)
	addReachableNodes = func(node int, edges [][]int, reachableMap map[int]bool) {
		if reachableMap[node] {
			return
		}

		reachableMap[node] = true

		for _, to := range edges[node] {
			addReachableNodes(to, edges, reachableMap)
		}
	}

	startReachableNodes := map[int]bool{}
	addReachableNodes(1, fromToEdges, startReachableNodes)
	goalReachableNodes := map[int]bool{}
	addReachableNodes(N, toFromEdges, goalReachableNodes)
	reachableNodes := map[int]bool{}

	for node, startReachable := range startReachableNodes {
		if startReachable && goalReachableNodes[node] {
			reachableNodes[node] = true
		}
	}

	INF := int(1e18)
	costs := make([]int, N+1)
	for i := range costs {
		costs[i] = INF
	}
	costs[1] = 0

	for i := 1; i <= N; i++ {
		updated := false

		for _, e := range edges {
			if !reachableNodes[e.to] || !reachableNodes[e.from] {
				continue
			}

			if costs[e.from]+e.cost < costs[e.to] {
				costs[e.to] = costs[e.from] + e.cost
				updated = true

				// 負の閉路が無ければ高々 N-1 回 しか更新されない
				if i == N {
					io.Println(-1)
					return
				}
			}
		}

		if !updated {
			break
		}
	}

	io.Println(Max(-costs[N], 0))
}

func main() {
	io := NewIo()
	defer io.Flush()
	solve2(io, nil)
}

/* IO Helpers */

// Io combines reader, writer, & tokens as the state when processing the input
type Io struct {
	reader    *bufio.Reader
	writer    *bufio.Writer
	tokens    []string
	nextToken int
}

// NewIo creates Io with Stdin & Stdout
func NewIo() *Io {
	return &Io{
		reader: bufio.NewReader(os.Stdin),
		writer: bufio.NewWriter(os.Stdout),
	}
}

// Flush calls the writer's Flush
func (io *Io) Flush() {
	io.writer.Flush()
}

// NextLine returns the string from reader.ReadLine()
func (io *Io) NextLine() string {
	if io.nextToken < len(io.tokens) {
		panic("io.nextToken < len(io.tokens)")
	}

	var buffer bytes.Buffer

	for {
		line, isPrefix, err := io.reader.ReadLine()
		if err != nil {
			panic(err)
		}
		buffer.Write(line)
		if !isPrefix {
			break
		}
	}

	return buffer.String()
}

// NextLines returns []string from next n lines
func (io *Io) NextLines(n int) []string {
	res := make([]string, n)
	for i := 0; i < n; i++ {
		res[i] = io.NextLine()
	}
	return res
}

// Next returns the string token (partial string of the line divided by spaces)
func (io *Io) Next() string {
	if io.nextToken >= len(io.tokens) {
		line := io.NextLine()
		io.tokens = strings.Fields(line)
		io.nextToken = 0
	}

	res := io.tokens[io.nextToken]
	io.nextToken++
	return res
}

// NextStrings returns the []string from the next n tokens
func (io *Io) NextStrings(n int) []string {
	res := make([]string, n)
	for i := 0; i < n; i++ {
		res[i] = io.Next()
	}
	return res
}

// NextInt returns the int from the next token
func (io *Io) NextInt() int {
	res, err := strconv.Atoi(io.Next())
	if err != nil {
		panic(err)
	}
	return res
}

// NextInts returns the []int from the next n tokens
func (io *Io) NextInts(n int) []int {
	res := make([]int, n)
	for i := 0; i < n; i++ {
		res[i] = io.NextInt()
	}
	return res
}

// NextFloat returns the float64 from the next token
func (io *Io) NextFloat() float64 {
	res, err := strconv.ParseFloat(io.Next(), 64)
	if err != nil {
		panic(err)
	}
	return res
}

// NextFloats returns the []float64 from the next n tokens
func (io *Io) NextFloats(n int) []float64 {
	res := make([]float64, n)
	for i := 0; i < n; i++ {
		res[i] = io.NextFloat()
	}
	return res
}

// Println prints the input to the writer in an easy-to-see form
func (io *Io) Println(a ...interface{}) {
	var values []string
	for i := 0; i < len(a); i++ {
		values = append(values, "%v")
	}
	io.Printfln(strings.Join(values, " "), a...)
}

// Print calls Fprint to the writer
func (io *Io) Print(a interface{}) {
	fmt.Fprint(io.writer, a)
}

// Printfln calls Fprint to the writer
func (io *Io) Printfln(format string, a ...interface{}) {
	fmt.Fprintf(io.writer, format+"\n", a...)
}

// Debug calls Println and Flush immediately
func (io *Io) Debug(a ...interface{}) {
	if io == nil {
		return
	}

	io.Println(a...)
	io.Flush()
}

/* Math Helpers */

// MOD is 10^9 + 7
const MOD = 1000000007

// Max of the ints
func Max(numbers ...int) int {
	max := numbers[0]
	for i, number := range numbers {
		if i == 0 {
			continue
		}
		if number > max {
			max = number
		}
	}
	return max
}

// Min of the ints
func Min(numbers ...int) int {
	max := numbers[0]
	for i, number := range numbers {
		if i == 0 {
			continue
		}
		if max > number {
			max = number
		}
	}
	return max
}

// DigitSum returns sum of the int's digits
func DigitSum(n int) int {
	if n < 0 {
		return -1
	}

	res := 0

	for n > 0 {
		res += n % 10
		n /= 10
	}

	return res
}

// Sum of the ints
func Sum(numbers ...int) int {
	sum := 0

	for _, number := range numbers {
		sum += number
	}

	return sum
}

// Pow calculates the pow for int with O(log e)
func Pow(a, e int) int {
	if a < 0 || e < 0 {
		panic(fmt.Sprintf("Pow was called for a < 0 or e < 0, a: %d, e: %d", a, e))
	}

	if e == 0 {
		return 1
	}

	if e%2 == 0 {
		half := Pow(a, e/2)
		return half * half
	}

	return a * Pow(a, e-1)
}

// Abs returns the absolute value of the input
func Abs(a int) int {
	if a < 0 {
		return -a
	}

	return a
}

/* Structure Helpers */

// Set is orderless List
type Set map[interface{}]struct{}

// NewSet returns empty Set
func NewSet() *Set {
	return &Set{}
}

// Add the value to the set
func (set *Set) Add(value interface{}) {
	(*set)[value] = struct{}{}
}

// Includes check the set has the value
func (set *Set) Includes(value interface{}) bool {
	_, included := (*set)[value]
	return included
}

// Remove deletes the value from the set if exists
func (set *Set) Remove(value interface{}) {
	if !set.Includes(value) {
		return
	}

	delete(*set, value)
}

// ImmutableSort returns sorted slice without mutating original one
func ImmutableSort(slice []int) []int {
	res := make([]int, len(slice))
	copy(res, slice)
	sort.Ints(res)
	return res
}

/* Util helpers */

// Ternary is like `cond ? a : b`. should assert the returned value like `Ternary(cond, a, b).(int)`
func Ternary(cond bool, a, b interface{}) interface{} {
	if cond {
		return a
	}

	return b
}

// TernaryInt uses Ternary and assert the value as int
func TernaryInt(cond bool, a, b int) int {
	return Ternary(cond, a, b).(int)
}

// TernaryString uses Ternary and assert the value as string
func TernaryString(cond bool, a, b string) string {
	return Ternary(cond, a, b).(string)
}
