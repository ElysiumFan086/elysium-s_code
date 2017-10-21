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
	if(mat_img.empty() || n_compress < 0 || n_compress > 100){
		return std::string("");
	}

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

/**
 * Convert image string, which is encoding with 'mat_to_string', into cv::Mat.
 * 
 * @param str_img_string : _IN_ image data string
 * @return : cv::Mat object, if input an empty string, it will return an empty cv::Mat.
 */
cv::Mat string_to_mat(const std::string& str_img_string){
	if(str_img_string.empty()){
		return cv::Mat();
	}

	cv::vector<uchar> vec_img_buff;
	for(int i = 0; i < str_img_string.length(); ++i)
		vec_img_buff.push_back(str_img_string[i]);

	cv::Mat mat_image = cv::imdecode(cv::Mat(vec_img_buff), CV_LOAD_IMAGE_COLOR);
	return mat_image;
}

#endif