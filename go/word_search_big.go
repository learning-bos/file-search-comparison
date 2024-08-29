package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strings"
	"time"
)

func searchWordInFile(filePath string, word string) (float64, error) {
	file, err := os.Open(filePath)
	if err != nil {
		fmt.Println("Unable to open file:", filePath)
		return 0, errors.New("Unable to open file")
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	y := 0
	start := time.Now()

	for scanner.Scan() {
		y++
		if strings.Contains(scanner.Text(), word) {
			break
		}
	}

	duration := time.Since(start)

	//fmt.Printf("Time taken: %v milliseconds.\n", duration.Seconds()*1000)
	//fmt.Printf("%v,", duration.Seconds()*1000)
	return duration.Seconds() * 1000, nil
}

func saveExperimentToCSV(word string) {
	// Create or open a file for writing
	file, err := os.Create("go-results.csv")
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close() // Ensure the file is closed after writing

	// HEADER
	_, err = fmt.Fprintf(file, "end,middle,start\n")
	if err != nil {
		fmt.Println("Error writing to file:", err)
		return
	}

	for i := 0; i < 100; i++ {
		endTime, _ := searchWordInFile("../text/big-end.txt", word)
		middleTime, _ := searchWordInFile("../text/big-middle.txt", word)
		startTime, _ := searchWordInFile("../text/big-start.txt", word)

		_, err = fmt.Fprintf(file, "%v,%v,%v\n", endTime, middleTime, startTime)
	}

	fmt.Println("Data successfully written to file.")
}

func main() {
	word := "pianissimo"
	saveExperimentToCSV(word)
}
