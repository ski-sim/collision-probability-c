#include "maximum_collision_probability.h"

/*
INPUT : dca (distance at close approach), hbr (hard-body radius)
OUPUT : pc_max (maximum collsiion probability)
*/
double calculate_pc_max(const double& dca, const double& hbr){
    const double ar = 3.0;  //reference : Alfano, S., “Relating Position Uncertainty to Maximum Conjunction Probability,
    double sd_max = dca / sqrt(2); //reference : Berend, N., "Estimation of the Probability of Collision Between Two Catalogued Orbiting Objects, " Advances in Space Research,
    double pc_max = exp(-pow(dca, 2) / (2 * pow(sd_max, 2))) * (1 - exp(-ar * pow(hbr, 2) / (2 * pow(sd_max, 2))));// reference : L.Chen.Orbital Data Applications for Space Object, Springer, China, p215
    return pc_max;
}

/*
INPUT : interval vector, satno
OUPUT : true or false
*/
bool is_satno_in_any_interval(const std::vector<Interval>& intervals,const int& satno) {
    for (const auto& interval : intervals) {
        if (satno >= interval.first && satno <= interval.second) {
            return true; 
        }
    }
    return false;
}

/*
INPUT : dimension csv파일,  interval vector,
OUPUT : map_from_satno_to_dimensions (type = unordered_map, key = satno, value = single_sat_dimension_map (type=DimensionMap)}
*/
unordered_map<int, DimensionMap> make_dimension_map(const string& dimension_csv_file_path, const vector<Interval>& intervals) {
    
    ifstream file(dimension_csv_file_path);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return {};
    }

    string line;
    unordered_map<string, int> column_names; 
    int column_index = 0;

    // 첫 번째 줄의 열이름을 먼저 읽음
    if (getline(file, line)) {
        stringstream ss_line(line);
        string element;

        while (getline(ss_line, element, ',')) {
            column_names[element] = column_index++;
        }
    }
    
    int current_satno = 0;
    unordered_map<int, DimensionMap> map_from_satno_to_dimensions;
    
    // 두번째 줄 부터 시작
    while (getline(file, line)) {
        stringstream ss_line(line);
        string element;
        vector<string> row;
        DimensionMap single_sat_dimension; // 특정 satno의 dimension 정보를 담은 map

        while (getline(ss_line, element, ',')) {
            row.push_back(element);
        }

        current_satno = stoi(row[column_names["satno"]]);
   
        if (is_satno_in_any_interval(intervals, current_satno)) {
            single_sat_dimension.set_shape(row[column_names["shape"]]);
            single_sat_dimension.set_span(row[column_names["span"]]);
            single_sat_dimension.set_diameter(row[column_names["diameter"]]);
            single_sat_dimension.set_height(row[column_names["height"]]);
            single_sat_dimension.set_width(row[column_names["width"]]);
            single_sat_dimension.set_depth(row[column_names["depth"]]);

            map_from_satno_to_dimensions[current_satno] = single_sat_dimension;
        }

    }
    file.close();

    return map_from_satno_to_dimensions;
};

/*
1. Nasa HBR 계산식 (참고 : Hejduk.Johnson, Evaluating Probability of Collision Uncertainty,p28)
1) Cyl + 2 Pan의 경우에 대해 radius를 계산하는 방법을 소개함.
2) 총 3가지 방법론을 제시하였음. 그중 2번째 방법론 사용

2. calculate_radius function
1) 총 30가지 shape에 대해 계산식을 달리 적용함.
2) object의 횡방향, 종방향 dimension을 포함하는 직사각형의 대각선을 반지름으로 설정함.
3) 자세한 내용은 워드파일로 정리되어있음.

INPUT : DimensionMap
OUPUT : radius of single object
*/
double calculate_radius(const DimensionMap& single_sat_dimension) {
    double radius = 0;
    DimensionMap dimension = single_sat_dimension;

    ShapeType shape;
    auto shape_it = map_from_string_to_shape_map.find(dimension.get_shape());
    if (shape_it != map_from_string_to_shape_map.end()) {
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
        case BOX_2_PAN_1_DISH: case BOX_2_PAN_1_ANT: case HEX_CYL_2_PAN_1_DISH: case BOX_1_PAN_1_ANT:\
        case CYL_2_PAN: case CYL_4_PAN: case HEX_CYL_1_PAN: case HEX_CYL_2_PAN: case HEX_CYL_3_PAN: case HALF_HEX_CYL_2_PAN:\
        case TRAP_CYL_2_PAN: case BOX_1_SAIL: case HALF_CONE_1_ROD:
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

        case CYL_1_ANT:
            if (dimension.check_diameter_span()){
                double span = dimension.get_span();
                double diameter = dimension.get_diameter();
                radius = sqrt(pow(diameter, 2) + pow(span, 2)) / 2;
            }else { 
                radius = 1; 
            }
            break;

        case BOX_1_ANT: case BOX_1_ROD: 
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

/*
INPUT : line (type = string)
OUPUT : line (type = vector)
*/
vector<string> convert_line_to_vector(const string &unsplitted_line, char delimiter) {
    vector<string> vector_line;
    string element;
    istringstream tokenStream(unsplitted_line);
    while (getline(tokenStream, element, delimiter)) {
        vector_line.push_back(element);
    }
    return vector_line;
}

/*
INPUT : line (type = vector)
OUPUT : line (type = string)
*/
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