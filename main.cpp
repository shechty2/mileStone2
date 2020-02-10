#include "Boot.h"
#include <iostream>
using namespace Boot;
using namespace std;
int main(int argc, char *argv[]) {
    if (argc == 1) {
        auto *m = new Main();
        m->main(5600);
    } else {
        auto *m = new Main();
        string ps = argv[1];
        int p = stoi(ps);
        m->main(p);
    }
    return 0;
}
