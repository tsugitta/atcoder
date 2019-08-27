// https://atcoder.jp/contests/abc134/tasks/abc134_e

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
	As := io.NextInts(N)

	// 最も長い広義減少列の長さを求める
	// LIS として解くために -1 を掛ける
	for i := range As {
		As[i] = -As[i]
	}

	// 長さが i + 1 であるような広義増加部分列の最終要素の最小値
	dp := make([]int, N)

	for i := range dp {
		dp[i] = 10e15
	}

	for _, a := range As {
		// dp を広義増加部分列にするため a+1 に対して lower_bound
		i := sort.SearchInts(dp, a+1)
		dp[i] = a
	}

	res := sort.SearchInts(dp, 10e15)

	io.Println(res)
}

// LIS を複数作り、もっとも差分の小さい所に新しい要素を入れるか、入れられなければ新しく追加して構成する
func solve2(io *Io, d *Io) {
	N := io.NextInt()
	As := io.NextInts(N)

	mins := []int{}

	// 新しい要素が入れられる場所を二分探索で求めたい。それは新しい要素より小さく、現状あるレーンで最大の要素があるレーン。
	// マイナスをかけるとそれは新しい要素より大きく、現状あるレーンで最小の要素があるレーンとなり、 lower_bound が使える。
	for i := range As {
		As[i] = -As[i]
	}

	for _, a := range As {
		toBeReplacedIndex := sort.SearchInts(mins, a+1)

		if toBeReplacedIndex == len(mins) {
			mins = append(mins, a)
		} else {
			mins[toBeReplacedIndex] = a
		}
	}

	res := len(mins)

	io.Println(res)
}

type SegmentTree struct {
	n         int // 最下段の数
	nodes     []int
	zeroValue int
}

func (st *SegmentTree) calc(a, b int) int {
	return Max(a, b)
}

func (st *SegmentTree) init(vs []int, zeroValue int) {
	st.zeroValue = zeroValue
	st.n = 1

	for st.n < len(vs) {
		st.n *= 2
	}

	st.nodes = make([]int, 2*st.n-1)

	for i := range st.nodes {
		st.nodes[i] = st.zeroValue
	}

	for i, v := range vs {
		st.nodes[i+st.n-1] = v
	}

	for i := st.n - 2; i >= 0; i-- {
		st.nodes[i] = st.calc(st.nodes[i*2+1], st.nodes[i*2+2])
	}
}

func (st *SegmentTree) update(i, val int) {
	i += st.n - 1
	st.nodes[i] = val

	for i > 0 {
		i = (i - 1) / 2
		st.nodes[i] = st.calc(st.nodes[2*i+1], st.nodes[2*i+2])
	}
}

// [from, to)
func (st *SegmentTree) query(from, to int) int {
	return st.queryInternal(from, to, 0, 0, st.n)
}

func (st *SegmentTree) queryInternal(from, to, k, l, r int) int {
	if r <= from || to <= l {
		return st.zeroValue
	}

	if from <= l && r <= to {
		return st.nodes[k]
	}

	vl := st.queryInternal(from, to, 2*k+1, l, (l+r)/2)
	vr := st.queryInternal(from, to, 2*k+2, (l+r)/2, r)

	return st.calc(vl, vr)
}

// LIS を SegTree で求める
func solve3(io *Io, d *Io) {
	N := io.NextInt()
	As := io.NextInts(N)

	// 圧縮
	sortedAs := ImmutableSort(As)
	cs := make([]int, N)

	for i, a := range As {
		// LIS として解くために順番を逆にしたい
		// 0~N-1 となっているから、 N-1 - c とする
		cs[i] = N - 1 - sort.SearchInts(sortedAs, a)
	}

	// dp[v]: v を最後の値とする LIS の長さの最大値
	st := SegmentTree{}
	st.init(make([]int, N), 0)

	for _, c := range cs {
		// 広義 LIS のため、 [0, c+1) の最長に c を付け加えることを考える
		cCt := 1 + st.query(0, c+1)
		st.update(c, cCt)
	}

	res := st.query(0, st.n)

	io.Println(res)
}

func main() {
	io := NewIo()
	defer io.Flush()
	solve3(io, nil)
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
