use std::cmp::Ordering;

#[snippet = "BinarySearch"]
pub trait BinarySearch<T> {
    fn lower_bound(&self, x: &T) -> usize;
    fn upper_bound(&self, x: &T) -> usize;
}

#[snippet = "BinarySearch"]
impl<T: Ord> BinarySearch<T> for [T] {
    fn lower_bound(&self, x: &T) -> usize {
        let mut low: isize = -1;
        let mut high: isize = self.len() as isize;

        // result exists in (low, high]
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

        // result exists in (low, high]
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

#[test]
fn test_binary_search() {
    let vec = vec![1, 2, 4, 6, 7, 12, 54, 60];

    assert_eq!(vec.lower_bound(&4), 2);
    assert_eq!(vec.upper_bound(&4), 3);
    assert_eq!(vec.upper_bound(&100), vec.len());
}
