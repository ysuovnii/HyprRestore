#include <filesystem>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace filesystem;

int main()
{
    const char* homeEnv = getenv("HOME");
    if (!homeEnv) {
        cerr << "ERROR: HOME environment variable is not set." << endl;
        return 1;
    }

    string output;
    FILE* pipe = popen("hyprctl clients -j", "r");
    if (!pipe) {
        perror("PIPE ERROR");
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }

    if (pclose(pipe) == -1) {
        perror("PCLOSE ERROR");
        return 1;
    }

    string dir = string(homeEnv) + "/.local/share/hyprrestore/snapshots";
    string path = dir + "/snapshot.json";

    try {
        create_directories(dir);
    } catch (const filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
        return 1;
    }

    FILE* file = fopen(path.c_str(), "w");
    if (!file) {
        perror("FILE ERROR");
        return 1;
    }

    if (fprintf(file, "%s", output.c_str()) < 0) {
        perror("WRITE ERROR");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
