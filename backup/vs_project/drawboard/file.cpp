#define _CRT_SECURE_NO_WARNINGS
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <QByteArray>

#define DEFAULT_FILE "ShapeList.bin"
#define BUFSIZE 255

File::File() {

}

File::~File() {

}

bool File::save(FileDataEntry *pFileDataEntry) {
	FILE *pFile = NULL;
	bool bSuccess = false;

	if ((pFile = fopen(DEFAULT_FILE, "ab")) != NULL) {
		try {
			fprintf(pFile, "%s\n", pFileDataEntry->szFileName);

			int numShapes = pFileDataEntry->pointsList.size();
			fwrite(&numShapes, sizeof(numShapes), 1, pFile);
			newLine(pFile);

			for (int i = 0;i < numShapes;i++) {
				QVector<QPoint> points = pFileDataEntry->pointsList.at(i);
				int numPoints = points.size();
				fwrite(&numPoints, sizeof(numPoints), 1, pFile);
				for (int n = 0;n < numPoints;n++) {
					QPoint point = points.at(n);
					fwrite(&point, sizeof(point), 1, pFile);
				}
			}
			bSuccess = true;
		}
		catch (...) {}
		fclose(pFile);
	}
	return bSuccess;
}

int File::read(FileDataEntry *pFileDataEntry, long offset) {
	FILE *pFile = NULL;
	int cbRead = 0;
	int numShapes = 0;
	int numPoints = 0;
	QPoint point;
	QVector<QPoint> points;

	if ((pFile = fopen(DEFAULT_FILE, "rb")) != NULL) {
		if (offset >= getFileSize(DEFAULT_FILE)) {
			return 0;
		}
		fseek(pFile, offset, SEEK_SET);
		try {
			fgets(pFileDataEntry->szFileName, sizeof(pFileDataEntry->szFileName), pFile);
			int cb = strlen(pFileDataEntry->szFileName);
			pFileDataEntry->szFileName[cb - 1] = 0;
			fread(&numShapes, sizeof(numShapes), 1, pFile);
			fgetc(pFile); // skip '\n'
			cbRead += (cb + sizeof(numShapes) + 1);

			for (int i = 0;i < numShapes;i++) {
				fread(&numPoints, sizeof(numPoints), 1, pFile);
				cbRead += sizeof(numPoints);
				for (int n = 0;n < numPoints;n++) {
					fread(&point, sizeof(point), 1, pFile);
					cbRead += sizeof(point);
					points.push_back(point);
				}
				pFileDataEntry->pointsList.push_back(points);
				points.clear();
			}
		}
		catch (...) {}
		fclose(pFile);
	}
	return cbRead;
}

long File::getFileSize(const char *pszFileName) {
	FILE *pFile = NULL;
	long fileSize = -1;

	if ((pFile = fopen(pszFileName, "rb")) != NULL) {
		fseek(pFile, 0, SEEK_END);
		fileSize = ftell(pFile);
	}
	return fileSize;
}

int File::newLine(FILE *_Stream) {
	return fputc('\n', _Stream);
}
