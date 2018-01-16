#define _CRT_SECURE_NO_WARNINGS
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <QByteArray>


File::File(QString &fileName, OptMode mode) {
	m_pFile = NULL;
	QByteArray ba = fileName.toLatin1();
	strcpy(m_FileName, ba.data());
	if (mode == Open) {
		m_pFile = fopen(m_FileName, "rb");
	}
	else if (mode == Save) {
		m_pFile = fopen(m_FileName, "ab");
	}
	m_FileSize = getFileSize();
}

File::~File() {
	if (m_pFile != NULL)
		fclose(m_pFile);
}

bool File::save(FileDataEntry *pFileDataEntry) {
	bool bSuccess = false;

	if (m_pFile != NULL) {
		try {
			// 保存插件DLL文件名
			fprintf(m_pFile, "%s\n", pFileDataEntry->szFileName);
			// 该插件DLL对应的Painter一共画了多少个Shape?
			int numShapes = pFileDataEntry->pointsList.size();
			fwrite(&numShapes, sizeof(numShapes), 1, m_pFile);
			newLine();

			for (int i = 0;i < numShapes;i++) { // 保存每个Shape的点集
				QVector<QPoint> points = pFileDataEntry->pointsList.at(i);
				int numPoints = points.size(); // 点集里有多少个点?
				fwrite(&numPoints, sizeof(numPoints), 1, m_pFile);
				for (int n = 0;n < numPoints;n++) {
					// 保存点集里的每个点
					QPoint point = points.at(n);
					fwrite(&point, sizeof(point), 1, m_pFile);
				}
			}
			bSuccess = true;
		}
		catch (...) {}
	}
	return bSuccess;
}

int File::read(FileDataEntry *pFileDataEntry, long offset) {
	int cbRead = 0;
	int numShapes = 0;
	int numPoints = 0;
	QPoint point;
	QVector<QPoint> points;

	if (m_pFile != NULL) {
		if (offset >= m_FileSize) {
			return 0;
		}
		fseek(m_pFile, offset, SEEK_SET);
		try {
			fgets(pFileDataEntry->szFileName, sizeof(pFileDataEntry->szFileName), m_pFile);
			int cb = strlen(pFileDataEntry->szFileName);
			pFileDataEntry->szFileName[cb - 1] = 0;
			fread(&numShapes, sizeof(numShapes), 1, m_pFile);
			fgetc(m_pFile); // skip '\n'
			cbRead += (cb + sizeof(numShapes) + 1);

			for (int i = 0;i < numShapes;i++) {
				fread(&numPoints, sizeof(numPoints), 1, m_pFile);
				cbRead += sizeof(numPoints);
				for (int n = 0;n < numPoints;n++) {
					fread(&point, sizeof(point), 1, m_pFile);
					cbRead += sizeof(point);
					points.push_back(point);
				}
				pFileDataEntry->pointsList.push_back(points);
				points.clear();
			}
		}
		catch (...) {}
	}
	return cbRead;
}

long File::getFileSize() {
	if (m_pFile != NULL) {
		fseek(m_pFile, 0, SEEK_END);
		return ftell(m_pFile);
	}
	return -1; // failed
}

void File::newLine() {
	if (m_pFile != NULL)
		fputc('\n', m_pFile);
}
