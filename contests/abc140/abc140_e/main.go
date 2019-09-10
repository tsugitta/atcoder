// https://atcoder.jp/contests/abc140/tasks/abc140_e

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

type Fenwick struct {
	tree []int
}

func NewFenwick(n int) *Fenwick {
	return &Fenwick{
		tree: make([]int, n),
	}
}

// sum of [0, i)
func (f *Fenwick) Sum(i int) (sum int) {
	for i--; i >= 0; i = (i & (i + 1)) - 1 {
		sum += f.tree[i]
	}

	return
}

func (f *Fenwick) Add(i, n int) {
	for l := len(f.tree); i < l; i |= i + 1 {
		f.tree[i] += n
	}
}

type OrderedSet struct {
	tree *Fenwick
	max  int
}

func NewOrderedSet(max int) *OrderedSet {
	s := &OrderedSet{}
	s.tree = NewFenwick(max + 1)
	s.max = max
	return s
}

// n 以下の最大の要素 O(log^2 N)
func (s *OrderedSet) Left(n int) (res int, found bool) {
	nCt := s.tree.Sum(n + 1)

	if nCt == 0 {
		return
	}

	// 0 ~ n で nCt となる最大が求めるもの

	// (l, r] に答えがあるとする
	// mid が条件を満たす → r を置き換えることとなる
	l := -1
	r := n

	for r-l > 1 {
		mid := (l + r) / 2

		midCt := s.tree.Sum(mid + 1)

		if midCt == nCt {
			r = mid
		} else {
			l = mid
		}
	}

	res = r
	found = true
	return
}

// n 以上の最小の要素 O(log^2 N)
func (s *OrderedSet) Right(n int) (res int, found bool) {
	nCt := s.tree.Sum(n) // n-1 以下の個数であることに注意

	if nCt == s.tree.Sum(s.max+1) {
		return
	}

	// n ~ max で > nCt となる最小が求めるもの

	// (l, r] に答えがあるとする
	// mid が条件を満たす → r を置き換えることとなる
	l := n - 1
	r := s.max

	for r-l > 1 {
		mid := (l + r) / 2

		midCt := s.tree.Sum(mid + 1)

		if midCt > nCt {
			r = mid
		} else {
			l = mid
		}
	}

	return r, true
}

func (s *OrderedSet) Add(n int) {
	s.tree.Add(n, 1)
}

func solve(io *Io, d *Io) {
	N := io.NextInt()
	ps := io.NextInts(N)

	numToIndex := make([]int, N+1)

	for i, p := range ps {
		numToIndex[p] = i
	}

	largeIndices := NewOrderedSet(N)
	largeIndices.Add(numToIndex[N])

	res := 0

	for num := N - 1; num >= 1; num-- {
		i := numToIndex[num]

		bi := N
		bi2 := N
		si := -1
		si2 := -1

		// その i より大きい index
		biCand, biFound := largeIndices.Right(i + 1)

		if biFound {
			bi = biCand

			bi2Cand, bi2Found := largeIndices.Right(bi + 1)

			if bi2Found {
				bi2 = bi2Cand
			}
		}

		siCand, siFound := largeIndices.Left(i - 1)

		if siFound {
			si = siCand

			si2Cand, si2Found := largeIndices.Left(si - 1)

			if si2Found {
				si2 = si2Cand
			}
		}

		// s を取る場合
		res += (si - si2) * (bi - i) * num
		// b ..
		res += (bi2 - bi) * (i - si) * num

		largeIndices.Add(i)
	}

	io.Println(res)
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
