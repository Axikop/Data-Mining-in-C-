#include "visualizer.h" 
#include <iostream>

using namespace std;

int main(int argc, char* args[]) {
    
    if (!init_visualizer()) {
        cout << "Failed to initialize visualizer. Exiting." << endl;
        return 1;
    }

    load_data("data/clustermoons.csv");
    initialize_centroids();


    cout << "Initialization complete. Press SPACE to run a K-Means step." << endl;
    while (is_running()) {
        handle_events();
        render();
    }

    close_visualizer();

    return 0;
}
