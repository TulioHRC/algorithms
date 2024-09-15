use std::time::Instant;

fn factorial(mut n: usize) -> usize {
    let mut result = 1;

    while n > 0 {
        result *= n;
        n -= 1;
    }

    return result;
}

fn main() {
    let factorial_of_20: usize = factorial(20);
    println!("Factorial of 20: {}", factorial_of_20);

    let factorial_number = 20;
    let mut iterations = 100_000_000;

    let start = Instant::now();

    while iterations != 0 {
        let _ = factorial(factorial_number);
        iterations -= 1;
    }

    let duration = start.elapsed();

    println!("Time taken: {:?}", duration);
}
