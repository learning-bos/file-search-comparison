# file-search-comparison
Haystack search in 1MB file and 54MB file in GO, Rust, C++
We have three different files. In each of these file we have placed a needle that needs to be retrieved at the end of file.
This is the result

![Image representing the boxplot of the 100 tries for each language](results-end-needle.png)

GO seems like the winner but the fact that it takes so little compared to language like C++ and Rust makes me wonder what magic are they actually using.
