#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <limits>
#include "kmeans.h" 

using namespace std;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
bool g_is_running = false;

Point map_to_screen(Point data_point, float min_x, float max_x, float min_y, float max_y) {
    float margin_x = (max_x - min_x) * 0.1f;
    float margin_y = (max_y - min_y) * 0.1f;
    float screen_x = ((data_point.x - (min_x - margin_x)) / ((max_x + margin_x) - (min_x - margin_x))) * SCREEN_WIDTH;
    float screen_y = ((data_point.y - (min_y - margin_y)) / ((max_y + margin_y) - (min_y - margin_y))) * SCREEN_HEIGHT;
    return {screen_x, SCREEN_HEIGHT - screen_y};
}

void find_data_bounds(float& min_x, float& max_x, float& min_y, float& max_y) {
    min_x = numeric_limits<float>::max();
    max_x = numeric_limits<float>::min();
    min_y = numeric_limits<float>::max();
    max_y = numeric_limits<float>::min();
    for(const auto& p : g_points) {
        if (p.x < min_x) min_x = p.x;
        if (p.x > max_x) max_x = p.x;
        if (p.y < min_y) min_y = p.y;
        if (p.y > max_y) max_y = p.y;
    }
}

bool init_visualizer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    g_window = SDL_CreateWindow("K-Means Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    g_is_running = true;
    return true;
}

void handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            g_is_running = false;
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
            cout << "Running one K-Means iteration..." << endl;
            run_kmeans_iteration();
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(g_renderer, 30, 30, 30, 255);
    SDL_RenderClear(g_renderer);
    
    float min_x, max_x, min_y, max_y;
    find_data_bounds(min_x, max_x, min_y, max_y);
    
    SDL_Color cluster_colors[] = {{255, 0, 0, 255}, {0, 0, 255, 255}};

    for (size_t i = 0; i < g_points.size(); ++i) {
        Point screen_pos = map_to_screen(g_points[i], min_x, max_x, min_y, max_y);
        int cluster_id = g_cluster_assignments[i];
        SDL_SetRenderDrawColor(g_renderer, cluster_colors[cluster_id].r, cluster_colors[cluster_id].g, cluster_colors[cluster_id].b, 255);
        SDL_RenderDrawPoint(g_renderer, screen_pos.x, screen_pos.y);
    }
    
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
    for (const auto& centroid : g_centroids) {
        Point screen_pos = map_to_screen(centroid, min_x, max_x, min_y, max_y);
        SDL_Rect rect = {(int)screen_pos.x - 4, (int)screen_pos.y - 4, 8, 8};
        SDL_RenderFillRect(g_renderer, &rect);
    }

    SDL_RenderPresent(g_renderer);
}

void close_visualizer() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_renderer = NULL;
    g_window = NULL;
    SDL_Quit();
    cout << "Application closed." << endl;
}

bool is_running() {
    return g_is_running;
}

#endif 
