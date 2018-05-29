#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/make_shared.hpp>

#ifndef CALIBRATION_CLASS
#define CALIBRATION_CLASS

class Calibration
{

private:

	// Parameters
	uint8_t _num_cams;
	cv::Size _frame_size;
	cv::Size _fov;
	cv::Size _fov_rad;
	cv::Size _board_size;
	float _board_square_size;
	cv::Size _search_win_size;
	cv::Size _zero_zone_size;
	int _max_iter;
	float _epsilon;

	// Containers
	cv::Mat _img_remap;
	boost::shared_ptr< std::vector< std::vector< cv::Point3f > > > _object_points = boost::make_shared< std::vector< std::vector< cv::Point3f > > >();
	boost::shared_ptr< std::vector< std::vector< cv::Point2f > > > _image_points = boost::make_shared< std::vector< std::vector< cv::Point2f > > >();
	boost::shared_ptr< std::vector< cv::Mat> > _confirmed_image_set;
	std::vector< cv::Point2f > _corners;
	cv::Mat _camera_mat, _distortion_mat; 
	std::vector< cv::Mat > _rotational_vect, _translational_vect;
	double _error;

	void GetCheckerboard(boost::shared_ptr< std::vector< std::vector< cv::Point3f > > >, cv::Size, int);
	void MakePixelMap(cv::Size, cv::Size);

public:

	Calibration(uint8_t, cv::Size, cv::Size);
	void SetCalibrationParams(cv::Size, float, cv::Size, cv::Size, int, float);
	void Calibrate_UseImgSet(boost::shared_ptr< std::vector< cv::Mat > >, bool);
};

#endif