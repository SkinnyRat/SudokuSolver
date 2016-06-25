#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <cstdlib> 
#include <cstring> 
#include <vector> 
#include <sstream>


class Sudoku
{
public:    
    Sudoku() : Sudoku("Sample.txt") { } 
    ~Sudoku()  { } 
    
    Sudoku(const std::string & Filename, std::ostream & OUT = std::cout, bool TEST = false, bool MANY = false, bool MODE = 0) 
        : File(Filename), 
          MANY(MANY), 
          MODE(MODE), 
          ONES(0x03FE), 
          SeqPtr(0), 
          Solved(0), 
          Count(0), 
          TotalCount(0), 
          OUTPUT(OUT) 
    { 
        InBlock.resize(81);      InRow.resize(81);      InCol.resize(81); 
        Block.resize(9);         Row.resize(9);         Col.resize(9); 
        LevelCount.resize(81);   Sequence.resize(81);   Entry.resize(81); 
        
        auto Square = 0; 
        for (auto i = 0; i < 9; i++)
        {
            for (auto j = 0; j < 9; j++) 
            {
                Square              = 9*i+j; 
                Sequence[Square]    = Square; 
                InRow[Square]       = i; 
                InCol[Square]       = j; 
                InBlock[Square]     = (i/3)*3+(j/3);             
            } 
            Block[i] = Row[i] = Col[i] = ONES; 
        } 
        
        GridValues.resize(81); 
        
        if (!MANY)
        { 
            if (!TEST)
            { 
                if (IOFile(OUTPUT))
                { 
                    Start(); 
                } 
                IOStats(OUTPUT); 
                TotalCount += Count; 
            }
        }
    }
    
    inline bool Check() 
    { 
        return SolverSane(OUTPUT, GridValues); 
    } 
    void Start() 
    { 
        if (MODE == 1) 
        {
            if (Check()) SolverPlace(SeqPtr);  
        }
        else 
        {
            SolverPlace(SeqPtr); 
        } 
    } 
    
    // In file Solver.cpp     
    void SolverInit (int i,  int j,  int val); 
    void SolverSwap (int S1, int S2); 
    int  SolverNext (int S); 
    int  SolverPlace(int S);     
    bool SolverSane (std::ostream & OUT, const std::vector<int> & RawData); 
    
    // In file IO.cpp 
    bool IOMany (std::ostream & OUT, std::ifstream & Input); 
    bool IOFile (std::ostream & OUT); 
    void IOPrint(std::ostream & OUT); 
    void IOStats(std::ostream & OUT); 
    
    Sudoku(const Sudoku &)                = delete; 
    Sudoku & operator=(const Sudoku &)    = delete; 
    
private: 
    const std::string File; 
    const int MANY, MODE, ONES; 
    int   SeqPtr, Solved, Count, TotalCount; 
    
    std::ostream & OUTPUT; 
    
    std::vector<int> GridValues; 
	std::vector<int> InBlock,      InRow,      InCol; 
    std::vector<int> Block,        Row,        Col;                             // Each int is a 9-bit array. 
    std::vector<int> LevelCount,   Sequence,   Entry;                           // Records entries 1-9 in the grid, has the corresponding bit set to 1. 
};




