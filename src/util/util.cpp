#include "util.hpp"
#include "../logging.hpp"
#include "directory_manager.hpp"

#include <math.h>

double my_angle(double x1, double y1, double x2, double y2){
    if(x1 == 0 && y1 ==0){
        return 0;
    }
    double angle1 = atan2(y1,x1);
    double angle2 = atan2(y2,x2);
    
    
    return angle2-angle1;
}

double angleBetweenPI2(double a){
    double angle = a;
    if(a>3.14/2){
        angle = angle-3.14;
    }
    if(angle>3.14/2){
        angle = angle-3.14;
    }
    if(angle < -3.14/2){
        angle = angle+3.14;
    }
    if(angle < -3.14/2){
        angle = angle+3.14;
    }
    return angle;
}

bool isNotEqualDoubles2 (double a, double b, double epsilon)
{
   double diff = a - b;
   INFO(diff << " " << epsilon);
   return (diff > epsilon) || (diff < -epsilon);
}

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream


std::string execute2(std::string cmd){
    std::string file = DirectoryManager::Instance().getBinDirectory() + "/tmp_cmd";
    std::string cmd2 = cmd + " > " + file;
    system(cmd2.c_str());
    std::ifstream infile(file);
    std::stringstream strStream;
    strStream << infile.rdbuf();//read the file
    std::string res = strStream.str();
    return res;
};
