#ifndef _PREVIEW_WINDOW_H
#define _PREVIEW_WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPainter>

#include "block.h"

//This class is for the UI of the preview window to see the incoming block
class PreviewWindow : public QLabel{
	Q_OBJECT

private:
	QPixmap pixmap;

public:
	PreviewWindow(QWidget * parent = 0, Qt::WindowFlags f = 0);

	//Updates its UI
	void updateView();
};

#endif
