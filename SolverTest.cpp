#include <iostream> 
#include <sstream> 
#include <cstring>

#include "TestHarness.h" 
#include "Sudoku.h" 


TEST(InputTest, CppUnitLite)
{ 
    std::stringstream Out, Out1, Out2; 
    std::string Line, Message; 
    
    
    // Default sample file where everything is expected to be OK. 
    
    Sudoku S("Sample.txt", Out, false); 
    while(std::getline(Out, Line)) 
    { 
        if (Line.find("Count") != std::string::npos) 
            Message = Line; 
    } 
    CHECK_EQUAL(Message, "Count = 14890"); 
    
    
    // Sample file with incomplete lines or delimeters between characters. 
    
    Sudoku S1("SampleBad1.txt", Out1, true); 
    S1.IOFile(Out1); 
    while(std::getline(Out1, Line)) 
    { 
        if (Line.find("Line") != std::string::npos) 
            Message = Line; 
    } 
    CHECK_EQUAL(Message, "Line 8 incomplete or mal-formatted."); 
    
    
    // Sample file with excess data or otherwise no valid solution. 
    
    Sudoku S2("SampleBad2.txt", Out2, true); 
    S2.IOFile(Out2); 
    Out2.str(""); 
    
    S2.IOStats(Out2); 
    CHECK_EQUAL(Out2.str(), "\nNo solution found.\n\n"); 
}


