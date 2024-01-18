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
class SatnoInterval{
    private:
        int m_lhs;
        int m_rhs;
    public:
        SatnoInterval(int lhs, int rhs) : m_lhs(lhs), m_rhs(rhs) {}

        inline void set_lhs_rhs(int lhs, int rhs){
            m_lhs = lhs;
            m_rhs = rhs;
        }
        inline int get_lhs(){
            return m_lhs;
        }
        inline int get_rhs(){
            return m_rhs;
        }
        inline bool is_in_interval(int satno){
            return m_lhs < satno  && satno < m_rhs;
        }
        

};
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
        CYL_1_ANT
    };
class DimensionMap{
    private:
        string m_shape;
        double m_span;
        double m_diameter;
        double m_height;
        double m_width;
        double m_depth;
    public:
        inline void set_shape(string sat_shape){
            m_shape = sat_shape;
        }
        inline void set_span(string sat_span){
            m_span = sat_span.empty() ? 0.0 : stod(sat_span);
        }
        inline void set_diameter(string sat_diameter){
            m_diameter = sat_diameter.empty() ? 0.0: stod(sat_diameter);
        }
        inline void set_height(string sat_height){
            m_height = sat_height.empty() ? 0.0 : stod(sat_height);
        }
        inline void set_width(string sat_width){
            m_width = sat_width.empty() ? 0.0 : stod(sat_width);
        }
        inline void set_depth(string sat_depth){
            m_depth = sat_depth.empty() ? 0.0 : stod(sat_depth);
        }
        inline string get_shape(){
            return m_shape;
        }
        inline double get_span(){
            return m_span;
        }
        inline double get_diameter(){
            return m_diameter;
        }
        inline double get_height(){
            return m_height;
        }
        inline double get_width(){
            return m_width;
        }
        inline double get_depth(){
            return m_depth;
        }
        inline bool check_diameter_height(){
            return m_diameter != 0.0 && m_height != 0.0;
        }
        inline bool check_span_height(){
            return m_span!= 0.0 && m_height!= 0.0;
        }
        inline bool check_depth_width_height(){
            return m_depth!= 0.0 && m_width!= 0.0 && m_height!= 0.0;
        }
        inline bool check_diameter_span(){
            return m_diameter!= 0.0 && m_span!= 0.0;
        }
        inline bool check_depth_width_span(){
            return m_depth!= 0.0 && m_width!= 0.0 && m_span!= 0.0;
        }
        inline double get_max_dimension(){
            double diameter = m_diameter!= 0.0 ? 0.0 : m_diameter;
            double width = m_width!= 0.0 ? 0.0 : m_width;
            double depth = m_depth!= 0.0 ? 0.0 : m_depth;
            double height = m_height!= 0.0 ? 0.0 : m_height;
            double max_dimension = max({diameter, width, depth, height});
            return max_dimension > 0 ? max_dimension : 1;
        }


       

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
    };
unordered_map<int, DimensionMap> make_dimension_map(const string& dimension_file_path, const vector<SatnoInterval>& intervals);
double calculate_radius(const DimensionMap dimension);
double calculate_pc_max(double dca, double hbr);
string convert_vector_to_string(const vector<string> &elements, char delimiter);
vector<string> convert_line_to_vector(const string &unsplitted_line, char delimiter) ;
bool is_satno_in_any_interval(std::vector<SatnoInterval> intervals, int value);