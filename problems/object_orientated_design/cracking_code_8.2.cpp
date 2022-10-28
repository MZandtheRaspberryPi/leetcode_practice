/*
Imagine call center w/ 3 levels employees: respondant, manager, director
incoming call must first be allocated to respondant free. if respondant cant handle
must escalate to manager. if manager not free or not able handle
escalate to director
desgin classes and datastructure for pbolem

implement method dispatchCall which assigns call to first available employee

*/

/*
Handle mabiguity: who, what, where, when, why, how

who, is this an emergency service like 911, where people are calling in danger? Or like tech support for software. How important are missed calls?
what, what are we supporting, are calls typically short or do they stretch longer?
where, are all employees geographically in same area, could influence model.
when,
why 
how

*/

/*
core objects
enum callstatus, in progress, terminated, needs_escalation
enum employee type
employee
call center
call
*/

/* relationships
a call center has multiple employees, in fact it has arrays of respondant, manager, and director. some are processing calls currently, some are free.
  a call center also has a list of calls in process. a call center also has a map of employee pointers and call pointers, to keep track of who is working on what.
a call has escalation level, which determines which next employee has to handle
an employee can take a call, one at a time, and then handle it which sometimes is succesful and sometimes is not successful.
*/

/*
actions
a call center is created and is assigned employees. As calls come it checks call level of employee required, and takes first available employee
  and assigns the call. it periodoically checks then the employee and if the and the call status, and if it is finished makes the employee
	free and then removes the call from list. if call needs escalation it frees that employee, puts them into available queue, and increments
	escalation level of call and tries to assign next employee.
	
An employee can take a call, and then return status of that call.
*/

#include <queue>
#include <vector>

enum CallStatus
{
	NotStarted,
	InProgress,
	Terminated,
	NeedsEscalation
};

enum EmployeeType
{
	Respondent,
	Manager,
	Director
};

class Call
{
	public:
		Call(EmployeeType employee_needed) : employee_needed(employee_needed) {}
		EmployeeType getEmployeeNeeded();
		void incrementEmployeeNeeded();
		CallStatus getStatus();
		void setStatus(CallStatus status);
	
	private:
	  EmployeeType employee_needed;
		CallStatus status;
};

class Employee
{
	private:
	  int id;
		bool isCallInProgress = false;
		Call * callInProgress;
		EmployeeType type;
		
	public:
	  int getId();
		EmployeeType getEmployeeType();
		CallStatus getCallStatus();
		Call* getCallInProgress();
		bool takeCall(Call* call);
		void endCall();
};



class CallCenter
{
	
	private:
	  std::queue<Employee *> availableRespondents;
		
	  std::queue<Employee *> availableManagers;
		
	  std::queue<Employee *> availableDirectors;
		
		std::vector<Call> calls;
		std::queue<Employee *> busyEmployees;
		
		std::vector<Employee> employees;
		
		removeCall(Call* call_to_remove);
		
	  bool assignCall(std::queue<Employee *>& available_queue, Call* call)
		{
			Employee* next_employee = available_queue.front();
			
			bool call_taken = next_employee->takeCall(call);
			if (!call_taken)
			{
				return false;
			}
			available_queue.pop();
			busyEmployees.push(next_employee);
		}
		
		void freeEmployee(Employee* employee)
		{
			EmployeeType emp_type = employee->getEmployeeType();
			if (emp_type == Respondent)
			{
				availableRespondents.push(employee);
			}
			else if (emp_type == Manager)
			{
				availableManagers.push(employee);
			}
			else if (emp_type == Director)
			{
				availableDirectors.push(employee);
			}
		
		}
		

	public:
	  void addEmployee(Employee employee)
		{
			employees.push_back(employee);
			
		}
	  void disbatchCall(Call call)
		{
			calls.push_back(call);
			bool assigned_call = false;
			switch (call.getEmployeeNeeded())
			{
				case Respondent:
					assigned_call = assignCall(availableRespondents, &call);
					break;
				case Manager:
				  assigned_call = assignCall(availableManagers, &call);
					break;
				case Director:
				  assigned_call = assignCall(availableDirectors, &call);
					break;
				default:
				  break;
			}
			if (!assigned_call)
			{
				call.setStatus(NotStarted);
			}
			else
			{
				call.setStatus(InProgress);
			}
		}
		
		void pollCalls()
		{
			std::queue<Employee*> tmp_busy_employees;
			std::queue<Call *> calls_needing_escalation;
			while (busyEmployees.size() > 0)
			{
				Employee* employee = busyEmployees.front();
				busyEmployees.pop();
				
				CallStatus status = employee->getCallStatus();
				Call* call = employee->getCallInProgress();
				switch (status)
				{
					case InProgress:
					  tmp_busy_employees.push(employee);
						break;
					case Terminated:
					  employee->endCall();
						freeEmployee(employee);
						removeCall(call);
						break;
					case NeedsEscalation:
					  employee->endCall();
						freeEmployee(employee);
						call->setStatus(NeedsEscalation);
						call->incrementEmployeeNeeded();
						break;
				}
			}
			
			while (tmp_busy_employees.size() > 0)
			{
				busyEmployees.push(tmp_busy_employees.front());
				tmp_busy_employees.pop();
			}
			
			for (Call call : calls)
			{
				CallStatus status = call.getStatus();
				if (status == NotStarted || status == NeedsEscalation)
				{
					disbatchCall(call);
				}
			}
		}
};

/*
The main stuff that they did differently:
CallCenter was singleton, all calls funelled through one instance
Levels was an int and so flexible, and employees was an arraz of array to help flexibilty
calls was queue with ranks
They also split managers, respondants, ect into subclasses which we should have done. even though the subclasses have nothing in them but ranks
as the jobs arent implemented, just call answering.


*/

int main()
{}