#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <vector>
#include <iostream>

#include "math.h"

using namespace std;

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void drawCircle(int x0, int y0, int radius, int thick, const float& red, const float& green, const float& blue);
void drawSq(const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue);

const int width = 640;
const int height = 480;

double xpos, ypos;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

//Line **my_lines = new Line*[num_lines];
//Box **my_boxes = new Box*[num_boxes];

void drawSq(const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= (i0 + length); i++)
	{
		int j = j0;
		drawPixel(i, j, red, green, blue);
		j = j0 + length;
		drawPixel(i, j, red, green, blue);
	}
	for (int j = j0; j <= (j0 + length); j++)
	{
		int i = i0;
		drawPixel(i, j, red, green, blue);
		i = i0 + length;
		drawPixel(i, j, red, green, blue);
	}
}

void drawCircle(int x0, int y0, int radius, int thick, const float& red, const float& green, const float& blue)
{
	int x = radius;
	int y = 0;
	int err = 0;
	int thickness = thick;

	while (x >= y)
	{
		//
		for (int i = 0; i < thickness; i++)
		{
			for (int j = 0; j < thickness; j++)
			{
				drawPixel(x0 + x + i, y0 + y + j, red, green, blue);
				drawPixel(x0 + y + j, y0 + x + i, red, green, blue);
				drawPixel(x0 - y - j, y0 + x + i, red, green, blue);
				drawPixel(x0 - x - i, y0 + y + j, red, green, blue);
				drawPixel(x0 - x - i, y0 - y - j, red, green, blue);
				drawPixel(x0 - y - j, y0 - x - i, red, green, blue);
				drawPixel(x0 + y + j, y0 - x - i, red, green, blue);
				drawPixel(x0 + x + i, y0 - y - j, red, green, blue);
			}
		}
		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}

class Box // NO PARENT
{
public:
	int start_x = 200, start_y = 190;
	int length = 100;

	void draw()
	{
		drawSq(start_x, start_y, length, 1.0f, 0.0f, 0.0f);
		cout << "Box::Draw();" << endl;
		// draw box here
	}
};

class Circle // NO PARENT
{
public:
	int x = 440 , y = 240, r = 50, thick = 2;
	float red = 0.0f, blue = 1.0f, green = 0.0f;

	void draw()
	{
		// draw circle here
		drawCircle(x, y, r, thick, red, green, blue);
		cout << "Circle::Draw();" << endl;
	}
};
class GeometricObjectInterface
{
public:
	virtual void draw() = 0;


};

template<class T_POLYMORP>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
		T_POLYMORP obj;
		obj.draw();
	}
};

int main(void)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			drawPixel(i, j, 255.0f, 255.0f, 255.0f);
		}
	}

	std::vector<GeometricObjectInterface*> obj_list;

	obj_list.push_back(new GeometricObject<Circle>);
	obj_list.push_back(new GeometricObject<Box>);
	
	for (auto itr : obj_list)
		itr->draw();


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Week5", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		//glClear(GL_COLOR_BUFFER_BIT);	

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	for (auto itr : obj_list)
	{
		delete itr;
	}

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}