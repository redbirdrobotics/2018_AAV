#include "Calibrate.h"

Calibrate::Calibrate(std::string directory, Camera cam) 
: a_inFile(directory) //a_basePath(boost::filesystem::current_path())
{
	getFileData();
	//printCalibrationData();
	checkDir(a_dir);
	getSampleData(cam);
}

void Calibrate::printCalibrationData()
{
	std::cout<<a_boardWdth<<std::endl;
	std::cout<<a_boardHght<<std::endl;
	std::cout<<a_numImg<<std::endl;
	std::cout<<a_squareSz<<std::endl;
	std::cout<<a_dir<<std::endl;
}	

void Calibrate::getFileData()
{
	cv::FileStorage in;
	in.open(a_inFile, cv::FileStorage::WRITE);
	in["BoardWidth"] >> a_boardWdth;
	in["BoardHeight"] >> a_boardHght;
	in["SquareSize"] >> a_squareSz;
	in["NumberofImages"] >> a_numImg;
	in["Directory"] >> a_dir;
	in["ZeroZoneWidth"] >> a_zZoneW;
	in["ZeroZoneHeight"] >> a_zZoneH;
	in["SearchWindowWidth"] >> a_sWinW;
	in["SearchWindowHeight"] >> a_sWinH;
	in["MaxIterations"] >> a_maxIter;
	in["Epsilon"] >> a_epsilon;

	a_boardSz = cv::Size(a_boardWdth, a_boardHght);
	a_sWinSz = cv::Size(a_sWinW, a_sWinH);
}

// void Calibrate::getFileData()
// {
// 	if(!a_inFile)
// 	{
// 		std::cout<< "Cannot open input file" <<std::endl;
// 		exit(1);
// 	}

// 	std::string line;
// 	for(std::string line; std::getline(a_inFile, line); )
// 	{
// 		if(line[0] != '#' && line.length() != 0)
// 		{
// 			std::istringstream in(line);
// 			std::string param;
// 			in >> param;

// 			if(param == "BoardWidth:")
// 			{
// 				in >> a_boardWdth;
// 			}
// 			else if(param == "BoardHeight:")
// 			{
// 				in >> a_boardHght;
// 			}
// 			else if(param == "SquareSize:")
// 			{
// 				in >> a_squareSz;
// 			}
// 			else if(param == "NumberOfImages:")
// 			{
// 				in >> a_numImg;
// 			}
// 			else if(param == "Directory:")
// 			{
// 				in >> a_dir;
// 			}
// 			else if(param == "ZeroZoneWidth:")
// 			{
// 				in >> a_zZoneW;
// 			}
// 			else if(param == "ZeroZoneHeight:")
// 			{
// 				in >> a_zZoneH;
// 			}
// 			else if(param == "SearchWindowWidth:")
// 			{
// 				in >> a_sWinW;
// 			}
// 			else if(param == "SearchWindowHeight:")
// 			{
// 				in >> a_sWinH;
// 			}
// 			else if(param == "MaxIterations:")
// 			{
// 				in >> a_maxIter;
// 			}
// 			else if(param == "Epsilon:")
// 			{
// 				in >>a_epsilon;
// 			}
// 			else
// 			{
// 				std::cout<<"Read Error"<<std::endl;
// 			}
// 		}
// 	}
// 	a_boardSz = cv::Size(a_boardWdth, a_boardHght);
// 	a_sWinSz = cv::Size(a_sWinW, a_sWinH);
// }

void Calibrate::writeData()
{
	cv::FileStorage fs;
	fs.open("a_outFile", cv::FileStorage::WRITE);
	fs << "Heading_1" << "##### CALIBRATION OUTPUT DATA #####";
	fs << "Subheading_1_1" << "CAMERA1 DATA #####";
	fs << "K1" << K1;
	fs << "D1" << D1;
	fs << "Subheading_1_2" << "CAMERA2 DATA #####";
	fs << "K2" << K2;
	fs << "D2" << D2;
	fs << "Subheading_1_3" << "RELATIONAL CAMERA DATA #####";
	fs << "R" << R;
	fs << "T" << T;
	fs << "E" << E;
	fs << "F" << F;
	fs << "Heading_2" << "##### RECTIFICATION OUTPUT DATA #####";
	fs << "Subheading_2_1" << "CAMERA1 DATA #####";
	fs << "P1" << P1;
	fs << "R1" << R1;
	fs << "Subheading_2_2" << "CAMERA2 DATA #####";
	fs << "P2" << P2;
	fs << "R2" << R2;
	fs << "Subheading_2_3" << "RELATIONAL CAMERA DATA #####";
	fs << "Q" << Q;
	fs.release();
}

