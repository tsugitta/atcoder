// https://atcoder.jp/contests/abc138/tasks/abc138_f

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
	L := io.NextInt()
	R := io.NextInt()

	// y と x の最上位ビットが違う場合、 y % x は x 未満であることも踏まえると、 y と y % x の最上位ビットが異なる。
	// この時 y ^ x の最上位ビットは y と等しいから、 y ^ x と y % x の最上位ビットは異なり、条件を満たさない。
	// よって、 y と x の最上位ビットが等しいことが必要。この時 y/2 < x すなわち y/x < 2 となり、 y // x = 1 すなわち y % x = y - x となる。
	// x と y の最上位ビットが等しく y ^ x = y - x であれば必要十分
	// 最上位から見ていって
	// 1. y と x が等しい → y - x = y ^ x = 0
	// 2. y = 1, x = 0 → y - x = y ^ x = 1
	// 3. y = 0, x = 1 -> この上位の桁の数値を 1 ずらしてしまう。
	// 最上位は等しいため、初めて 3 が起こるタイミングで上位は全て 1, 2 となっており、その桁がずれ、条件を満たさない
	// よって 1, 2 のみである必要があり、逆にそれであれば十分
	// よって x と y の最上位ビットが等しく、各桁で x <= y であることが必要十分
	// x, y の各桁について x <= y であることの別の示し方として
	// y ^ x = y - x
	// y = y ^ x + x
	// x + y = y ^ x + 2x
	// 2(x & y) + x ^  y = y ^ x + 2x
	// x & y = y
	// a + b = 2 * a & b + a ^ b, a | b = a & b + a ^ b であることを使うと変形しやすいことを留意しておく。ベン図で見れば明らか

	// dp[i][msb-appeared][top-tight][bottom-tight]: 上から i: 0, 1,.. 桁 目を決めた時の個数。 msb-appeared は 1 が一度でも現れたかどうか。 tight は max / min とその桁まで一致しているケースの個数
	// i = 0: まだ何も桁を決めていない時の個数すなわち tight & !msb であって 1
	dp := [65][2][2][2]int{}
	dp[0][0][1][1] = 1

	res := 0

	for i := 0; i+1 < 65; i++ {
		// i+1 桁目の bit を見る。 1 桁目 == 下から 64 bit 目
		rBit := R >> uint(64-(i+1)) & 1
		lBit := L >> uint(64-(i+1)) & 1

		// 桁 DP では貰うより配る方がやりやすい
		for msb := 0; msb <= 1; msb++ {
			for tTight := 0; tTight <= 1; tTight++ {
				for bTight := 0; bTight <= 1; bTight++ {
					for y := 0; y <= 1; y++ {
						for x := 0; x <= y; x++ {
							// i 桁の msb, tTight, bTight を踏まえて i+1 桁で y, x を選んだ時を考える
							if msb == 0 && y != x {
								continue
							}

							if tTight == 1 && rBit < y {
								continue
							}

							if bTight == 1 && x < lBit {
								continue
							}

							msbNext := TernaryInt(msb == 1 || y == 1, 1, 0)
							tTightNext := TernaryInt(tTight == 1 && rBit == y, 1, 0)
							bTightNext := TernaryInt(bTight == 1 && lBit == x, 1, 0)
							dp[i+1][msbNext][tTightNext][bTightNext] += dp[i][msb][tTight][bTight]
						}
					}
				}
			}

			for m := 0; m <= 1; m++ {
				for t := 0; t <= 1; t++ {
					for b := 0; b <= 1; b++ {
						dp[i][m][t][b] %= MOD
					}
				}
			}
		}
	}

	for i := 1; i <= 1; i++ {
		for j := 0; j <= 1; j++ {
			for k := 0; k <= 1; k++ {
				res += dp[64][i][j][k]
				res %= MOD
			}
		}
	}

	io.Println(res)
}

// メモ化再帰
func solve2(io *Io, d *Io) {
	L := io.NextInt()
	R := io.NextInt()

	memo := [64][2][2][2]int{}
	used := [64][2][2][2]bool{}

	toI := func(cond bool) int {
		return TernaryInt(cond, 1, 0)
	}

	var dfs func(pos int, tTight, bTight, msb bool) int

	// 前の桁が指定条件を満たしていたものについての pos (0-indexed) 以下の桁の通り
	dfs = func(pos int, tTightPrev, bTightPrev, msbPrev bool) (res int) {
		if pos == -1 {
			return 1
		}

		if used[pos][toI(tTightPrev)][toI(bTightPrev)][toI(msbPrev)] {
			return memo[pos][toI(tTightPrev)][toI(bTightPrev)][toI(msbPrev)]
		}

		lBit := L >> uint(pos) & 1
		rBit := R >> uint(pos) & 1

		for y := 0; y <= 1; y++ {
			for x := 0; x <= y; x++ {
				if tTightPrev && y > rBit {
					continue
				}

				if bTightPrev && x < lBit {
					continue
				}

				if !msbPrev && x != y {
					continue
				}

				tTight := tTightPrev && rBit == y
				bTight := bTightPrev && lBit == x
				msb := msbPrev || y == 1
				res += dfs(pos-1, tTight, bTight, msb)
			}
		}

		res %= MOD
		used[pos][toI(tTightPrev)][toI(bTightPrev)][toI(msbPrev)] = true
		memo[pos][toI(tTightPrev)][toI(bTightPrev)][toI(msbPrev)] = res
		return
	}

	res := dfs(63, true, true, false)
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
