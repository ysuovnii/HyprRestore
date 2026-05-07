#include <nlohmann/json.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
using json = nlohmann::json;

bool isBrowserApp(string className, string initialClass)
{
    if (className.find("chrome") != string::npos || initialClass.find("chrome") != string::npos)
        return true;
    else if (className.find("chromium") != string::npos || initialClass.find("chromium") != string::npos)
        return true;

    return false;
}

// bool looksLikeUrl(const string& text)
// {
//     if (text.empty()) {
//         return false;
//     }

//     string lower = text;
//     transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

//     if (lower.rfind("http://", 0) == 0 || lower.rfind("https://", 0) == 0 || lower.rfind("www.", 0) == 0) {
//         return true;
//     }

//     if (text.find(' ') != string::npos) {
//         return false;
//     }

//     return text.find('.') != string::npos;
// }

string fixUrl(string url)
{
    for (int i = 0; i < url.size(); i++)
    {
        if (url[i] == '_')
        {
            url.erase(i--, 1);
        }
    }
    return url;
}

// bool launchProcess(const vector<string> &args)
// {
//     if (args.empty())
//     {
//         return false;
//     }

//     vector<char *> argv;
//     argv.reserve(args.size() + 1);
//     for (const auto &arg : args)
//     {
//         argv.push_back(const_cast<char *>(arg.c_str()));
//     }
//     argv.push_back(nullptr);

//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         perror("fork");
//         return false;
//     }

//     if (pid == 0)
//     {
//         execvp(argv[0], argv.data());
//         perror("execvp");
//         _exit(127);
//     }

//     int status = 0;
//     if (waitpid(pid, &status, 0) < 0)
//     {
//         perror("waitpid");
//         return false;
//     }

//     return WIFEXITED(status) && WEXITSTATUS(status) == 0;
// }

int main()
{
    try
    {
        string home = getenv("HOME");
        string path = home + "/.local/share/hyprrestore/snapshots/snapshot.json";
        ifstream file(path);
        if (!file)
        {
            cerr << "Snapshot not found: " << path << "\n";
            return 1;
        }

        json data;
        file >> data;
        if (!data.is_array())
        {
            cerr << "Invalid snapshot format. Expected a JSON array." << endl;
            return 1;
        }

        // for (const auto &item : data)
        // {
        //     string app = item.value("class", string());
        //     string initialClass = item.value("initialClass", string());
        //     string initialTitle = item.value("initialTitle", string());

        //     if (app.empty())
        //     {
        //         cerr << "Skipping entry with empty class field." << endl;
        //         continue;
        //     }

        //     vector<string> command;
        //     if (isBrowserApp(app, initialClass))
        //     {
        //         string url = initialTitle;
        //         if (url.rfind("http://", 0) != 0 && url.rfind("https://", 0) != 0)
        //         {
        //             url = "https://" + url;
        //         }
        //         url = fixUrl(url);
        //         command = {"xdg-open", url};
        //     }
        //     else
        //     {
        //         command = {app};
        //     }

        //     if (!launchProcess(command))
        //     {
        //         cerr << "Failed to launch: " << command[0] << endl;
        //     }
        // }

        for (int i = 0; i < data.size(); i++)
        {
            string app = data[i]["class"];
            string initialClass = data[i]["initialClass"];
            string initialTitle = data[i]["initialTitle"];
            string script;

            if (isBrowserApp(app, initialClass))
            {
                string site = "https://" + fixUrl(initialTitle) + "";
                script = ("xdg-open \"" + site + "\"");
            }
            else script = initialTitle + " &";

            transform(script.begin(), script.end(), script.begin(), [](unsigned char c)
                      { return tolower(c); });

            int status = system(script.c_str());
            if (status != 0)
            {
                cout << "script : " << script << "endl";
                cerr << "Failed to start " << app << endl;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Restore error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
