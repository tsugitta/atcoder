// https://atcoder.jp/contests/abc115/tasks/abc115_d

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

fn get_res(n: usize, x: usize, layers: Vec<usize>, patties: Vec<usize>) -> usize {
    if n == 0 {
        return x;
    }

    if x == 1 {
        0
    } else if x <= 1 + layers[n - 1] {
        get_res(n - 1, x - 1, layers, patties)
    } else if x == 2 + layers[n - 1] {
        1 + patties[n - 1]
    } else if x <= 2 + 2 * layers[n - 1] {
        1 + patties[n - 1] + get_res(n - 1, x - 2 - layers[n - 1], layers, patties)
    } else {
        1 + 2 * patties[n - 1]
    }
}

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let input = io.read_all();
    input! {
        source = input,
        N: usize,
        X: usize,
    }

    let mut layers = vec![0; N + 1];

    for i in (0..layers.len()) {
        layers[i] = match i {
            0 => 1,
            _ => 2 * layers[i - 1] + 3,
        }
    }

    let mut patties = vec![0; N + 1];

    for i in (0..patties.len()) {
        patties[i] = match i {
            0 => 1,
            _ => 2 * patties[i - 1] + 1,
        }
    }

    let res = get_res(N, X, layers, patties);

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
