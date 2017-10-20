#ifndef _MAT_STRING_CONVEERT_
#define _MAT_STRING_CONVEERT_

#include <opencv2/opencv.hpp>

/**
 * Convert OpenCV cv::Mat structure into char squence, so that it can be used for 
 * sending to somewhere with Socket or inserting into database as Blob.
 *
 * @param mat_img : _IN_ input cv::Mat object to be converted
 * @param n_compress : _IN_ compressing factor that control the encoding quality.
 * @return : return a non-empty string if converting successfully, and return empty string otherwise.
 */
std::string mat_to_string(cv::Mat& mat_img, int n_compress = 95){
	std::vector<uchar> vec_img_buff;
	std::vector<int>   vec_params = std::vector<int>(2);
	vec_params[0] = CV_IMWRITE_JPEG_QUALITY;
	vec_params[1] = n_compress;    //default(95) 0-100 
	char* p_img_data = NULL;
	std::size_t n_img_len = 0;
	std::string str_img_string;
	if (true == cv::imencode(".jpg", mat_img, vec_img_buff, vec_params))
	{
		str_img_string = std::string((char*)vec_img_buff.data(), vec_img_buff.size());
	}

	return str_img_string;
}

#endif