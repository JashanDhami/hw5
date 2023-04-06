#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelp(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts, 
    DailySchedule& sched, map<int, int>& shifts,
		int day, unsigned int shift
		);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

		// int n = avail.size();  // number of days 
		int k = avail[0].size();  //number of workers 

		map<int, int> shifts; // a map of all the workers and their shifts 
		for(int i = 0; i < k; i++){
			shifts[i] = 0; //everyone starts with 0 shifts
		}

		// std:: cout << INVALID_ID << std::endl; 
		// sched.resize(avail.size(), vector<Worker_T>(maxShifts, INVALID_ID));
		sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
 
	
	return scheduleHelp(avail, dailyNeed, maxShifts, sched, shifts, 0, 0 );

}


bool scheduleHelp(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts, 
    DailySchedule& sched, map<int, int>& shifts,
		int day, unsigned int shift
		)
{

	//base case entire schedue is filled
	// if(day == sched.size() || shift == maxShifts){
	// 	return true; 
	// }
	if(day == sched.size()){
		// std:: cout << "DEBUG5" << std:: endl; 
		return true; 
	}

	// if(shift == dailyNeed){ // end of row 
	// 		shift =0; 
	// 		worker = 0;
	// 		return scheduleHelp(avail, dailyNeed, maxShifts, sched, shifts, day+1 , worker, shift);
	// 	}
	

	
	
	//loop through the workers
	// for(unsigned int i = worker; i < avail[day].size(); i++){

	for(unsigned int i = 0; i < avail[day].size(); i++){
			
		if(shifts[i] == maxShifts || avail[day][i] != 1){// move on to the next
			// std:: cout << "Debug:" << std:: endl; 
			continue;
		}

	// std:: cout << "Shift:" << shift << std:: endl; 
		if(shifts[i] < maxShifts && avail[day][i] == 1){
			// std:: cout << "Debug:1" << std:: endl; 
			//update schedule 
			sched[day][shift] = i; 
			//update workers shifts count
			shifts[i]++; 
		

		bool helper = false; 
	// std:: cout << sched[day].size() -1 << std:: endl; 
		if(shift == sched[day].size() -1){
			// std:: cout << "Debug:2" << std:: endl; 
			shift = 0; 
			helper = scheduleHelp(avail, dailyNeed, maxShifts, sched, shifts, day+1 , shift);

		}

		else{
			// std:: cout << "Debug:3" << std:: endl; 
			helper = scheduleHelp(avail, dailyNeed, maxShifts, sched, shifts, day, shift+1); 	
		}

		if(helper){
			// std:: cout << "Debug:4" << std:: endl; 
			return true;
		}

		//backtracking 
		shifts[i]--;
		sched[day][shift] = INVALID_ID; 
		
	}
}
	return false; 
	
}


// 	// 	if(shifts[i] <= maxShifts){
			
// 	// 			sched[day][shift] = i;
// 	// 			shifts[i]++; 

// 	// 		if(avail[day][i] == 1){
// 	// 			bool helper = scheduleHelp(avail, dailyNeed, maxShifts, sched, shifts, day, i, shift+1); 	
// 	// 				if(helper)
// 	// 						return true;
// 	// 		}
// 	// 	}

// 	// 	//backtracking 
// 	// 		shifts[i]--;
// 	// 		sched[day][shift] = INVALID_ID; 

// 	// }

// 	// 	return false; 



// }

