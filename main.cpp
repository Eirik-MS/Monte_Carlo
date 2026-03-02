
#include <iostream>
#include <random>
#include <vector>
#include <tuple>

#include "cnpy/cnpy.h"

void print_help(char * argv[]);

int main(int argc, char* argv[]) {
    bool save = false;
    int n = 100;
    if (argc >1){
        for (int i = 1; i < argc; i++){
            try
            {
                n =std::stoi(argv[i]);
            }
            catch(const std::exception& e)
            {
                if ((std::string(argv[i]) == "--help") || (std::string(argv[i]) == "-h")){
                    print_help(argv);
                }else if ((std::string(argv[i]) == "--save") || (std::string(argv[i]) == "-s")){
                    save = true;
                } else{
                    std::cout << "Invalid argument" << std::endl;
                    print_help(argv);
                    return 1;
                }
            }  
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    double const min = -1.0f;
    double const max = 1.0f;

    std::uniform_real_distribution<float> distrebution(min, max);

    double x = distrebution(gen);
    double y = distrebution(gen);
    long points_inside = 0;
    long points_total = 0;

    std::vector<double> data; 

    if (n < 1000000){
        for (int i = 0; i < n; i++){
        x = distrebution(gen);
        y = distrebution(gen);
        
        if (x*x + y*y <= 1.0f){
            points_inside++;
            data.push_back(x);
            data.push_back(y);
            data.push_back(1.0); // true
        } else{
            data.push_back(x);
            data.push_back(y);
            data.push_back(0.0); // false
        }
        points_total++;
        }
    } else {
        for (int i = 0; i < n; i++){
        x = distrebution(gen);
        y = distrebution(gen);
        
        if (x*x + y*y <= 1.0f){
            points_inside++;
        }
        points_total++;
        }
    }

    
    
    double pi_estimate = 4.0f * points_inside / points_total;
    std::cout << "Estimated value of pi: " << pi_estimate << std::endl;

    data.insert(data.begin(), (double) pi_estimate);
    data.insert(data.begin(), (double) points_inside);
    data.insert(data.begin(), (double) points_total);

    if (save && !data.empty()){
        cnpy::npy_save("points.npy", data, "w");
    }

    return 0;
}

void print_help(char * argv[]){
    std::cout << "Usage: " << argv[0] << " <args> [number_of_points]" << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  --help, -h: Show this help message and exit" << std::endl;
    std::cout << "  --save, -s: Save the gereated data to a .npy file named 'points.npy'" << std::endl;
    return;
}