/**
 * Simulation portion of MC Pi program
 * 11.08.2019
 * CSCI 335
 * Caleb Spradlin
 **/
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

long int calculate_pi(int iter){
    long int num_darts = 0;
    for (int i = 0; i < iter; i++){
        double x = get_random(-1.0, 1.0);
        double y = get_random(-1.0, 1.0);
        double distance_sq = x*x + y*y;
        if (distance_sq <= 1){
            num_darts++;
        }
    }
    return num_darts;
}

double get_random(double max, double min){
    double range = (max - min);
    double divide = RAND_MAX / range;
    return min + (rand() / divide);
}