void Calibrate::checkDir(boost::filesystem::path dir)
{
	if(!boost::filesystem::is_directory(dir))
	{
		boost::filesystem::create_directories(dir);
	}
}

//############### Single Camera Prototypes ###############//
void Calibrate::getSampleData(Camera Cam)
{
	//Check if directory exists for specific camera
	//If not, make one
	boost::filesystem::path dir( a_dir / Cam.getID());
	checkDir(dir);

	//Get number of frames from camera as specified in calibration document
	for(int i=0; i<a_numImg; i++)
	{
		cv::Mat frame, grey_frame;
		std::vector< cv::Point3f > obj;

		frame = Cam.getFrame(frame);

		cv::cvtColor(frame, grey_frame, CV_BGR2GRAY);
		cv::imwrite((dir.string() + '/' + Cam.getID() + std::to_string(i) + ".jpg"), grey_frame);
		calculate(frame, grey_frame, obj);
	}
}

void Calibrate::calculate(cv::Mat img, cv::Mat grey_img, std::vector< cv::Point3f > obj)
{
	bool found = cv::findChessboardCorners(img, a_boardSz, a_corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	if(found)
	{
		cv::cornerSubPix(grey_img, a_corners, a_sWinSz, a_zZoneSz, cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, a_maxIter, a_epsilon));
		cv::drawChessboardCorners(grey_img, a_boardSz, a_corners, found);

		//Should be a struct that is constructed elsewhere, no dependent variables
		for(int i=0; i<a_boardHght; i++)
		{
			for(int j=0; j<a_boardWdth; j++)
			{
				obj.push_back(cv::Point3f((float)j*a_squareSz, (float)i*a_squareSz, 0));
			}
		}

		a_imagePoints.push_back(a_corners);
		a_objectPoints.push_back(obj);
	}
}

//############### TWO CAMERA PROTOTYPES ###############// 

Calibrate::Calibrate(std::string inDir, std::string outDir, Camera cam1, Camera cam2) 
: a_inFile(inDir), a_outFile(outDir)//a_basePath(boost::filesystem::current_path())
{
	bool found;

	std::cout << "##### BEGINNING CALIBRATION ##### \n";
	getFileData();
	std::cout << "##### RETRIEVING SAMPLE IMAGES ##### \n";
	//printCalibrationData();
	found = getSampleData(cam1, cam2);
	if(found)
	{
		std::cout << "##### GENERATING RELATIONAL MATRICES ##### \n";
		cv::stereoCalibrate(a_objectPoints, a_imagePoints1, a_imagePoints2, K1, D1, K2, D2, a_frameSz, R, T, E, F);
		std::cout << "##### STARTING RECTIFICATION ##### \n";
		cv::stereoRectify(K1, D1, K2, D2, a_frameSz, R, T, R1, R2, P1, P2, Q);
		std::cout << "##### FINISHED RECTIFICATION ##### \n";
	}
	else
	{
		std::cout << "##### NO PATTERN DETECTED, CALIBRATION FAILED ##### \n";
	}
}

bool Calibrate::getSampleData(Camera Cam1, Camera Cam2)
{
	bool iFound oFound;
	checkDir(a_dir);

	boost::filesystem::path dir1( a_dir / Cam1.getID());
	boost::filesystem::path dir2( a_dir / Cam2.getID());

	checkDir(dir1);
	checkDir(dir2);

	for(int i=0; i<a_numImg; i++)
	{
		cv::Mat frame1, grey_frame1;
		cv::Mat frame2, grey_frame2;
		std::vector< cv::Point3f > obj;

		frame1 = Cam1.getFrame(frame1);
		frame2 = Cam2.getFrame(frame2);

		a_frameSz = frame1.size();

		cv::cvtColor(frame1, grey_frame1, CV_BGR2GRAY);
		cv::cvtColor(frame2, grey_frame2, CV_BGR2GRAY);

		cv::imwrite((dir1.string() + '/' + Cam1.getID() + std::to_string(i) + ".jpg"), grey_frame1);
		cv::imwrite((dir2.string() + '/' + Cam2.getID() + std::to_string(i) + ".jpg"), grey_frame2);

		iFound = getCorners(frame1, grey_frame1, frame2, grey_frame2, obj);
		if(iFound)
		{
			oFound = true;
		}
	}
	return oFound;
}

