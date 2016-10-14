#include "util.h"

QColor resolveColor(CubeColor in_color){
	QColor color;

	switch(in_color){
		case (COLOR_RED):
			color = QColor(255, 0, 0);
		break;
		case (COLOR_GREEN):
			color = QColor(0, 255, 0);
		break;
		case (COLOR_BLUE):
			color = QColor(0, 0, 255);
		break;
		case (COLOR_YELLOW):
			color = QColor(255, 255, 0);
		break;
		case (COLOR_CYAN):
			color = QColor(0, 255, 255);
		break;
		case (COLOR_ORANGE):
			color = QColor(255, 128, 0);
		break;
		case (COLOR_PURPLE):
			color = QColor(128, 0, 255);
		break;
		default:
			color = QColor(255, 255, 255);
		break;
	}
	return color;
}
