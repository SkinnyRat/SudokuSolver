
## C++11 Sudoku Solver System Design 
<br>

#### [1] SYSTEM DESCRIPTION 


The main aim of this project is to take an existing but somewhat dated C++ solution to solving Sudoku puzzles (originally written by incumbent Singapore Prime Minister Lee Hsien Loong) and updating it to use modern and idiomatic C++14. This project doesn't aim to improve or otherwise modify the underlying algorithm applied in solving the Sudoku puzzles, rather it aims to ensure that the program design adopts an object-oriented memory-safe approach, as well as to ensure the inputs/outputs are well-guarded against malformed data. 

The user interface will be kept simple - an unsolved (incomplete) Sudoku puzzle will be fed in from an ASCII text file with a prescribed format, and the program will output the solved (completed) Sudoku puzzle on the standard output stream. Currently the program expects the text file name to be specified in the code and displays user-friendly error messages should the file contents not be formatted according to the expected format. This program also offers a function to convert puzzles stored on a single line to the format used in the program. 

<br>
 
#### [2] APPLICATION FEATURES 


The following features will be the focus of this implementation: 
- Object-oriented organization 
- STL data containers 
- Guarded inputs/outputs 
- Automated unit testing 
- Multi-threaded support 
- No-throw exception safety 

The usage of templates and inheritance/polymorphism are not required in this design model. 

<img src="https://cloud.githubusercontent.com/assets/13679090/16379504/76ccf2f6-3ca4-11e6-9282-7ab19d35c34f.png" width="720">

The following command line arguments are provided, where the name of the program is "main": 
- ./main test => Perform unit testing. 
- ./main safe => Check that the puzzles are valid. 
- ./main fast => Solve the puzzles in multi-threaded mode. 

If no arguments are specified, the program will assume the given puzzles are valid and solve them in single-threaded mode. The program is also able to print out solver statistics but this option is turned off by default. 

<br>
 
#### [3] PROGRAM TESTING  


The system-level unit-testing for this project will use CppUnitLite and will place a greater focus on the inputs/outputs and checking that the program can handle various cases of improperly-formatted data, and not so much on the underlying algorithm, which is assumed to be correct. The minimal testing will be applied to the algorithm itself to verify that it works and that there are no memory leaks or out-of-bound array elements; other edge cases will not be tested. 

Single-threaded execution for 10,000 & 20,000 puzzles: <br/> 

| MODE   | 10,000 Take 1   | 10,000 Take 2   | 20,000 Take 1   | 20,000 Take 2 |
| ---    | ---             | ---             | ---             | ---           |
| REAL   | 0m 3.295s       | 0m 3.348s       | 0m 6.591s       | 0m 6.661s     |
| USER   | 0m 2.083s       | 0m 2.169s       | 0m 4.166s       | 0m 4.232s     |
| SYS    | 0m 0.633s       | 0m 0.590s       | 0m 1.252s       | 0m 1.245s     |

<img src="https://cloud.githubusercontent.com/assets/13679090/17644374/51e5874a-61b7-11e6-8bfa-ee7efaa0d07e.png" width="720">


Multi-threaded  execution for 10,000 & 20,000 puzzles: <br/> 

| MODE   | 10,000 Take 1   | 10,000 Take 2   | 20,000 Take 1   | 20,000 Take 2 |
| ---    | ---             | ---             | ---             | ---           |
| REAL   | 0m 2.349s       | 0m 2.429s       | 0m 4.601s       | 0m 4.656s     |
| USER   | 0m 2.836s       | 0m 2.854s       | 0m 5.624s       | 0m 5.633s     |
| SYS    | 0m 0.622s       | 0m 0.646s       | 0m 1.229s       | 0m 1.232s     |

<img src="https://cloud.githubusercontent.com/assets/13679090/17644375/55811cca-61b7-11e6-858f-89a53f2a95ee.png" width="720">
<img src="https://cloud.githubusercontent.com/assets/13679090/17644376/55dc9c6c-61b7-11e6-8c90-aa38110cc78f.png" width="720">

<br>
 
#### [4] DESIGN STRATEGY 


The algorithm layout looks suitable to be organized into 2 groups - 1 group to handle the file I/O, and 1 group to handle the actual puzzle-solving. Where necessary, STL containers (e.g. std::vector, std::stringstream) will be used in place of the existing C-style arrays, and pre-existing global data members from the original program will be encapsulated in the class definition. Operators may be overloaded as needed where helpful in handling I/O streaming operations. 

In terms of Exception safety, the goal is to have no exceptions thrown during the execution of the critical parts of the program (optional parts like file format conversion or unit testing are not scrutinized for exception safety). In these parts the usage of STL components that don't throw or are explicitly marked 'noexcept' is maximized, and usage of STL components that do throw is carefully guarded if the possible exceptions that can arise come from program bugs rather than unforseen circumstances; e.g. std::string::erase() throws std::out_of_range if index > size(). 

All other sources of possible exceptions in this program stem from either having not enough memory (e.g. std::vector::reserve(), std::make_unique, std::string) or some other serious system error (e.g. std::thread, std::mutex), and offering exception safety in these regards involve testing the system in addition to testing the program. Each Sudoku object requires at most 900*sizeof(int) bytes of memory, and also if the std::string allocations for each object don't exceed 400 bytes, an x86-64 Linux system with 4 GB free RAM that's not running any other userspace processes should be able to handle up to 1,000,000 puzzles without throwing any exceptions within the program's lifetime. 

<br>

Original Version Source [MIT Licence] : http://bit.ly/1zAXbua 

CNN Article: http://edition.cnn.com/2015/05/06/asia/singapore-pm-code-sudoku/ 

Sample Puzzles From: https://projecteuler.net/problem=96 and http://www.printable-sudoku-puzzles.com/wfiles/ 



