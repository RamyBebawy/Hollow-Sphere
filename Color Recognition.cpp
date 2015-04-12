#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

 void main()
 {
    //VideoCapture cap(0); //capture the video from web cam
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  int iLowH = 0;
 int iHighH = 179;

  int iLowS = 0; 
 int iHighS = 255;

  int iLowV = 0;
 int iHighV = 255;

 int iLastX=0;
 int iLastY=0;


  //Create trackbars in "Control" window
 cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &iHighV, 255);
 
 while (true)
    {
      
Mat imgHSV,imgThresholded,imgOriginal;

         //cap.read(imgOriginal); // read a new frame from video
           imgOriginal=imread("C:/Users/user/Desktop/Untitled.png");
		
//Mat imgOriginal (D, Rect(530, 700, 1180, 680));

  
 cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
 inRange(imgHSV, Scalar(iLowH, iLowS,iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
 // morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2,2)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(12, 12)) ); 
 
 // morphological closing (fill small holes in the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) );

    Moments oMoments = moments(imgThresholded);
  double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

  
 
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY-20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY-20), Scalar(0,255,255), 2);
	   circle( imgOriginal,Point(posX,posY),20,Scalar( 0, 200, 255 ),4,2 );
	  putText(imgOriginal,"Reddish", Point (posX+20.0,posY ),FONT_HERSHEY_SIMPLEX,0.35, Scalar(0,0,0),1, 5, false );

   }




   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
// morphological opening (remove small objects from the foreground)
 erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2,2)) );
 dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(12, 12)) ); 

//morphological closing (fill small holes in the foreground)
dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) ); 
erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) );
  
  oMoments = moments(imgThresholded);
   dM01 = oMoments.m01;
   dM10 = oMoments.m10;
   dArea = oMoments.m00;

   //calculate the position of the ball
    posX = dM10 / dArea;
    posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY-20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY-20), Scalar(0,255,255), 2);
	   circle( imgOriginal,Point(posX,posY),20,Scalar( 0, 200, 255 ),4,2 );
	  putText(imgOriginal,"Greenish", Point (posX+20.0,posY ),FONT_HERSHEY_SIMPLEX,0.35, Scalar(0,0,0),1, 5, false );

   }

   
   
   inRange(imgHSV, Scalar(iLowH, iLowS, iHighV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2,2)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(12, 12)) ); 

   //morphological closing (fill small holes in the foreground)
dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) ); 
erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) );
  
  oMoments = moments(imgThresholded);
   dM01 = oMoments.m01;
   dM10 = oMoments.m10;
   dArea = oMoments.m00;
 
   //calculate the position of the ball
    posX = dM10 / dArea;
    posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY-20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY-20), Scalar(0,255,255), 2);
	   circle( imgOriginal,Point(posX,posY),20,Scalar( 0, 200, 255 ),4,2 );
	  putText(imgOriginal,"Purple", Point (posX+20.0,posY ),FONT_HERSHEY_SIMPLEX,0.35, Scalar(0,0,0),1, 5, false );

   }
   imshow("Thresholded Image", imgThresholded);

   inRange(imgHSV, Scalar(iLowH, iLowS, iHighV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2,2)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(12, 12)) ); 

   //morphological closing (fill small holes in the foreground)
dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) ); 
erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) );
  
  oMoments = moments(imgThresholded);
   dM01 = oMoments.m01;
   dM10 = oMoments.m10;
   dArea = oMoments.m00;
 
   //calculate the position of the ball
    posX = dM10 / dArea;
    posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY-20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY-20), Scalar(0,255,255), 2);
	   circle( imgOriginal,Point(posX,posY),20,Scalar( 0, 200, 255 ),4,2 );
	  putText(imgOriginal,"Orangish", Point (posX+20.0,posY ),FONT_HERSHEY_SIMPLEX,0.35, Scalar(0,0,0),1, 5, false );

   }
   
   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2,2)) );
 dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(12, 12)) ); 
   //morphological closing (fill small holes in the foreground)
 dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );
 
  oMoments = moments(imgThresholded);
   dM01 = oMoments.m01;
   dM10 = oMoments.m10;
   dArea = oMoments.m00;
   
   //calculate the position of the ball
    posX = dM10 / dArea;
    posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY+20), Scalar(0,0,0), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY-20), Scalar(0,0,0), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY+20), Scalar(0,0,0), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY-20), Scalar(0,0,0), 2);
	   circle( imgOriginal,Point(posX,posY),20,Scalar( 0, 200, 255 ),4,2 );
	  putText(imgOriginal,"Yellowish", Point (posX+20.0,posY ),FONT_HERSHEY_SIMPLEX,0.35, Scalar(0,0,0),1, 5, false );

   }

   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2,2)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(12, 12)) ); 

   //morphological closing (fill small holes in the foreground)
dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) ); 
erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(40, 40)) );
  
  oMoments = moments(imgThresholded);
   dM01 = oMoments.m01;
   dM10 = oMoments.m10;
   dArea = oMoments.m00;
 
   //calculate the position of the ball
    posX = dM10 / dArea;
    posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX+20, posY-20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY+20), Scalar(0,255,255), 2);
	   line(imgOriginal, Point(posX, posY),Point(posX-20, posY-20), Scalar(0,255,255), 2);
	  circle( imgOriginal,Point(posX,posY),20,Scalar( 0, 200, 255 ),4,2 );
	  putText(imgOriginal,"Bluish", Point (posX+20.0,posY ),FONT_HERSHEY_SIMPLEX,0.35, Scalar(0,0,0),1, 5, false );

   }


    iLastX = posX;
   iLastY = posY;
  }

   imshow("Original", imgOriginal); //show the original image
  if (waitKey(1)==27) break;
  
    }
}