fn main() {
    let stdin = std::io::read_to_string(std::io::stdin()).unwrap();
    let mut stdin = stdin.split_whitespace();

    let n: usize = stdin.next().unwrap().parse().unwrap();
    let s = stdin.next().unwrap();

    let mut cnt = 0;
    for c in s.chars() {
        if c != 'o' {
            break;
        }
        cnt += 1;
    }

    println!("{}", &s[cnt..]);
}