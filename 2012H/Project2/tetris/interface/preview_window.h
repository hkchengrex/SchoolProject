#ifndef _PREVIEW_WINDOW_H
#define _PREVIEW_WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPainter>

#include "block.h"

class PreviewWindow : public QLabel{
	Q_OBJECT

private:
	QPixmap pixmap;

public:
	PreviewWindow(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~PreviewWindow();

	void updateView();
};

#endif
