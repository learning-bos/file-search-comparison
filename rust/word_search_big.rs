use std::fs::File;
use std::io::Write;
use std::io::{self, BufRead};
use std::path::Path;
use std::time::Instant;

fn search_word_in_file(file_path: &str, search_word: &str) -> f64 {
    let path = Path::new(file_path);
    let start = Instant::now();

    let file = match File::open(&path) {
        Ok(file) => file,
        Err(_) => {
            println!("Failed to open file: {}", file_path);
            let nanos = start.elapsed().subsec_nanos();// Total nanoseconds
            let fractional_millis = nanos as f64 / 1_000_000.0;

            return fractional_millis
        }
    };

    let reader = io::BufReader::new(file);

    for line in reader.lines() {
        if let Ok(line) = line {
            if line.to_lowercase().contains(&search_word.to_lowercase()) {
                break;
            }
        }
    }

    let nanos = start.elapsed().subsec_nanos();// Total nanoseconds
    let fractional_millis = nanos as f64 / 1_000_000.0;

    return fractional_millis;
}

fn main() -> std::io::Result<()> {
    let search_word = "pianissimo";
    let file_locations = ["../text/big-end.txt", "../text/big-middle.txt", "../text/big-start.txt"];

    // Open a file in write-only mode, creates the file if it doesn't exist
    let mut file = File::create("rust-results.csv")?;
    
    // header
    writeln!(file, "end,middle,start")?;

    for _i in 0..100 {
        for location in file_locations.iter() {
            let duration = search_word_in_file(location, search_word);
            if *location == "../text/big-start.txt" {
                writeln!(file, "{:.4}", duration)?;
            } else {
                write!(file, "{:.4},", duration)?;
            }
        }
    }
    Ok(())
}