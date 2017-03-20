#define _CRT_SECURE_NO_WARNINGS
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <qbytearray.h>
#include <qpoint.h>

#ifndef DEFAULT_FILE
#define DEFAULT_FILE "SHAPELIST"
#endif

#ifndef PROC_INSTANCE
#define PROC_INSTANCE "?instance@@YAPAVShape@@XZ"
#endif

#define BUFFSIZE 255

typedef Shape *(*PPROC_INSTANCE)();

File::File(QList<Shape *> FileData) {
	this->FileData = FileData;
}

File::~File() {

}

bool File::open() {
	char *DllModName;
	int x1, x2, y1, y2;
	FILE *fp;
	char buf[BUFFSIZE] = { 0 };

	if ((fp = fopen(DEFAULT_FILE, "rb")) != NULL) {
		while (!feof(fp)) {
			fgets(buf, BUFFSIZE, fp);
			fpos_t pos;
			fgetpos(fp, &pos);

			// Get index of '#', so as to get the name of DLL module.
			QString str(buf);
			int index = str.indexOf('#');
			int nameLen = index + 1;
			DllModName = (char *)malloc(nameLen * sizeof(char));
			if (DllModName != NULL) {
				int i;
				// Copy
				for (i = 0;i < index;i++) {
					DllModName[i] = buf[i];
				}
				DllModName[i] = '\0';
			}

			// Get two key points.
			int *p = (int *)(buf + index + 1);
			x1 = *(p);
			y1 = *(p + 1);
			x2 = *(p + 2);
			y2 = *(p + 3);
			QPoint keyP1(x1, y1);
			QPoint keyP2(x2, y2);
			
			// Get DLL module handle.
			HMODULE hInstDll = GetModuleHandleA(DllModName);
			if (hInstDll != NULL) {
				PPROC_INSTANCE instance = (PPROC_INSTANCE)GetProcAddress(hInstDll, PROC_INSTANCE);
				if (instance != NULL) {
					// Get shape object instance.
					Shape *shape = instance();
					shape->setKeyP1(keyP1);
					shape->setKeyP2(keyP2);
					FileData.push_back(shape);
				}
			}
			free(DllModName);
		}
		// 最后一行数据会被读两次, 不知为何
		FileData.removeLast();
		return true;
	}

	return false;
}

bool File::save() {
	Shape *shape;
	FILE *fp;

	if (!FileData.empty()) {
		
		if ((fp = fopen(DEFAULT_FILE, "wb+")) != NULL) {
			for (int i = 0;i < FileData.size();i++) {
				shape = FileData.at(i);

				// QString -> char*
				QByteArray ba = shape->getDllModName().toLatin1();
				char *DllModName = ba.data();

				int x1 = shape->keyP1->rx();
				int y1 = shape->keyP1->ry();
				int x2 = shape->keyP2->rx();
				int y2 = shape->keyP2->ry();

				fwrite(DllModName, lstrlenA(DllModName), 1, fp);
				fprintf(fp, "#");
				fwrite(&x1, sizeof(int), 1, fp);
				fwrite(&y1, sizeof(int), 1, fp);
				fwrite(&x2, sizeof(int), 1, fp);
				fwrite(&y2, sizeof(int), 1, fp);
				fprintf(fp, "\n");
			}
			fclose(fp);
			return true;
		}
	}

	return false;
}

QList<Shape *> File::getFileData() {
	return this->FileData;
}
