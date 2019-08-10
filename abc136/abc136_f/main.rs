// https://atcoder.jp/contests/abc136/tasks/abc136_f

#[allow(unused)]
use std::cmp::{max, min, Ordering};
#[allow(unused)]
use std::collections::{BTreeMap, BTreeSet, HashSet, VecDeque};
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

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let input = io.read_all();
    input! {
        source = input,
        N: usize,
        original_ps: [[isize; 2]; N],
    }
    let MOD = 998244353;

    // y の座標圧縮
    let mut map = BTreeMap::new();

    for p in &original_ps {
        map.insert(p[1], 0);
    }

    for (i, (k, v)) in map.iter_mut().enumerate() {
        *v = i
    }

    let mut ps = original_ps
        .iter()
        .map(|p| [p[0], map[&p[1]] as isize])
        .vec();

    ps.sort_by(|a, b| a[0].cmp(&b[0]));

    let mut lu = vec![0; N];
    let mut ld = vec![0; N];
    let mut ru = vec![0; N];
    let mut rd = vec![0; N];

    {
        let mut bit = fenwick_tree::FenwickTree::new(N, 0);

        for i in 0..ps.len() {
            let p = &ps[i];
            lu[i] = bit.sum(p[1] as usize, N);
            ld[i] = bit.sum_one(p[1] as usize);

            bit.add(p[1] as usize, 1);
        }
    }

    {
        let mut bit = fenwick_tree::FenwickTree::new(N, 0);

        for i in (0..ps.len()).rev() {
            let p = &ps[i];
            ru[i] = bit.sum(p[1] as usize, N);
            rd[i] = bit.sum_one(p[1] as usize);

            bit.add(p[1] as usize, 1);
        }
    }

    let mut res = 0;

    for i in 0..ps.len() {
        let lu_select = (pow_m(2, lu[i], MOD) + MOD - 1) % MOD;
        let lu_any = pow_m(2, lu[i], MOD);
        let ld_select = (pow_m(2, ld[i], MOD) + MOD - 1) % MOD;
        let ld_any = pow_m(2, ld[i], MOD);
        let ru_select = (pow_m(2, ru[i], MOD) + MOD - 1) % MOD;
        let ru_any = pow_m(2, ru[i], MOD);
        let rd_select = (pow_m(2, rd[i], MOD) + MOD - 1) % MOD;
        let rd_any = pow_m(2, rd[i], MOD);

        // その点を選ばない場合
        res += lu_select * ld_any % MOD * ru_any % MOD * rd_select % MOD;
        res %= MOD;
        res += lu_any * ld_select % MOD * ru_select % MOD * rd_any % MOD;
        res %= MOD;
        res -= lu_select * ld_select % MOD * ru_select % MOD * rd_select % MOD;
        res = (res + MOD) % MOD;

        // その点を選ぶ場合
        res += lu_any * ld_any % MOD * ru_any % MOD * rd_any % MOD;
        res %= MOD;
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

pub trait BinarySearch<T> {
    fn lower_bound(&self, x: &T) -> usize;
    fn upper_bound(&self, x: &T) -> usize;
}
impl<T: Ord> BinarySearch<T> for [T] {
    fn lower_bound(&self, x: &T) -> usize {
        let mut low: isize = -1;
        let mut high: isize = self.len() as isize;
        while high - low > 1 {
            let mid = (low + high) / 2;
            match self[mid as usize].cmp(x) {
                Ordering::Less => {
                    low = mid;
                }
                Ordering::Equal | Ordering::Greater => {
                    high = mid;
                }
            }
        }
        high as usize
    }
    fn upper_bound(&self, x: &T) -> usize {
        let mut low: isize = -1;
        let mut high: isize = self.len() as isize;
        while high - low > 1 {
            let mid = (low + high) / 2;
            match self[mid as usize].cmp(x) {
                Ordering::Less | Ordering::Equal => {
                    low = mid;
                }
                Ordering::Greater => {
                    high = mid;
                }
            }
        }
        high as usize
    }
}

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

fn pow_m(a: usize, e: usize, m: usize) -> usize {
    if e == 0 {
        return 1;
    }

    if e % 2 == 0 {
        let half = pow_m(a, e / 2, m);
        return half * half % m;
    }

    a * pow_m(a, e - 1, m) % m
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
