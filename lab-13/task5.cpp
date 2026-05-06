#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>
using namespace std;
using namespace chrono;

int lab13_task5() {
    int N, M, K;
    cin >> N >> M >> K;

    // map
    map<int, int> m;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        m[i] = i;
    }
    auto end = high_resolution_clock::now();
    cout << "map insert: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < M; i++) {
        m.erase(i);
    }
    end = high_resolution_clock::now();
    cout << "map erase: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < K; i++) {
        m.find(i);
    }
    end = high_resolution_clock::now();
    cout << "map find: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    // unordered_map
    unordered_map<int, int> um;
    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        um[i] = i;
    }
    end = high_resolution_clock::now();
    cout << "unordered_map insert: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < M; i++) {
        um.erase(i);
    }
    end = high_resolution_clock::now();
    cout << "unordered_map erase: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < K; i++) {
        um.find(i);
    }
    end = high_resolution_clock::now();
    cout << "unordered_map find: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    return 0;
}
