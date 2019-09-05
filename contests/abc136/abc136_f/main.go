// https://atcoder.jp/contests/abc136/tasks/abc136_f

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

type Fenwick struct {
	tree []int
}

func NewFenwick(n int) *Fenwick {
	f := &Fenwick{
		tree: make([]int, n),
	}

	return f
}

// sum of [0, i)
func (f *Fenwick) Sum(i int) int {
	sum := 0

	for i--; i >= 0; i = (i & (i + 1)) - 1 {
		sum += f.tree[i]
	}

	return sum
}

func (f *Fenwick) Add(i, n int) {
	for l := len(f.tree); i < l; i |= i + 1 {
		f.tree[i] += n
	}
}

type Pairs [][]int

func (p Pairs) Len() int {
	return len(p)
}

func (p Pairs) Less(i, j int) bool {
	return p[i][0] < p[j][0]
}

func (p Pairs) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

func PowM(a, e, m int) int {
	if a < 0 || e < 0 {
		panic(fmt.Sprintf("Pow was called for a < 0 or e < 0, a: %d, e: %d", a, e))
	}

	if e == 0 {
		return 1
	}

	if e%2 == 0 {
		half := PowM(a, e/2, m)
		return half * half % m
	}

	return a * PowM(a, e-1, m) % m
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N := io.NextInt()

	ps := make(Pairs, N)

	for i := 0; i < N; i++ {
		x := io.NextInt()
		y := io.NextInt()
		ps[i] = []int{x, y}
	}

	sort.Sort(ps)

	// y の座標圧縮
	ys := make([]int, N)
	for i := range ps {
		ys[i] = ps[i][1]
	}

	sort.Ints(ys)

	for i := range ps {
		ps[i][1] = sort.SearchInts(ys, ps[i][1])
	}

	lu := make([]int, N)
	ld := make([]int, N)
	ru := make([]int, N)
	rd := make([]int, N)

	bit := NewFenwick(N)

	for i, p := range ps {
		ld[i] = bit.Sum(p[1])
		lu[i] = bit.Sum(N) - ld[i]
		bit.Add(p[1], 1)
	}

	bit = NewFenwick(N)

	for i := len(ps) - 1; i >= 0; i-- {
		p := ps[i]
		rd[i] = bit.Sum(p[1])
		ru[i] = bit.Sum(N) - rd[i]
		bit.Add(p[1], 1)
	}

	res := 0
	mod := 998244353
	for i := range ps {
		// E: Exist, A: Any
		luA := PowM(2, lu[i], mod)
		luE := (luA - 1 + mod) % mod
		ldA := PowM(2, ld[i], mod)
		ldE := (ldA - 1 + mod) % mod
		ruA := PowM(2, ru[i], mod)
		ruE := (ruA - 1 + mod) % mod
		rdA := PowM(2, rd[i], mod)
		rdE := (rdA - 1 + mod) % mod

		// その点を含まない場合
		res += luE * ldA % mod * ruA % mod * rdE % mod
		res += luA * ldE % mod * ruE % mod * rdA % mod
		res -= luE * ldE % mod * ruE % mod * rdE % mod
		res += mod
		res %= mod

		// その点を含む場合
		res += luA * ldA % mod * ruA % mod * rdA % mod
		res %= mod
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
