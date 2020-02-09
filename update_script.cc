#include <math.h>
#include <random>
#include <numeric>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

//This file works essentially as a c++ replica of the python script file, with
//essentially the same functions and tasks, but it also includes a testing functions
//which can be ran by using args with the program command

using data_t = double; //So I can easily test different int/double types in the program

//fill a vector with numbers within |bound| of zero
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
void update_coords(std::vector<data_t>& xs, std::vector<data_t>& ys, std::vector<data_t>& zs, const std::vector<data_t>& vx, const std::vector<data_t>& vy,  const std::vector<data_t>& vz)
{
    for(int i = 0; i < xs.size(); i++){
        xs[i] = xs[i] + vx[i];
        ys[i] = ys[i] + vy[i];
        zs[i] = zs[i] + vz[i];
    }
    return;
}

//test function, can be called using 't' when running the program
//testing decisions are explained in the readme
bool test_coords()
{
    bool success = true;
    //first check the generate_random_list func
    std::vector<data_t> rng_list = generate_random_list(100.0, 1000.0, 100.0);
    if( rng_list.size() != 100){
        std::cout << "Length of generated random list is wrong." << std::endl;
        success = false;
    }
    if(rng_list[1] == rng_list[99]){ //if randomized, there is a very low chance these two will be the same
        std::cout << "Random list does not appear to be random." << std::endl;
        success = false;
    }
    for(int i = 0; i < 100; i++){
        if(rng_list[i] > 1000.0 or rng_list[i] < -1000.0){
            std::cout << "Random values appear outside of given bounds." << std::endl;
            success = false;
        }
    }
    //Now check the update_coords func
    std::vector<data_t> xs(3,100.0);
    std::vector<data_t> ys(3,100.0);
    std::vector<data_t> zs(3,100.0);
    std::vector<data_t> vx(3,5.0);
    std::vector<data_t> vy(3,10.0);
    std::vector<data_t> vz(3,-5.0);
    update_coords(xs, ys, zs, vx, vy, vz);
    if(xs[0] != 105.0 or ys[1] != 110.0 or zs[1] != 95.0){
        std::cout << "Updating with velocities didn't work as expected." << std::endl;
        success = false;
    }
    return success;
}


//-----------------------------

//Loop through all the sizes and scale down the iters as appropriate, now as the main func
int main(int argc, const char * argv[]){
    //check if using test commands, otherwise run the normal script
    if(argc > 1){
        if(*argv[1] == 't'){ //seems that and isn't shortcircuited, so I have to put this as a separate condition
        if(test_coords() == false){
            std::cout << "Test has failed." << std::endl;
        } else {
            std::cout << "Test succeeded!" << std::endl;
        }
    } else {
        std::cout << "It seems that argument isn't recognized." << std::endl;
    }
    } else {

    std::vector<data_t> chksum_array = {}; //Holds all the checksums, so that I can check them automatically on later loops, and don't have to include them in output. Chksum for size is at [size_p-8].
    std::vector<double> time_array = {}; //Holds all the times in a similar manner, updating them when a new minimum is found

    for(int i = 0; i < 5; i++){//Do five times; record minimums and confirm checksums
        //we start at the smallest size used of 2^8, and have 2^17 iterations for this;
        //as described in the readme, these then scale in opposite directions as the loop continues
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
            
            //timing using std clock functions
            std::clock_t start;
            double elapsed;
            start = std::clock();
            for(int i = 0; i < iters; i++){
                update_coords(xs, ys, zs, vx, vy, vz);
            }
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
                //push to the array in microseconds, so we can print to file later
                if (time_array[size_p - 8] > (1000000.0 * elapsed / (size * iters))){
                    time_array[size_p - 8] = (1000000.0 * elapsed / (size * iters));
                }
            }
            std::cout<<size_p<<"    "<<elapsed<<std::endl;
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
    }
    return 0;
}




