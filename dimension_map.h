#include <string>
#include <cmath>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
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