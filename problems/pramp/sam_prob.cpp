// array of arrays of length 2
// start and end time of meeting
// can attend all meetings

// represent as 32bit integer

#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

typedef std::vector<uint32_t> Meeting;
typedef std::vector<Meeting> Schedule;

bool does_meeting_start_earlier(const Meeting& a, const Meeting& b)
{
	return a[0] < b[0];
}

bool does_meeting_end_earlier(const Meeting& a, const Meeting& b)
{
	return a[1] <= b[0];
}

bool is_schedule_valid(const Schedule& schedule)
{
	/*
	Time complexity is O(n) for going through schedule, and then in worst case when we have all events that start later earlier in array, 
	for each element in array we will move it back and forth. so n^2. could do heap instead perhaps.
	
	*/
	std::stack<Meeting> room;
	std::stack<Meeting> tmp;
	
	for (uint64_t i = 0; i < schedule.size(); i++)
	{
		Meeting meeting = schedule[i];
		// we want to store stack in a way that most recent events are the earlier in day events
		// to put a meeting into the stack, we want to pop off while the stack has some stuff and its events are earlier in the day than ours. if we can't put back on
		// we return a fail
		
		while (room.size() > 0 && does_meeting_start_earlier(room.top(), meeting))
		{
			Meeting prior_meeting = room.top();
			room.pop();
			tmp.push(prior_meeting);
		}
		
		if (room.size() > 0 && !does_meeting_end_earlier(meeting, room.top()))
		{
			return false;
		}
		
		room.push(meeting);
		
		for (uint64_t j = 0; j < tmp.size(); j++)
		{
			Meeting prior_meeting = tmp.top();
			if ((!does_meeting_start_earlier(prior_meeting, room.top())) || (!does_meeting_end_earlier(prior_meeting, room.top())))
			{
				return false;
			}
			room.push(prior_meeting);
			tmp.pop();
		}
	}
	return true;
	
}

void print_schedule(const Schedule& schedule)
{
	for (uint64_t i = 0; i < schedule.size(); i++)
	{
		Meeting meeting = schedule[i];
		std::cout << "meeting: " << meeting[0] << "," << meeting[1] << std::endl;
	}
}



int main()
{
	Schedule schedule;
	std::vector<uint32_t> meeting_1;
	meeting_1.push_back(1);
	meeting_1.push_back(9);
	schedule.push_back(meeting_1);
	
	meeting_1[0] = 2;
	meeting_1[1] = 3;
	schedule.push_back(meeting_1);
	
	meeting_1[0] = 3;
	meeting_1[1] = 4;
	schedule.push_back(meeting_1);
	
	std::cout << "schedule result " << is_schedule_valid(schedule) << std::endl;
}

