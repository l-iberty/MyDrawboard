#ifndef FILE_H
#define FILE_H
#include <vector>
#include <QFileDialog>
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
	enum OptMode { Save, Open };

	File(QString &fileName, OptMode mode);
	~File();
	bool save(FileDataEntry *pFileDataEntry);
	int read(FileDataEntry *pFileDataEntry, long offset);
private:
	long getFileSize();
	void newLine();

private:
	FILE *m_pFile;
	char m_FileName[MAX_PATH];
	long m_FileSize;
};

#endif // FILE_H
