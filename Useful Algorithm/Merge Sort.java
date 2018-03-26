    
    public ArrayList<int[]> mergeSort(ArrayList<int[]> a){
    	if(a.isEmpty())
    		return a;
    	if(a.size()==1)
    		return a;
    	else{
    		int size=a.size();
    		int size_a=size/2;
    		int size_b=size-size_a;
    		
    		ArrayList<int[]> a_a = new ArrayList<int[]>(a.subList(0, size_a));
    		ArrayList<int[]> a_b = new ArrayList<int[]>(a.subList(size_a,size));
    		
    		return helper(a_a,a_b,size_a,size_b);
    	}
    }
    
    public ArrayList<int[]> helper(ArrayList<int[]> a, ArrayList<int[]> b,int sizea,int sizeb){
    	ArrayList<int[]> r = new ArrayList<int[]>();
    	if(a.size()==1&&b.size()==1)
    		return merge(a,b,r);
    	if(a.size()==1&&b.size()==0)
    		return a;
    	if(a.size()==0&&b.size()==1)
    		return b;
    	
    		int sizea_a=(sizea+1)/2;
    		int sizea_b=sizea-sizea_a;
    		int sizeb_a=(sizeb+1)/2;
    		int sizeb_b=sizeb-sizeb_a;
    		
    		ArrayList<int[]> a_a = new ArrayList<int[]>(a.subList(0, sizea_a));
    		ArrayList<int[]> a_b = new ArrayList<int[]>(a.subList(sizea_a,sizea));
    		ArrayList<int[]> b_a = new ArrayList<int[]>(b.subList(0, sizeb_a));
    		ArrayList<int[]> b_b = new ArrayList<int[]>(b.subList(sizeb_a,sizeb));
    		
    		return merge(helper(a_a,a_b,sizea_a,sizea_b), helper(b_a,b_b,sizeb_a,sizeb_b),r);
    		
    		
    	
    }
    
    public ArrayList<int[]> merge(ArrayList<int[]> a, ArrayList<int[]> b, ArrayList<int[]> r){
    	if(a.isEmpty()&&b.isEmpty())
    		return r;
    	
    	else
    		if ((b.isEmpty()&&!a.isEmpty())||(!a.isEmpty()&&a.get(0)[1]<b.get(0)[1])){
    			r.add(a.get(0));
    			
    			a.remove(0);
    			return merge(a,b,r);
    		}
    		else if((a.isEmpty()&&!b.isEmpty())||(!b.isEmpty()&&b.get(0)[1]<a.get(0)[1])){
    			r.add(b.get(0));
    			b.remove(0);
    			return merge(a,b,r);
			}
    		else
    			return r;
    	
    	
    }
}
