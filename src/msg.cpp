#include "msg.hpp"

namespace report 
{

void error (const std::string& msg, const std::string& note)
{
    std::cerr << msg << "\n";
    std::cerr << note << "\n";
    std::cerr << std::endl;
    num_errors++;
}

void summary () 
{
    if (num_errors > 0) 
      {
        std::cerr << "\ntotal number of errors: " << num_errors << '\n';
      }
}

} /* namespace report */