#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <limits>
#include <cmath>

using namespace std;

struct Point {
    float x;
    float y;
};

vector<Point> g_points;
vector<Point> g_centroids;
vector<int> g_cluster_assignments;
int K = 2;

void load_data(const string& filepath) {
    ifstream file(filepath);
    string line;
    if (!file.is_open()) {
        cout << "Failed to open file: " << filepath << endl;
        return;
    }
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        Point p;
        getline(ss, cell, ',');
        p.x = stof(cell);
        getline(ss, cell, ',');
        p.y = stof(cell);
        g_points.push_back(p);
    }
    g_cluster_assignments.resize(g_points.size());
    cout << "Loaded " << g_points.size() << " points." << endl;
}

void initialize_centroids() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, g_points.size() - 1);
    for (int i = 0; i < K; ++i) {
        int random_index = distrib(gen);
        g_centroids.push_back(g_points[random_index]);
    }
}

void run_kmeans_iteration() {
    for (size_t i = 0; i < g_points.size(); ++i) {
        double min_dist = numeric_limits<double>::max();
        int best_cluster = 0;
        for (int j = 0; j < K; ++j) {
            float dx = g_points[i].x - g_centroids[j].x;
            float dy = g_points[i].y - g_centroids[j].y;
            double dist = sqrt(dx * dx + dy * dy);
            if (dist < min_dist) {
                min_dist = dist;
                best_cluster = j;
            }
        }
        g_cluster_assignments[i] = best_cluster;
    }

    vector<Point> new_centroids(K, {0.0f, 0.0f});
    vector<int> counts(K, 0);
    for (size_t i = 0; i < g_points.size(); ++i) {
        int cluster_id = g_cluster_assignments[i];
        new_centroids[cluster_id].x += g_points[i].x;
        new_centroids[cluster_id].y += g_points[i].y;
        counts[cluster_id]++;
    }
    for (int i = 0; i < K; ++i) {
        if (counts[i] > 0) {
            g_centroids[i].x = new_centroids[i].x / counts[i];
            g_centroids[i].y = new_centroids[i].y / counts[i];
        }
    }
}

#endif 
