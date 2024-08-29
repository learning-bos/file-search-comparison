use std::fs::File;
use std::io::{self, BufRead, BufReader, BufWriter, Write};
use std::path::Path;
use std::time::Instant;

fn main() -> io::Result<()> {
    let search_word = "pianissimo";
    let file_locations = [
        "../text/big-end.txt",
        "../text/big-middle.txt",
        "../text/big-start.txt",
    ];

    let file = File::create("rust-results.csv")?;
    let mut file = BufWriter::new(file);
    writeln!(file, "end,middle,start")?;

    for _ in 0..100 {
        for (idx, &location) in file_locations.iter().enumerate() {
            let duration = search_word_in_file(location, search_word);

            if idx > 0 {
                write!(file, ",")?;
            }
            write!(file, "{:.4}", duration)?;
        }
        writeln!(file)?;
    }

    Ok(())
}

fn search_word_in_file(file_path: &str, search_word: &str) -> f64 {
    let path = Path::new(file_path);
    let start = Instant::now();

    let file = File::open(&path).unwrap();
    let reader = BufReader::new(file);

    for line in reader.lines() {
        if let Ok(line) = line {
            if line.contains(&search_word) {
                break;
            }
        }
    }
    start.elapsed().as_micros() as f64 / 1000.0
}