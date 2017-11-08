package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * For use in CSE 331 HW1.
 * This is the class you will be editing and turning in. It will be timed against our implementation
 * NOTE that if you declare this file to be in a package, it will not compile in Autolab
 */
public class Solution {

    private int numberOfMenAndWomen;


    // The following represent the preference list for the men and women.
    // The KEY represents the integer representation of a given man or woman.
    // The VALUE is a list, from most preferred to least, of the member of the opposite gender.
    private HashMap<Integer, ArrayList<Integer>> men;
    private HashMap<Integer, ArrayList<Integer>> women;
    private ArrayList<Matching> stableMatchings = new ArrayList<>();
    private int count;

    /**
     * The constructor simply sets up the necessary data structures.
     * The grader for the homework will first call this class and pass the necessary variables.
     * There is no need to edit this constructor.
     *
     * @param n The number of men/women.
     * @param men A map linking each man (integer value) with their preference list.
     * @param women A map linking each woman (integer value) with their preference list.
     */
    public Solution(int n, HashMap<Integer, ArrayList<Integer>> men, HashMap<Integer, ArrayList<Integer>> women){
        this.numberOfMenAndWomen = n;
        this.men = men;
        this.women = women;
    }

    /**
     * This method must be filled in by you. You may add other methods and subclasses as you see fit,
     * but they must remain within the HW1_Student_Solution class.
     * @return Your set of stable matches. Order does not matter.
     */
    public ArrayList<Matching> outputStableMatchings() {
    	count = 0;
        
        ArrayList<Marriage> tmp=new ArrayList<Marriage>();
        Matching tt=new Matching(tmp);

        for(int i=1;i<=numberOfMenAndWomen;i++)
        {
       		Marriage cpl=new Marriage(i,i);
       		tt.add(cpl);
       	}
        this.permutate( (Matching) tt, numberOfMenAndWomen);
        
        
        return this.stableMatchings;
    }
    private void permutate(Matching set, int length){
        if(length == 1){
        	int reFlag=0;
        	
        	
        	for(int j=0;j<numberOfMenAndWomen-1;j++){
        		for(int k=j+1;k<numberOfMenAndWomen;k++){
        			reFlag=0;
        			int tmpm1=set.get(j).man;
        			int tmpw1=set.get(j).woman;
        			int tmpm2=set.get(k).man;
        			int tmpw2=set.get(k).woman;
        			//System.out.println(men.get(tmpm2).indexOf(tmpw1)+","+men.get(tmpm2).indexOf(tmpw2));
        			//System.out.println(women.get(tmpw1).indexOf(tmpm2)+","+men.get(tmpw1).indexOf(tmpm1));
        			if((men.get(tmpm1).indexOf(tmpw2)< men.get(tmpm1).indexOf(tmpw1))&&(women.get(tmpw2).indexOf(tmpm1)< women.get(tmpw2).indexOf(tmpm2))||
        				(men.get(tmpm2).indexOf(tmpw1)< men.get(tmpm2).indexOf(tmpw2))&&(women.get(tmpw1).indexOf(tmpm2)< women.get(tmpw1).indexOf(tmpm1))){
        				//System.out.printf("1");
         				reFlag=1;
        				break;
        			}
        		}
        		if(reFlag==1)
    				break;
       		}
        	
        	if(reFlag==0){
        		Matching tmpSet= new Matching();
        		for(int m=0;m<set.size();m++){
        			int m1=set.get(m).man;
       				int m2=set.get(m).woman;
       				Marriage tmpM=new Marriage(m1,m2);
       				tmpSet.add(tmpM);
        		}
        		this.stableMatchings.add(tmpSet);
            	count++;
        	}
            //System.out.println(set);
        }
        else{
            for(int i = 0; i < length; i++){
                permutate(set, length - 1);
                int j = (length % 2 == 0 ) ? i : 0;
                Integer t = set.get(length-1).woman;
                set.get(length-1).woman = set.get(j).woman;
                set.get(j).woman = t;
            }
        }
    }

   

}
