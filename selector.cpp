//
//  selector.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 05-06-18.
//

#include "selector.hpp"
#include <initializer_list>

Selector::Selector()
{
}

Selector::~Selector()
{
    
    
}

void Selector::selector(int signal)
{
    selectedInput = signal;
    std::cout << selectedInput << std::endl;
}


double Selector::process(std::vector<double>& a_args)
{
    return a_args[selectedInput];
}
