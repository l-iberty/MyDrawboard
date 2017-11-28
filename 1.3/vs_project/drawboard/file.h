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

	bool getKeyPoints(Shape *shape, int nPoints, int *x, int *y);
	void writeFile(FILE *fp, char *DllModName, int nPoints, int *x, int *y);
	bool parse(char *buf, char *DllModName, int *x, int *y);
	int getPointNum(char *buf);
	int getDllModNameLen(char *buf);
};

#endif // FILE_H