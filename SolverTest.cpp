#include <iostream> 
#include <sstream> 
#include <cstring> 
#include <cstdio> 

#include "TestHarness.h" 
#include "Sudoku.h" 

TEST(IOTest, CppUnitLite)
{ 
    std::stringstream Out; 
    Sudoku S("Sample.txt", Out, true); 
    
    
    // Test for repeated digits on rows. 
    
    std::vector<int>  Puzzle = 
    {
        0,0,0,0,0,0,0,0,0,
        0,0,3,0,0,3,0,8,5,
        0,0,1,0,2,0,0,0,0,
        0,0,0,5,0,7,0,0,0,
        0,0,4,0,0,0,1,0,0,
        0,9,0,0,0,0,0,0,0,
        5,0,0,0,0,0,0,7,3,
        0,0,2,0,1,0,0,0,0,
        0,0,0,0,4,0,0,0,9 
    }; 
    
    S.SolverSane(Out, Puzzle); 
    CHECK_EQUAL(Out.str(), "Error: Repeated '3's on Row 2.\n"); 
    Out.str(""); 
    
    
    // Test for repeated digits on columns. 
    
    Puzzle = 
    {
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,3,0,8,5,
        0,0,1,0,2,0,0,0,0,
        0,0,0,5,0,7,0,0,0,
        0,0,4,0,0,0,1,0,0,
        0,9,0,0,4,0,0,0,0,
        5,0,0,0,0,0,0,7,3,
        0,0,2,0,1,0,0,0,0,
        0,0,0,0,4,0,0,0,9 
    }; 
    
    S.SolverSane(Out, Puzzle); 
    CHECK_EQUAL(Out.str(), "Error: Repeated '4's on Col 5.\n"); 
    Out.str(""); 
    
    
    // Test for repeated digits in boxes. 
    
    Puzzle = 
    {
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,3,0,8,5,
        0,0,1,0,2,0,0,0,0,
        0,0,0,5,0,7,0,0,0,
        0,0,4,0,0,0,1,0,0,
        0,9,0,0,0,0,0,0,0,
        5,0,0,4,0,0,0,7,3,
        0,0,2,0,1,0,0,0,0,
        0,0,0,0,4,0,0,0,9 
    }; 
    
    S.SolverSane(Out, Puzzle); 
    CHECK_EQUAL(Out.str(), "Error: Repeated '4's in Box 8.\n"); 
    Out.str(""); 
    
    
    // Test of final result based on sample valid solution. 
    //   Taken from: https://projecteuler.net/problem=96 
    
    std::string After = 
        "\nSolution: \n" \
        " 483 921 657\n" \
        " 967 345 821\n" \
        " 251 876 493\n" \
        "\n"             \
        " 548 132 976\n" \
        " 729 564 138\n" \
        " 136 798 245\n" \
        "\n"             \
        " 372 689 514\n" \
        " 814 253 769\n" \
        " 695 417 382\n" ; 
    
    Sudoku T("SampleGood.txt", Out, false); 
    Out.str(""); 
    T.IOPrint(Out); 
    CHECK_EQUAL(Out.str(), After); 
}



