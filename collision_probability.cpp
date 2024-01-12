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
using namespace std;

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
        string shape;
        string span;
        string diameter;
        string height;
        string width;
        string depth;
    public:
        void SetShape(string sat_shape){
            shape = sat_shape;
        }
        void SetSpan(string sat_span){
            span = sat_span;
        }
        void SetDiameter(string sat_diameter){
            diameter = sat_diameter;
        }
        void SetHeight(string sat_height){
            height = sat_height;
        }
        void SetWidth(string sat_width){
            width = sat_width;
        }
        void SetDepth(string sat_depth){
            depth = sat_depth;
        }
        string GetShape(){
            return shape;
        }
        string GetSpan(){
            return span;
        }
        string GetDiameter(){
            return diameter;
        }
        string GetHeight(){
            return height;
        }
        string GetWidth(){
            return width;
        }
        string GetDepth(){
            return depth;
        }
        bool CheckDiameterHeight(){
            if (!diameter.empty() && !height.empty()){
                    return true;
                }else{
                    return false;
                }
        }
        bool CheckSpanHeight(){
            if (!span.empty() && !height.empty()){
                    return true;
                }else{
                    return false;
                }
        }
        bool CheckDepthWidthHeight(){
            if (!depth.empty() && !width.empty() && !height.empty()) {
                    return true;
                }else {
                    return false;
                }
        }
        bool CheckDiameterSpan(){
            if (!diameter.empty() && !span.empty()) {
                    return true;
                }else {
                    return false;
                }
        }
        bool CheckDepthWidthSpan(){
            if (!depth.empty() && !width.empty() && !span.empty()) {
                    return true;
                }else {
                    return false;
                }
        }
        double GetMaxDimension(){
            double my_diameter = diameter.empty() ? 0.0 : stod(diameter);
            double my_width = width.empty() ? 0.0 : stod(width);
            double my_depth = depth.empty() ? 0.0 : stod(depth);
            double my_height = height.empty() ? 0.0 : stod(height);
            double max_dimension = max({my_diameter, my_width, my_depth, my_height});
            if (max_dimension > 0){
                return max_dimension;
            }else{
                return 1;
            }
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
unordered_map<string, DimensionMap> MakeDimensionMap(const string& dimension_file_path, const int& start_satno, const int& end_satno);
double CalculateRadius(const DimensionMap dimension);
double CalculatePcMax(double dca, double hbr);
string ConvertVectorToString(const vector<string> &elements, char delimiter);
vector<string> ConvertLinetoVector(const string &unsplitted_line, char delimiter) ;

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
    unordered_map<string, DimensionMap> total_sat_dimension = MakeDimensionMap(dimension_file_path, start_satno, end_satno);

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
            string primary_satno;
            string secondary_satno;
            double dca ;
            if (getline(ss_line, element, '\t')) {
                 primary_satno = element;
                
            }
            if (getline(ss_line, element, '\t')) {
                secondary_satno = element;
                
            }
            if (getline(ss_line, element, '\t')) {
                dca= stod(element)/1000;
                
            }
            double primary_radius = CalculateRadius(total_sat_dimension[primary_satno]);
            double secondary_radius = CalculateRadius(total_sat_dimension[secondary_satno]);
            double hbr = primary_radius + secondary_radius;
            double pc_max = CalculatePcMax(dca, hbr) ;

            vector<string> tokens = ConvertLinetoVector(line, '\t');
            tokens.back() = to_string(pc_max);
            string modified_line = ConvertVectorToString(tokens, '\t');
            out_file << modified_line << endl; 
            cout << modified_line << endl; 

        }
        i++;
        if(i>=100){
            break;
        }
    }
    return 0;

}

