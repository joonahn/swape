
class Image
{
private:
	unsigned int *phy_addr;
	unsigned int *imageref;
	unsigned int background;
	int x, y;
	int width, height;
public:
	Image(unsigned int *img, int width, int height, int x, int y, unsigned int *_phy_addr);
	void move(int dx, int dy);
};