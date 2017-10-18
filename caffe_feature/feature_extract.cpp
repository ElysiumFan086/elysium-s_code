#include "feature_extract.hpp"
#include "xml_parser.h"

#include <glog/logging.h>

#include <caffe/layers/image_data_layer.hpp>
#include <caffe/layers/slice_layer.hpp>
#include <caffe/layers/conv_layer.hpp>
#include <caffe/layers/prelu_layer.hpp>
#include <caffe/layers/pooling_layer.hpp>
#include <caffe/blob.hpp>
#include <caffe/net.hpp>
#include <caffe/proto/caffe.pb.h>
#include <caffe/util/db.hpp>
#include <caffe/util/format.hpp>
#include <caffe/util/io.hpp>
#include <caffe/common.hpp>

#include <thread>

namespace caffe{
	extern INSTANTIATE_CLASS(SliceLayer);
	extern INSTANTIATE_CLASS(ConvolutionLayer);
	extern INSTANTIATE_CLASS(PReLULayer);
	extern INSTANTIATE_CLASS(PoolingLayer);
}

FaceFeature::FaceFeature(const std::string& str_config) : Feature(str_config)
{
	XMLParser parser_config;
	parser_config.readFile(str_config);
	this->str_pretrained_proto = parser_config.getParam("FE");
	this->str_netmodel_proto = parser_config.getParam("FE_enp");
	this->str_net_mode = parser_config.getParam("mode");
	this->str_layer_name = parser_config.getParam("input");
	this->str_blob_name = parser_config.getParam("output");
	this->str_data_name = parser_config.getParam("dataset_names");
	std::string str_dev_id = parser_config.getParam("device_id");
	this->n_device_idx = std::stoi(str_dev_id);
	std::string str_feat_len = parser_config.getParam("FeatureLen");
	this->n_feature_len = std::stoi(str_feat_len);

	#ifdef PRINT_LOG_INFO
		std::cout << "Pre-trained proto: " << str_pretrained_proto << std::endl;
		std::cout << "Net model proto: " << str_netmodel_proto << std::endl;
		std::cout << "Input layer name: " << str_layer_name << std::endl;
		std::cout << "Output layer name: " << str_blob_name << std::endl;
		std::cout << "Dataset name: " << str_data_name << std::endl;
		std::cout << "Device ID: " << n_device_idx << std::endl;
		std::cout << "Feature length: " << n_feature_len << std::endl;
	#endif

	/* Initial caffe::Net and related onjects */
	if (this->str_net_mode.compare("GPU") == 0){
		CHECK_GE(this->n_device_idx, 0);
		caffe::Caffe::SetDevice(this->n_device_idx);
		caffe::Caffe::set_mode(caffe::Caffe::GPU);
	}
	else{
		LOG(INFO) << "Build net using CPU.";
		caffe::Caffe::set_mode(caffe::Caffe::CPU);
	}
	this->net_extracting = new caffe::Net<float>(this->str_netmodel_proto, caffe::TEST, (caffe::Net<float>*)NULL);
	this->net_extracting->CopyTrainedLayersFrom(this->str_pretrained_proto);
}

void FaceFeature::extract_feature(cv::Mat& mat_img, float* p_feature, std::size_t& n_size){
	try{
		Caffe::set_mode(Caffe::GPU);
		const boost::shared_ptr<caffe::Layer<float> > layer = this->net_extracting->layer_by_name(this->str_layer_name);
		caffe::ImageDataLayer<float>* layer_img_data = (caffe::ImageDataLayer<float>*)layer.get();
		// Self-defined in caffe source code /include/layers/image_data_layer.hpp

		#ifdef PRINT_RUN_MODE
			if (Caffe::mode() == Caffe::GPU){
				std::cout << "Thread " << std::this_thread::get_id() << " runs on GPU" << std::endl;
			}
			else{
				std::cout << "Thread " << std::this_thread::get_id() << " runs on CPU" << std::endl;
			}
		#endif
			
		layer_img_data->SetImage(mat_img);
	}
	catch (std::exception e){
		LOG(ERROR) << "Set image error: " << e.what();
		n_size = 0;
		return;
	}

	CHECK(this->net_extracting->has_blob(this->str_blob_name))
		<< "Unknown feature blob name " << this->str_blob_name << " in the network ";

	std::vector<caffe::Blob<float>*> vec_input_blob;
	int n_batch_size = 0;

	try{
		this->net_extracting->Forward(vec_input_blob);
	}
	catch (std::exception e)
	{
		LOG(ERROR) << "Calculate forward network error: " << e.what();
		n_size = 0;
		return;
	}

	const boost::shared_ptr<caffe::Blob<float> > blob_feature
		= this->net_extracting->blob_by_name(this->str_blob_name);

	n_batch_size = blob_feature->num();
	int n_feature_dim = blob_feature->count() / n_batch_size;
	if (n_feature_dim != this->n_feature_len){
		LOG(ERROR) << "Output feature length not match wanted one "
			<< n_feature_dim << " vs. " << this->n_feature_len;
		n_size = 0;
		return;
	}

	float* blob_feature_data;

	for (int n = 0; n < n_batch_size; ++n) {
		blob_feature_data = blob_feature->mutable_cpu_data()
			+ blob_feature->offset(n);
		for (int d = 0; d < n_feature_dim; ++d) {
			p_feature[d] = blob_feature_data[d];
		}
	}
	n_size = n_batch_size * n_feature_dim;
}

void FaceFeature::extract_feature(cv::Mat& mat_img, std::vector<float>& vec_feature){

	float* p_feature_val = new float[this->n_feature_len];
	std::size_t n_feat_len = 0;
	this->extract_feature(mat_img, p_feature_val, n_feat_len);
	if (n_feat_len == 0)    return;

	for (std::size_t i = 0; i < n_feat_len; ++i){
		vec_feature.push_back(p_feature_val[i]);
	}

	delete[] p_feature_val;
	p_feature_val = NULL;
}

std::size_t FaceFeature::get_feature_size(){
	return n_feature_len;
}

Feature* create_feature_extractor(const std::string& str_xml_file){

	Feature *p = new FaceFeature(str_xml_file);
	return p;
}

void delete_extractor(Feature* p_feature){

	if (p_feature != NULL){
		delete p_feature;
		p_feature = NULL;
	}
}
