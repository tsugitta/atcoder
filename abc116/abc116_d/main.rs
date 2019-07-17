// https://atcoder.jp/contests/abc116/tasks/abc116_d

use std::cell::RefCell;
#[allow(unused)]
use std::cmp::{max, min, Ord, Ordering, PartialOrd};
#[allow(unused)]
use std::collections::{BinaryHeap, HashMap, HashSet, VecDeque};
use std::io;
use std::io::{BufRead, Read, Write};
use std::str::FromStr;

struct Sushi {
    t: usize,
    d: usize,
}

fn calc(sum: usize, types: usize) -> usize {
    sum + types.pow(2)
}

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let N: usize = io.next();
    let K: usize = io.next();

    // 美味しい順に K 個取ることを考える。これより評価値が高いのは種類数がより大きい場合しかあり得ない。
    // またこれより種類数が少ないケースは美味しさの総数も劣るので答えになりえない。
    // K+1 個目から最後の要素まで順番に見ていき、それが新しい種類であれば、
    // K 個のうち 2 つ以上あるものの中での最小のものと交換する。この時、この種類数において最大となっていると言える。
    // なぜなら、この時の種類数を L とすると、各種類の最も美味しいものを降順に並べた列の先頭 L 個が含まれており、
    // その他全体の中から K+1-L 個美味しい順に選んでいるため。
    // よって、この操作を最後の要素まで繰り返すことで、最初に得たものより種類数が多い全ての場合の
    // ケースを網羅することができ、その最大値が答えとなる。

    let mut sushis = (0..N)
        .map(|_| {
            let t: usize = io.next();
            let d: usize = io.next();

            Sushi { t: t, d: d }
        })
        .vec();

    sushis.sort_by(|a, b| b.d.cmp(&a.d));

    // 各種類の最大のものは必ず選ばれ、以降取り出される必要はないから、そのタイプを Set で持つ。
    // 最大以外のものについては、最小のものが取り出されていくから、それらのみを含んだ priority queue で持つ。
    let mut added_types = RefCell::new(HashSet::new());
    let mut sum: usize = 0;
    let mut heap = BinaryHeap::new();

    for sushi in &sushis[0..K] {
        if !added_types.borrow().contains(&sushi.t) {
            added_types.borrow_mut().insert(&sushi.t);
        } else {
            heap.push(Reverse(sushi.d));
        }

        sum += sushi.d;
    }

    let mut res = calc(sum, added_types.borrow().len());

    for sushi in &sushis[K..N]{
        if added_types.borrow().contains(&sushi.t) {
            continue;
        }

        let min = match heap.pop() {
            Some(Reverse(x)) => x,
            None => break,
        };

        sum = sum - min + sushi.d;
        added_types.borrow_mut().insert(&sushi.t);
        res = max(res, calc(sum, added_types.borrow().len()));
    }

    io.println(res);
}

#[allow(dead_code)]
fn main() {
    let stdin = io::stdin();
    let stdin_lock = stdin.lock();
    let stdout = io::stdout();
    let stdout_lock = stdout.lock();

    let io = Io {
        reader: stdin_lock,
        writer: stdout_lock,
    };

    solve(io);
}

/* IO helpers */

pub struct Io<R, W>
where
    R: BufRead,
    W: Write,
{
    pub reader: R,
    pub writer: W,
}

#[allow(dead_code)]
impl<R, W> Io<R, W>
where
    R: BufRead,
    W: Write,
{
    fn println<T: std::fmt::Display>(&mut self, value: T) {
        writeln!(&mut self.writer, "{}", value).expect("Unable to write");
    }

    fn print<T: std::fmt::Display>(&mut self, value: T) {
        write!(&mut self.writer, "{}", value).expect("Unable to write");
    }

    fn debug<T: std::fmt::Debug>(&mut self, value: T) {
        writeln!(&mut self.writer, "{:?}", value).expect("Unable to write");
    }

    fn next<T: FromStr>(&mut self) -> T {
        let token = self
            .reader
            .by_ref()
            .bytes()
            .map(|c| c.unwrap() as char)
            .skip_while(|c| c.is_whitespace())
            .take_while(|c| !c.is_whitespace())
            .collect::<String>();
        token.parse::<T>().ok().expect("Unable to parse")
    }

    fn nexts<T: FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.next::<T>()).collect::<Vec<T>>()
    }
}

/* Structure helpers */

trait IteratorExt: Iterator + Sized {
    fn vec(self) -> Vec<Self::Item> {
        self.collect()
    }
}

impl<T: Iterator> IteratorExt for T {}

// AtCoder uses 1.15.1 and does not have std::cmp::Reverse
#[derive(PartialEq, Eq, Debug, Copy, Clone, Default, Hash)]
pub struct Reverse<T>(pub T);

impl<T: PartialOrd> PartialOrd for Reverse<T> {
    #[inline]
    fn partial_cmp(&self, other: &Reverse<T>) -> Option<Ordering> {
        other.0.partial_cmp(&self.0)
    }

    #[inline]
    fn lt(&self, other: &Self) -> bool {
        other.0 < self.0
    }
    #[inline]
    fn le(&self, other: &Self) -> bool {
        other.0 <= self.0
    }
    #[inline]
    fn ge(&self, other: &Self) -> bool {
        other.0 >= self.0
    }
    #[inline]
    fn gt(&self, other: &Self) -> bool {
        other.0 > self.0
    }
}

impl<T: Ord> Ord for Reverse<T> {
    #[inline]
    fn cmp(&self, other: &Reverse<T>) -> Ordering {
        other.0.cmp(&self.0)
    }
}
