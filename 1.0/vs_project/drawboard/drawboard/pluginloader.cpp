#include "pluginloader.h"

PluginLoader::PluginLoader(char *path) {
	if (!getFiles(path, dll_files_name)) {
		MessageBoxA(0, "Error loading plugins", "ERROR", MB_ICONERROR);
	}
}

PluginLoader::~PluginLoader() {

}

vector<string> PluginLoader::getPluginNames() {
	vector<string> plugin_names;

	for (int i = 0;i < dll_files_name.size();i++) {
		string s = dll_files_name.at(i);
		int start = s.find_last_of("\\") + 1;
		int end = s.find_last_of(".");
		s = s.substr(start, end - start);
		plugin_names.push_back(s);
	}

	return plugin_names;
}

vector<string> PluginLoader::getDllFileNames() {
	return this->dll_files_name;
}

bool PluginLoader::getFiles(char *path, vector<string> &files) {
	int hFile;
	struct _finddata_t fileinfo;

	if ((hFile = _findfirst(path, &fileinfo)) != -1) {
		do {
			// 不是文件夹
			if (!(fileinfo.attrib & _A_SUBDIR)) {
				string filespec = string(path);
				filespec = filespec.substr(0, filespec.length() - 1);
				filespec.append(fileinfo.name);
				files.push_back(filespec);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		return true;
	}
	return false;
}