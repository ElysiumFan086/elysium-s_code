/**
 * This file is a simple demo for how to use self-sealed interface to extract a 
 * given image(with cv::Mat format)'s feature vector with pre-trained deep lea-
 * rning model, under the Deep Learning architecture 'caffe'. Since the original 
 * code of 'caffe' is mainly used for training Deep Learning model with the input  
 * data format of LMDB, and it is not good at processing single input inmage of
 * cv::Mat, so some modifying work is performed with original 'caffe' code, one 
 * can browse the modified code at:
 *    https://github.com/ElysiumFan086/caffe 
 */

#include "feature_extract.hpp"
#include <vector>

int main(int argc, char* argv[]){
	if(argc != 3){
		std::cout << "You may have to input a path for an existing \
			image file and the configuration file for feature extraction." << std::endl;
		return -1;
	}

	std::string str_img_path = std::string(argv[1]);
	cv::Mat mat_img = cv::imread(str_img_path);

	if(mat_img.empty()){
		std::cout << "Fail to read image from path: " << str_img_path << std::endl;
		return -2;
	}

	std::string str_config = std::string(argv[2]);
	Feature* p_extractor = create_feature_extractor(str_config);
	if(p_extractor == NULL){
		std::cout << "Fail to create feature extractor with config file: " << str_config << std::endl;
		return -3;
	}

	std::vector<float> vec_feature;
	p_extractor->extract_feature(mat_img, vec_feature);
	if(vec_feature.empty()){
		std::cout << "Extract empty feature value!" << std::endl;
		goto FINISHI_EXTRACT;
	}

	for(auto itr = vec_feature.begin(); itr != vec_feature.end(); ++itr){
		std::cout << *itr << '\t';
	}
	std::cout << std::endl;

FINISHI_EXTRACT:
	delete_extractor(p_extractor);

	return 0;
}
