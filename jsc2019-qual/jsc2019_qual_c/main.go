// https://atcoder.jp/contests/jsc2019-qual/tasks/jsc2019_qual_c

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
	S := io.Next()
	chs := []rune(S)

	// 各マスについて見ると、左にある右向きの、右にある左向きの閉じていない range の数だけフリップすると言える
	// また、そのマスは上記 2 つのうち 1 少ない向きの逆向きとなる。
	// よって、条件を満たすパターンを考えるにあたって、各マスのペアを考える必要はなく、ただ各マスの向きを考えれば良い。

	dirs := make([]bool, 2*N) // true: 右, false: 左

	if chs[0] != 'B' {
		io.Println(0)
		return
	}

	dirs[0] = true

	// 先頭から埋めていき、連続する二枚に注目すると、この 2 枚より前後のマスによる影響は 2 枚とも等しく受ける。
	// よって、この 2 枚それぞれの向きによってこの 2 枚の色の違いがあるかどうかが決定される。
	// i-1 枚目の向きが確定している状況で、 i の向きを選んでこの二枚の色を同じにすることを考える。
	for i, ch := range S {
		if i == 0 {
			continue
		}

		// prev における右と curr における左は２者をずらさない（どちらもひっくり返す）向き、 prev における左と curr における右は２者をずらす向き
		if ch == chs[i-1] {
			// prev がずらすなら curr もずらす、逆も然り
			dirs[i] = !dirs[i-1]
		} else {
			// prev がずらすなら curr はずらさない、逆も然り
			dirs[i] = dirs[i-1]
		}
	}

	{
		rCt := 0

		for _, d := range dirs {
			if d {
				rCt++
			}
		}

		if rCt != len(dirs)/2 {
			io.Println(0)
			return
		}
	}

	pairCt := 1 // dirs を満たすペアの作り方

	{
		// 左向きが現れる度に未使用の右向きから選ぶ
		rCt := 0
		lCt := 0

		for _, d := range dirs {
			if d {
				rCt++
			} else {
				pairCt *= rCt - lCt
				pairCt %= MOD
				lCt++
			}
		}
	}

	// 操作順は N! 通り

	res := pairCt

	for i := 2; i <= N; i++ {
		res *= i
		res %= MOD
	}

	io.Println(res)
}

// d: debug IO. it can print debug in test.
func solve2(io *Io, d *Io) {
	N := io.NextInt()
	S := io.Next()
	chs := []rune(S)

	if chs[0] != 'B' {
		io.Println(0)
		return
	}

	res := 1

	for i := 2; i <= N; i++ {
		res *= i
		res %= MOD
	}

	// 先頭は右向き
	rCt := 1

	for i, ch := range S {
		if i == 0 {
			continue
		}

		// このマスを右向きにすると rCt + 1 回、 左向きにすると rCt 回ひっくり返る
		if ch == 'W' && rCt%2 == 0 || ch == 'B' && rCt%2 == 1 {
			res *= rCt
			res %= MOD
			rCt--
		} else {
			rCt++
		}
	}

	if rCt != 0 {
		io.Println(0)
		return
	}

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
