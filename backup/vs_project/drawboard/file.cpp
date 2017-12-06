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
	FILE *fp = NULL;
	bool bSuccess = false;

	if ((fp = fopen(DEFAULT_FILE, "wb+")) != NULL) {
		try {
			fprintf(fp, "%s\n", pFileDataEntry->szFileName);

			int numShapes = pFileDataEntry->pointsList.size();
			fwrite(&numShapes, sizeof(numShapes), 1, fp);
			newLine(fp);

			for (int i = 0;i < numShapes;i++) {
				QVector<QPoint> points = pFileDataEntry->pointsList.at(i);
				int numPoints = points.size();
				fwrite(&numPoints, sizeof(numPoints), 1, fp);
				for (int n = 0;n < numPoints;n++) {
					QPoint point = points.at(n);
					fwrite(&point, sizeof(point), 1, fp);
				}
			}
			bSuccess = true;
		}
		catch (...) {}
		fclose(fp);
	}
	return bSuccess;
}

bool File::read(FileDataEntry *pFileDataEntry) {
	FILE *fp = NULL;
	bool bSuccess = false;
	int numShapes = 0;
	int numPoints = 0;
	QPoint point;
	QVector<QPoint> points;

	if ((fp = fopen(DEFAULT_FILE, "rb")) != NULL) {
		try {
			fgets(pFileDataEntry->szFileName, sizeof(pFileDataEntry->szFileName), fp);
			int cb = strlen(pFileDataEntry->szFileName);
			pFileDataEntry->szFileName[cb - 1] = 0;
			fread(&numShapes, sizeof(numShapes), 1, fp);
			fgetc(fp); // skip '\n'

			for (int i = 0;i < numShapes;i++) {
				fread(&numPoints, sizeof(numPoints), 1, fp);
				for (int n = 0;n < numPoints;n++) {
					fread(&point, sizeof(point), 1, fp);
					points.push_back(point);
				}
				pFileDataEntry->pointsList.push_back(points);
				points.clear();
			}
			bSuccess = true;
		}
		catch (...) {}
		fclose(fp);
	}
	return bSuccess;
}

int File::newLine(FILE *_Stream) {
	return fputc('\n', _Stream);
}
