#include "Sudoku.h" 


bool Sudoku::IOFile(std::ostream & OUT) 
{
    OUT << std::endl << "Sudoku puzzle input from file '" << File << "': " << std::endl; 
    std::fstream Input; 
    std::string  Line; 
    
    Input.open(File, std::fstream::in); 
    if (Input.fail() || !Input.is_open())
    {
        OUT << "Unable to read file... =( " << std::endl; 
        return false; 
    }
    
    auto ch = '-';     
    for (auto i = 0; i < 9; i++) 
    {
        Input >> Line; 
        if (Input.eof() || Line.length() < 9)
        {
            OUT << "Line " << (i+1) << " incomplete or mal-formatted." << std::endl; 
            return false; 
        }
        for (auto j = 0; j < 9; j++) 
        {
            ch = Line[j]-'0'; 
            if (ch >= 1 && ch <= 9) 
            { 
                SolverInit(i, j, ch); 
            }
        }
    }    
    IOPrint(OUT); 
    
    Input.close(); 
    return true; 
}


void Sudoku::IOPrint(std::ostream & OUT) 
{
    auto valbit = 0, Square = 0, OK = Solved; 
    if (OK) 
    {
        OUT << std::endl << "Solution: " << std::endl; 
    } 
    
    for (auto i = 0; i < 9; i++) 
    {
        if (i > 0 && i%3 == 0) 
        {
            OUT << std::endl; 
        }
        for (auto j = 0; j < 9; j++) 
        {
            if (j % 3 == 0) 
            {
                OUT << " "; 
            }
            valbit = Entry[Square++]; 
            
            if (valbit == 0) 
            {
                OUT << "-"; 
            }
            else 
            {
                for (auto v = 1; v <= 9; v++) 
                {
                    if (valbit == (1<<v)) 
                    {
                        if (OK) 
                        {
                            GridValues[Square-1] = v; 
                        } 
                        OUT << v; 
                        break; 
                    }
                }
            }
        }
        OUT << std::endl; 
    }
}


void Sudoku::IOStats(std::ostream & OUT) 
{
    if (Solved)
    {
        if (!SolverSane(OUT, GridValues))
        {
            return; 
        }
    }
    else
    {
        OUT << std::endl << "No solution found." << std::endl << std::endl; 
        return; 
    }
    
    OUT << std::endl << "Level Counts: " << std::endl; 
    
    auto S = 0, Seq = 0, i = 0;     
    while (LevelCount[S] == 0 && S < 100) 
    {
        S++; 
    }    
    while (S < 81) 
    {
        Seq = Sequence[S]; 
        OUT << " (" << (Seq/9+1) << "," << (Seq%9+1) << "):";
        OUT << std::setfill(' ') << std::setw(4) << LevelCount[S] << "  "; 
        
        S++; 
        if (i++ > 4)
        {
            OUT << std::endl; 
            i = 0; 
        }        
    }
    OUT << std::endl << "Count = " << Count << std::endl << std::endl; 
}


