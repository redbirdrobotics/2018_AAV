#include "Calibration.h"

Calibration::Calibration(uint8_t num_cams, cv::Size frame_size, cv::Size fov)
:_num_cams(num_cams), _frame_size(frame_size), _fov(fov)
{
	MakePixelMap(frame_size, fov);
}

void Calibration::MakePixelMap(cv::Size frame_size, cv::Size fov)
{
	// One pixel before center since resolution is even
	cv::Point_<int> center;
	center.x = (frame_size.width/2)-1;
	center.y = (frame_size.height/2)-1;

	// Make single channel, float matrix of equal size to top left quater of frame size
	cv::Mat img_remap_tl(center.y, center.x, CV_64FC1);
	cv::Mat img_remap_tr(center.y, center.x, CV_64FC1);
	cv::Mat img_remap_bl(center.y, center.x, CV_64FC1);
	cv::Mat img_remap_br(center.y, center.x, CV_64FC1);
	cv::Mat img_remap_th(center.y, frame_size.width, CV_64FC1);
	cv::Mat img_remap_bh(center.y, frame_size.width, CV_64FC1);

	_img_remap.convertTo(_img_remap, CV_64FC1);

	// each pixel is equal to resolution divided by field of view
	double pixel_degree = frame_size.width/fov.width;

	// Populate top left quarter of map
	for(int i=0; i<center.y; i++)
	{
		for(int j=0; j<center.x; j++)
		{
			double distance = sqrt(pow((center.y - i),2) + pow((center.x - j),2));
			img_remap_tl.at<double>(i,j) = distance*pixel_degree;
		}
	}

	// Flip top left matrix to get all quarters
	cv::flip(img_remap_tl, img_remap_tr, 1);
	cv::flip(img_remap_tl, img_remap_bl, 0);
	cv::flip(img_remap_tl, img_remap_br, -1);

	// Combine left and right quarters
	cv::hconcat(img_remap_tl, img_remap_tr, img_remap_th);
	cv::hconcat(img_remap_bl, img_remap_br, img_remap_bh);

	// Combine remaining top and bottom halves
	cv::vconcat(img_remap_th, img_remap_bh, _img_remap);
}

void Calibration::SetCalibrationParams(cv::Size board_size, float board_square_size, cv::Size search_win_size, cv::Size zero_zone_size, int max_iter, float epsilon)
{
	_board_size = board_size;
	_board_square_size = board_square_size;
	_search_win_size = search_win_size;
	_zero_zone_size = zero_zone_size;
	_max_iter = max_iter;
	_epsilon = epsilon;
}

void Calibration::GetCheckerboard(boost::shared_ptr< std::vector< std::vector< cv::Point3f > > > checkerboard_vect_ptr, cv::Size board_size, int square_size)
{
	if(checkerboard_vect_ptr->empty())
	{
		std::vector< cv::Point3f > checkerboard;
		for(int i=0; i<board_size.height; i++)
		{
			for(int j=0; j<board_size.width; j++)
			{
				checkerboard.push_back(cv::Point3f((float)j*square_size, (float)i*square_size, 0));
			}
		}
		checkerboard_vect_ptr->push_back(checkerboard);
	}
	else
	{
		std::vector< cv::Point3f > checkerboard((*checkerboard_vect_ptr)[0]);
		checkerboard_vect_ptr->push_back(checkerboard);
	}
}

void Calibration::Calibrate_UseImgSet(boost::shared_ptr< std::vector< cv::Mat > > img_set, bool draw_corners)
{
	cv::Mat img, grey_img;

	for(int i=0; i<img_set->size(); i++)
	{
		cv::cvtColor((*img_set)[i], grey_img, CV_BGR2GRAY);
		bool found = cv::findChessboardCorners(img, _board_size, _corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

		if(!found) continue;

		cv::cornerSubPix(grey_img, _corners, _search_win_size, _zero_zone_size, cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, _max_iter, _epsilon));

		if(draw_corners)
		{
			cv::drawChessboardCorners(grey_img, _board_size, _corners, found);
		}

		GetCheckerboard(_object_points, _board_size, _board_square_size);
		_image_points->push_back(_corners);
		_confirmed_image_set->push_back(grey_img);
	}

	_error = cv::calibrateCamera((*_object_points),
						(*_image_points),
						_frame_size,
						_camera_mat,
						_distortion_mat,
						_rotational_vect,
						_translational_vect,
						CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);
}

// void Calibration::MakeViewAngleMap(cv::Mat, cv::Size frame_size)
// {
// 	cv::Mat< cv::Point2f > point_mat(frame_size.height, frame_size.width);

// 	for(int i=0; i<frame_size.height; i++)
// 	{
// 		for(int j=0; j<frame_size.width; j++)
// 		{
// 			cv::Point2f point = (i,j);
// 			point_mat.at<cv::Point2f>(i,j) = point;
// 		}
// 	}
// 	cv::undistortPoints(point_vect, cv::Mat, _camera_mat, _distortion_mat);
// }