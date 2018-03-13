#include <iostream>
#include "opencv2/opencv.hpp"
#include <boost/filesystem.hpp>
#include <fstream>
#include "Camera.h"

#ifndef CALIBRATE_CLASS
#define CALIBRATE_CLASS

class Calibrate
{
private:

	//############### ATTRIBUTES ###############//
	//System
	std::ifstream a_inFile;
	std::string a_outFile;
	boost::filesystem::path a_dir; 

	//Board
	int a_boardWdth, a_boardHght;
	int a_zZoneW, a_zZoneH;
	float a_squareSz;
	cv::Size a_boardSz;
	cv::Size a_zZoneSz;
	std::vector< cv::Point2f > a_corners;
	std::vector< cv::Point2f > a_corners1, a_corners2;

	//Search Parameters
	int a_numImg;
	int a_sWinW, a_sWinH;
	cv::Size a_sWinSz, a_frameSz;
	int a_maxIter;
	float a_epsilon;

	//############### FINAL CONTAINERS ###############//
	// NOTE:
	// 1.)	Each Camera has one of these structures
	//
	// 2.)	Double vector structure explained:
	// 		There is a vector which contains all data found in a image (data)
	// 		There is a vector which contains all image data for a single camera (camera)

	// IMAGEPOINTS: ###############//
	// Contains pixel locations of all found found corners
	std::vector< std::vector< cv::Point2f > > a_imagePoints;
	std::vector< std::vector< cv::Point2f > > a_imagePoints1;
	std::vector< std::vector< cv::Point2f > > a_imagePoints2;

	// OBJECTPOINTS: ###############//
	// Contains physical but relative locations of all corners 
	// If object is planar, z component is always 0
	// Object need not be in the same orientation for each image
	// If part of the object is out of frame, excluded points need to be
	// accounted for in this structure.
	std::vector< std::vector< cv::Point3f > > a_objectPoints;

	// CAMERA MATRIX: ###############//
	// Will contain aspect ratio data and focal center 
	// Aspect ratio should be close to 1 for calcs to be correct
	// If aspect ratio correction is needed, this matrix needs to be altered before calc
	cv::Mat K1, K2;

	// RELATIONAL MATRICES: ###############//
	// Matrices that describe the relationship betweeen cameras
	// R: Rotational F: Fundamental E: Essential T: Translational
	cv::Mat R, F, E;
	cv::Vec3d T;

	// DISTORTION COEFFICIENTS: ###############//
	// Due to curvature of lens
	cv::Mat D1, D2;

	// RECTIFICATION TRANSFORM: ###############//
	// Rotational matrix for each camera
	// 3X3 Matrix
	cv::Mat R1, R2;

	// PROJECTION MATRIX: ###############//
	// Projection matrix for each camera
	// 3X4 Matrix
	cv::Mat P1, P2;

	// DISPARITY-TO-DEPTH MAPPING MATRIX: ###############//
	// 4X4 Matrix
	cv::Mat Q;

	//############### FUNCTIONS ###############//
	void getFileData();
	void printCalibrationData();
	void checkDir(boost::filesystem::path);
	void writeData();

	//Single Camera
	void getSampleData(Camera);
	void calculate(cv::Mat, cv::Mat, std::vector< cv::Point3f >);

	//Static Two Camera
	void getSampleData(Camera, Camera);
	bool getCorners(cv::Mat, cv::Mat, cv::Mat, cv::Mat, std::vector< cv::Point3f >);

	//Dynamic Multi Camera

public:
	//Single Camera
	Calibrate(std::string, Camera);

	//Two Camera
	Calibrate(std::string, std::string, Camera, Camera);

};

#endif