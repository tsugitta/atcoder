// https://atcoder.jp/contests/abc133/tasks/abc133_f

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

type Edge struct {
	to    int
	color int
	dist  int
}

type Graph struct {
	root   int
	edges  [][]Edge // 1-based
	parent [][]int  // parent[v][i] node v の 2^i 回親を辿った node。根を超える場合は -1
	depth  []int    // depth[v] node v の depth (root: 0)
	dists  []int
	N      int
	log2N  int
}

func NewGraph(root int, edges [][]Edge, N int) *Graph {
	l := Graph{}
	l.N = N

	l.root = root
	l.edges = edges
	l.parent = make([][]int, l.N)
	l.depth = make([]int, l.N)
	l.dists = make([]int, l.N)

	// parent[i] の最後の要素は 2^k >= N なる最小の k に対応する ceil(log_2 N)。よって要素数はその値 + 1
	l.log2N = int(math.Ceil(math.Log2(float64(len(edges))))) + 1
	for i := range l.parent {
		l.parent[i] = make([]int, l.log2N)
	}

	return &l
}

// depth と parent を埋める
func (l *Graph) Init() {
	var dfs func(v, p, depth, dist int)

	dfs = func(v, p, depth, dist int) {
		l.parent[v][0] = p
		l.depth[v] = depth
		l.dists[v] = dist

		for _, e := range l.edges[v] {
			if e.to == p {
				continue
			}

			dfs(e.to, v, depth+1, dist+e.dist)
		}
	}

	dfs(l.root, -1, 0, 0)

	// parent の 2^i から 2^(i+1) を埋める
	for i := 0; i+1 < l.log2N; i++ {
		for v := 0; v < l.N; v++ {
			if l.parent[v][i] < 0 {
				l.parent[v][i+1] = -1
			} else {
				parI := l.parent[v][i]
				l.parent[v][i+1] = l.parent[parI][i]
			}
		}
	}
}

func (l *Graph) getLCA(u, v int) int {
	if l.depth[u] > l.depth[v] {
		u, v = v, u
	}

	for i := 0; i < l.log2N; i++ {
		if (l.depth[v]-l.depth[u])>>uint(i)&1 == 1 {
			v = l.parent[v][i]
		}
	}

	if u == v {
		return u
	}

	for i := l.log2N - 1; i >= 0; i-- {
		if l.parent[u][i] != l.parent[v][i] {
			u = l.parent[u][i]
			v = l.parent[v][i]
		}
	}

	return l.parent[u][0]
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	N, Q := io.NextInt(), io.NextInt()

	type Query struct {
		x int
		y int
		u int
		v int
	}

	edges := make([][]Edge, N)

	for i := 0; i < N-1; i++ {
		a, b, c, d := io.NextInt()-1, io.NextInt()-1, io.NextInt()-1, io.NextInt()
		edges[a] = append(edges[a], Edge{to: b, color: c, dist: d})
		edges[b] = append(edges[b], Edge{to: a, color: c, dist: d})
	}

	queries := make([]Query, Q)

	for i := range queries {
		x, y, u, v := io.NextInt()-1, io.NextInt(), io.NextInt()-1, io.NextInt()-1
		q := Query{x, y, u, v}
		queries[i] = q
	}

	// 1. LCA を求める。ダブリングで求めると O(N log N)
	// 2. クエリを先読みし、クエリに含まれる頂点とその LCA までの根からの当該色の個数・当該色辺の長さをメモするため、 3 頂点と色を記録。
	//    頂点を指定すると取るべき色が取れるようにする
	// 3. 再度再帰をかけ、 2 で必要となったものを求める
	// 3. 1 と 2 から各クエリを O(logN) でさばくことができる

	// 再帰で O(N) Q 個に LCA で O(Q log Q) ?

	// 1. LCA の構築
	g := NewGraph(0, edges, N)
	g.Init()

	// 2. necessities[i] i 番目のノードで先読みが必要な色のリスト
	necessities := make([][]int, N)

	for _, q := range queries {
		necessities[q.u] = append(necessities[q.u], q.x)
		necessities[q.v] = append(necessities[q.v], q.x)

		lca := g.getLCA(q.u, q.v)
		necessities[lca] = append(necessities[lca], q.x)
	}

	type NodeWithColor struct {
		u int
		c int
	}

	// これを N^2 の配列で持つのは N <= 10^5 より不可
	cts := map[NodeWithColor]int{}
	dists := map[NodeWithColor]int{}

	// DFS で necessities から cts, dists を埋る
	curCts := make([]int, N)
	curDists := make([]int, N)

	var dfs func(u, p int)
	dfs = func(u, p int) {
		for _, color := range necessities[u] {
			nwc := NodeWithColor{u, color}
			cts[nwc] = curCts[color]
			dists[nwc] = curDists[color]
		}

		for _, e := range edges[u] {
			if e.to == p {
				continue
			}

			c := e.color
			curCts[c]++
			curDists[c] += e.dist

			dfs(e.to, u)

			curCts[c]--
			curDists[c] -= e.dist
		}
	}

	dfs(0, -1)

	for _, q := range queries {
		lca := g.getLCA(q.u, q.v)
		dist := g.dists[q.u] + g.dists[q.v] - 2*g.dists[lca]
		uc := NodeWithColor{q.u, q.x}
		vc := NodeWithColor{q.v, q.x}
		lc := NodeWithColor{lca, q.x}
		colorDist := dists[uc] + dists[vc] - 2*dists[lc]
		colorCt := cts[uc] + cts[vc] - 2*cts[lc]
		dist = dist - colorDist + colorCt*q.y
		io.Println(dist)
	}
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
