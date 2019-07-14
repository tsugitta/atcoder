// https://atcoder.jp/contests/abc116/tasks/abc116_b

#[allow(unused)]
use std::cmp::{max, min};
#[allow(unused)]
use std::collections::HashSet;
#[allow(unused)]
use std::collections::VecDeque;
use std::io;
use std::io::{BufRead, Read, Write};
use std::str::FromStr;

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let s: usize = io.next();

    let mut cur = s;
    let mut used: HashSet<usize> = HashSet::new();
    used.insert(cur);

    let mut res = 1;
    loop {
        res += 1;
        cur = if cur % 2 == 0 { cur / 2 } else { 3 * cur + 1 };

        if used.contains(&cur) {
            break;
        }

        used.insert(cur);
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
}

/* Structure helpers */

trait IteratorExt: Iterator + Sized {
    fn vec(self) -> Vec<Self::Item> {
        self.collect()
    }
}

impl<T: Iterator> IteratorExt for T {}
