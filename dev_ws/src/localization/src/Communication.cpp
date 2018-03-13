#include <Communication.h>	

void Communication::write(cv::FileStorage& fs, const std::string&, const MyData& x)
{
	x.write(fs);
}

void Communication::read(const cv::FileNode& node, MyData& x, const MyData& default_value)
{
	if(node.empty())
	{
		x = default_value;
	}
	else
	{
		x.read(node);
	}
}

void Communication::getRobotData(std::vector<Robot*> roboList)
{
	cv::FileStorage in;
	in.open("Parameters.xml", cv::FileStorage::READ);

	if(!in.isOpened())
	{
		std::cout<< "Failed to Open XML FILE \n";
	}

	for(int i=0; i<roboList.size(); i++)	
	{
		in["red1LowerH"] >> roboList[i]->a_redThresh1[0];
		in["red1LowerS"] >> roboList[i]->a_redThresh1[1];
		in["red1LowerV"] >> roboList[i]->a_redThresh1[2];

		in["red1UpperH"] >> roboList[i]->a_redThresh1[3];
		in["red1UpperS"] >> roboList[i]->a_redThresh1[4];
		in["red1UpperV"] >> roboList[i]->a_redThresh1[5];

		in["red2LowerH"] >> roboList[i]->a_redThresh2[0];
		in["red2LowerS"] >> roboList[i]->a_redThresh2[1];
		in["red2LowerV"] >> roboList[i]->a_redThresh2[2];

		in["red2UpperH"] >> roboList[i]->a_redThresh2[3];
		in["red2UpperS"] >> roboList[i]->a_redThresh2[4];
		in["red2UpperV"] >> roboList[i]->a_redThresh2[5];

		in["greenLowerH"] >> roboList[i]->a_greenThresh[0];
		in["greenLowerS"] >> roboList[i]->a_greenThresh[1];
		in["greenLowerV"] >> roboList[i]->a_greenThresh[2];

		in["greenUpperH"] >> roboList[i]->a_greenThresh[3];
		in["greenUpperS"] >> roboList[i]->a_greenThresh[4];
		in["greenUpperV"] >> roboList[i]->a_greenThresh[5];

		in["whiteLowerH"] >> roboList[i]->a_whiteThresh[0];
		in["whiteLowerS"] >> roboList[i]->a_whiteThresh[1];
		in["whiteLowerV"] >> roboList[i]->a_whiteThresh[2];

		in["whiteUpperH"] >> roboList[i]->a_whiteThresh[3];
		in["whiteUpperS"] >> roboList[i]->a_whiteThresh[4];
		in["whiteUpperV"] >> roboList[i]->a_whiteThresh[5];

		in["blackLowerH"] >> roboList[i]->a_blackThresh[0];
		in["blackLowerS"] >> roboList[i]->a_blackThresh[1];
		in["blackLowerV"] >> roboList[i]->a_blackThresh[2];

		in["blackUpperH"] >> roboList[i]->a_blackThresh[3];
		in["blackUpperS"] >> roboList[i]->a_blackThresh[4];
		in["blackupperV"] >> roboList[i]->a_blackThresh[5];
	}
}

// void Communication::getCalibration_XMLData(Stereo* pClass)
// {
// 	cv::FileStorage in;
// 	in.open(pClass->getParamFile(), cv::FileStorage::READ);

// 	if(!in.isOpened())
// 	{
// 		std::cout<< "Failed to Open XML File \n";
// 	}

// 	in["BoardWidth"] >> pClass->a_pCal->boardWdth;
// 	in["BoardHeight"] >> pClass->a_pCal->boardHght;
// 	in["SquareSize"] >> pClass->a_pCal->squareSz;
// 	in["NumberOfImages"] >> pClass->a_pCal->numImg;
// 	in["Directory"] >> pClass->a_imgDir;
// 	in["ZeroZoneWidth"] >> pClass->a_pCal->zZoneW;
// 	in["ZeroZoneHeight"] >> pClass->a_pCal->zZoneH;
// 	in["SearchWindowWidth"] >> pClass->a_pCal->sWinW;
// 	in["SearchWindowHeight"] >> pClass->a_pCal->sWinH;
// 	in["MaxIterations"] >> pClass->a_pCal->maxIter;
// 	in["Epsilon"] >> pClass->a_pCal->epsilon;
// 	pClass->a_pCal->setExtra();

// 	in.release();
// }

// void Communication::getDisparity_XMLData(Stereo* pClass)
// {
// 	cv::FileStorage in;
// 	in.open(pClass->getParamFile(), cv::FileStorage::READ);

