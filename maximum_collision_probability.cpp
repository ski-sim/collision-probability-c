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
unordered_map<int, DimensionMap> make_dimension_map(const string& dimension_file_path, vector<SatnoInterval> satno_ranges);
double calculate_radius(const DimensionMap dimension);
double calculate_pc_max(double dca, double hbr);
string convert_vector_to_string(const vector<string> &elements, char delimiter);
vector<string> convert_line_to_vector(const string &unsplitted_line, char delimiter) ;

bool is_value_in_any_interval(std::vector<SatnoInterval> intervals, int value) {
    for (SatnoInterval interval : intervals) {
        if (interval.is_in_interval(value)) {
            return true;
        }
    }
    return false;
}
/*
INPUT : 
1. dimension csv 파일
2. PPDB2.txt

OUTPUT : 
    output.txt file (DCA, Pcmax)
*/
int main() {
    const int start_satno = 1;
    const int end_satno = 99999;
    string dimension_file_path = "./dimension/dimension.csv";
    string ppdb_file_path = "./PPDB2.txt"; 
    std::vector<SatnoInterval> satno_ranges = {
        SatnoInterval(1, 100), SatnoInterval(100, 200)
        // 추가적인 구간이 있다면 여기에 계속 추가
    };
    unordered_map<int, DimensionMap> total_sat_dimension = make_dimension_map(dimension_file_path, satno_ranges);

    ofstream out_file("./output/PPDB_pc.txt"); // 출력 파일 생성
    if (!out_file.is_open()) {
        cerr << "출력 파일을 열 수 없습니다." << endl;
        return 1;
    }
    ifstream ppdb_file(ppdb_file_path);
    if (!ppdb_file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << ppdb_file_path << endl;
        return 1;
    }

    string line;
    int i =0;
    while (getline(ppdb_file, line)) {

        if (i >=6){
            stringstream ss_line(line);
            string element;
            int primary_satno;
            int secondary_satno;
            double dca ;
            if (getline(ss_line, element, '\t')) {
                 primary_satno = stoi(element);
                
            }
            if (getline(ss_line, element, '\t')) {
                secondary_satno = stoi(element);
                
            }
            if (getline(ss_line, element, '\t')) {
                dca= stod(element)/1000;
                
            }
            double primary_radius = calculate_radius(total_sat_dimension[primary_satno]);
            double secondary_radius = calculate_radius(total_sat_dimension[secondary_satno]);
            double hbr = primary_radius + secondary_radius;
            double pc_max = calculate_pc_max(dca, hbr) ;

            vector<string> tokens = convert_line_to_vector(line, '\t');
            tokens.back() = to_string(pc_max);
            string modified_line = convert_vector_to_string(tokens, '\t');
            out_file << modified_line << endl; 
            cout << modified_line << endl; 

        }
        i++;
        if(i>=20){
            break;
        }
    }
    return 0;

}

double calculate_pc_max(double dca, double hbr){//calculate_pc_max
    const double AR = 3.0;  //reference : Alfano, S., “Relating Position Uncertainty to Maximum Conjunction Probability,
    double sd_max = dca / sqrt(2); //reference : Berend, N., "Estimation of the Probability of Collision Between Two Catalogued Orbiting Objects, " Advances in Space Research,
    double pc_max = exp(-pow(dca, 2) / (2 * pow(sd_max, 2))) * (1 - exp(-AR * pow(hbr, 2) / (2 * pow(sd_max, 2))));// reference : L.Chen.Orbital Data Applications for Space Object, Springer, China, p215
    return pc_max;
}

/*
INPUT : 
1. dimension csv 파일
2. start Satno
3. end Satno
OUTPUT : 
total_sat_dimension (type = unordered_map) :   {key : satno (type=string), value : single_sat_dimension (type=DimensionMap)}
*/
unordered_map<int, DimensionMap> make_dimension_map(const string& dimension_file_path, vector<SatnoInterval> satno_ranges) {
    
    ifstream file(dimension_file_path);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return {};
    }

    string line;
    unordered_map<string, int> column_names; // 열 이름과 인덱스 매핑
    int column_index = 0;

    // 첫 번째 줄을 먼저 처리합니다.
    if (getline(file, line)) {
        stringstream ss_line(line);
        string element;

        while (getline(ss_line, element, ',')) {
            column_names[element] = column_index++;
        }
    }
    
    int current_satno = 0;
    unordered_map<int, DimensionMap> total_sat_dimension;
    
    // 이제 파일의 나머지 줄을 처리합니다.
    while (getline(file, line)) {
        stringstream ss_line(line);
        string element;
        vector<string> row;
        DimensionMap single_sat_dimension; // 특정 satno의 dimension 정보를 담은 map

        while (getline(ss_line, element, ',')) {
            row.push_back(element);
        }

        current_satno = stoi(row[column_names["satno"]]);

        
        if (is_value_in_any_interval(satno_ranges, current_satno)) {
            single_sat_dimension.set_shape(row[column_names["shape"]]);
            single_sat_dimension.set_span(row[column_names["span"]]);
            single_sat_dimension.set_diameter(row[column_names["diameter"]]);
            single_sat_dimension.set_height(row[column_names["height"]]);
            single_sat_dimension.set_width(row[column_names["width"]]);
            single_sat_dimension.set_depth(row[column_names["depth"]]);
            total_sat_dimension[current_satno] = single_sat_dimension;
        }

        
    }
    file.close();

    return total_sat_dimension;
};

