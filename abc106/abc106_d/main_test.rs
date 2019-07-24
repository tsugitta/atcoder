mod main;
use std::fs::File;
use std::io::Read;
extern crate serde_yaml;
#[macro_use]
extern crate serde_derive;

#[derive(Debug, PartialEq, Deserialize)]
struct Case {
    r#in: String,
    out: String,
}

fn main() {}

#[allow(unused)]
fn get_cases() -> Vec<Case> {
    let mut file = File::open("test.yaml").expect("Unable to open test.yaml");
    let mut contents = String::new();

    file.read_to_string(&mut contents)
        .expect("Unable to read test.yaml");

    serde_yaml::from_str(&contents).unwrap()
}

#[test]
fn test_solve() {
    let cases = get_cases();

    for case in cases {
        let input = case.r#in.as_bytes();
        let mut output = Vec::new();

        let io = main::Io {
            reader: &input[..],
            writer: &mut output,
        };

        main::solve3(io);

        let output = String::from_utf8(output).expect("Not UTF-8");
        assert_eq!(output, case.out);
    }
}
