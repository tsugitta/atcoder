// https://atcoder.jp/contests/abc123/tasks/abc123_d

package main

import (
	"bufio"
	"bytes"
	"container/heap"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

type int64s []int64

func (is int64s) Len() int {
	return len(is)
}

// Desc
func (is int64s) Less(i, j int) bool {
	return is[i] > is[j]
}

func (is int64s) Swap(i, j int) {
	is[i], is[j] = is[j], is[i]
}

// d: debug IO. it can print debug in test.
func solve(io *Io, d *Io) {
	X := io.NextInt()
	Y := io.NextInt()
	Z := io.NextInt()
	K := io.NextInt()

	as := int64s(io.NextInt64s(X))
	bs := int64s(io.NextInt64s(Y))
	cs := int64s(io.NextInt64s(Z))

	sort.Sort(as)
	sort.Sort(bs)
	sort.Sort(cs)

	abSums := make(int64s, 0)

	for i := 0; i < X; i++ {
		a := as[i]

		for j := 0; j < Y; j++ {
			b := bs[j]

			abSums = append(abSums, a+b)
		}
	}

	// O(X*Y)
	sort.Sort(abSums)

	abcSums := make(int64s, 0)

	for i := 0; i < Min(K, len(abSums)); i++ {
		abSum := abSums[i]

		for j := 0; j < Z; j++ {
			c := cs[j]

			abcSums = append(abcSums, abSum+c)
		}
	}

	// O(K*Z)
	sort.Sort(abcSums)

	for i := 0; i < K; i++ {
		io.Println(abcSums[i])
	}
}

type abcSum struct {
	sum int64
	is  []int // index for a, b, c
}

type priorityQueue []*abcSum

func (pq *priorityQueue) Len() int {
	return len(*pq)
}

func (pq *priorityQueue) Less(i, j int) bool {
	return (*pq)[i].sum > (*pq)[j].sum
}

func (pq *priorityQueue) Swap(i, j int) {
	(*pq)[i], (*pq)[j] = (*pq)[j], (*pq)[i]
}

func (pq *priorityQueue) Push(item interface{}) {
	abcSum := item.(*abcSum)
	*pq = append(*pq, abcSum)
}

func (pq *priorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}

func indicesToKey(ai, bi, ci int) string {
	return fmt.Sprintf("%d %d %d", ai, bi, ci)
}
func solve2(io *Io, d *Io) {
	X := io.NextInt()
	Y := io.NextInt()
	Z := io.NextInt()
	K := io.NextInt()

	as := int64s(io.NextInt64s(X))
	bs := int64s(io.NextInt64s(Y))
	cs := int64s(io.NextInt64s(Z))

	sort.Sort(as)
	sort.Sort(bs)
	sort.Sort(cs)

	pq := &priorityQueue{}
	heap.Init(pq)
	heap.Push(pq, &abcSum{
		sum: as[0] + bs[0] + cs[0],
		is:  []int{0, 0, 0},
	})

	res := make([]int64, K)
	addedSet := NewSet()
	addedSet.Add(indicesToKey(0, 0, 0))

	for poppedCt := 0; poppedCt < K; poppedCt++ {
		popped := heap.Pop(pq).(*abcSum)
		res[poppedCt] = popped.sum

		ai := popped.is[0]
		bi := popped.is[1]
		ci := popped.is[2]

		if ai+1 < X && !addedSet.Includes(indicesToKey(ai+1, bi, ci)) {
			heap.Push(pq, &abcSum{
				sum: as[ai+1] + bs[bi] + cs[ci],
				is:  []int{ai + 1, bi, ci},
			})
			addedSet.Add(indicesToKey(ai+1, bi, ci))
		}

		if bi+1 < Y && !addedSet.Includes(indicesToKey(ai, bi+1, ci)) {
			heap.Push(pq, &abcSum{
				sum: as[ai] + bs[bi+1] + cs[ci],
				is:  []int{ai, bi + 1, ci},
			})
			addedSet.Add(indicesToKey(ai, bi+1, ci))
		}

		if ci+1 < Z && !addedSet.Includes(indicesToKey(ai, bi, ci+1)) {
			heap.Push(pq, &abcSum{
				sum: as[ai] + bs[bi] + cs[ci+1],
				is:  []int{ai, bi, ci + 1},
			})
			addedSet.Add(indicesToKey(ai, bi, ci+1))
		}
	}

	for i := 0; i < K; i++ {
		io.Println(res[i])
	}
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

// NextInt64 returns the int64 from the next token
func (io *Io) NextInt64() int64 {
	res, err := strconv.ParseInt(io.Next(), 10, 64)
	if err != nil {
		panic(err)
	}
	return res
}

// NextInt64s returns the []int64 from the next n tokens
func (io *Io) NextInt64s(n int) []int64 {
	res := make([]int64, n)
	for i := 0; i < n; i++ {
		res[i] = io.NextInt64()
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

// Max64 is the max of the int64s
func Max64(numbers ...int64) int64 {
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

// Min64 is the min of the int64s
func Min64(numbers ...int64) int64 {
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

// Sum64 is the sum of the int64s
func Sum64(numbers ...int64) int64 {
	sum := int64(0)

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

// TernaryInt64 uses Ternary and assert the value as int
func TernaryInt64(cond bool, a, b int64) int64 {
	return Ternary(cond, a, b).(int64)
}

// TernaryString uses Ternary and assert the value as string
func TernaryString(cond bool, a, b string) string {
	return Ternary(cond, a, b).(string)
}
