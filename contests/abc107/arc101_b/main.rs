// https://atcoder.jp/contests/abc107/tasks/arc101_b

#[allow(unused)]
use std::cmp::{max, min};
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

// 非反転数. i < j で a[i] <= a[j] の組の個数
fn get_non_inv_count(values: Vec<usize>) -> usize {
    let max_v = (&values).iter().max().unwrap();
    let mut bit = fenwick_tree::FenwickTree::new(*max_v + 1, 0);
    let mut res = 0;

    for v in &values {
        // 過去の v ともペアを組める（部分和の差が 0）
        res += bit.sum_one(v + 1);
        bit.add(*v, 1);
    }

    res
}

// 部分列において target 以上であるものが ceil(length / 2) 以上であるか（median の必要条件）
#[allow(non_snake_case)]
fn check(As: &Vec<usize>, N: usize, target: usize) -> bool {
    let acc_sums = (0..N)
        .scan(0, |acc, curr| {
            let val: isize = if As[curr] >= target { 1 } else { -1 };
            let res = *acc + val;
            *acc = res;
            Some(res)
        })
        .vec();

    let acc_sums_min = acc_sums.iter().min().unwrap();
    let offset = min(*acc_sums_min, 0).abs();

    let acc_offset_sums = acc_sums.iter().map(|x| (*x + offset) as usize).vec();

    // S_r - S_l が 0 以上のものの個数
    let non_inv_count = get_non_inv_count(acc_offset_sums);

    // 0 からの部分和が 0 以上のものの個数
    let ok_from_zero_count = acc_sums.iter().filter(|&x| *x >= 0).count();

    // N+C(N, 2) = (N+1)*N/2 の半分以上かどうかを見る
    // (N+1)*N/2 が奇数であれば、半分の ceil 以上である必要がある → 1 を足しておく
    return non_inv_count + ok_from_zero_count >= ((N + 1) * N / 2 + 1) / 2;
}

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(
    mut io: Io<R, W>,
    mut debug: Option<Io<std::io::StdinLock, std::io::StdoutLock>>,
) {
    let input = io.read_all();
    input! {
        source = input,
        N: usize,
        As: [usize; N],
    }

    let min_a = *As.iter().min().unwrap();
    let max_a = *As.iter().max().unwrap();

    // 解の範囲:  [low, high)
    // check 関数の条件は小さい方が通るため
    let mut low = min_a;
    let mut high = max_a + 1;

    while high - low > 1 {
        let mid = (low + high) / 2;

        if check(&As, N, mid) {
            low = mid
        } else {
            high = mid
        }
    }

    io.println(low);
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

    solve(io, None);
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

#[allow(unused)]
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

        /// Returns a sum of range `[l, r)`
        pub fn sum(&self, l: usize, r: usize) -> T {
            self.sum_one(r) - self.sum_one(l)
        }

        /// Returns a sum of range `[0, k)`
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
