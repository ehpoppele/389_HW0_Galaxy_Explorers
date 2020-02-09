# Homework_0
### Eli Poppele
I have two main files for this project. `update_script.py` is my edited version of `update_locations.py` that automatically runs the function for several trials for all the sizes and iterations that I chose. `update_script.cc` does the same in c++, while `update_script_20.cc` is set for size 2^20 for Part 4. None of my files take arguments, they all run the predetermined sizes and iterations. The update scripts write to the txt files that are included. I also have .png images included for my graphs.

## Iterations and Sizes
For the number of iterations, I started with 1 at the highest object count, since even 2 started to take a few minutes. After that, I tried increasing iterations by a power of two as object count decreased by a power of 2, and although times for each size still varied, with the shortest being several seconds and the longest over a minute, most sizes took about 20 seconds or so. I thought this provided a good amount of data for each size count, and the whole set could still be completed in several minutes.
## Data and Speed
The code I wrote ran each size at the appropriate number of iterations over five trials, gathering the minimum. I chose this because I found some trials produced large outliers that took long amounts of time, but there weren't extreme outliers in the other direction. It seems something could occassionally slow down the code unreasonably, but nothing would speed it up un reasonably, so I went with the minimum.
My python script was not working well for the largest size, giving something about three times what was expected, so I ran the regular update_locations.py a few times for that measurement. I also ran both the python and c++ code on my virtual machine, and the python at least seemed to perform slower there (I didn't do c++ on my regular windows machine).
## Results and Graphs
The results are displayed in the png graphs, one for python, one for the c++ types, and one for the two combined. There was a slight upward trend for longer speed at larger sizes, which was at least noticeable in python but not so much in c++. C++ was in general nearly 100 times faster. The data shown in those graphs uses doubles for the c++ code. Changing the number type, I found float to be slightly faster than double, especially at larger sizes, scaling up to nearly twice as fast. For the integer types, they seemed to be more variant, as they were about the same as the double times, scaling up with vector size, but some, such as int16_t, were at consistent speeds for all sizes, and closer to 0.001-0.002 microseconds. 
## Memory Use
For memory use, I used the time -v function on my scripts, using the modified c++ one ending in _20 to run just that set size, and the update_locations.py set to the size of 2^20 with several iterations. I believe the line `Maximum resident set size` gives the maximum amount of memory in use, which for this set size was usually about 60500 kilobytes, or about 59 mb. In the case of python, the same test found the maximum usage to be about 248500 kb, or 242 mb. Although about 5 times worse, this is still much closer to c++ than in speed. Personally I find memory to be the more important resource, especially given how much three tabs of Firefox will eat.
## Testing
I added testing somewhat last-minute to the .cc file. Since I only had one file and no .hh, I added the tests as a separate function. If the program is run with no arguments, it executes the script normally, but if you add the argument "t", it runs the test function. For the test, I just made sure that the functions for generating and updating lists seemed to work correctly. The other parts of my program, for creating and updating the vectors of certain sizes, couldn't be tested so easily, and are also very noticeable if they're broken.

For these functions then, I simply created a random vector, and confirmed that it was of the correct size with all the values wihtin the appropriate bounds. I also checked some of the values against each other, since the odds of two values being the same in the range I used are very low, and a proper test for randomness would be beyond the scope of this homework. For the update_coords, I just used pre-determined vectors for position and velocity, updated them with the function, and checked that the values were what they were expected to be. While this part wasn't very thorough and probably missed some edge cases, the function that it's testing is about three lines long and doesn't do anything more complicated than addition on vector elements.


