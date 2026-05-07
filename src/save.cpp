#include <filesystem>
#include <cstdio>
#include <iostream>
using namespace std;
using namespace filesystem;

int main()
{
  FILE* pipe = popen("hyprctl clients -j", "r");
  if(!pipe)
  {
    perror("PIPE ERROR");
    return 1;
  }
  
  char buffer[128];
  string output;
  
  while(fgets(buffer, sizeof(buffer), pipe)) 
  {
    output += buffer;
  }
  pclose(pipe);
  
  string home = getenv("HOME");
  string dir = home + "/.local/share/hyprrestore/snapshots";
  string path = dir + "/snapshot.json";
  
  try
  {
    create_directories(dir);
  }
  catch(const filesystem_error& e)
  {
    cerr << "Filesystem error: " << e.what() << endl;
    return 1;
    
  }
  
  FILE* file = fopen(path.c_str(), "w");
  if(!file)
  {
    perror("FILE ERROR");
    return 1;
  }
  fprintf(file, "%s", output.c_str());
  fclose(file);    
  


  return 0;
}
