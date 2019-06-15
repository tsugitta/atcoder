package main

import (
	"bufio"
	"bytes"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type Set map[int]struct{}

func NewSet() *Set {
	return &Set{}
}

func (set *Set) add(number int) {
	(*set)[number] = struct{}{}
}

func (set *Set) includes(number int) bool {
	_, included := (*set)[number]
	return included
}

type Lamp struct {
	switches *Set // 1 ~ N
	even     bool
}

func solve(io *Io, debugIo *Io) {
	N := io.NextInt()
	M := io.NextInt()

	ls := make([]Lamp, M)

	for i := 0; i < M; i++ {
		l := Lamp{
			switches: NewSet(),
		}

		k := io.NextInt()

		for j := 0; j < k; j++ {
			s := io.NextInt()
			l.switches.add(s)
		}

		ls[i] = l
	}

	for i := 0; i < M; i++ {
		p := io.NextInt()

		if p == 0 {
			ls[i].even = true
		} else {
			ls[i].even = false
		}
	}

	res := 0

	limit := int(math.Pow(2, float64(N)))
	for i := 0; i < limit; i++ {
		binString := strconv.FormatInt(int64(i), 2) // like 1010101010
		binStringWithPadding := strings.Repeat("0", N-len(binString)) + binString

		allLampOk := true

		for j := 0; j < M; j++ {
			l := ls[j]

			ct := 0
			for k := 0; k < N; k++ {
				isOn := binStringWithPadding[k] == '1'

				if !isOn {
					continue
				}

				switchNumber := k + 1
				if l.switches.includes(switchNumber) {
					ct++
				}
			}

			if l.even && ct%2 != 0 || !l.even && ct%2 == 0 {
				allLampOk = false
				break
			}
		}

		if allLampOk {
			res++
		}
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

// Println prints the input to the writer in an easy-to-see form
func (io *Io) Println(a ...interface{}) {
	var values []string
	for i := 0; i < len(a); i++ {
		values = append(values, "%v")
	}
	io.Printfln(strings.Join(values, " "), a...)
}

// Debug calls Println and Flush immediately
func (io *Io) Debug(a ...interface{}) {
	if io == nil {
		return
	}

	var values []string
	for i := 0; i < len(a); i++ {
		values = append(values, "%v")
	}
	io.Printfln(strings.Join(values, " "), a...)
	io.Flush()
}

// Print calls Fprint to the writer
func (io *Io) Print(a interface{}) {
	fmt.Fprint(io.writer, a)
}

// Printfln calls Fprint to the writer
func (io *Io) Printfln(format string, a ...interface{}) {
	fmt.Fprintf(io.writer, format+"\n", a...)
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
