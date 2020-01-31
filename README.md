## Iterations and Sizes
For the number of iterations, I started with 1 at the highest object count, since even 2 started to take a few minutes. After that, I tried increasing iterations by a power of two as object count decreased by a power of 2, and although times for each size still varied, with the shortest being several seconds and the longest over a minute, most sizes took about 20 seconds or so. I thought this provided a good amount of data for each size count, and the whole set could still be completed in several minutes.
## Data and Speed
The code I wrote ran each size at the appropriate number of iterations over five trials, gathering the minimum. I chose this because I found some trials produced large outliers that took long amounts of time, but there weren't extreme outliers in the other direction. It seems something could occassionally slow down the code unreasonably, but nothing would speed it up un reasonably, so I went with the minimum.
My python script was not working well for the largest size, giving something about three times what was expected, so I ran the regular update_locations.py a few times for that measurement. I also ran both the python and c++ code on my virtual machine, and the python at least seemed to perform slower there (I didn't do c++ on my regular windows machine).
## Results and Graphs
The results are displayed in the png graphs, one for python and one for the two combined. There was a slight upward trend for longer speed at larger sizes, which was at least noticeable in python but not so much in c++. C++ was in general about 10 times faster. The data shown in those graphs uses doubles for the c++ code. Changing the number type, I found float to be slightly faster than double, closer to 0.05us average, while double was about 0.06us. For the integer types, ...
## Memory Use
For memory use, I used the time -v function on my scripts, using the modified c++ one ending in _20 to run just that set size, and the update_locations.py set to the size of 2^20 with several iterations. I believe the line `Maximum resident set size` gives the maximum amount of memory in use, which for this set size was usually about 101400 kilobytes, or about 99 mb. In the case of python, the same test found the maximum usage to be about 248500 kb, or 242 mb. Although 2.5 times worse, this is still much closer to c++ than in speed. Personally I find memory to be the more important resource, especially given how much three tabs of Firefox will eat.


