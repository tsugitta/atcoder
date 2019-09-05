// https://atcoder.jp/contests/abc131/tasks/abc131_f

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

type UnionFind struct {
	parents []int
}

func (uf *UnionFind) init(n int) {
	uf.parents = make([]int, n)

	for i := range uf.parents {
		uf.parents[i] = -1
	}
}

func (uf *UnionFind) root(x int) int {
	if uf.parents[x] < 0 {
		return x
	}

	r := uf.root(uf.parents[x])
	uf.parents[x] = r
	return r
}

func (uf *UnionFind) same(x, y int) bool {
	return uf.root(x) == uf.root(y)
}

func (uf *UnionFind) merge(x, y int) {
	xr := uf.root(x)
	yr := uf.root(y)

	if xr == yr {
		return
	}

	if xr > yr {
		xr, yr = yr, xr
	}

	uf.parents[xr] += uf.parents[yr]
	uf.parents[yr] = xr
}

type point struct {
	x int
	y int
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N := io.NextInt()
	ps := make([]*point, N)

	// x もしくは y が等しいもので union find を作る
	// uf で merge するためには merge 先を知らないといけない → x, y 一方のみでクエリできるようにする必要がある
	// 同一グループのうち一つの要素さえ得られれば merge はできるから、同一グループ（同一 x / y 座標）の値を一つ持つ map を用意する
	// key: 座標, value: その座標を持つある point の index
	xs := map[int]int{}
	ys := map[int]int{}

	uf := &UnionFind{}
	uf.init(N)

	for i := 0; i < N; i++ {
		x := io.NextInt()
		y := io.NextInt()

		ps[i] = &point{
			x: x,
			y: y,
		}

		if _, xAdded := xs[x]; xAdded {
			uf.merge(xs[x], i)
		} else {
			xs[x] = i
		}

		if _, yAdded := ys[y]; yAdded {
			uf.merge(ys[y], i)
		} else {
			ys[y] = i
		}
	}

	// key: root index, value: x / y 座標の種類の個数
	// NOTE: UF で x, y の pair を持たずに y を y + X_MAX として単一次元で表現すれば uf 構成時点で x, y それぞれの個数を作ることができ
	// Set を使わない分速い -> solve 2
	xCountForGroup := map[int]*Set{}
	yCountForGroup := map[int]*Set{}

	for i := 0; i < N; i++ {
		p := ps[i]
		root := uf.root(i)

		if _, exists := xCountForGroup[root]; !exists {
			xCountForGroup[root] = NewSet()
		}
		if _, exists := yCountForGroup[root]; !exists {
			yCountForGroup[root] = NewSet()
		}

		xCountForGroup[root].Add(p.x)
		yCountForGroup[root].Add(p.y)
	}

	total := 0
	for ri := range xCountForGroup {
		xCt := len(*xCountForGroup[ri])
		yCt := len(*yCountForGroup[ri])
		total += xCt * yCt
	}

	res := total - N
	io.Println(res)
}

func solve2(io *Io, d *Io) {
	N := io.NextInt()

	uf := &UnionFind{}

	max := 100000
	uf.init(2*max + 1) // index 1..max for x, max+1..2*max for y.

	for i := 0; i < N; i++ {
		x := io.NextInt()
		y := io.NextInt()

		uf.merge(x, y+max)
	}

	mx := map[int]int{}
	my := map[int]int{}
	for i := 1; i <= max; i++ {
		mx[uf.root(i)]++
	}
	for i := max + 1; i <= 2*max; i++ {
		my[uf.root(i)]++
	}

	total := 0
	for i := 1; i <= max*2; i++ {
		// 存在しなかった座標は mx, my いずれかが 0 になっている
		total += mx[i] * my[i]
	}

	res := total - N
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

// MinCalculator is helper to get min value
type MinCalculator struct {
	current int
}

// NewMinCalculator returns new MinCalculator with initial value
func NewMinCalculator(initial int) *MinCalculator {
	return &MinCalculator{
		current: initial,
	}
}

// Check compares the value with current and update current if necessary
func (mc *MinCalculator) Check(val int) {
	if val < mc.current {
		mc.current = val
	}
}

// MaxCalculator is helper to get max value
type MaxCalculator struct {
	current int
}

// NewMaxCalculator returns new MaxCalculator with initial value
func NewMaxCalculator(initial int) *MaxCalculator {
	return &MaxCalculator{
		current: initial,
	}
}

// Check compares the value with current and update current if necessary
func (mc *MaxCalculator) Check(val int) {
	if val > mc.current {
		mc.current = val
	}
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
