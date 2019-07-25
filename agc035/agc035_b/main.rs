#[allow(unused)]
use std::cmp::{max, min};
use std::collections::HashSet;
use std::collections::VecDeque;
use std::io;
use std::io::{BufRead, Read, Write};
use std::str::FromStr;

fn create_minimum_spanning_tree(N: usize, edges: &Vec<Vec<usize>>) -> Vec<Vec<usize>> {
    let mut non_checked: VecDeque<usize> = VecDeque::new();
    non_checked.push_back(1);

    let mut added: HashSet<usize> = HashSet::new();
    added.insert(1);

    let mut res: Vec<Vec<usize>> = vec![vec![]; N + 1];

    while non_checked.len() > 0 {
        let par = non_checked.pop_front().unwrap();
        let next_edges = &edges[par];

        for child in next_edges {
            if added.contains(child) {
                continue;
            }

            res[par].push(*child);
            added.insert(*child);
            non_checked.push_back(*child);
        }
    }

    res
}

#[allow(unused, non_snake_case)]
pub fn solve<R: BufRead, W: Write>(mut io: Io<R, W>) {
    let N: usize = io.next();
    let M: usize = io.next();

    if M % 2 == 1 {
        io.println(-1);
        return;
    }

    let mut edgeMat = vec![vec![false; N + 1]; N + 1];
    let mut edges = vec![vec![]; N + 1];

    for i in 1..M {
        let a: usize = io.next();
        let b: usize = io.next();
        edgeMat[a][b] = true;
        edgeMat[b][a] = true;
        edges[a].push(b);
        edges[b].push(a);
    }

    let mut min_edges = create_minimum_spanning_tree(N, &edges);
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
