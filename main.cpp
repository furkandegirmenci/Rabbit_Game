#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int mouseX, mouseY;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
    if (event == EVENT_MOUSEMOVE) {
        mouseX = x, mouseY = y;
    }
}
int main()
{
	srand(time(0));
	namedWindow("rabbit Game", 0);
	int imgX = 1280, imgY = 960;
	Mat img(imgY, imgX, CV_8UC3);
	Mat imgClone;
	img.copyTo(imgClone);

	int rabbitSize = 75;
	Mat rabbit = imread("images/rabbit.jpeg");
	resize(rabbit, rabbit, Size(rabbitSize, rabbitSize));

	int carrotSize = 50;
	Mat carrot = imread("images/carrot.png");
	resize(carrot, carrot, Size(carrotSize, carrotSize));

	int points = 0, pointSize = imgY / 200;
	//Randomizing carrot placement and movements by chosing a destination
	int dotX = 0 + (int) ((imgX - carrotSize) * (rand() / (RAND_MAX + 1.0)));
	int dotY = 0 + (int) ((imgY - carrotSize) * (rand() / (RAND_MAX + 1.0)));
	int dotDestination[2] = {0, 0};
	dotDestination[0] = 0 + (int) ((imgX - carrotSize) * (rand() / (RAND_MAX + 1.0)));
	dotDestination[1] = 0 + (int) ((imgY - carrotSize) * (rand() / (RAND_MAX + 1.0)));
	while(true)
	{
		//if we catch the carrot, we randomize the place of the carrot and the destination it will go
		if((mouseX + rabbitSize > dotX && mouseX - carrotSize < dotX) && (mouseY + rabbitSize > dotY && mouseY - carrotSize < dotY))
		{
			dotX = 0 + (int) ((imgX - carrotSize) * (rand() / (RAND_MAX + 1.0)));
			dotY = 0 + (int) ((imgY - carrotSize) * (rand() / (RAND_MAX + 1.0)));
			dotDestination[0] = 0 + (int) ((imgX - carrotSize) * (rand() / (RAND_MAX + 1.0)));
			dotDestination[1] = 0 + (int) ((imgY - carrotSize) * (rand() / (RAND_MAX + 1.0)));
		    points++;
		}
		//carrot movement towards the destination
		dotX += (int)(dotDestination[0] - dotX) / 10;
		dotY += (int)(dotDestination[1] - dotY) / 10;
		//checking if carrot reached close to the destination. If close enough, will choose another destination
		if((dotDestination[0] <= dotX + 20 && dotDestination[0] >= dotX -20) && (dotDestination[1] <= dotY +20 && dotDestination[1] >= dotY -20))
		{
			dotDestination[0] = 0 + (int) ((imgX - carrotSize) * (rand() / (RAND_MAX + 1.0)));
			dotDestination[1] = 0 + (int) ((imgY - carrotSize) * (rand() / (RAND_MAX + 1.0)));
		}
		//adding the image for carrot
		Mat carrotPoint(imgClone, Rect(dotX, dotY, carrotSize, carrotSize));
		carrot.copyTo(carrotPoint);
		//keeping the rabbit at the edge to prevent crash
		setMouseCallback("rabbit Game", mouse_callback);
		if(mouseY + rabbitSize > imgY)
			mouseY = imgY - rabbitSize;
		if(mouseX + rabbitSize > imgX)
			mouseX = imgX - rabbitSize;
		//adding image for rabbit
		Mat rabbitPoint(imgClone, Rect(mouseX, mouseY, rabbitSize, rabbitSize));
		rabbit.copyTo(rabbitPoint);
		//points
		putText(imgClone, to_string(points), Point(10, pointSize*15), FONT_HERSHEY_COMPLEX_SMALL, pointSize, Scalar(0,255,255), 3);
		imshow("rabbit Game", imgClone);

		waitKey(40);
		img.copyTo(imgClone);
	}
	return 0;
}

