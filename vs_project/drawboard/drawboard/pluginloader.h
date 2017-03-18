#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <Windows.h>
using namespace std;

class PluginLoader {
private:
	vector<string> dll_files_name;
	bool getFiles(char *path, vector<string> &files);
public:
	PluginLoader(char *path);
	~PluginLoader();
	vector<string> getPluginNames();
	vector<string> getDllFileNames();
};

#endif // PLUGINLOADER_H