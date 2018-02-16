#include "decomposition.h"
#include <math.h>
#include <malloc.h>

extern double size;
extern int InitialCapacity;
extern double RegionSize;

decomp::decomp(double num_particle, particle_t* particles){
    int required = ceil(size/RegionSize);
    M = required;
    Num_region = M*M;
    region_list = (region*)malloc(Num_region*sizeof(region));
    for(int i = 0; i < Num_region; i++){
        region_list[i].Num = 0;
        region_list[i].Capacity = InitialCapacity;
        region_list[i].ind = (int*)malloc(InitialCapacity*sizeof(int));
    }

    for(int i = 0; i < num_particle; i++){
        int m = particles[i].x/RegionSize, n = particles[i].y/RegionSize;
        add_particle(i, m, n);
    }
}

void decomp::init(double num_particle, particle_t* particles){
    for(int i = 0; i < Num_region; i++){
        region_list[i].Num = 0;
    }
    for(int i = 0; i < num_particle; i++){
        int m = particles[i].x/RegionSize, n = particles[i].y/RegionSize;
        add_particle(i, m, n);
    }
}

decomp::~decomp(){
    for(int i = 0; i < Num_region; i++){
        free(region_list[i].ind);
    }
    free(region_list);
    //_mm_free(save);
}

region& decomp::operator()(int i, int j){
    if(i < 0 || j < 0 || i >= M || j>= M){
        printf("indices excess the boundary\n");
        printf("i = %d, j = %d\n", i,j);
        exit(1);
    }
    return region_list[i+j*M];
}

void decomp::add_particle(int particle_ind, int i, int j){
    region& temp = region_list[i+j*M];
    if(temp.Num == temp.Capacity){
        temp.Capacity*=2;
        temp.ind = (int*)realloc(temp.ind, temp.Capacity*sizeof(int));
    }
    temp.ind[temp.Num] = particle_ind;
    temp.Num++;
}

void decomp::delete_particle(int particle_ind, int i, int j){
    region& temp = region_list[i+j*M];
    for(int k = 0; k < temp.Num; k++){
        if(temp.ind[k] == particle_ind){
            for(int s = k; s < temp.Num-1; s++){
                temp.ind[s] = temp.ind[s+1];
            }
            break;
        }
        if(k == temp.Num-1){
            printf("Fail to remove particle %d from region (%d, %d)\n", particle_ind,i,j);
            exit(1);
        }
    }
    temp.Num--;
}

void decomp::check(int num_particle, particle_t* particles){
    int test = 0;
    for(int i = 0;i < Num_region; i++){
        test += region_list[i].Num;
    }
    if(test != num_particle){
        printf("wrong total number");
        exit(1);
    }
    for(int i = 0; i < Num_region; i++){
        for(int j = 0; j < region_list[i].Num; j++){
            int index = region_list[i].ind[j];
            int m = particles[index].x/RegionSize, n = particles[index].y/RegionSize;
            if(i%M!=m || i/M!=n){
                printf("particles wrong position");
                exit(1);
            }
        }
    }
}
