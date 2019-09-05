// https://atcoder.jp/contests/abc106/tasks/abc106_d

#[allow(unused)]
use std::cmp::{max, min, Ordering};
#[allow(unused)]
use std::collections::{HashSet, VecDeque};
use std::io;
use std::io::{BufRead, Read, Write};
use std::str::FromStr;

/* Input macro */

#[allow(unused)]
macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
}

#[allow(unused)]
macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr, ) => {};

    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}

#[allow(unused)]
macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        ( $(read_value!($iter, $t)),* )
    };

    ($iter:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };

    ($iter:expr, chars) => {
        read_value!($iter, String).chars().collect::<Vec<char>>()
    };

    ($iter:expr, usize1) => {
        read_value!($iter, usize) - 1
    };

    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

// 二次元累積和: O(N^2 + Q)
#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let input = io.read_all();
    input! {
        source = input,
        N: usize,
        M: usize,
        Q: usize,
        trains: [[usize; 2]; M],
        queries: [[usize; 2]; Q],
    }

    // acc[l][r]: 左端が l 以下かつ右端が r 以下のものの個数
    // 例えば acc[l][r] - acc[l-t-1][r] は 左端が l-t 以上 l 以下かつ右端が r 以下のものの個数
    // 同様にして左端が a 以上 b 以下、右端が a 以上 b 以下のものを得ることができ、これが Q(a, b) の答えとなる
    let mut acc = vec![vec![0; N + 1]; N + 1];

    for train in &trains {
        let (l, r) = (train[0], train[1]);
        acc[l][r] += 1;
    }

    for i in 1..N + 1 {
        for j in 1..N + 1 {
            acc[i][j] += acc[i][j - 1];
        }
    }

    for i in 1..N + 1 {
        for j in 1..N + 1 {
            acc[i][j] += acc[i - 1][j];
        }
    }

    for query in queries {
        let (l, r) = (query[0], query[1]);
        let res = acc[r][r] + acc[l - 1][l - 1] - acc[l - 1][r] - acc[r][l - 1];
        io.println(res);
    }
}

// 一次元累積和: O(N^2 + NQ)
#[allow(unused, non_snake_case)]
pub fn solve2<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let input = io.read_all();
    input! {
        source = input,
        N: usize,
        M: usize,
        Q: usize,
        trains: [[usize; 2]; M],
        queries: [[usize; 2]; Q],
    }

    // acc[l][r]: 左端が l 、右端が r 以下のものの和集合
    // a から b までのループで 左端が a 以上 b 以下、右端が a 以上 b 以下のものを得ることができ、これが Q(a, b) の答えとなる
    let mut acc = vec![vec![0; N + 1]; N + 1];

    for train in &trains {
        let (l, r) = (train[0], train[1]);
        acc[l][r] += 1;
    }

    for i in 1..N + 1 {
        for j in 1..N + 1 {
            acc[i][j] += acc[i][j - 1];
        }
    }

    for query in queries {
        let (l, r) = (query[0], query[1]);

        let res: usize = (l..r + 1).map(|l2| acc[l2][r]).sum();
        io.println(res);
    }
}

// 平面操作法: O((M+Q)log(M+Q))
#[allow(unused, non_snake_case)]
pub fn solve3<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let input = io.read_all();
    input! {
        source = input,
        N: usize,
        M: usize,
        Q: usize,
        trains: [[usize; 2]; M],
        queries: [[usize; 2]; Q],
    }

    #[derive(Debug)]
    enum Type {
        Train,
        Query,
    }

    #[derive(Debug)]
    struct Item {
        range: Vec<usize>,
        itemType: Type,
        index: usize,
    }

    let mut all: Vec<Item> = Vec::with_capacity(trains.len() + queries.len());

    all.append(
        &mut trains
            .into_iter()
            .enumerate()
            .map(|(i, train)| Item {
                range: train,
                itemType: Type::Train,
                index: i,
            })
            .vec(),
    );

    all.append(
        &mut queries
            .into_iter()
            .enumerate()
            .map(|(i, query)| Item {
                range: query,
                itemType: Type::Query,
                index: i,
            })
            .vec(),
    );

    all.sort_by(|a, b| {
        // 右端で昇順に並び替える
        if a.range[1] != b.range[1] {
            return a.range[1].cmp(&b.range[1]);
        }

        match a.itemType {
            Type::Train => Ordering::Less,
            _ => Ordering::Greater,
        }
    });

    let mut bit = fenwick_tree::FenwickTree::new(N + 1, 0);

    let mut res = vec![0; Q];

    for el in all {
        match el.itemType {
            Type::Train => bit.add(el.range[0], 1),
            Type::Query => res[el.index] = bit.sum(el.range[0], el.range[1] + 1),
        }
    }

    for r in res {
        io.println(r);
    }
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

    fn read_all(&mut self) -> String {
        let mut res = String::new();
        self.reader.read_to_string(&mut res).unwrap();
        res
    }
}

/* Structure helpers */

trait IteratorExt: Iterator + Sized {
    fn vec(self) -> Vec<Self::Item> {
        self.collect()
    }
}

impl<T: Iterator> IteratorExt for T {}

pub mod fenwick_tree {
    use std::ops::{AddAssign, Sub};
    pub struct FenwickTree<T> {
        n: usize,
        data: Vec<T>,
        init: T,
    }
    impl<T: Copy + AddAssign + Sub<Output = T>> FenwickTree<T> {
        pub fn new(size: usize, init: T) -> FenwickTree<T> {
            FenwickTree {
                n: size + 1,
                data: vec![init; size + 1],
                init: init,
            }
        }
        pub fn add(&mut self, k: usize, value: T) {
            let mut x = k;
            while x < self.n {
                self.data[x] += value;
                x |= x + 1;
            }
        }
        #[doc = " Returns a sum of range `[l, r)`"]
        pub fn sum(&self, l: usize, r: usize) -> T {
            self.sum_one(r) - self.sum_one(l)
        }
        #[doc = " Returns a sum of range `[0, k)`"]
        pub fn sum_one(&self, k: usize) -> T {
            assert!(k < self.n, "k={} n={}", k, self.n);
            let mut result = self.init;
            let mut x = k as isize - 1;
            while x >= 0 {
                result += self.data[x as usize];
                x = (x & (x + 1)) - 1;
            }
            result
        }
    }
}