/*
1. Nasa hbr 계산식 (참고 : Hejduk.Johnson, Evaluating Probability of Collision Uncertainty,p28)
1) Cyl + 2 Pan의 경우에 대해 radius를 계산하는 방법을 소개함.
2) object의 dimension을 모두 포함할 수 있는 직사각형의 대각선을 반지름으로 설정함.

2. CalculateRadius function
1) Cyl + 2 Pan 포함 총 30가지 shape에 대해 계산식을 분류해서 적용함.
2) object의 dimension을 모두 포함할 수 있는 직사각형의 대각선을 반지름으로 설정함.
3) 자세한 내용은 워드파일로 정리되어있음.
*/
double calculate_radius(DimensionMap single_sat_dimension) {
    double radius = 0;
    DimensionMap dimension = single_sat_dimension;

    ShapeType shape;
    auto shape_it = ShapeMap.find(dimension.get_shape());
    if (shape_it != ShapeMap.end()) {
        shape = shape_it->second; 
    }
    else{
        shape= UNKNOWN;
    }


    double maxDimension = 0;
    switch (shape) {

        case CYL: case CYL_1_NOZZLE: case OCT_CYL: case HEX_CYL:
            if (dimension.check_diameter_height()) {
                double height = dimension.get_height();
                double diameter = dimension.get_diameter();
                radius = sqrt(pow(diameter, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case BOX_1_PAN: case BOX_2_PAN: case BOX_3_PAN: case BOX_4_PAN: case BOX_2_ANT: \
        case BOX_2_PAN_1_DISH: case BOX_2_PAN_1_ANT: case HEX_CYL_2_PAN_1_DISH: case BOX_1_PAN_1_ANT:
            if (dimension.check_span_height()) {
                double height = dimension.get_height();
                double span = dimension.get_span();
                radius = sqrt(pow(span, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case BOX:
            if (dimension.check_depth_width_height()) {
                double height = dimension.get_height();
                double width = dimension.get_width();
                double depth = dimension.get_depth();
                double x = max(width, depth);
                radius = sqrt(pow(x, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case SPHERE:
            radius = dimension.get_max_dimension();
            break;

        case CONE:
            if (dimension.check_diameter_height()) {
                double height = dimension.get_height();
                double diameter = dimension.get_diameter();
                radius = sqrt(pow(diameter, 2) + pow(height, 2)) / 2;
            }
            else if (dimension.check_depth_width_height()) {
                double height = dimension.get_height();
                double width = dimension.get_width();
                double depth = dimension.get_depth();
                double x = max(width, depth);
                radius = sqrt(pow(x, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case SPHERE_CYL: case CYL_CONE:
            if (dimension.check_diameter_height()) {
                double height = dimension.get_height();
                double diameter = dimension.get_diameter();
                radius = sqrt(pow(diameter, 2) + pow(height, 2)) / 2;
            }
            else if (dimension.check_diameter_span()) {
                double span = dimension.get_span();
                double diameter = dimension.get_diameter();
                radius = sqrt(pow(diameter, 2) + pow(span, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case CYL_2_PAN: case CYL_4_PAN: case HEX_CYL_1_PAN: case HEX_CYL_2_PAN: case HEX_CYL_3_PAN: case HALF_HEX_CYL_2_PAN:
        case TRAP_CYL_2_PAN: case BOX_1_SAIL:
            if (dimension.check_span_height()) {
                double height = dimension.get_height();
                double span = dimension.get_span();
                radius = sqrt(pow(span, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;


        case BOX_1_ANT: case BOX_1_ROD: case CYL_1_ANT:
            if (dimension.check_depth_width_span()) {
                double width = dimension.get_width();
                double depth = dimension.get_depth();
                double span = dimension.get_span();
                double x = max(width, depth);
                radius = sqrt(pow(x, 2) + pow(span, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        default:
            radius = 1;
    }
    radius = radius / 1000; 
    return radius;
}

vector<string> convert_line_to_vector(const string &unsplitted_line, char delimiter) {
    vector<string> vector_line;
    string element;
    istringstream tokenStream(unsplitted_line);
    while (getline(tokenStream, element, delimiter)) {
        vector_line.push_back(element);
    }
    return vector_line;
}

string convert_vector_to_string(const vector<string> &elements, char delimiter) {
    ostringstream joined_element;
    for (size_t i = 0; i < elements.size(); ++i) {
        joined_element << elements[i];
        if (i < elements.size() - 1) {
            joined_element << delimiter;
        }
    }
    return joined_element.str();
}