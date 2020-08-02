int tree_predict(double *attr){
	if(attr[1] < 12.810000){
		return -1;
	}else{
		if(attr[13] < 655.000000){
			return -1;
		}else{
			if(attr[2] < 1.145000){
				return -1;
			}else{
				return 1;
			}
		}
	}
}
