
#ifndef A6_JOBS_HPP
#define A6_JOBS_HPP
#include<queue>





class Job{
public:
    int _pid;
    unsigned char _priority;

    Job(int PID, int priority);
    ~Job();

};

Job::Job(int PID, int priority) {
    _pid=PID;
    _priority=priority;
}

Job::~Job() {
}

class Comppid{
public:
    bool operator()(Job& lhs,Job& rhs){
        if(lhs._priority>rhs._priority){
            return true;
        }
        else if(lhs._priority<rhs._priority){
            return false;
        }
        else{
            if(lhs._pid>rhs._pid){
                return true;
            }
            return false;
        }
    }
};

class JobQueue{
public:
    std::priority_queue<Job,std::vector<Job>,Comppid> aa;

    void push(Job jobPro);
    void pop();
    Job top();

};

void JobQueue::push(Job jobPro) {
    aa.push(jobPro);
}

void JobQueue::pop() {
    aa.pop();
}

Job JobQueue::top() {
    return aa.top();
}

#endif
