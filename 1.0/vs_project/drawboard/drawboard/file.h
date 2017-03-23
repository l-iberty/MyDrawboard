#ifndef FILE_H
#define FILE_H
#include <vector>
#include "shape.h"


class File {
public:
	File(QList<Shape *> FileData);
	~File();

	bool open();
	bool save();
	QList<Shape *> getFileData();

private:
	QFile *theFile;
	QList<Shape *> FileData;
};

#endif // FILE_H