// 	if(!in.isOpened())
// 	{
// 		std::cout<< "Failed to Open XML File \n";
// 	}

// 	in["Preset"] >> pClass->a_pDis->preset;
// 	in["PreFilterType"] >> pClass->a_pDis->preFilType;
// 	in["PreFilterSize"] >> pClass->a_pDis->preFilSz;
// 	in["PreFilterCap"] >> pClass->a_pDis->preFilCap;
// 	in["TextureThreshold"] >> pClass->a_pDis->texThresh;
// 	in["SADWindowSize"] >> pClass->a_pDis->SADWinSz;
// 	in["NumberOfDisparities"] >> pClass->a_pDis->numDis;
// 	in["UniquenessRatio"] >> pClass->a_pDis->unique;
// 	in["SpeckleWindowSize"] >> pClass->a_pDis->speckleSz;
// 	in["SpeckleRange"] >> pClass->a_pDis->speckleRng;		

// 	in.release();
// }

// void Communication::writeCalibration_XMLData(Stereo* pClass)
// {
// 	cv::FileStorage out;
// 	out.open(pClass->getParamFile(), cv::FileStorage::WRITE);

// 	if(!out.isOpened())
// 	{
// 		std::cout<< "Failed to Open XML File \n";
// 	}

// 	out.writeComment("CALIBRATION OUTPUT DATA");
// 	out.writeComment("CAMERA1 DATA");
// 	out << "K1" << pClass->a_pCal->K1;
// 	out << "D1" << pClass->a_pCal->D1;
// 	out.writeComment("CAMERA2 DATA");
// 	out << "K2" << pClass->a_pCal->K2;
// 	out << "D2" << pClass->a_pCal->D2;
// 	out.writeComment("RELATIONAL CAMERA DATA");
// 	out << "R" << pClass->a_pCal->R;
// 	out << "T" << pClass->a_pCal->T;
// 	out << "E" << pClass->a_pCal->E;
// 	out << "F" << pClass->a_pCal->F;
// 	out.writeComment("RECTIFICATION OUTPUT DATA");
// 	out.writeComment("CAMERA1 DATA");
// 	out << "P1" << pClass->a_pCal->P1;
// 	out << "R1" << pClass->a_pCal->R1;
// 	out.writeComment("CAMERA2 DATA");
// 	out << "P2" << pClass->a_pCal->P2;
// 	out << "R2" << pClass->a_pCal->R2;
// 	out.writeComment("RELATIONAL CAMERA DATA");
// 	out << "Q" << pClass->a_pCal->Q;

// 	out.release();
// }

void Communication::checkDir(boost::filesystem::path dir)
{
	//std::cout<< "##### Checking if " << dir.string() << " Directory Exists ##### \n";

	if(!boost::filesystem::is_directory(dir))
	{
		boost::filesystem::create_directories(dir);
		//std::cout<< "##### Made " << dir.string() << " Directory ##### \n";
	}
}

void Communication::storeIMG(boost::shared_ptr< std::vector<cv::Mat> > imgList, std::string directory)
{
	boost::filesystem::path auxDir(directory);
	checkDir(auxDir);
	for(int i=0; i<imgList->size(); i++)
	{
		cv::imwrite(directory + '/' + "codeName_overwritten" + std::to_string(i) + ".jpg", (*imgList)[i]);
	}
}

void Communication::storeIMG(boost::shared_ptr< std::vector< std::vector< cv::Mat> > > imgList, std::string directory)
{
	boost::filesystem::path auxDir(directory);
	checkDir(auxDir);
	for(int i=0; i<imgList->size(); i++)
	{
		for(int j=0; j<(*imgList)[i].size(); j++)
		{
			cv::imwrite(directory + '/' + "codeName_overwritten" + std::to_string(i) + std::to_string(j) + ".jpg", (*imgList)[i][j]);
		}	
	}
}

// void Communication::storeIMG(Stereo* pClass)
// {
// 	boost::filesystem::path baseDir{pClass->a_imgDir};
// 	checkDir(baseDir);
// 	std::vector< Camera* > camList = pClass->getCamList();

// 	for(int i=0; i<camList.size(); i++)
// 	{
// 		//std::string name = camList[i]->a_ID;
// 		boost::filesystem::path branchDir( baseDir / camList[i]->getID());
// 		checkDir(branchDir);

// 		for(int j=0; j<pClass->a_imgList[i].size(); j++)
// 		{
// 			cv::imwrite((branchDir.string() + '/' + camList[i]->getID() + std::to_string(j) + ".jpg"), pClass->a_imgList[i][j]);
// 		}
// 	}
// }
