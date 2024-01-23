#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include<algorithm>
#include <chrono>
#include <ctime>
#include <typeinfo> 
#include <unordered_map>
#include <cmath>
#include <typeinfo>
using namespace std;
#include <iostream>
#include <utility>
#include "dimension_map.h"
// 구간을 나타내는 Pair
typedef pair<int, int> Interval;
bool is_satno_in_any_interval( const std::vector<Interval>& intervals, int value) ;

enum ShapeType {
        UNKNOWN,
        CYL,
        CYL_1_NOZZLE,
        OCT_CYL,
        HEX_CYL,
        BOX_1_PAN,
        BOX_2_PAN,
        BOX_3_PAN,
        BOX_4_PAN,
        BOX_2_ANT,
        BOX_2_PAN_1_DISH,
        BOX_2_PAN_1_ANT,
        HEX_CYL_2_PAN_1_DISH,
        BOX_1_PAN_1_ANT,
        BOX,
        SPHERE,
        CONE,
        SPHERE_CYL,
        CYL_CONE,
        CYL_2_PAN,
        CYL_4_PAN,
        HEX_CYL_1_PAN,
        HEX_CYL_2_PAN,
        HEX_CYL_3_PAN,
        HALF_HEX_CYL_2_PAN,
        TRAP_CYL_2_PAN,
        BOX_1_SAIL,
        BOX_1_ANT,
        BOX_1_ROD,
        CYL_1_ANT,
        HALF_CONE_1_ROD
    };

const map<string, ShapeType> ShapeMap = {
        {"Unknown", UNKNOWN},//1
        {"Cyl", CYL},
        {"Cyl + 1 Nozzle", CYL_1_NOZZLE},
        {"Oct Cyl", OCT_CYL},
        {"Hex Cyl", HEX_CYL},
        {"Box + 1 Pan", BOX_1_PAN},//2
        {"Box + 2 Pan", BOX_2_PAN},
        {"Box + 3 Pan", BOX_3_PAN},
        {"Box + 4 Pan", BOX_4_PAN},
        {"Box + 2 Ant", BOX_2_ANT},
        {"Box + 2 Pan + 1 Dish", BOX_2_PAN_1_DISH},
        {"Box + 2 Pan + 1 Ant", BOX_2_PAN_1_ANT},
        {"Hex Cyl + 2 Pan + 1 Dish", HEX_CYL_2_PAN_1_DISH},
        {"Box + 1 Pan + 1 Ant", BOX_1_PAN_1_ANT},
        {"Box", BOX},//3
        {"Sphere", SPHERE},//4
        {"Cone", CONE},//5
        {"Sphere + Cyl", SPHERE_CYL},//6
        {"Cyl + Cone", CYL_CONE},
        {"Cyl + 2 Pan", CYL_2_PAN},//7
        {"Cyl + 4 Pan", CYL_4_PAN},
        {"Half Hex Cyl + 2 Pan", HALF_HEX_CYL_2_PAN},
        {"Hex Cyl + 1 Pan", HEX_CYL_1_PAN},
        {"Hex Cyl + 2 Pan", HEX_CYL_2_PAN},
        {"Hex Cyl + 3 Pan", HEX_CYL_3_PAN},
        {"Trap Cyl + 2 Pan", TRAP_CYL_2_PAN},//8
        {"Box + 1 Sail", BOX_1_SAIL},
        {"Box + 1 Ant", BOX_1_ANT},//9
        {"Box + 1 Rod", BOX_1_ROD},
        {"Cyl + 1 Ant", CYL_1_ANT},
        
        {"Half Cone + 1 Rod", HALF_CONE_1_ROD},
    };
unordered_map<int, DimensionMap> make_dimension_map(const string& dimension_file_path, const vector<Interval>& intervals);
double calculate_radius(const DimensionMap dimension);
double calculate_pc_max(double dca, double hbr);
string convert_vector_to_string(const vector<string> &elements, char delimiter);
vector<string> convert_line_to_vector(const string &unsplitted_line, char delimiter) ;
