package ub.cse.algo;

import java.util.HashMap;
import java.util.ArrayList;

/**
 * For use in CSE 331 HW1.
 * This is the class you will be editing and turning in. It will be timed against our implementation
 * NOTE that if you declare this file to be in a package, it will not compile in Autolab
 */

public class Solution {
	private int _nHospital;
	private int _nStudent;

    // The following represent the preference list of hospitals and students.
    // The KEY represents the integer representation of a given hospital or student.
    // The VALUE is a list, from most preferred to least.
    // For hospital, first element of the list is number of available slots
	private HashMap<Integer, ArrayList<Integer>> _hospitalList;
	private HashMap<Integer, ArrayList<Integer>> _studentList;
    
    
    /**
     * The constructor simply sets up the necessary data structures.
     * The grader for the homework will first call this class and pass the necessary variables.
     * There is no need to edit this constructor.
     * @param m Number of hospitals
     * @param n Number of students
     * @param A map linking each hospital with its preference list
     * @param A map linking each student with their preference list
     * @return
     */
	public Solution(int m, int n, HashMap<Integer, ArrayList<Integer>> hospitalList, HashMap<Integer, ArrayList<Integer>> studentList) {
		_nHospital = m;
		_nStudent = n;
		_hospitalList = hospitalList;
		_studentList = studentList;
		
	}
    
    /**
     * This method must be filled in by you. You may add other methods and subclasses as you see fit,
     * but they must remain within the HW1_Student_Solution class.
     * @return Your stable matches
     */
	public ArrayList<Match> getMatches() {
		
		ArrayList<Match> result=new ArrayList<Match>();
		
		/*ArrayList<ArrayList<Integer>> hos=new ArrayList<ArrayList<Integer>>();
		for(int i=0;i<_nHospital;i++){
			ArrayList<Integer> tmpList=new ArrayList<Integer>();
			hos.add(tmpList);
		}*/
		
		int tgStu=0;
		int tgHosp=0;
		int curSize=0;
		ArrayList<Integer> hospSize=new ArrayList<Integer>();
		ArrayList<Integer> hospSet=new ArrayList<Integer>();
		ArrayList<ArrayList<Integer>> stud=new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> hosp=new ArrayList<ArrayList<Integer>>();
		
		for(int i=1;i<=_nHospital;i++){
			hospSize.add(_hospitalList.get(i).get(0));
			_hospitalList.get(i).remove(0);
			//System.out.println(_hospitalList.get(i).get(0));
		}
		
		for(int i=1;i<=_nHospital;i++){
			hospSet.add(i);
		}
		
		for(int i=1;i<=_nHospital;i++){
			ArrayList<Integer> tmpHosp=new ArrayList<Integer>();
			tmpHosp.add(i);
			tmpHosp.add(0);
			hosp.add(tmpHosp);
		}
		
		for(int i=1;i<=_nStudent;i++){
			ArrayList<Integer> tmpStud=new ArrayList<Integer>();
			tmpStud.add(i);
			tmpStud.add(0);	
			stud.add(tmpStud);
		}
		
		while(!hospSet.isEmpty()){
			tgHosp=hospSet.get(0);
			if(!_hospitalList.get(tgHosp).isEmpty()){
				tgStu=_hospitalList.get(tgHosp).get(0);
//				System.out.println(tgStu);
				_hospitalList.get(tgHosp).remove(0);
			}else
				//hospSet.remove(0);
				;
			int flagStu=stud.get(tgStu-1).get(1);
			
			if(flagStu==0){
				//result.add(new Match(tgHosp,tgStu));
				curSize=hosp.get(tgHosp-1).get(1)+1;
				hosp.get(tgHosp-1).set(1, curSize);
				if(curSize==hospSize.get(tgHosp-1)){
					hospSet.remove(0);
				}
				stud.get(tgStu-1).set(1,tgHosp);
			}else{
				int cmpHosp=stud.get(tgStu-1).get(1);
				if(_studentList.get(tgStu).indexOf(cmpHosp)>_studentList.get(tgStu).indexOf(tgHosp)){
					int tmp=hosp.get(cmpHosp-1).get(1)-1;
					hosp.get(cmpHosp-1).set(1, tmp);
					curSize=hosp.get(tgHosp-1).get(1)+1;
					hosp.get(tgHosp-1).set(1, curSize);
					if(!hospSet.contains(cmpHosp)){
						hospSet.add(cmpHosp);
					}
					if(curSize==hospSize.get(tgHosp-1)){
						hospSet.remove(0);
					}
					
					stud.get(tgStu-1).set(1,tgHosp);
				}else if(_studentList.get(tgStu).indexOf(cmpHosp)<_studentList.get(tgStu).indexOf(tgHosp)){
					//System.out.println(11);;
				}
			}
			
			
		}
		
		for(int i=0;i<_nStudent;i++){
			if(stud.get(i).get(1)!=0){
				result.add(new Match(stud.get(i).get(0),stud.get(i).get(1)));
			}
		}
        // Returns an empty ArrayList for now
        return result;
	}
}
