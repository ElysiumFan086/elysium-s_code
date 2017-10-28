struct Interval {
	int start; 
	int end; 
	Interval() : start(0), end(0) {} 
	Interval(int s, int e) : start(s), end(e) {} 
}; 

std::vector<Interval> merge_interval(std::vector<Interval> &vec_inter) {
	std::vector<Interval> vec_res;
	std::sort(vec_inter.begin(), vec_inter.end(), [](const Interval& a, const Interval& b)->{
		return a.start < b.start;
	});

	vec_res.push_back(vec_inter[0]);
	for(std::size_t i = 1; i < vec_inter.size(); ++i) {
		if(vec_res.back().end >= vec_inter[i].start) {
			vec_res.back.end = max(res.back.end, vec_inter[i].end);
		}
		else {
			vec_res.push_back(vec_inter[i]);
		}
	}

	return vec_res;
}