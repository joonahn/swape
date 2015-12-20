
class Image
{
private:
	unsigned int *fb;
	unsigned int *imageref;
	unsigned int background;
	int x, y;
	int width, height;
public:
	Image(unsigned int *img, int width, int height, int x, int y, unsigned int *_fb);
	void move(int dx, int dy);
};