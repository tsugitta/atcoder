// https://atcoder.jp/contests/abc115/tasks/abc115_c

#[allow(unused)]
use std::cmp::{max, min};
#[allow(unused)]
use std::collections::{HashSet, VecDeque};
use std::io;
use std::io::{BufRead, Read, Write};
use std::str::FromStr;

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let N: usize = io.next();
    let K: usize = io.next();
    let mut hs: Vec<usize> = io.nexts(N);

    hs.sort();

    let res = (0..N - K + 1).map(|i| hs[i + K - 1] - hs[i]).min().unwrap();

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
