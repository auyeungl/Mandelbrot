#include "ComplexPlane.h"

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size= { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
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

}

void ComplexPlane::zoomOut()
{

}
void ComplexPlane::setCenter(Vector2i mousePixel)
{

}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}
void ComplexPlane::loadText(Text& text)
{

}
void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				m_vArray[i * width + j].position = { (float)j, (float)i };
				//continue later
			}
	}
}

int ComplexPlane::countIterations(Vector2f coord) 
{

}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}