double CalculatePcMax(double dca, double hbr){
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
unordered_map<string, DimensionMap> MakeDimensionMap(const string& dimension_file_path, const int& start_satno, const int& end_satno) {
    
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
    
    int min_satno = start_satno;
    int max_satno = end_satno;
    int current_satno = 0;
    unordered_map<string, DimensionMap> total_sat_dimension;
    
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

        if (current_satno >= min_satno && current_satno <= max_satno) {
            single_sat_dimension.SetShape(row[column_names["shape"]]);
            single_sat_dimension.SetSpan(row[column_names["span"]]);
            single_sat_dimension.SetDiameter(row[column_names["diameter"]]);
            single_sat_dimension.SetHeight(row[column_names["height"]]);
            single_sat_dimension.SetWidth(row[column_names["width"]]);
            single_sat_dimension.SetDepth(row[column_names["depth"]]);

            total_sat_dimension[row[column_names["satno"]]] = single_sat_dimension;
        }

        if (current_satno > max_satno) {
            break;
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
double CalculateRadius(DimensionMap single_sat_dimension) {
    double radius = 0;
    DimensionMap dimension = single_sat_dimension;

    ShapeType shape;
    auto shape_it = ShapeMap.find(dimension.GetShape());
    if (shape_it != ShapeMap.end()) {
        shape = shape_it->second; 
    }
    else{
        shape= UNKNOWN;
    }


    double maxDimension = 0;
    switch (shape) {

        case CYL: case CYL_1_NOZZLE: case OCT_CYL: case HEX_CYL:
            if (dimension.CheckDiameterHeight()) {
                double height = stod(dimension.GetHeight());
                double diameter = stod(dimension.GetDiameter());
                radius = sqrt(pow(diameter, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case BOX_1_PAN: case BOX_2_PAN: case BOX_3_PAN: case BOX_4_PAN: case BOX_2_ANT: \
        case BOX_2_PAN_1_DISH: case BOX_2_PAN_1_ANT: case HEX_CYL_2_PAN_1_DISH: case BOX_1_PAN_1_ANT:
            if (dimension.CheckSpanHeight()) {
                double height = stod(dimension.GetHeight());
                double span = stod(dimension.GetSpan());
                radius = sqrt(pow(span, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case BOX:
            if (dimension.CheckDepthWidthHeight()) {
                double height = stod(dimension.GetHeight());
                double width = stod(dimension.GetWidth());
                double depth = stod(dimension.GetDepth());
                double x = max(width, depth);
                radius = sqrt(pow(x, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case SPHERE:
            radius = dimension.GetMaxDimension();
            break;

        case CONE:
            if (dimension.CheckDiameterHeight()) {
                double height = stod(dimension.GetHeight());
                double diameter = stod(dimension.GetDiameter());
                radius = sqrt(pow(diameter, 2) + pow(height, 2)) / 2;
            }
            else if (dimension.CheckDepthWidthHeight()) {
                double height = stod(dimension.GetHeight());
                double width = stod(dimension.GetWidth());
                double depth = stod(dimension.GetDepth());
                double x = max(width, depth);
                radius = sqrt(pow(x, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case SPHERE_CYL: case CYL_CONE:
            if (dimension.CheckDiameterHeight()) {
                double height = stod(dimension.GetHeight());
                double diameter = stod(dimension.GetDiameter());
                radius = sqrt(pow(diameter, 2) + pow(height, 2)) / 2;
            }
            else if (dimension.CheckDiameterSpan()) {
                double span = stod(dimension.GetSpan());
                double diameter = stod(dimension.GetDiameter());
                radius = sqrt(pow(diameter, 2) + pow(span, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case CYL_2_PAN: case CYL_4_PAN: case HEX_CYL_1_PAN: case HEX_CYL_2_PAN: case HEX_CYL_3_PAN: case HALF_HEX_CYL_2_PAN:
        case TRAP_CYL_2_PAN: case BOX_1_SAIL:
            if (dimension.CheckSpanHeight()) {
                double height = stod(dimension.GetHeight());
                double span = stod(dimension.GetSpan());
                radius = sqrt(pow(span, 2) + pow(height, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;


        case BOX_1_ANT: case BOX_1_ROD: case CYL_1_ANT:
            if (dimension.CheckDepthWidthSpan()) {
                double width = stod(dimension.GetWidth());
                double depth = stod(dimension.GetDepth());
                double span = stod(dimension.GetSpan());
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


vector<string> ConvertLinetoVector(const string &unsplitted_line, char delimiter) {
    vector<string> vector_line;
    string element;
    istringstream tokenStream(unsplitted_line);
    while (getline(tokenStream, element, delimiter)) {
        vector_line.push_back(element);
    }
    return vector_line;
}

string ConvertVectorToString(const vector<string> &elements, char delimiter) {
    ostringstream joined_element;
    for (size_t i = 0; i < elements.size(); ++i) {
        joined_element << elements[i];
        if (i < elements.size() - 1) {
            joined_element << delimiter;
        }
    }
    return joined_element.str();
}