bool Calibrate::getCorners(cv::Mat img1, cv::Mat grey_img1, cv::Mat img2, cv::Mat grey_img2, std::vector< cv::Point3f > obj)
{
	bool found1 = cv::findChessboardCorners(img1, a_boardSz, a_corners1, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	bool found2 = cv::findChessboardCorners(img2, a_boardSz, a_corners2, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	if(found1 & found2)
	{
		cv::cornerSubPix(grey_img1, a_corners1, a_sWinSz, a_zZoneSz, cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, a_maxIter, a_epsilon));
		cv::cornerSubPix(grey_img2, a_corners2, a_sWinSz, a_zZoneSz, cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, a_maxIter, a_epsilon));

		cv::drawChessboardCorners(grey_img1, a_boardSz, a_corners1, found1);
		cv::drawChessboardCorners(grey_img2, a_boardSz, a_corners2, found2);

		//Should be a struct that is constructed elsewhere, no dependent variables
		for(int i=0; i<a_boardHght; i++)
		{
			for(int j=0; j<a_boardWdth; j++)
			{
				obj.push_back(cv::Point3f((float)j*a_squareSz, (float)i*a_squareSz, 0));
			}
		}

		a_imagePoints1.push_back(a_corners1);
		a_imagePoints2.push_back(a_corners2);

		a_objectPoints.push_back(obj);
	}
	return (found1 & found2);
}

//############### Mutliple Camera Prototypes ###############//
//This should take a frame from each camera do a calc on that set then get another set until all numImg met
// void Calibrate::getSampleData(std::vector< Camera > camList)
// {
// 	for(int i=0; i<a_numImg; i++)
// 	{
// 		boost::filesystem::path dir( a_dir / "SET" + j);
// 		checkDir(dir);

// 		for(int j=0; j<camList.size(); j++)
// 		{
// 			cv::Mat frame, grey_frame;
// 			std::vector< cv::Point3f > obj;

// 			frame = camList[j].getFrame(frame, true);
// 			cv::cvtColor(frame, grey_frame, CV_BGR2GRAY);
// 			cv::imwrite((dir.string() + '/' + Cam.getID() + std::to_string(i) + ".jpg"), grey_frame);
// 			set.push_back()
// 		}
// 	}
// }

// bool Calibrate::calculate(cv::Mat img, cv::Mat grey_img, std::vector< cv::Point3f > obj, int cam)
// {
// 	bool found = cv::findChessboardCorners(img, a_boardSz, a_corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
// 	if(found)
// 	{
// 		cv::cornerSubPix(grey_img, a_corners, a_sWinSz, a_zZoneSz, cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, a_maxIter, a_epsilon));
// 		cv::drawChessboardCorners(grey_img, a_boardSz, a_corners, found);
// 		for(int i=0; i<a_boardHght; i++)
// 		{
// 			for(int j=0; j<a_boardWdth; j++)
// 			{
// 				obj.push_back(cv::Point3f((float)j*a_squareSz, (float)i*a_squareSz, 0));
// 			}
// 		}
// 		a_imagePoints[cam].push_back(a_corners);
// 	}
// 	return found;
// }

// //***//***//***STRUCT FUNCTIONS***//***//***//

// //***BOARD FUNCTIONS***//
// void Board::setSize()
// {
// 	if(a_boardWdth != 0 && a_boardHght != 0)
// 	{
// 		a_boardSz = cv::Size(a_boardWdth, a_boardHght);
// 	}
// }

// //***SEARCH FUNCTIONS***//
// void Search::setWinSz()
// {
// 	if(a_sWinW != 0 && a_sWinH != 0)
// 	{
// 		a_sWinSz = cv::Size(a_sWinW, a_sWinH);
// 	}
// }