//
//  selector.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 05-06-18.
//


//NOT IMPLEMENTED JET!!

#ifndef selector_hpp
#define selector_hpp

#include <stdio.h>
#include <iostream>
#include <initializer_list>
#include <vector>

class Selector
{
public:
    Selector();
    ~Selector();
    void selector(int signal);
    double process(std::vector<double>& a_args);
    double getOutput();
    int selectedInput = 0;
private:
    int numberofinputs;
};
#endif /* selector_hpp */
