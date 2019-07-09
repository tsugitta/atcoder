// https://atcoder.jp/contests/abc117/tasks/abc117_d

package main

import (
	"bufio"
	"bytes"
	"fmt"
	"math"
	"os"
	"sort"
	"strconv"
	"strings"
)

func hasBit(n int, pos uint) bool {
	val := n & (1 << pos)
	return val > 0
}

// 桁 DP
// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N := io.NextInt()
	K := io.NextInt()
	As := io.NextInts(N)

	// K を 2進法で表し、同じ桁数の数字を考える
	max := Max(Max(As...), K)
	digit := TernaryInt(max == 0, 1, int(math.Ceil(math.Log2(float64(max)))))

	oneCts := make([]int, digit) // 下から i >= 0 桁目について A のうち bit が立っているものの個数

	for i := 0; i < digit; i++ {
		oneCt := 0

		for _, A := range As {
			if hasBit(A, uint(i)) {
				oneCt++
			}
		}

		oneCts[i] = oneCt
	}

	// dp[i][tight]: 上から i 桁目までを決めた時の xor の最大値で、 tight true なら K と一致、 false なら K 未満
	dp := make([][]int, digit+1)
	for i := range dp {
		dp[i] = []int{-1, -1} // -1: 求める必要無し
	}
	dp[0][1] = 0

	for i := 1; i <= digit; i++ {
		oneCt := oneCts[digit-i]
		mask := 1 << uint(digit-i)
		res0 := mask * oneCt
		res1 := mask * (N - oneCt)
		kHasBit := hasBit(K, uint(digit-i))

		if dp[i-1][0] != -1 {
			dp[i][0] = Max(dp[i][0], dp[i-1][0]+Max(res0, res1))
		}

		if dp[i-1][1] != -1 {
			if kHasBit {
				dp[i][0] = Max(dp[i][0], dp[i-1][1]+res0)
				dp[i][1] = Max(dp[i][1], dp[i-1][1]+res1)
			} else {
				dp[i][1] = Max(dp[i][1], dp[i-1][1]+res0)
			}
		}
	}

	res := Max(dp[digit][0], dp[digit][1])

	io.Println(res)
}

// i 桁目で初めて K と異なる値を取る場合の最大値を求め、 K を動かして最大値を得る
func solve2(io *Io, d *Io) {
	N := io.NextInt()
	K := io.NextInt()
	As := io.NextInts(N)

	// K を 2進法で表し、同じ桁数の数字を考える
	max := Max(Max(As...), K)
	digit := TernaryInt(max == 0, 1, int(math.Ceil(math.Log2(float64(max)))))

	oneCts := make([]int, digit) // 下から i >= 0 桁目について A のうち bit が立っているものの個数

	for i := 0; i < digit; i++ {
		oneCt := 0

		for _, A := range As {
			if hasBit(A, uint(i)) {
				oneCt++
			}
		}

		oneCts[i] = oneCt
	}

	mc := NewMaxCalculator(0)

	for firstDiffDigit := 1; firstDiffDigit <= digit+1; firstDiffDigit++ {
		if firstDiffDigit != digit+1 && !hasBit(K, uint(digit-firstDiffDigit)) {
			continue
		}

		res := 0

		for i := 1; i <= digit; i++ {
			oneCt := oneCts[digit-i]
			mask := 1 << uint(digit-i)
			res0 := mask * oneCt
			res1 := mask * (N - oneCt)
			kHasBit := hasBit(K, uint(digit-i))

			if i < firstDiffDigit {
				res += TernaryInt(kHasBit, res1, res0)
			} else if i == firstDiffDigit {
				res += res0
			} else {
				res += Max(res0, res1)
			}
		}

		mc.Check(res)
	}

	io.Println(mc.current)
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
