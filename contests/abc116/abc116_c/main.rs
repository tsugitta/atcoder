// https://atcoder.jp/contests/abc116/tasks/abc116_c

#[allow(unused)]
use std::cmp::{max, min, Ordering};
#[allow(unused)]
use std::collections::{HashSet, VecDeque};
use std::io;
use std::io::{BufRead, Read, Write};
use std::str::FromStr;

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let N: usize = io.next();
    let mut hs: Vec<usize> = io.nexts(N);

    let mut res = 0;

    loop {
        let mut in_has_height_range = false;
        let mut mutated_ct = 0;

        for (i, h) in hs.iter_mut().enumerate() {
            if *h > 0 {
                *h -= 1;
                in_has_height_range = true;
            } else if *h == 0 && in_has_height_range {
                mutated_ct += 1;
                in_has_height_range = false;
            }
        }

        if in_has_height_range {
            mutated_ct += 1;
        }

        if mutated_ct == 0 {
            break;
        } else {
            res += mutated_ct;
        }
    }

    io.println(res);
}

// more functional way
#[allow(unused, non_snake_case)]
pub fn solve2<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let N: usize = io.next();
    let mut hs: Vec<usize> = io.nexts(N);

    let mut res = 0;

    loop {
        let mutating_count: usize = hs
            .iter()
            .scan(0, |prev, curr| {
                let was_zero = *prev == 0;
                *prev = *curr;

                if was_zero && *curr > 0 {
                    Some(1)
                } else {
                    Some(0)
                }
            })
            .sum();

        hs = hs.iter().map(|h| if *h > 0 { *h - 1 } else { 0 }).vec();

        if mutating_count > 0 {
            res += mutating_count
        } else {
            break;
        }
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
    fn println<T: std::fmt::Debug>(&mut self, value: T) {
        writeln!(&mut self.writer, "{:?}", value).expect("Unable to write");
    }

    fn print<T: std::fmt::Debug>(&mut self, value: T) {
        write!(&mut self.writer, "{:?}", value).expect("Unable to write");
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
