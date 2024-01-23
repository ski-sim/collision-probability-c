
#include "maximum_collision_probability_module.cpp"
/*
INPUT : 
1. dimension csv 파일
2. PPDB2.txt

OUTPUT : 
    output.txt file (DCA, Pcmax)
*/
int main() {
    string dimension_file_path = "./dimension/dimension.csv";
    vector<Interval> intervals = { {1, 30000}, {40000,50000} };

    unordered_map<int, DimensionMap> total_sat_dimension = make_dimension_map(dimension_file_path, intervals);

    int primary_satno = 44713;
    int secondary_satno = 47647;
    double dca = 528.414 / 1000;
    double primary_radius;
    double secondary_radius;

    if (!is_satno_in_any_interval(intervals, primary_satno) || !is_satno_in_any_interval(intervals, secondary_satno)) {
        cerr << "Error: satno is not within any interval." << endl;
        return 0;
    }

    primary_radius = calculate_radius(total_sat_dimension[primary_satno]);
    secondary_radius = calculate_radius(total_sat_dimension[secondary_satno]);
    double hbr = primary_radius + secondary_radius;
    double pc_max = calculate_pc_max(dca, hbr);
    cout << "primary radius : "<<primary_radius << endl;
    cout << "secondary radius : "<<secondary_radius << endl;
    cout << "maximum collision probability : "<<pc_max << endl;
        
   
    
    return 0;

}

