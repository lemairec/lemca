#ifndef UTIL_H
#define UTIL_H

#include "environnement.hpp"
#include <fstream>
#include <memory>
#include <list>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>

double my_angle(double x1, double y1, double x2, double y2);
double angleBetweenPI2(double a);
bool isNotEqualDoubles2 (double a, double b, double epsilon);
std::string execute2(std::string cmd);

#endif //UTIL_H
