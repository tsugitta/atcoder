#[snippet = "FenwickTree"]
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

#[test]
fn test_fenwick_tree() {
    let mut bit = fenwick_tree::FenwickTree::new(5, 0);

    bit.add(0, 1);
    bit.add(1, 2);
    bit.add(2, 3);
    bit.add(4, 4);

    assert_eq!(bit.sum_one(2), 3);
    assert_eq!(bit.sum(1, 3), 5);
    assert_eq!(bit.sum(0, 5), 10);
}
