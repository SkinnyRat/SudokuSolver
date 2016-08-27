#include <iostream> 
#include <algorithm> 
#include <thread> 
#include <future> 
#include <chrono> 

#include "TestHarness.h" 
#include "Sudoku.h" 


int FormatFile(std::string FileName); 
int SHandler(std::unique_ptr<Sudoku> SD,                        std::mutex & MLock, bool & Done); 
int VHandler(std::vector< std::unique_ptr<Sudoku> > SudoVector, std::mutex & MLock, bool & Done); 


int main(int argc, char * argv[]) 
{ 
    // Random number generator used in some tests. 
    srand(::time_t(NULL)); 
    
    // Accepted arguments => Default, "safe", "fast", "test". 
    std::vector<std::string> args(argv, argv+argc); 
    std::string command = ""; 
    if (argc>1) command = args[1]; 
    
    if (command == "test")
    {
        TestResult tr; 
        TestRegistry::runAllTests(tr);         
        return (0); 
    } 
    auto MODE = 0; 
    if (command == "safe") MODE = 1; 
    
    // Example usage for single puzzle, with safety checks. 
    // Sudoku sudoku("Sample.txt", std::cout, false, false, 1); 
    
    // Use to covert rows of 81 into matrices of 9x9. 
    // FormatFile("TEMP.txt"); 
    
    std::ifstream Input("SampleGood.txt"); 
    if (Input.fail() || !Input.is_open())
    {
        std::cout << "Unable to read file... =( " << std::endl; 
        return false; 
    }
    std::cout << std::endl << "Sudoku puzzles from file '" << "SampleGood.txt" << "': " << std::endl; 
    
    // Count number of lines in file in order to allocate correct number of class instances. 
    auto Count = std::count(std::istreambuf_iterator<char>(Input), std::istreambuf_iterator<char>(), '\n')/9; 
    Input.seekg(std::ios::beg);     
    
    std::vector< std::unique_ptr<Sudoku> > SudoVector; 
    SudoVector.reserve(Count); 
    
    for (auto i=0; i<(Count); i++)
    {
        SudoVector.push_back(std::make_unique<Sudoku>("", std::cout, false, true, MODE)); 
        SudoVector[i]->IOMany(std::cout, Input); 
    }    
    Input.close(); 
    
    // Multi-threaded solving is performed in this block, and single-threaded solving in the next block. 
    //   If max threads > Count, solve each Sudoku in a separate thread. 
    //   If max threads < Count, pass a subset of Sudokus to be solved in a separate thread. 
    
    if (command == "fast")
    {
        unsigned int MAX = std::thread::hardware_concurrency(); 
        bool Done[MAX]; 
        std::mutex  MLock; 
        std::thread Focks[MAX]; 
        
        if (MAX >= Count)
        {
            for (unsigned int i=0; i<Count; i++)
            {
                Done[i]  = false; 
                Focks[i] = std::thread(SHandler, std::move(SudoVector[i]), std::ref(MLock), std::ref(Done[i])); 
            } 
            for (unsigned int i=0; i<Count; i++)
            {
                while (!Done[i]) std::this_thread::sleep_for(std::chrono::milliseconds(20)); 
                Focks[i].join(); 
            }
        }
        else
        {
            unsigned int block = (Count%MAX<MAX/2) ? (Count/MAX) : (Count/MAX)+1; 
            unsigned int added = 0; 
            
            for (unsigned int i=0; i<MAX; i++)
            {
                std::vector< std::unique_ptr<Sudoku> > Subset; 
                //Subset.reserve(Count/MAX); 
                
                for (unsigned int j=0; j<block && (added+j)<Count; j++) 
                    Subset.push_back(std::move(SudoVector[added+j])); 
                added += block; 
                
                if (added >= (block*MAX) && (Count-added) > 0)
                {
                    for (auto j=added; j<Count; j++) 
                        Subset.push_back(std::move(SudoVector[j])); 
                }
                
                Done[i]  = false; 
                Focks[i] = std::thread(VHandler, std::move(Subset), std::ref(MLock), std::ref(Done[i])); 
            }
            for (unsigned int i=0; i<MAX; i++)
            {
                while (!Done[i]) std::this_thread::sleep_for(std::chrono::milliseconds(20)); 
                Focks[i].join(); 
            }
        }
    }
    else
    { 
        for (auto i=0; i<(Count); i++)
        {
            SudoVector[i]->Start(); 
            SudoVector[i]->IOPrint(std::cout); 
            //SudoVector[i]->IOStats(std::cout); 
        }
    }    
    std::cout << std::endl; 
    
    return (0); 
}


int SHandler(std::unique_ptr<Sudoku> SD, std::mutex & MLock, bool & Done)
{ 
    SD->Start(); 
    MLock.lock(); 
    SD->IOPrint(std::cout); 
    //SD->IOStats(std::cout); 
    MLock.unlock(); 
    Done = true; 
    return (0); 
}


int VHandler(std::vector< std::unique_ptr<Sudoku> > SudoVector, std::mutex & MLock, bool & Done)
{ 
    // std::cout << "%%%% Block size = " << SudoVector.size() << " %%%%" << std::endl; 
    for (unsigned int i=0; i<SudoVector.size(); i++)
    {
        SudoVector[i]->Start(); 
    }
    MLock.lock(); 
    for (unsigned int i=0; i<SudoVector.size(); i++)
    {
        SudoVector[i]->IOPrint(std::cout); 
        //SudoVector[i]->IOStats(std::cout); 
    }
    MLock.unlock(); 
    Done = true; 
    return (0); 
}


int FormatFile(std::string FileName)
{ 
    std::ifstream Input(FileName); 
    if (Input.fail() || !Input.is_open()) 
    {
        std::cout << "Unable to read file... =( " << std::endl; 
        return -1; 
    }    
    std::stringstream buffer;     
    buffer << Input.rdbuf(); 
    Input.close(); 
    
    std::string Text = buffer.str(); 
    //Text.erase(std::remove(Text.begin(), Text.end(), '\n'), Text.end()); 
    
    std::ofstream Output(FileName); 
    if (Output.fail() || !Output.is_open()) 
    {
        std::cout << "Unable to read file... =( " << std::endl; 
        return -1; 
    }
    auto col = 0; 
    for (unsigned int i=0; i<Text.length(); i++) 
    {
        if (Text[i] >= '0' && Text[i] <= '9')
        {
            Output << Text[i]; 
            col++; 
            if (col%9 == 0) Output << std::endl; 
        }
    }
    Output.close(); 
    return (0); 
}



