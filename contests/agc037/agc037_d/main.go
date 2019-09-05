// https://atcoder.jp/contests/agc037/tasks/agc037_d

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

type BipartiteMatching struct {
	edges [][]int
	match []int
	used  []bool
}

func (b *BipartiteMatching) init(n int) {
	b.edges = make([][]int, n)
	b.match = make([]int, n)

	for i := range b.match {
		b.match[i] = -1
	}
}

func (b *BipartiteMatching) add(from, to int) {
	b.edges[from] = append(b.edges[from], to)
	b.edges[to] = append(b.edges[to], from)
}

// edges がソートされている必要がある
func (b *BipartiteMatching) remove(from, to int) {
	{
		i := sort.SearchInts(b.edges[from], to)
		if b.edges[from][i] != to {
			panic(fmt.Sprintf("the edge does not exist %d %d", from, to))
		}
		b.edges[from] = append(b.edges[from][:i], b.edges[from][i+1:]...)
	}

	// match に対して loop をかけるため双方向に消しに行かない
	// {
	// 	i := sort.SearchInts(b.edges[to], from)
	// 	if b.edges[to][i] != from {
	// 		panic(fmt.Sprintf("the edge does not exist %d %d", from, to))
	// 	}
	// 	b.edges[to] = append(b.edges[to][:i], b.edges[to][i+1:]...)
	// }
}

func (b *BipartiteMatching) dfs(v int) bool {
	b.used[v] = true

	for _, u := range b.edges[v] {
		w := b.match[u]
		if w == -1 || !b.used[w] && b.dfs(w) {
			b.match[u] = v
			b.match[v] = u
			return true
		}
	}

	return false
}

func (b *BipartiteMatching) exec() int {
	res := 0

	// 前回の match の情報を消すため
	for i := range b.match {
		b.match[i] = -1
	}

	for _, e := range b.edges {
		// 後で削除するため
		sort.Ints(e)
	}

	for v := 0; v < len(b.edges); v++ {
		if b.match[v] == -1 {
			b.used = make([]bool, len(b.edges))

			if b.dfs(v) {
				res++
			}
		}
	}

	for u, v := range b.match {
		b.remove(u, v)
	}

	return res
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N := io.NextInt()
	M := io.NextInt()

	a := make([][]int, N)
	for i := range a {
		a[i] = make([]int, M)

		for j := 0; j < M; j++ {
			a[i][j] = io.NextInt()
		}
	}

	// N 以上の要素は b において値があるべき行、 N 未満の要素は a において値がある行
	// これらの頂点を結び、 M 個の完全マッチングを実現することを考える。
	// 一つのマッチングは、 a -> b における各行に存在する値からあるべき行が被らないような点の選び方を表す。
	// マッチングを繰り返し、列を埋めていくことを考える。
	bp := BipartiteMatching{}
	bp.init(N * 2)

	// [row][ideal]: a の row 行目にある数であるべき行が ideal なものの index
	aIdealToCol := make([][][]int, N)
	for i := range aIdealToCol {
		aIdealToCol[i] = make([][]int, N)
	}

	for i := range a {
		for j, val := range a[i] {
			row := (val - 1) / M // あるべき行

			aIdealToCol[i][row] = append(aIdealToCol[i][row], j)
			bp.add(i, N+row)
		}
	}

	// [row][ideal]: aIdealToCol で次参照すべき index
	aIdealToColNextIndex := make([][]int, N)
	for i := range aIdealToColNextIndex {
		aIdealToColNextIndex[i] = make([]int, N)
	}

	b := make([][]int, N)
	for i := range b {
		b[i] = make([]int, M)
	}

	for col := 0; col < M; col++ {
		bp.exec()

		for row := 0; row < N; row++ {
			matched := bp.match[row]
			idealRow := matched - N

			ni := aIdealToColNextIndex[row][idealRow]
			aIdealToColNextIndex[row][idealRow]++

			colForA := aIdealToCol[row][idealRow][ni]

			b[row][col] = a[row][colForA]
		}
	}

	for i := range b {
		io.PrintInts(b[i])
	}

	c := make([][]int, N)
	for i := range c {
		c[i] = make([]int, M)
	}

	// 縦でソートして埋める
	for i := 0; i < M; i++ {
		tmp := make([]int, N)

		for j := 0; j < N; j++ {
			tmp[j] = b[j][i]
		}

		sort.Ints(tmp)

		for j := 0; j < N; j++ {
			b[j][i] = tmp[j]
		}
	}

	for i := range b {
		io.PrintInts(b[i])
	}
}

func main() {
	io := NewIo()
	defer io.Flush()
	solve(io, nil)
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

// Printf calls Fprintf to the writer
func (io *Io) Printf(format string, a ...interface{}) {
	fmt.Fprintf(io.writer, format, a...)
}

// Printfln calls Fprint to the writer
func (io *Io) Printfln(format string, a ...interface{}) {
	fmt.Fprintf(io.writer, format+"\n", a...)
}

// PrintInts prints ints with space and new line at the end
func (io *Io) PrintInts(ints []int) {
	for i, e := range ints {
		io.Print(e)

		if i == len(ints)-1 {
			io.Println()
		} else {
			io.Print(" ")
		}
	}
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
