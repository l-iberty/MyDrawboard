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
	FILE *fp;
	char buf[BUFFSIZE] = { 0 };

	if ((fp = fopen(DEFAULT_FILE, "rb")) != NULL) {
		while (!feof(fp)) {

			// Get information from buf
			fgets(buf, BUFFSIZE, fp);
			int nPoints, nameLen;
			int *x, *y;
			char *DllModName;
			nPoints = getPointNum(buf);
			x = (int *)malloc(sizeof(int) * nPoints);
			y = (int *)malloc(sizeof(int) * nPoints);
			nameLen = getDllModNameLen(buf);
			DllModName = (char *)malloc(sizeof(char) * nameLen + 1);
			if (x && y && DllModName) {
				parse(buf, DllModName, x, y);
			}
			else {
				return false;
			}
			
			// Get DLL module handle.
			HMODULE hInstDll = GetModuleHandleA(DllModName);
			if (hInstDll != NULL) {
				PPROC_INSTANCE instance = (PPROC_INSTANCE)GetProcAddress(hInstDll, PROC_INSTANCE);
				if (instance != NULL) {
					// Get shape object instance.
					Shape *shape = instance();
					for (int i = 0;i < nPoints;i++) {
						QPoint keyPoint(x[i], y[i]);
						shape->addKeyPoints(keyPoint);
					}
					FileData.push_back(shape);
				}
			}
			free(DllModName);
			free(x);
			free(y);
		}
		// 最后一行数据会被读两次
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
			// Save the information of each shape
			for (int i = 0;i < FileData.size();i++) {
				shape = FileData.at(i);

				// Get DLL module name ( QString -> char* )
				QByteArray ba = shape->getDllModName().toLatin1();
				char *DllModName = ba.data();

				// Get nPoints and all the key points
				int nPoints = shape->keyPoints.size();
				int *x = (int *)malloc(sizeof(int) * nPoints);
				int *y = (int *)malloc(sizeof(int) * nPoints);
				if (x && y) {
					getKeyPoints(shape, nPoints, x, y);
				}
				else {
					return false;
				}
					
				// Write to file
				writeFile(fp, DllModName, nPoints, x, y);
				free(x);
				free(y);
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

bool File::getKeyPoints(Shape *shape, int nPoints, int *x, int *y) {
	for (int i = 0;i < nPoints;i++) {
		QPoint keyPoint = shape->keyPoints.at(i);
		x[i] = keyPoint.rx();
		y[i] = keyPoint.ry();
	}
	return true;
}

void File::writeFile(FILE *fp, char *DllModName, int nPoints, int *x, int *y) {
	fwrite(DllModName, lstrlenA(DllModName), 1, fp); // DLL module name
	fprintf(fp, "#"); // Separator
	fwrite(&nPoints, sizeof(nPoints), 1, fp); // The number of key points
	
	 // All the key points
	for (int i = 0;i < nPoints;i++) {
		fwrite(&x[i], sizeof(x[i]), 1, fp);
		fwrite(&y[i], sizeof(y[i]), 1, fp);
	}
	fprintf(fp, "\n"); // End of line
}

bool File::parse(char *buf, char *DllModName, int *x, int *y) {
	// Get index of '#', so as to get DLL module name.
	QString str(buf);
	int index = str.indexOf('#');

	// Get DLL module name
	CopyMemory(DllModName, buf, index);
	DllModName[index] = 0;

	// Get all key points
	int *p = (int *)(buf + index + 1);
	int pointCount = *p;

	for (int i = 0;i < pointCount;i++, p += 2) {
		x[i] = *(p + 1);
		y[i] = *(p + 2);
	}
	return true;
}

int File::getPointNum(char *buf) {
	// Get index of '#'
	QString str(buf);
	int index = str.indexOf('#');

	int nPoints;
	int *p = (int *)(buf + index + 1);
	nPoints = *p;

	return nPoints;
}

int File::getDllModNameLen(char *buf) {
	// Get index of '#'
	QString str(buf);
	int index = str.indexOf('#');
	return index;
}