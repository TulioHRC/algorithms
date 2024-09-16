use std::time::Instant;
use std::hint::black_box;

fn factorial_aux(n: usize, acc: usize) -> usize {
    if n == 1 { return acc; }
    return factorial_aux(n - 1, acc * n);
}

fn factorial(n: usize) -> usize {
    return factorial_aux(n, 1);
}

fn main() {
    let factorial_of_20: usize = factorial(20);
    println!("Factorial of 20: {}", factorial_of_20);

    let mut factorial_number = String::new();
    std::io::stdin()
        .read_line(&mut factorial_number)
        .expect("Failed to read line!");

    let factorial_number : usize = factorial_number.trim().parse().expect("Type a number please.");
    let mut iterations : u64 = 500_000_000;

    let start = Instant::now();

    while iterations != 0 {
        let value = factorial(factorial_number);
        black_box(value); // Prevent the optimizer from removing this
        iterations -= 1;
    }

    let duration = start.elapsed();

    println!("Time taken: {:?}", duration);
}
