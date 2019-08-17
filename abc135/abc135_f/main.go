// https://atcoder.jp/contests/abc135/tasks/abc135_f

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

// O(|s|)
func zAlgorithm(s string) []int {
	n := len(s)
	z := make([]int, n)
	z[0] = n
	for i, j := 1, 0; i < n; {
		for i+j < n && s[j:j+1] == s[i+j:i+j+1] {
			j++
		}
		z[i] = j
		if j == 0 {
			i++
			continue
		}
		k := 1
		for ; i+k < n && k+z[k] < j; k++ {
			z[i+k] = z[k]
		}
		i, j = i+k, j-k
	}
	return z
}

func getPatternIndices(s, pat string) (res []int) {
	arg := pat + s
	z := zAlgorithm(arg)
	ls := len(s)
	lp := len(pat)

	for i := 0; i < ls; i++ {
		if z[lp+i] >= lp {
			res = append(res, i)
		}
	}

	return
}

type TopologicalSort struct {
	edges   [][]int
	inCount []int
}

func (t *TopologicalSort) init(n int) {
	t.edges = make([][]int, n)
	t.inCount = make([]int, n)
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

	for len(s) > 0 {
		popped := s[0]
		res = append(res, popped)
		s = s[1:len(s)]

		for _, to := range t.edges[popped] {
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

	return
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	s := io.Next()
	t := io.Next()

	// t が収まり、かつ s を一周してマッチするかを見れるサイズ Max(|t| * 2, |s|+ |t|）にする必要がある
	// ここでは |t| * 2 + |s| 以上の大きさにする
	// NOTE: `+` をループで回すのは遅いので Repeat を必ず使う
	s2 := strings.Repeat(s, (2*len(t)+len(s)-1)/len(s)+1)

	// 標準の SA は TLE
	// sa := suffixarray.New([]byte(s2))
	// offsets := sa.Lookup([]byte(t), -1)
	offsets := getPatternIndices(s2, t)

	// offsets のうち |s|-1 以下のもののみが重要
	// その index から |s| 進んだ点が index に含まれている限り進めることとすると、
	// 進められた回数の最大値が答えとなる。
	// グラフを作り、各 index についてそれを求める。同じ index に訪れたら無限に含まれるということなので -1
	// ただ実際はグラフを作るまでもなく offsets と visited map で十分そう.. → O(VE) になってしまい TLE
	// グラフを作りトポロジカルソートすることで全体で同じ辺を見ずに済むため O(V + E) にできる

	nextOffset := make([]int, len(s))
	for i := range nextOffset {
		nextOffset[i] = -1
	}

	ts := &TopologicalSort{}
	ts.init(len(s))

	for _, offset := range offsets {
		if offset >= len(s) {
			continue
		}

		next := (offset + len(t)) % len(s)
		nextOffset[offset] = next
		ts.add(offset, next)
	}

	sorted, loop := ts.sort()

	if loop {
		io.Println(-1)
		return
	}

	res := 0
	visited := make([]bool, len(s))

	for _, node := range sorted {
		if visited[node] {
			continue
		}

		curr := node
		ct := 0

		// next にいける → 今の node が match している
		// よって next にいけた回数が match の数

		for {
			visited[curr] = true
			next := nextOffset[curr]

			if next == -1 {
				break
			}

			curr = next
			ct++
		}

		res = Max(res, ct)
	}

	io.Println(res)
}

type UnionFind struct {
	// for children, the value is its parent index. for root, the value is -1 * the size of the group
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

	// make less index one as a root
	if xr > yr {
		xr, yr = yr, xr
	}

	uf.parents[xr] += uf.parents[yr]
	uf.parents[yr] = xr
}

func (uf *UnionFind) size(x int) int {
	return -uf.parents[uf.root(x)]
}

func (uf *UnionFind) groupCount() int {
	res := 0

	for _, parent := range uf.parents {
		if parent < 0 {
			res++
		}
	}

	return res
}

// トポロジカルソートでなく Union Find がより速い
func solve2(io *Io, d *Io) {
	s := io.Next()
	t := io.Next()

	// t が収まり、かつ s を一周してマッチするかを見れるサイズ Max(|t| * 2, |s|+ |t|）にする必要がある
	// ここでは |t| * 2 + |s| 以上の大きさにする
	s2 := strings.Repeat(s, (2*len(t)+len(s)-1)/len(s)+1)

	offsets := getPatternIndices(s2, t)

	uf := &UnionFind{}
	uf.init(len(s))
	res := 0

	for _, offset := range offsets {
		if offset >= len(s) {
			continue
		}

		next := (offset + len(t)) % len(s)

		if uf.same(offset, next) {
			io.Println(-1)
			return
		}

		uf.merge(offset, next)
		// a -> b -> c と offset が推移するとき、 a, b は match していて c は match しない
		// よって size-1 が match 数
		res = Max(res, uf.size(offset)-1)
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
