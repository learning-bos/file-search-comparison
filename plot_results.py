import pandas as pd
import matplotlib.pyplot as plt

# File paths of the CSVs
csv_files = ["./rust/rust-results-optmized-no-lowercase.csv" ,"./go/go-results.csv", "./rust/rust-results-non-optimized.csv", "./cpp/cpp-results.csv"]

# List to store the data from the first column of each CSV
data_to_plot = []

# Read each CSV and extract the first column
for file in csv_files:
    df = pd.read_csv(file)  # Read the CSV file into a DataFrame
    first_column = df.iloc[:, 0]  # Extract the first column
    data_to_plot.append(first_column)  # Add it to the list

# Create a boxplot
plt.figure(figsize=(10, 6))  # Set the figure size
plt.boxplot(data_to_plot)  # Plot the boxplot
plt.xlabel("Languages used")  # Set the x-axis label
plt.ylabel("milliseconds")  # Set the y-axis label
plt.title("100 tries for each with needle in the end")  # Set the title
plt.xticks([1, 2, 3, 4], ["Rust optimized", "GO", "Rust", "C++"])  # Set x-axis ticks and labels

# Show the plot
plt.show()
