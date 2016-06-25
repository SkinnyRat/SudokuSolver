#include "Sudoku.h" 


void Sudoku::SolverInit(int i, int j, int val) 
{
    auto Square              = 9*i+j; 
    auto valbit              = 1<<val; 
    auto SeqPtr2             = SeqPtr; 
    
    GridValues[Square]       =  val; 
    Entry[Square]            =  valbit; 
    Block[InBlock[Square]]  &= ~valbit; 
    Col[j]                  &= ~valbit; 
    Row[i]                  &= ~valbit; 
    
    while (SeqPtr2 < 81 && Sequence[SeqPtr2] != Square) 
    {
        SeqPtr2++; 
    } 
    
    SolverSwap(SeqPtr, SeqPtr2); 
    SeqPtr++; 
}


void Sudoku::SolverSwap(int S1, int S2) 
{
	auto temp       = Sequence[S2]; 
    Sequence[S2]    = Sequence[S1]; 
    Sequence[S1]    = temp; 
}


int  Sudoku::SolverNext(int S) 
{
    auto S2 = 0, Square = 0, Possibles = 0, BitCount = 0, MinBitCount = 100; 

    for (auto T = S; T < 81; T++) 
    {
        Square      = Sequence[T]; 
        Possibles   = Block[InBlock[Square]] & Row[InRow[Square]] & Col[InCol[Square]]; 
        BitCount    = 0; 
        
        while (Possibles) 
        {
            Possibles &= ~(Possibles & -Possibles); 
            BitCount++; 
        }
        if (BitCount < MinBitCount) 
        {
            MinBitCount = BitCount; 
            S2 = T; 
        }
    }    
    return S2; 
}


int  Sudoku::SolverPlace(int S) 
{
    LevelCount[S]++;
    Count++;
    
    if (S >= 81) 
    {
        Solved++; 
        if (!MANY) IOPrint(OUTPUT); 
        
        return (1); 
    }
    
    auto    S2               = SolverNext(S); 
    SolverSwap(S, S2); 
    
    auto    Square           = Sequence[S], 
         	BlockIndex       = InBlock[Square], 
            RowIndex         = InRow[Square], 
            ColIndex         = InCol[Square], 
         	Possibles        = Block[BlockIndex] & Row[RowIndex] & Col[ColIndex]; 
    
    while (Possibles) 
    {
        auto valbit          = Possibles & (-Possibles);                        // Lowest 1 bit in Possibles. 
        Possibles           &= ~valbit; 
        Entry[Square]        =  valbit; 
        Block[BlockIndex]   &= ~valbit; 
        Row[RowIndex]       &= ~valbit; 
        Col[ColIndex]       &= ~valbit; 
        
        SolverPlace(S+1); 
        
        Block[BlockIndex]   |= valbit; 
        Row[RowIndex]       |= valbit; 
        Col[ColIndex]       |= valbit; 
    } 
    
    //SolverSwap(S, S2); 
    return (0); 
}


bool Sudoku::SolverSane(std::ostream & OUT, const std::vector<int> & RawData)
{
    if (RawData.size() < 81)
    {
        OUT << "Error: Vector used for sanity checking is invalid." << std::endl; 
        return false; 
    }
    
    std::vector<int> RDigits, CDigits, BDigitsA, BDigitsB, BDigitsC; 
    
    RDigits.resize(10);     CDigits.resize(10); 
    BDigitsA.resize(10);    BDigitsB.resize(10);    BDigitsC.resize(10); 
        
    for (auto i=0; i<9; i++)
    {
        // Checking rows & columns for repeated numbers. 
        for (auto j=1; j<10; j++)
        {            
            RDigits[RawData[(9*i+(j-1))]]++; 
            CDigits[RawData[(i+(j-1)*9)]]++; 
        } 
        
        // Checking boxes for repeated numbers. 
        if (!(i%3))
        {
            for (auto j=1; j<4; j++) 
            {
                for (auto k=0; k<3; k++) 
                {
                    BDigitsA[RawData[(i*9)+((j-1)*9)+(k+0)]]++; 
                    BDigitsB[RawData[(i*9)+((j-1)*9)+(k+3)]]++; 
                    BDigitsC[RawData[(i*9)+((j-1)*9)+(k+6)]]++; 
                }
            } 
        }            
        
        for (auto k=1; k<10; k++)
        { 
            if (RDigits[k] > 1)
            {
                OUT << "Error: Repeated '" << k << "'s on Row " << (i+1) << "." << std::endl; 
                return false; 
            }
            if (CDigits[k] > 1)
            {
                OUT << "Error: Repeated '" << k << "'s on Col " << (i+1) << "." << std::endl; 
                return false; 
            } 
            RDigits[k] = 0; 
            CDigits[k] = 0; 
            
            if (!(i%3)) 
            {
                if (BDigitsA[k] > 1)
                {
                    OUT << "Error: Repeated '" << k << "'s in Box " << (i+1) << "." << std::endl; 
                    return false; 
                }
                if (BDigitsB[k] > 1)
                {
                    OUT << "Error: Repeated '" << k << "'s in Box " << (i+2) << "." << std::endl; 
                    return false; 
                }
                if (BDigitsC[k] > 1)
                {
                    OUT << "Error: Repeated '" << k << "'s in Box " << (i+3) << "." << std::endl; 
                    return false; 
                }
                BDigitsA[k] = 0; 
                BDigitsB[k] = 0; 
                BDigitsC[k] = 0; 
            }
        }
    }
    
    return true; 
}


