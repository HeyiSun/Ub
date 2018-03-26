
bool neighborhoodIsViable(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          bool* const chosenCust) {
    int a=1;int i,j;
    int bandSum;
    int priceSum;

    for(i=0;i<numCust;i++)
    {
        a=a*2;
    }
    a-=1;
    
    for(j=1;j<=a;j++)
    {
        int para=j;
        bandSum=0;
        priceSum=0;
	
        for(i=0;i<numCust;para/=2,i++){
            if(para%2==1) {
                bandSum += reqBand[i];
                priceSum += reqPrice[i];
                chosenCust[i]=true;
            }
            else{
                chosenCust[i]=false;
            }
        }
        if(bandSum<=maxBandwidth && priceSum>=maintenanceCost)
        {
            return true;
        }
    }
    return false;

}


// Bonus function.

bool neighborhoodIsViableMaxProfit(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          bool* const chosenCust) {
    int a=1;int i;
    int index;
    int profit=0;
    int bandSum;
    int priceSum;

    for(i=0;i<numCust;i++)
    {
        a=a*2;
    }
    a-=1;

    for( ;a>0;a--)
    {
        int para=a;
        bandSum=0;
        priceSum=0;
	
        for(i=0;i<numCust;para/=2,i++){
            if(para%2==1) {
                bandSum += reqBand[i];
                priceSum += reqPrice[i];
            }
        }
	//cout<<":  "<<bandSum<<","<<priceSum<<endl; 
        if(bandSum<=maxBandwidth && priceSum>=maintenanceCost)
        {
            if (priceSum>profit){
		index=a;profit=priceSum; 
		}
        }
	
    }
    if(profit!=0)
    {
          for(i=0;i<numCust;i++,index/=2)
	  {
		if(index%2==1)
			chosenCust[i]=true;
		else
			chosenCust[i]=false;
          }
	  return true;

    }
    else{
    	return false;
    }
}



// Bonus function.
bool neighborhoodIsViablePartialBand(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          double* const chosenCust) {
        double* ratio = new double[numCust];
	int* index= new int[numCust];
	int i;
	int sumBand=0;
	int sumPrice=0;
	
	for(i=0;i<numCust;i++){
		ratio[i]=reqPrice[i]*1.0/reqBand[i];
		index[i]=i;
		chosenCust[i]=0;
	}
	
	for(i=0; i<numCust;i++)
	{
		for(int j=i+1 ;j<numCust;j++)
		{
			if(ratio[i]<ratio[j])
			{
				double tempd= ratio[j];
				ratio[j]=ratio[i];
				ratio[i]=tempd;

				int tempi=index[j];
				index[j]=index[i];
				index[i]=tempi;
			}
		}
	}
	//std::cout<<"index: "<<index[0]<<","<<index[1]<<","<<index[2]<<","<<index[3]<<","<<index[4]<<endl;
	
	for(i=0 ; i<numCust ; i++)
	{
		chosenCust[index[i]]=1;
               // cout<<"i="<<i<<endl;
		sumBand+=reqBand[index[i]];    //cout<<"sumBand="<<sumBand<<endl;
		sumPrice+=reqPrice[index[i]];    //cout<<"sumPrice="<<sumPrice<<endl;
		if(sumBand>maxBandwidth)
		{
			sumBand-=reqBand[index[i]];
			sumPrice-=reqPrice[index[i]];
			break;
		}
	}
	//cout<<"finally  i="<<i<<endl;
	if(i==numCust)
	{
		if(sumPrice>maintenanceCost)
			return true;
		else	
		return false;
	}
	else{
		chosenCust[index[i]]=(maxBandwidth - sumBand)*1.0/reqBand[index[i]];
		if( sumPrice+ reqPrice[index[i]] * chosenCust[index[i]]>=maintenanceCost   )
		{
			return true;
		}
		else
			return false;
		
	
	}	
}
