#include "ComplexPlane.h"
using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size= { BASE_WIDTH, BASE_HEIGHT*m_aspectRatio };
	m_zoomCount = 0;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
	width = pixelWidth;
	height = pixelHeight;

}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x, y };
	m_state = CALCULATING;

}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x, y };
	m_state = CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = this->mapPixelToCoords(mousePixel);
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = this->mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text)
{
	stringstream strStream;
	strStream << "Mandelbrot Set " << endl;
	strStream << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	strStream << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	strStream << "Left-click to Zoom In" << endl;
	strStream << "Right-click to Zoom Out" << endl;
	strStream << "Window Dimensions: (" << m_pixel_size.x << "," << m_pixel_size.y << ")" << endl;
	text.setString(strStream.str());



}
void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Uint8 r, g, b;

				m_vArray[i * width + j].position = { (float)j, (float)i };

				this->iterationsToRGB(this->countIterations(this->mapPixelToCoords(Vector2i(j, i))),r,g,b);	
				m_vArray[j + i * width].color = { r, g, b };
				cout << j + i * width << " " << height* width <<endl;

			}
		}
		m_state = DISPLAYING;
	}
}

int ComplexPlane::countIterations(Vector2f coord) 
{
	int count;
	bool halt = false;
	double re = coord.x;
	double im = coord.y;
	complex<double> c(re, im);
	complex<double> z = (0, 0);

	for (count = 0; count < MAX_ITER && halt != true; count++)
	{
		z = (z * z) + (c);
		if (abs(z) >= 2)
		{
			halt = true;
		}
	}
	return count;
	
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		r = 255-3*count;
		b = 255-3*count;
		g = 255-3*count;
	}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float planeX = m_plane_center.x + (mousePixel.x - m_pixel_size.x / 2.0) / (m_pixel_size.x / 2.0) * (m_plane_size.x/2.0);
	float planeY = m_plane_center.y - (mousePixel.y - m_pixel_size.y / 2.0) / (m_pixel_size.y / 2.0) * (m_plane_size.y/2.0)*m_aspectRatio;
	return Vector2f(planeX, planeY);

}