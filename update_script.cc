#include <math.h>
#include <random>
#include <numeric>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

using data_t = double;

std::vector<data_t> generate_random_list(int size, int bound, int seed)
{
    std::vector<data_t> ret = {};
    //seed with size when func is called, then use uniform real distribution
    std::mt19937 gen(seed); //don't understand what this is entirely but it was on the c++ ref
    std::uniform_real_distribution<> rng(-bound, bound);
    for(int i = 0; i < size; i++){
        ret.push_back(rng(gen));
    }
    return ret;
}

//Update position by velocity, one time-step
void update_coords(std::vector<data_t> xs, std::vector<data_t> ys, std::vector<data_t> zs, std::vector<data_t> vx, std::vector<data_t> vy, std::vector<data_t> vz)
{
    for(int i = 0; i < xs.size(); i++){
        xs[i] = xs[i] + vx[i];
        ys[i] = ys[i] + vy[i];
        zs[i] = zs[i] + vz[i];
    }
    return;
}

//-----------------------------

//Loop through all the sizes and scale down the iters as appropriate, now as the main func
int main(){


    std::vector<data_t> chksum_array = {}; //Holds all the checksums, so that I can check them automatically on later loops, and don't have to include them in output. Chksum for size is at [size_p-8].
    std::vector<double> time_array = {}; //Holds all the times in a similar manner, updating them when a new minimum is found

    for(int i = 0; i < 5; i++){//Do five times; record minimums and confirm checksums
        int size_p = 8;
        int iters_p = 17;
        while (size_p < 25){
            int size = pow(2, size_p);
            int iters = pow(2, iters_p);
            std::vector<data_t> xs = generate_random_list(size, 1000.0, size);
            std::vector<data_t> ys = generate_random_list(size, 1000.0, size);
            std::vector<data_t> zs = generate_random_list(size, 1000.0, size);
            std::vector<data_t> vx = generate_random_list(size, 1.0, size);
            std::vector<data_t> vy = generate_random_list(size, 1.0, size);
            std::vector<data_t> vz = generate_random_list(size, 1.0, size);
            
            std::clock_t start;
            double elapsed;
            start = std::clock();
            for(int i = 0; i < iters; i++){
                update_coords(xs, ys, zs, vx, vy, vz);
            }
            //fin = std::clock();
            elapsed = (std::clock() - start ) / (double) CLOCKS_PER_SEC; //Stackoverflow informs me I should be able to just call this var
            
            //use accumulate for checksum
            data_t chksum = std::accumulate(xs.begin(), xs.end(), 0.0) + std::accumulate(ys.begin(), ys.end(), 0.0) + std::accumulate(zs.begin(), zs.end(), 0.0);
            
            if(i == 0){ //First time through, record chksum and time
                chksum_array.push_back(chksum);
                time_array.push_back(1000000.0 * elapsed / (size * iters)); 
            } else { //later, check the chksum and record time only if lower
                if(chksum_array[size_p - 8]!=chksum){
                    std::cout << "Checksums don't match!" << std::endl;
                }
                if (time_array[size_p - 8] > (1000000.0 * elapsed / (size * iters))){
                    time_array[size_p - 8] = (1000000.0 * elapsed / (size * iters));
                }
            }
            std::cout<<size_p<<"    "<<elapsed<<"\n";
            size_p += 1;
            iters_p -= 1;
            
        }
    }

    //write to file
    std::ofstream outfile ("cpp_times.txt"); //Change this each time too
    if(outfile.is_open()){
        //iterate through the time array, grabbing out numbers by size
        for(int size_p = 8; size_p <25; size_p++){
            int size = pow(2, size_p);
            outfile << std::to_string(size);
            outfile << "\t";
            outfile << std::to_string(time_array[size_p-8]) << std::endl;
        }
        outfile.close();
    }
    return 0;
}




