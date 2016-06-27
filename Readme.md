
## C++11 Sudoku Solver System Design 
<br>

#### [1] SYSTEM DESCRIPTION 


The main aim of this project is to take an existing but somewhat dated C++ solution to solving Sudoku puzzles (originally written by incumbent Singapore Prime Minister Lee Hsien Loong) and updating it to use modern and idiomatic C++14. This project doesn't aim to improve or otherwise modify the underlying algorithm applied in solving the Sudoku puzzles, rather it aims to ensure that the program design adopts an object-oriented memory-safe approach, as well as to ensure the inputs/outputs are well-guarded against malformed data. 

The user interface will be kept simple - an unsolved (incomplete) Sudoku puzzle will be fed in from an ASCII text file with a prescribed format, and the program will output the solved (completed) Sudoku puzzle on the standard output stream. Currently the program will expect the text file name to be predefined and display user-friendly error messages should the file contents not be formatted according to the expected format. This program also offers a function to convert puzzles stored on a single line to the format used in the program. 

<br>
 
#### [2] APPLICATION FEATURES 


The following features will be the focus of this implementation: 
- Object-oriented organization 
- STL data containers 
- Guarded inputs/outputs 
- Automated unit testing 
- Multi-threaded support 
- Basic Exception safety 

The usage of templates and inheritance/polymorphism are not required in this design model. 

<img src="https://cloud.githubusercontent.com/assets/13679090/16379504/76ccf2f6-3ca4-11e6-9282-7ab19d35c34f.png" width="720">

COMMAND LINE ARGUMENTS. 

The program is also able to print out solver statistics but this option is turned off by default. 

<br>
 
#### [3] PROGRAM TESTING  


The system-level unit-testing for this project will place a greater focus on the inputs/outputs and checking that the program can handle various cases of improperly-formatted data, and not so much on the underlying algorithm, which is assumed to be correct. The minimal testing will be applied to the algorithm itself to verify that it works and that there are no memory leaks or out-of-bound array elements; other edge cases will not be tested. 

PERFORMANCE TESTING GOES HERE. 

<br>
 
#### [4] DESIGN STRATEGY 


The algorithm layout looks suitable to be organized into 2 groups - 1 group to handle the file I/O, and 1 group to handle the actual puzzle-solving. Where necessary, STL containers (e.g. std::vector, std::stringstream) will be used in place of the existing C-style arrays, and pre-existing global data members from the original program will be encapsulated in the class definition. Operators will be overloaded as needed where helpful in handling I/O streaming operations. 

EXCEPTION SAFETY GOES HERE. 

<br>
 
Original Version Source [MIT Licence] : http://bit.ly/1zAXbua 

CNN Article: http://edition.cnn.com/2015/05/06/asia/singapore-pm-code-sudoku/ 


