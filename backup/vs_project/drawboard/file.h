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
	bool read(FileDataEntry *pFileDataEntry);
private:
	int newLine(FILE *_Stream);
};

#endif // FILE_H
