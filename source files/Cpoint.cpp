#include "Cpoint.h"
Cpoint Cpoint::fromXYToRowCol(Cpoint v) {
	return { (v.y - 1 - TOP) / 2, (v.x - 2 - LEFT) / 4, v.c };
}
Cpoint Cpoint::fromRowColToXY(Cpoint s) {
	return { 4 * s.y + 2 + LEFT, 2 * s.x + 1 + TOP, s.c };
}