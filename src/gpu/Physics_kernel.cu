#ifndef DIRECT_SUM_KERNEL_H_
#define DIRECT_SUM_KERNEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "constants.h"
#include "err.h"
#include "Body.h"

#define BLOCK_SIZE 256

__device__ float getDistance(glm::vec2 pos1, glm::vec2 pos2)
{
    return glm::length(pos1 - pos2);
}

__device__ bool isCollide(Body &b1, Body &b2)
{
    return b1.radius + b2.radius + COLLISION_TH > getDistance(glm::vec2(b1.position.x, b1.position.y), glm::vec2(b2.position.x, b2.position.y));
}

__global__ void DirectSumTiledKernel(Body *bodies, int n)
{
    __shared__ Body Bds[BLOCK_SIZE];

    int bx = blockIdx.x;
    int tx = threadIdx.x;
    int i = bx * blockDim.x + tx;

    if (i < n)
    {
        Body &bi = bodies[i];
        glm::vec2 forceAccum = glm::vec2(0.0f, 0.0f);
        bi.acceleration = glm::vec3(0.0f, 0.0f, 0.0f); // Reset acceleration
        for (int tile = 0; tile < gridDim.x; ++tile)
        {
            Bds[tx] = bodies[tile * blockDim.x + tx];
            __syncthreads();

            for (int b = 0; b < BLOCK_SIZE; ++b)
            {
                int j = tile * blockDim.x + b;
                if (j < n)
                {
                    Body bj = Bds[b];
                    if (!isCollide(bi, bj) && bi.isDynamic)
                    {
                        glm::vec2 rij = glm::vec2(bj.position.x - bi.position.x, bj.position.y - bi.position.y);
                        float r = glm::length(rij) + E;
                        float f = (GRAVITY * bi.mass * bj.mass) / (r * r * r + (E * E));
                        glm::vec2 force = rij * f;
                        forceAccum += force / bi.mass;
                    }
                }
            }
            __syncthreads();
        }
        bi.acceleration += glm::vec3(forceAccum, 0.0f);
        bi.velocity += bi.acceleration * DT;
        bi.position += bi.velocity * DT;
    }
}

Body *initRandomBodies(int n)
{
    Body *bodies = new Body[n];
    srand(time(NULL));
    float maxDistance = MAX_DIST;
    float minDistance = MIN_DIST;
    glm::vec3 centerPos = {CENTERX, CENTERY, 0.0f};
    for (int i = 0; i < n - 1; ++i)
    {
        float angle = 2 * M_PI * (rand() / (float)RAND_MAX);
        float radius = (maxDistance - minDistance) * (rand() / (float)RAND_MAX) + minDistance;

        float x = centerPos.x + radius * cos(angle);
        float y = centerPos.y + radius * sin(angle);
        glm::vec3 position = {x, y, 0.0f};
        bodies[i] = Body(EARTH_MASS, EARTH_DIA, position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), true);
    }

    bodies[n - 1] = Body(SUN_MASS, SUN_DIA, centerPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), false);
    return bodies;
}


Body *Simulate(int n)
{

    Body *bodies = new Body[n];
    srand(time(NULL));
    float maxDistance = MAX_DIST;
    float minDistance = MIN_DIST;
    glm::vec2 centerPos = {CENTERX, CENTERY};
    for (int i = 0; i < n - 1; ++i)
    {

        float angle = 2 * M_PI * (rand() / (float)RAND_MAX);
        // Generate random distance from center within the given max distance
        float radius = (maxDistance - minDistance) * (rand() / (float)RAND_MAX) + minDistance;

        // Calculate coordinates of the point
        float x = centerPos.x + radius * std::cos(angle);
        float y = centerPos.y + radius * std::sin(angle);

        glm::vec2 position = {x, y};

        float distance = sqrt(pow(x - centerPos.x, 2) + pow(y - centerPos.y, 2));
        glm::vec2 r = {position.x - centerPos.x, position.y - centerPos.y};
        glm::vec2 a = {r.x / distance, r.y / distance};

        // Calculate velocity vector components
        float esc = sqrt((GRAVITY * SUN_MASS) / (distance));
        glm::vec2 velocity = {-a.y * esc, a.x * esc};

        bodies[i].isDynamic = true;
        bodies[i].mass = EARTH_MASS;
        bodies[i].radius = EARTH_DIA;
        bodies[i].position = position;
        bodies[i].velocity = velocity;
        bodies[i].acceleration = {0.0, 0.0};
    }

    bodies[n - 1].isDynamic = false;
    bodies[n - 1].mass = SUN_MASS;
    bodies[n - 1].radius = SUN_DIA;
    bodies[n - 1].position = centerPos;
    bodies[n - 1].velocity = {0.0, 0.0};
    bodies[n - 1].acceleration = {0.0, 0.0};
    return bodies;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_bodies> <2d_or_3d>" << std::endl;
        return 1;
    }

    int nBodies = std::atoi(argv[1]);
    if (nBodies <= 0)
    {
        std::cerr << "Error, number of bodies must be a positive integer" << std::endl;
        return 1;
    }
    
    h_bodies = initSpiralBodies(nBodies);
    
    int bytes = nBodies * sizeof(Body);

    Body *d_bodies;
    
    CHECK_CUDA_ERROR(cudaMalloc((void **)&d_bodies, bytes));
    CHECK_CUDA_ERROR(cudaMemcpy(d_bodies, h_bodies, bytes, cudaMemcpyHostToDevice));

    int blockSize = BLOCK_SIZE;
    int gridSize = ceil((float)nBodies / blockSize);
    int it = 0;
    int iters = 1000;

    while (it < iters)
    {
        DirectSumTiledKernel<<<gridSize, blockSize>>>(d_bodies, nBodies);
        CHECK_LAST_CUDA_ERROR();
        CHECK_CUDA_ERROR(cudaMemcpy(h_bodies, d_bodies, bytes, cudaMemcpyHostToDevice));
        // Visualization or logging logic can go here if needed
        ++it;
    }

    CHECK_CUDA_ERROR(cudaFree(d_bodies));
    free(h_bodies);

    CHECK_LAST_CUDA_ERROR();
    return 0;
}

#endif
