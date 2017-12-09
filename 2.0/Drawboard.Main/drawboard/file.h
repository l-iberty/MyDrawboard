#ifndef FILE_H
#define FILE_H
#include <vector>
#include <Windows.h>
#include "shape.h"
#include <QVector>
#include <QPoint>

typedef struct _FileDataEntry {
	char szFileName[MAX_PATH];
	QVector<QVector<QPoint>> pointsList;
} FileDataEntry;

class File {
public:
	File();
	~File();
	bool save(FileDataEntry *pFileDataEntry);
	int read(FileDataEntry *pFileDataEntry, long offset);
	long getFileSize(const char *pszFileName);
private:
	int newLine(FILE *_Stream);
};

#endif // FILE_H
