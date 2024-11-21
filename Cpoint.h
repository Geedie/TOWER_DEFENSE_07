class Cpoint {
public:
	// Constants and data
	const static int MAP_SIZE = 200;// Map matrix size
	const static int LEFT = 1;// Left–coordinates of the map screen
	const static int TOP = 1;// Top-coordinates of map screen
private:
	int x, y, c;
public:
	Cpoint() { x = y = c = 0; }
	Cpoint(int tx, int ty, int tc) { x = tx;y = ty;c = tc; }
	int getX() { return x; }
	int getY() { return y; }
	int getC() { return c; }
	void setC(int tc) { c = tc; }
	static Cpoint fromXYToRowCol(Cpoint v);
	static Cpoint fromRowColToXY(Cpoint s);
};