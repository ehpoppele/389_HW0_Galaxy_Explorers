#This code automatically runs the update locations functions for the complete range of object counts, starting at running 2^24 once, and then running lower counts more times, scaling iterations up by a power of two as the number of objects scaled down by a power of 2.

import random, sys, timeit

###############
# Create a list of 'size' floating point numbers in the range [-bound, bound]
def generate_random_list(size, bound):
    return [random.uniform(-bound, bound) for i in range(size)]

###############
# Update position by velocity, one time-step
def update_coords(xs, ys, zs, vx, vy, vz):
    for i in range(len(xs)):
        xs[i] = xs[i] + vx[i]
        ys[i] = ys[i] + vy[i]
        zs[i] = zs[i] + vz[i]

############ Main:
#Loop through all the sizes and scale down the iters as appropriate


chksum_array = [] #Holds all the checksums, so that I can check them automatically on later loops, and don't have to include them in output. Chksum for size is at [size_p-8].
time_array = [] #Holds all the times in a similar manner, updating them when a new minimum is found

for i in range(5): #Do five times; record minimums and confirm checksums
    size_p = 8
    iters_p = 17
    while size_p < 25:

        size = 2**size_p
        iters = 2**iters_p
        random.seed(size)
        xs = generate_random_list(size, 1000.)
        ys = generate_random_list(size, 1000.)
        zs = generate_random_list(size, 1000.)
        vx = generate_random_list(size, 1.)
        vy = generate_random_list(size, 1.)
        vz = generate_random_list(size, 1.)
        t = timeit.timeit(stmt = "update_coords(xs, ys, zs, vx, vy, vz)",
            setup = "from __main__ import update_coords, xs, ys, zs, vx, vy, vz",
            number = iters)
        print(1000000 * t / (size * iters))
        chksum = sum(xs) + sum(ys) + sum(zs)
        #prints size and time in microseconds
        if i == 0: #First time through, record chksum and time
            chksum_array.append(chksum)
            time_array.append(1000000 * t / (size * iters))
        else: #later, check the chksum and record time only if lower
            if chksum_array[size_p - 8]!=chksum:
                print("Checksums don't match")
            if time_array[size_p - 8] > 1000000 * t / (size * iters):
                time_array[size_p - 8] = 1000000 * t / (size * iters)
        size_p +=1
        iters_p -=1

#write to file
outfile = open("py_times.txt", "w")
size_p = 8
for time in time_array:
    size = 2**size_p
    outfile.write(str(size) + "    " + str(time) + "\n")
    size_p += 1
    
outfile.close()
exit(0)

