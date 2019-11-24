use std::cmp::{max, min, Ordering};

#[snippet = "UnionFind"]
pub struct UnionFind {
    parents: Vec<isize>,
}

#[snippet = "UnionFind"]
impl UnionFind {
    pub fn new(size: usize) -> UnionFind {
        UnionFind {
            // for children, the value is its parent index. for root, the value is -1 * the size of the group
            parents: vec![-1; size],
        }
    }

    pub fn root(&mut self, x: usize) -> usize {
        match self.parents[x].cmp(&0) {
            Ordering::Less => x,
            _ => {
                let root = self.root(self.parents[x] as usize);
                self.parents[x] = root as isize;
                root
            }
        }
    }

    pub fn same(&mut self, x: usize, y: usize) -> bool {
        self.root(x) == self.root(y)
    }

    pub fn merge(&mut self, x: usize, y: usize) {
        let (x_root, y_root) = (self.root(x), self.root(y));

        if x_root == y_root {
            return;
        }

        // make less index one as a root
        let new_root = min(x_root, y_root);
        let new_child = max(x_root, y_root);

        self.parents[new_root] += self.parents[new_child];
        self.parents[new_child] = x_root as isize;
    }

    pub fn size(&mut self, x: usize) -> usize {
        let root = self.root(x);
        -self.parents[root] as usize
    }

    pub fn group_count(&self) -> usize {
        self.parents.iter().filter(|&&r| r < 0).count()
    }
}

#[test]
fn test_union_find() {
    let mut uf = UnionFind::new(5);
    assert_eq!(uf.group_count(), 5);

    uf.merge(0, 1);
    assert_eq!(uf.same(0, 1), true);
    assert_eq!(uf.root(1), 0);
    assert_eq!(uf.root(0), 0);

    uf.merge(1, 2);
    assert_eq!(uf.root(2), 0);
    assert_eq!(uf.size(2), 3);
    assert_eq!(uf.group_count(), 3);
}
