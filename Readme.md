
### C++11 Sudoku Solver System Design 
<br>

[1] SYSTEM DESCRIPTION 


The main aim of this project is to take an existing but somewhat dated C++ solution to solving Sudoku puzzles (written incumbent Singapore Prime Minister Lee Hsien Loong) and updating it to use modern and idiomatic C++11. This project doesn't aim to improve or otherwise modify the underlying algorithm applied in solving the Sudoku puzzles, rather it aims to ensure that the program design adopts an object-oriented memory-safe approach, as well as to ensure the inputs/outputs are well-guarded against malformed data. 

The user interface will be kept simple - an unsolved (incomplete) Sudoku puzzle will be fed in from an ASCII text file with a prescribed format, and the program will output the solved (completed) Sudoku puzzle on the standard output stream. Currently the program will expect the text file name to be predefined (i.e. users can't specify the file name yet) and display user-friendly (I hope...) error messages should the file contents not be formatted according to the expected format. 

<br>
 
[2] APPLICATION FEATURES 


The following features will be the focus of this implementation: 
- Object-oriented approach 
- STL data structures 
- Guarded inputs/outputs 
- Automated unit testing 
- Multi-threaded support (coming soon) 
- Exception-safe execution (coming soon) 

<br>
 
[3] TEST REQUIREMENTS 


The system-level testing for this project will place a greater focus on the inputs/outputs and checking that the program can handle various cases of improperly-formatted data, and not so much on the underlying algorithm, which is assumed to be correct. The minimal testing will be applied to the algorithm itself to verify that it works and that there are no memory leaks, and edge cases, performance, etc. will not be tested. 

User acceptance testing would (in the case of an actual field test) focus on user-friendliness, in particular ease of use of the program as well as convenience of preparing the data with the expected file format. Automated unit testing doesn't look like it can significantly benifit this manner of testing though, so no unit testing will be applied towards such user acceptance testing. 

<br>
 
[4] INITIAL DESIGN STRATEGY 


The current program layout looks suitable to be grouped into 2 classes - 1 class to handle the file I/O, and 1 class to handle the actual puzzle-solving. Where necessary, STL containers (e.g. std::vector, std::stringstream) will be used in place of the existing C-style arrays, and existing global data members will be encapsulated in the respective classes. Operators will be overloaded as needed where helpful in handling I/O streaming operations. 

<br>
 
Original Version Source [MIT Licence] : http://bit.ly/1zAXbua 

CNN Article: http://edition.cnn.com/2015/05/06/asia/singapore-pm-code-sudoku/ 


