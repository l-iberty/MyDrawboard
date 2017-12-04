#include "pluginloader.h"

PluginLoader::PluginLoader() {
	bool bSuccess = false;
	
	if (getDllFilePaths(PLUGIN_DIR, dll_paths)) { // get DLL paths
		 // get DLL module handle
		for (int i = 0;i < dll_paths.size();i++) {
			HMODULE hMod = LoadLibraryA(dll_paths.at(i).c_str());
			if (hMod != NULL) {
				hModList.push_back(hMod);
			}
		}
		bSuccess = true;
	}
	if (!bSuccess) {
		MessageBox(0, TEXT("Error loading plugins"), TEXT("ERROR"), MB_ICONERROR);
	}
}

PluginLoader::~PluginLoader() {
	for (int i = 0;i < hModList.size();i++) {
		FreeLibrary(hModList.at(i));
	}
}

bool PluginLoader::getDllFilePaths(char *path, vector<string> &paths) {
	int hFile;
	struct _finddata_t fileinfo;

	if ((hFile = _findfirst(path, &fileinfo)) != -1) {
		do {
			// 不是文件夹
			if (!(fileinfo.attrib & _A_SUBDIR)) {
				string filespec = string(path);
				filespec = filespec.substr(0, filespec.length() - 1);
				filespec.append(fileinfo.name);
				paths.push_back(filespec);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		return true;
	}
	return false;
}

vector<string> PluginLoader::getPluginNames() {
	for (int i = 0;i < dll_paths.size();i++) {
		string s = dll_paths.at(i);
		int start = s.find_last_of("\\") + 1;
		int end = s.find_last_of(".");
		s = s.substr(start, end - start);
		plugin_names.push_back(s);
	}
	return plugin_names;
}

QList<HMODULE> PluginLoader::getDllModList() {
	return hModList;
}
