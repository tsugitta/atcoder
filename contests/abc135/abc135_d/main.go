// https://atcoder.jp/contests/abc135/tasks/abc135_d

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

func pairsToKey(n, k int) string {
	return fmt.Sprintf("%d_%d", n, k)
}

// 下から n (1, .., len(chars)) 桁以上で見て 13 で割って k 余らせることができる個数
func rec(n, k int, chars []rune, memo [][]int) int {
	if n == len(chars) {
		if chars[0] == '?' {
			if k <= 9 {
				return 1
			}

			return 0
		}

		num := int(chars[0] - '0')

		if num == k {
			return 1
		}

		return 0
	}

	// 10a + b ≡ k ⇔ 40a + 4b ≡ a + 4b ≡ 4k
	// よって 1 の位と 10 の位以上に分けて、 a ≡ 4k - 4b となる個数を再帰で求めれば良い
	if memo[n][k] != -1 {
		return memo[n][k]
	}

	c := chars[len(chars)-n]

	res := 0

	if c == '?' {
		for i := 0; i < 10; i++ {
			rest := (4*k - i*4 + 13*3) % 13
			res += rec(n+1, rest, chars, memo)
		}
	} else {
		num := int(c - '0')
		rest := (4*k - num*4 + 13*3) % 13
		res = rec(n+1, rest, chars, memo)
	}

	res %= MOD

	memo[n][k] = res
	return res
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	S := io.Next()

	chars := []rune(S)
	memo := make([][]int, len(chars))

	for i := range memo {
		memo[i] = make([]int, 13)

		for j := 0; j < 13; j++ {
			memo[i][j] = -1
		}
	}

	res := rec(1, 5, chars, memo)
	io.Println(res)
}

// d: debug IO. it can print debug in test.
func solve2(io *Io, d *Io) {
	S := io.Next()

	chars := []rune(S)
	// dp[i][j] 先頭 i 文字目（1 <= i <= len(chs)）までで余りが j になる個数
	dp := make([][]int, len(chars)+1)

	for i := range dp {
		dp[i] = make([]int, 13)
	}

	// 一文字目を取った時の mod はその文字自体で決定されるため、 0 文字目相当のものの mod は 0 のものが 1 つあるとする必要がある
	dp[0][0] = 1

	for i := 0; i < len(chars); i++ {
		for j := 0; j < 10; j++ {
			if !(chars[i] == '?' || int(chars[i]-'0') == j) {
				continue
			}

			// i+1 桁目が j で i 桁目までの余りが k であれば i+1 桁目までの余りは 10k + j % 13
			for k := 0; k < 13; k++ {
				dp[i+1][(10*k+j)%13] += dp[i][k]
			}

			for k := 0; k < 13; k++ {
				dp[i+1][k] %= MOD
			}
		}
	}

	res := dp[len(chars)][5]
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
