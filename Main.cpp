#include "TestHarness.h" 
#include "Sudoku.h" 

int main()
{
    // Random number generator used in some tests. 
    srand(::time_t(NULL));        
    
    Sudoku sudoku; 
    
    TestResult tr; 
    TestRegistry::runAllTests(tr);     
    return 0;
}

