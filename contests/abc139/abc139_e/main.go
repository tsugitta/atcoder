// https://atcoder.jp/contests/abc139/tasks/abc139_e

package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"reflect"
	"runtime"
	"sort"
	"strconv"
	"strings"
)

func naive(io *Io, d *Io) {
	N := io.NextInt()

	as := make([][]int, N)
	for i := range as {
		as[i] = make([]int, N-1)

		for j := range as[i] {
			as[i][j] = io.NextInt() - 1 // 0-based
		}
	}

	res := 0
	allCt := 0

	for allCt < N*(N-1)/2 {
		updated := false
		used := make([]bool, N)

		for p := 0; p < N; p++ {
			if used[p] {
				continue
			}

			if len(as[p]) == 0 {
				continue
			}

			op := as[p][0]

			if !used[op] && as[op][0] == p {
				used[p] = true
				used[op] = true
				as[p] = as[p][1:]
				as[op] = as[op][1:]
				updated = true
				allCt++
			}
		}

		if !updated {
			io.Println(-1)
			return
		}

		res++
	}

	io.Println(res)
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N := io.NextInt()

	as := make([][]int, N)
	for i := range as {
		as[i] = make([]int, N-1)

		for j := range as[i] {
			as[i][j] = io.NextInt() - 1 // 0-based
		}
	}

	res := 0
	allCt := 0

	queue := []int{}

	for p := 0; p < N; p++ {
		op := as[p][0]

		if p < op && as[op][0] == p {
			queue = append(queue, p)
		}
	}

	for allCt < N*(N-1)/2 {
		if len(queue) == 0 {
			io.Println(-1)
			return
		}

		toBeChecked := map[int]bool{}

		for _, p := range queue {
			op := as[p][0]
			toBeChecked[p] = true
			toBeChecked[op] = true
			as[p] = as[p][1:]
			as[op] = as[op][1:]
			allCt++
		}

		nextQueue := []int{}
		queued := map[int]bool{}

		for p := range toBeChecked {
			if len(as[p]) == 0 {
				continue
			}

			op := as[p][0]
			min := Min(p, op)
			if as[op][0] == p && !queued[min] {
				queued[min] = true
				nextQueue = append(nextQueue, min)
			}
		}

		queue = nextQueue

		res++
	}

	io.Println(res)
}

type TopologicalSort struct {
	edges   [][]int
	inCount []int
	sorted  []int
	length  []int // 入次数 0 のノードからそのノードまでの長さ
}

func (t *TopologicalSort) init(n int) {
	t.edges = make([][]int, n)
	t.inCount = make([]int, n)
	t.length = make([]int, n)
}

func (t *TopologicalSort) add(from, to int) {
	t.edges[from] = append(t.edges[from], to)
}

func (t *TopologicalSort) sort() (res []int, isLoop bool) {
	// 全ての nodes の入次数をカウント O(E)
	for _, edgesForNode := range t.edges {
		for _, to := range edgesForNode {
			t.inCount[to]++
		}
	}

	// inCount が 0 のものの集合
	s := []int{}

	for node, in := range t.inCount {
		if in == 0 {
			s = append(s, node)
		}
	}

	for i := range t.length {
		t.length[i] = 1
	}

	for len(s) > 0 {
		popped := s[0]
		res = append(res, popped)
		s = s[1:len(s)]

		for _, to := range t.edges[popped] {
			if t.length[popped]+1 > t.length[to] {
				t.length[to] = t.length[popped] + 1
			}

			t.inCount[to]--

			if t.inCount[to] == 0 {
				s = append(s, to)
			}
		}
	}

	if len(res) != len(t.edges) {
		isLoop = true
		return
	}

	t.sorted = res

	return
}

// 試合を頂点として試合順で有向辺を貼りトポロジカルソート。最長パスが答え
func solve2(io *Io, d *Io) {
	N := io.NextInt()

	as := make([][]int, N)
	for i := range as {
		as[i] = make([]int, N-1)

		for j := range as[i] {
			as[i][j] = io.NextInt() - 1 // 0-based
		}
	}

	pairToNodeID := make([][]int, N)
	for i := range pairToNodeID {
		pairToNodeID[i] = make([]int, N)
	}

	nodeCt := 0

	for i := 0; i < N; i++ {
		for j := i + 1; j < N; j++ {
			pairToNodeID[i][j] = nodeCt
			pairToNodeID[j][i] = nodeCt
			nodeCt++
		}
	}

	tp := TopologicalSort{}
	tp.init(nodeCt)

	for p := range as {
		for i := 0; i+1 < len(as[p]); i++ {
			// トポロジカルソートは入力の無いエッジから取り除いていくため、それに合わせて
			// 先に終わっていないといけない試合から辺を張る
			firstOp := as[p][i]
			secondOp := as[p][i+1]
			first := pairToNodeID[p][firstOp]
			next := pairToNodeID[p][secondOp]
			tp.add(first, next)
		}
	}

	_, isLoop := tp.sort()

	if isLoop {
		io.Println(-1)
		return
	}

	res := Max(tp.length...)

	io.Println(res)
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

// NextRunes returns next string as []rune
func (io *Io) NextRunes() []rune {
	return []rune(io.Next())
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

// Assert checks the value equality for debug
func (io *Io) Assert(a, b interface{}) {
	if io == nil {
		return
	}

	if !reflect.DeepEqual(a, b) {
		_, _, line, _ := runtime.Caller(1)
		io.Debug("Diff:", line, "\na:", a, "\nb:", b)
	}
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
	min := numbers[0]
	for i, number := range numbers {
		if i == 0 {
			continue
		}
		if min > number {
			min = number
		}
	}
	return min
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