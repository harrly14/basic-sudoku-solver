# Log 1 - 9/27
- found data and importing kaggle data set
- learned stringstream and array and fstream libraries a little more
    - didn't end up using stringstream or the array library at all
- improved data manipulation skills
- screwed up my git connection a bunch, but eventually corrected it

the code: 
- open file, go through lines to selected puzzle
- grab appropriate numbers
- convert string to int array
- print the int array 
- format the printed grid 

# Log 2 - 10/29
At the start of this dev log, I had a program that could simply take in a sudoku puzzle and print it out. By the end of this devlog, I will have a working Sudoku solver. After not working on the project in a couple weeks, I came back to find some half-baked code attempting to validate digits. The first thing I did was clear that out and start from scratch when it comes to solving the puzzle. Then, I took a sec to look over Sudoku solving algorithms and found this Wikipedia page: https://en.wikipedia.org/wiki/Sudoku_solving_algorithms. Backtracking seemed the simplest, so I decided to try that and attempt the other algorithms afterwards if I felt like it. I think it would be cool to compare the speed of different algorithms, but there are also other projects I want to work on so I may not get around to actually doing that. 

Anyways, I tried writing out my backtracking algorithm as pseudocode and as flowcharts, but was still struggling with how to actually do the backtracking part. I tabled this issue for now, and decided to spend my time making the digit validation, which seemed much simpler. I built that out with some simple logic, by simply going through all the digits in the row, column, and box and checking if they were equal to the digit I was trying. With that complete, I was able to turn my sights towards backtracking.

I was still not sure how to backtrack when I put in a wrong digit, but decided that was a problem for future-me and got to work writing. I put some basic logic in place for when we should go to the next row and when we should stop the algorithm, then got stuck. I knew that I had to only run the algorithm when the position didn't have a digit in that, so I wrote the if statement for that, but didn't know what to put inside it. At first, I put all the algorithm logic inside that loop so that it would only run when the position was empty, but I still got had no idea how to implement backtracking. 

I decided that bashing my head against the wall was a bad approach and that I should go back to doing more research. I found some youtube videos explaining backtracking a little more and heard the concept of recursion more and more, which scared me because recursion seems so complicated and easy to mess up. Regardless, I also watched some quick Python tutotials building similar algorithms and decided that recursion is what I would have to do, since I could think of any other way to do it. The key insight I got from the Python tutorial I watched, was that their backtracking seemed to look forward rather than backwards. I was struggling with how I would know the previous digit that I changed so that I could go back and change it again if need be, but the tutorial showed me that instead of looking backwards, I should run the function recursively and have it try to complete the next digit and the next digit and so on until it couldn't any more. Once it could not, I knew I had to change the digit I was currently on. This was (and still is) so cool to me, but I definately would not have figured it out on my own. If there is any part of this code that is the least mine, I would say its the loop that says: 

if (backtracking(grid, row, col + 1)){
                return true;
            } 

This was the key piece I was missing, and once I had it, it was smooth sailing. I did some minor optimizations and changed things around a little bit to be more readable and I was done! I had a working sudoku solver! Just for fun, I also added in a clock so that you can see how long the algorithm takes to solve the sudoku puzzles. Next on the docket I have: 
- input validation on the file -- if you can open it and it has the right number of values
- optimization/cleanup
- gui? I would love to see the backtracking algorithm actually work in real time
- other solving algorithms
- comparing and analyzing the time it takes to each algorithm to solve different quantities of puzzles. Is one significantly more efficient?