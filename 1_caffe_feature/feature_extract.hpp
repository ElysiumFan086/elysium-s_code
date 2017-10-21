#ifndef _EXTRACT_FEATURE_H_
#define _EXTRACT_FEATURE_H_

#include <string>
#include <iostream>
#include <iomanip>

#include <opencv2/opencv.hpp>

#include <google/protobuf/text_format.h>

#include <caffe/blob.hpp>
#include <caffe/common.hpp>
#include <caffe/proto/caffe.pb.h>
#include <caffe/util/db.hpp>
#include <caffe/util/format.hpp>
#include <caffe/util/io.hpp>
#include <caffe/layers/image_data_layer.hpp>
#include <caffe/net.hpp>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/algorithm/string.hpp>

// #define FEATURE_NUM 5

using namespace caffe;

/***
 * Base class for feature extraction.
 *  This is s pure virtual class, which is mainly derived to FaceFeature.
 */
class Feature
{
public:
	/* Constructor and destructor */
	Feature(const std::string& str_config_file) { };
	virtual ~Feature() { }

	/* Feature extraction interface. (Overload 2) */
	virtual void extract_feature(cv::Mat& mat_img, float* p_feature, std::size_t& n_size) = 0;
	virtual void extract_feature(cv::Mat& mat_img, std::vector<float>& vec_feature) = 0;

	virtual int  get_feature_size() = 0;
};

class FaceFeature : public Feature{
public:
	/**  FaceFeature
	 *   @brief: constructor for FaceFeature class
	 *   @parameter:
	 *       str_config -- Input configuration file path, currently only accept XML file.
	 */
	FaceFeature(const std::string& str_config);
	virtual ~FaceFeature() { };

	/**  extract_feature
	 *   @brief: extracting features for a given cv::Mat image (overload +1)
	 *   @parameter:
	 *       mat_img   -- _IN_  Input face image Mat, it is asked to be a three channels image
	 *       p_feature -- _OUT_ pointer to output feature array
	 *       n_size    -- _OUT_ feature array length, and if correct equals to n_feature_len
	 */
	void extract_feature(cv::Mat& mat_img, float* p_feature, std::size_t& n_size);

	/**  extract_feature
	 *   @brief: extracting features for a given cv::Mat image (overload +2)
	 *   @parameter:
	 *       mat_img     -- _IN_  Input face image Mat, it is asked to be a three channels image
	 *       vec_feature -- _OUT_ Contrainer for output feature value, whose size equals to n_feature_len if correct
	 */
	void extract_feature(cv::Mat& mat_img, std::vector<float>& vec_feature);

	/**  get_feature_size
	 *   @brief: return the feature vector's size extracted by given model
	 */
	std::size_t get_feature_size();

private:
	caffe::Net<float>* net_extracting;           // Pointer to caffe Net object
	std::string        str_pretrained_proto;     // Pretrained binary model file path
	std::string        str_netmodel_proto;       // Loaded net model prototxt file path
	std::string        str_net_mode;             // Net running mode (alternative for CPU or GPU)
	std::string        str_layer_name;           // Input layer name
	std::string        str_blob_name;            // Output feature blob name
	std::string        str_data_name;            // Input dataset file path, in which contains a 
	//  single file path used for pre-load net weights.

	int         n_device_idx;                    // Net running device ID(unuse in CPU mode)
	std::size_t n_feature_len;                   // Feature vector size, which is coresponding to output blob count.
};

/** create_feature_extractor
 *  @brief: Creating a ointer to a feature exracting instance
 *  @parameter:
 *      str_xml_file -- _IN_ Configuration XML file path
 *  @return: Return a FaceFeature pointer if success and NULL otherwise.
 */
Feature* create_feature_extractor(const std::string& str_xml_file);

/** delete_extractor
 *  @brief: Deleting a feature extracing pointer and free related recouses
 *  @parameter:
 *      p_feature -- _IN_ Pointer to be deleted.
 */
void delete_extractor(Feature* p_feature);

#endif