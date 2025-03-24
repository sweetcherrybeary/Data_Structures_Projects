#include <iostream>
using namespace std;

class CPUJob {
    public:
        int job_id;             //Unique identifier for the job
        int priority;           //Priority level of the job (1-10)
        int job_type;           //Job type (1-10)
        int cpu_time_consumed;  //Total CPU time consumed by the job
        int memory_consumed;    //Total memory consumed thus far
        //Constructors
        CPUJob();
        CPUJob(int new_job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed);
        CPUJob(CPUJob& job);
        //Display Method
        void display();
        //Setters
        void setPriority(int new_priority);
        void setJobType(int new_job_type);
        void setCPUTimeConsumed(int new_cpu_time_consumed);
        void setMemoryConsumed(int new_memory_consumed);
        //getters
        int getJobID();
        //Destructor
        ~CPUJob();
        //Overloaded operator
        friend std::ostream& operator<<(std::ostream& os, const CPUJob& job);
};

//Overloaded << operator for the CPUJob class.
std::ostream& operator<<(std::ostream& os, const CPUJob& job)
{
    //Displays the information for the given CPUJob in proper formatting.
    os << "Job ID: " << job.job_id << ", Priority: " << job.priority << ", Job Type: " << job.job_type << ", "
        << "CPU Time Consumed: " << job.cpu_time_consumed << ", Memory Consumed: " << job.memory_consumed;
}

CPUJob::CPUJob() {
    //Default constructor, initializes each variable to -1
    job_id = -1;
    priority = -1;
    job_type = -1;
    cpu_time_consumed = -1;
    memory_consumed = -1;
}

CPUJob::CPUJob(int new_job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    //Constructor with each variable's information given. Stores the info in the proper variables.
    job_id = new_job_id;
    priority = new_priority;
    job_type = new_job_type;
    cpu_time_consumed = new_cpu_time_consumed;
    memory_consumed = new_memory_consumed;
}

CPUJob::CPUJob(CPUJob& job) {
    //Copy Constructor
    job_id = job.job_id;
    priority = job.priority;
    job_type = job.job_type;
    cpu_time_consumed = job.cpu_time_consumed;
    memory_consumed = job.memory_consumed;
}

void CPUJob::setPriority(int new_priority) {
    //Set method for priority
    priority = new_priority;
}

void CPUJob::setJobType(int new_job_type) {
    //Set method for Job Type
    job_type = new_job_type;
}

void CPUJob::setCPUTimeConsumed(int new_cpu_time_consumed) {
    //Set method for CPU Time Consumed
    cpu_time_consumed = new_cpu_time_consumed;
}

void CPUJob::setMemoryConsumed(int new__memory_consumed) {
    //Set method for Memory Consumed
    memory_consumed = new__memory_consumed;
}

int CPUJob::getJobID() {
    //Get method that returns the Job ID of the CPUJob
    return job_id;
}

void CPUJob::display() {
    //Display method for CPUJob, displays the CPUJob in proper format
    cout << "Job ID: " << job_id << ", Priority: " << priority << ", Job Type: " << job_type << ", ";
    cout << "CPU Time Consumed: " << cpu_time_consumed << ", Memory Consumed: " << memory_consumed << endl;
}

CPUJob::~CPUJob(){} //All variables will be automatically deleted once the CPU job is as they are all ints, so no further handling of them needs to be done.

template <class DT>
class Queue {
    public:
        DT* job_pointer;     //Pointer to a Job
        Queue<DT>* next;    //Pointer to the next node in the Queue
        //Constructors
        Queue();
        Queue(const DT& new_job_pointer);
        Queue(const DT& new_job_pointer, Queue<DT>* new_next);
        Queue(const Queue<DT>& Q);
        //Display Method
        void display();
        //Getters
        DT& getJobPointer();
        int getJobID();
        //Setters
        void setInfo(int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed);
        void setPriority(int new_priority);
        void setJobType(int new_job_type);
        void setCPUTimeConsumed(int new_cpu_time_consumed);
        void setMemoryConsumed(int new_memory_consumed);
        //Destructor
        ~Queue();
};

template <class DT>
Queue<DT>::Queue() {
    //Default constructor for the Queue class. Initialized each variable to NULL
    job_pointer = NULL;
    next = NULL;
}

template <class DT>
Queue<DT>::Queue(const DT& new_job_pointer) {
    //Constructor for Queue class. Initializes Job Pointer to be the given info, and sets next to be NULL
    job_pointer = new DT(new_job_pointer);
    next = NULL;
}

template <class DT>
Queue<DT>::Queue(const DT& new_job_pointer, Queue<DT>* new_next) {
    //Constructor for Queue class that sets Job Pointer and Next to be what is given by the constructor.
    job_pointer = new DT(new_job_pointer);
    next = new_next;
}

template <class DT>
Queue<DT>::Queue(const Queue<DT>& Q) {
    //Cpoy constructor. Checks if the variables from the Queue passed to the constructor are NULL before assigning their values to the variables in the current Queue
    if (Q.job_pointer != NULL) {
        job_pointer = new DT(Q.job_pointer);
    }
    if (Q.next != NULL) {
        next = new Queue<DT>(*(Q.next)); //Derefrences the next variable for Q and uses it to recursively finish creating the Queue
    }
}

template <class DT>
void Queue<DT>::display() {
    //Display method for the Queue class.
    if (job_pointer != NULL) { //Checks if Job Pointer is NULL
        cout << (**job_pointer) << endl; //Displays Job Pointer if it isn't
    }
    if (next != NULL) { //Check if next is NULL
        (*next).display(); //If it isn't, call the display method for the next Queue object in the list.
    }
}

template <class DT>
DT& Queue<DT>::getJobPointer() {
    //Get method that returns the Job Pointer of the current Queue
    return (*job_pointer);
}

template <class DT>
int Queue<DT>::getJobID() {
    //Get method that returns the Job ID of the Job Pointer of the current Queue
    return (**job_pointer).getJobID();
}

template <class DT>
void Queue<DT>::setInfo(int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    //Setter that sets the info for the Job Pointer. Calls the set methods of the CPUJob class to do this
    (**job_pointer).setPriority(new_priority);
    (**job_pointer).setJobType(new_job_type);
    (**job_pointer).setCPUTimeConsumed(new_cpu_time_consumed);
    (**job_pointer).setMemoryConsumed(new_memory_consumed);
}

template <class DT>
void Queue<DT>::setPriority(int new_priority) {
    //Setter method that sets the Priority of the Job Pointer
    (**job_pointer).setPriority(new_priority);
}

template <class DT>
void Queue<DT>::setJobType(int new_job_type) {
    //Setter method that sets the Job Type of the Job Pointer
    (**job_pointer).setJobType(new_job_type);
}

template <class DT>
void Queue<DT>::setCPUTimeConsumed(int new_cpu_time_consumed) {
    //Setter method that sets the CPU Time Consumed of the Job Pointer
    (**job_pointer).setCPUTimeConsumed(new_cpu_time_consumed);
}

template <class DT>
void Queue<DT>::setMemoryConsumed(int new_memory_consumed) {
    //Setter method that sets the Memory Consumed of the Job Pointer
    (**job_pointer).setMemoryConsumed(new_memory_consumed);
}

template <class DT>
Queue<DT>::~Queue() {
    //Destructor.
    //Deletes the Job Pointer if it isn't NULL
    if (job_pointer != NULL) {
        delete job_pointer;
    }
    //Deletes the Next Queue in the list if it isn't NULL
    if (next != NULL) {
        delete next;
    }
}

template <class DT>
class NovelQueue {
    public:
        Queue<DT>* front;       //Pointer to the front of the Queue
        Queue<DT>* rear;        //Pointer to the rear of the Queue, used for more efficient enqueue.
        Queue<DT>** node_pointers;   //Array of pointers to Queue nodes
        int size;               //Number of elements in the Queue
        int array_max_elements; //Max number of elements that can currently be stred in the array, array will grow when max is no longer enough
        //Constructor
        NovelQueue();
        //Display methods
        void display();
        void listJobs();
        //Helper Methods
        int binarySearch(int job_id); //Returns the index position of the job with that job_id, if none is found it will return -1.
        void enqueue(DT& new_element);
        DT& dequeue();
        void modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed);
        void change(int job_id, int field_index, int new_value);
        void promote(int job_id, int positions);
        void reorder(int attribute_index);
        int count();
        //Destructor
        ~NovelQueue();
};

template <class DT>
NovelQueue<DT>::NovelQueue() {
    //Constructor Method. Sets Queue pointers to be NULL before any elements are added.
    front = NULL;
    rear = NULL;
    //Sets variable to keep track of max number of elements in the array, and uses that to create the Node Pointers array
    array_max_elements = 10;
    node_pointers = new Queue<DT>*[array_max_elements];
    //Sets size to be 0 as no elements have been added.
    size = 0;
}

template <class DT>
void NovelQueue<DT>::display() {
    //Calls the display method on the front object of the Queue. This will then call the display method for the rest of the Queue in order
    (*front).display();
}

template <class DT>
void NovelQueue<DT>::listJobs() {
    //Works through the Node Pointers array and calls the display method on each CPUJob in order of Job ID
    for (int i = 0; i < size; i++) {
        //Gets the Job Pointer of the Queue at the index i and calls the display method
        (*(*node_pointers[i]).getJobPointer()).display();
    }
}

template <class DT>
int NovelQueue<DT>::binarySearch(int job_id) {
    int left = 0;   //Sets left index to be equal to zero as that is the leftmost index of the array
    int right = size - 1;   //Sets right index to be equal to size - 1 as that is the rightmost index of the array
    int array_index = -1;   //Denotes the position of the job_id in the array, if isn't found then it will be -1.

    //Continues to search the list until left becomes greater than right, or the element is found.
    while (left <= right && array_index == -1) {
        //Finds the current mid index
        int mid = (left + right) / 2;
        //Finds the Job ID of the element at the middle index
        int mid_index_job_id = (*node_pointers[mid]).getJobID();
        //If the Job ID at the mid index is the one being searched for, make Array Index the index of that CPUJob
        if (mid_index_job_id == job_id) {
            array_index = mid;
        }
        //If the Job ID at the mid index is less than the one being looked for, look at only the right side of the list
        else if (mid_index_job_id < job_id) {
            left = mid + 1;
        }
        //If the Job ID at the mid index is greater than the one being looked for, look at only the left side of the list
        else {
            right = mid - 1;
        }
    }
    return array_index;
}

template <class DT>
void NovelQueue<DT>::enqueue(DT& new_element) {
    //Code for if there are no elements in the list
    if (front == NULL) {
        front = rear = new Queue<DT>(new_element); //Sets the front and the rear of the NovelQueue to be the same element whenever something is added to the empty list
        node_pointers[size] = front; //Sets the Node Pointer at the current next empty index to be the new element
        size++; //Increments Size of the list
    }
    else {
        //Executes if the new element is already in the list
        if ((*this).binarySearch((*new_element).job_id) != -1) {
            cout << "Job ID " << (*new_element).job_id << " already exists!" << endl;
            return;
        }
        //Creates a new Queue for the given element
        Queue<DT>* new_queue = new Queue<DT>(new_element);
        //Sets the next of the current rear to be the new element
        (*rear).next = new_queue;
        //Sets the rear to the new element
        rear = new_queue;
        //Executes if the array is currently full
        if (size == array_max_elements) {
            //Doubles the max elements of the array
            array_max_elements = array_max_elements * 2;
            //Creates a temporary array with the new max elements as the size
            Queue<DT>** temp = new Queue<DT>*[array_max_elements];
            //Copies the info from Node Pointers to the temp array
            for (int i = 0; i < size; i++) {
                temp[i] = node_pointers[i];
            }
            //Sets Node Pointers to be equal to the temp array
            node_pointers = temp;
        }
        node_pointers[size] = rear; //Sets the Node Pointer at the current next empty index to be the new element
        size++; //Increments size
    }

    //Displays the enqueued job
    cout << "Enqueued Job:" << endl;
    (*rear).display();
    //Displays the jobs in proper order
    cout << "Jobs after enqueue:" << endl;
    (*front).display();
}

template <class DT>
DT& NovelQueue<DT>::dequeue() {
    //Throws an exception if dequeue is called while no elements are in the queue
    if (size == 0) {
        throw exception();
    }
    //Creates a temp Queue to hold onto the current front object
    Queue<DT>* temp = front;
    //Makes front equal to the next element in the Queue
    front = (*front).next;
    //Checks if the new front is NULL, if it is then it sets rear to be NULL
    if (front == NULL) {
        rear = NULL;
    }
    //If there is only one element in the Queue before dequeue, then set the first element in the node pointers list to be NULL.
    if (size == 1) {
        node_pointers[0] = NULL;
    }
    else {
        //Find the Node Pointer index of the dequeued job
        int dequeued_job_index = (*this).binarySearch((*temp).getJobID());
        //Shift every element after the dequeued job to the left by 1.
        for (int i = dequeued_job_index; i < size - 1; i++) {
            node_pointers[i] = node_pointers[i + 1];
        }
        //Set the empty element at the end of the Node Pointers array to be NULL
        node_pointers[size] = NULL;
    }
    size--; //De-increments size.

    DT* info_to_return = (*temp).job_pointer; //Sets the info to return to be the Job Pointer that used to be at the front of the Queue

    //Sets temps info to NULL and then deletes it
    (*temp).job_pointer = NULL;
    (*temp).next = NULL;
    delete temp;
    
    return (*info_to_return);
}

template <class DT>
void NovelQueue<DT>::modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    //Finds the index of the given Job ID
    int job_id_index = (*this).binarySearch(job_id);
    //If the index is -1, then the element isn't in the NovelQueue
    if (job_id_index == -1) {
        cout << "Job with ID " << job_id << " not found in the queue." << endl;
        return;
    }
    //Sets the info of the Queue at the Job ID index to be equal to the new information
    (*node_pointers[job_id_index]).setInfo(new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed);

    //Displays the modified job
    cout << "Modified Job ID " << job_id << ":" << endl;
    (**(*node_pointers[job_id_index]).job_pointer).display();
    //Displays the Queue of CPUJobs in order
    cout << "Jobs after modification:" << endl;
    (*front).display();
}

template <class DT>
void NovelQueue<DT>::change(int job_id, int field_index, int new_value) {
    //Constant variables that denote the different CPUJob field indexes
    const int PRIORITY = 1;
    const int JOB_TYPE = 2;
    const int CPU_TIME = 3;
    const int MEMORY = 4;
    //Finds the index of the Job ID in the Node Pointers array
    int job_id_index = (*this).binarySearch(job_id);
    //Executes if the element with that Job ID isn't found in the list
    if (job_id_index == -1) {
        cout << "Job with ID " << job_id << " not found in the queue." << endl;
        return;
    }
    //Checks which field needs to change.
    if (field_index == PRIORITY) {
        (*node_pointers[job_id_index]).setPriority(new_value);  //Changes Priority
    }
    else if (field_index == JOB_TYPE) {
        (*node_pointers[job_id_index]).setJobType(new_value);   //Changes Job Type
    }
    else if (field_index == CPU_TIME) {
        (*node_pointers[job_id_index]).setCPUTimeConsumed(new_value);   //Changes CPU Time Consumed
    }
    else if (field_index == MEMORY) {
        (*node_pointers[job_id_index]).setMemoryConsumed(new_value);    //Changes Memory Consumed
    }
    else {
        cout << "Field index is out of bounds, please input a correct field index." << endl; //Executes if the given field index is out of bounds
        return;
    }
    //Displays the changed CPUJob
    cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":" << endl;
    (**(*node_pointers[job_id_index]).job_pointer).display();
    //Displays the Queue of CPUJob in order
    cout << "Jobs after changing field:" << endl;
    (*front).display();
}

template <class DT>
void NovelQueue<DT>::promote(int job_id, int positions) {
    //Finds the index of the Job ID in the Node Pointer array
    int job_id_index = (*this).binarySearch(job_id);
    //Executes if the element isn't found in the array
    if (job_id_index == -1) {
        cout << "Job with ID " << job_id << " not found in the queue." << endl;
        return;
    }
    //Stores the Queue element at the Job ID index into a temp variable
    Queue<DT>* temp = node_pointers[job_id_index];
    //Checks if temp is already at the front, and therefore doesn't need to be promoted any further
    if (temp != front) {
        //Creates a Queue object to contain the previous element of the Queue as we work through it.
        Queue<DT>* previous = front;
        //Sets previous to be the next element of the queue until the next queue object in the list is temp
        while ((*previous).next != temp) {
            previous = (*previous).next;
        }

        (*previous).next = (*temp).next; //Makes the element before the one with the Job ID, point to the next of the Queue with the given Job ID
        //Executes if the element being promoted was the one at the end of the list
        if (job_id_index == (size - 1)) {
            //Sets the new rear to be the element in the Queue that used to be before the old rear.
            rear = previous;
        }
        //Executes if promoting by that many positions would put it at the front of the Queue
        if ((job_id_index - positions) <= 0) {
            //Sets temp's Next variable to be qeual to the current front of the Queue and then makes temp the new front.
            (*temp).next = front;
            front = temp;
        }
        else {
            //Finds the number of iterations necessary to reach the new positionf of the Queue with the given Job ID
            int iterations = (job_id_index - positions);
            //Creates a new Queue object to store the element that will come after the queue with the given Job ID
            Queue<DT>* next = front;
            //Iterates through the Queue a number of times equal to the number of iterations found earlier
            for (int i = 0; i < iterations; i++) {
                //Sets previous to be euqal to the next element of the Queue
                previous = next;
                //Sets next to be the next element in the queue
                next = (*previous).next;
            }
            //Sets temp's Next variable to be the element after it in the Queue
            (*temp).next = next;
            //Sets the next for the element before temp to be equal to temp
            (*previous).next = temp;
            //Deletes uncessesary variables
            next = NULL;
            delete next;
        }
        //Deletes uncessesary variables
        previous = NULL;
        delete previous;
    }
    //Deletes uncessesary variables
    temp = NULL;
    delete temp;
    //Displays the promoted CPUJob
    cout << "Promoted Job ID " << job_id << " by " << positions << " Position(s):" << endl;
    (**(*node_pointers[job_id_index]).job_pointer).display();
    //Displays the Queue in order
    cout << "Jobs after promotion:" << endl;
    (*front).display();
}

template <class DT>
void NovelQueue<DT>::reorder(int attribute_index) {
    //Constant variables that denote the different CPUJob attribute indexes
    const int JOB_ID = 1;
    const int PRIORITY = 2;
    const int JOB_TYPE = 3;
    const int CPU_TIME = 4;
    const int MEMORY = 5;
    //Executes if the Queue is empty
    if (size == 0) {
        cout << "The Queue is empty!" << endl;
        return;
    }

    //Creates a temporary array of the same size of the Node Pointers array
    Queue<DT>** temp_array = new Queue<DT>*[size];
    //Iterates through the Node Pointers queue and copies the pointer over to the temporary array
    for (int i = 0; i < size; i++) {
            temp_array[i] = node_pointers[i];
        }
    //A switch statement that determines which element to sort by using the given attribute index.
    switch(attribute_index) {
        case JOB_ID: {
            //Iterates through the array starting from the second element
            for (int i = 1; i < size; i++) {
                //Creates a Queue object to hold the current elemet of the array to be sorted
                Queue<DT>* current_element = temp_array[i];
                int j = i - 1;
                //Continues to move elements in the array to the right until the Job ID of the current element is greater than the element that would be moved
                while ((j >= 0) && (((**(*temp_array[j]).job_pointer).job_id) > (**(*current_element).job_pointer).job_id)) {
                    temp_array[j + 1] = temp_array[j];
                    j = j - 1; //Moves the index to check to the left by one
                }
                temp_array[j + 1] = current_element; //Stores the pointer for the current element in its properly sorted place in the array
            }
            break;
        }
        case PRIORITY: {
            //Iterates through the array starting from the second element
            for (int i = 1; i < size; i++) {
                //Creates a Queue object to hold the current elemet of the array to be sorted
                Queue<DT>* current_element = temp_array[i];
                int j = i - 1;
                //Continues to move elements in the array to the right until the Priority of the current element is greater than the element that would be moved
                while ((j >= 0) && (((**(*temp_array[j]).job_pointer).priority) > (**(*current_element).job_pointer).priority)) {
                    temp_array[j + 1] = temp_array[j];
                    j = j - 1; //Moves the index to check to the left by one
                }
                temp_array[j + 1] = current_element; //Stores the pointer for the current element in its properly sorted place in the array
            }
            break;
        }
        case JOB_TYPE: {
            //Iterates through the array starting from the second element
            for (int i = 1; i < size; i++) {
                //Creates a Queue object to hold the current elemet of the array to be sorted
                Queue<DT>* current_element = temp_array[i];
                int j = i - 1;
                //Continues to move elements in the array to the right until the Job Type of the current element is greater than the element that would be moved
                while ((j >= 0) && (((**(*temp_array[j]).job_pointer).job_type) > (**(*current_element).job_pointer).job_type)) {
                    temp_array[j + 1] = temp_array[j];
                    j = j - 1; //Moves the index to check to the left by one
                }
                temp_array[j + 1] = current_element; //Stores the pointer for the current element in its properly sorted place in the array
            }
            break;
        }
        case CPU_TIME: {
            //Iterates through the array starting from the second element
            for (int i = 1; i < size; i++) {
                //Creates a Queue object to hold the current elemet of the array to be sorted
                Queue<DT>* current_element = temp_array[i];
                int j = i - 1;
                //Continues to move elements in the array to the right until the CPU Time Consumed of the current element is greater than the element that would be moved
                while ((j >= 0) && (((**(*temp_array[j]).job_pointer).cpu_time_consumed) > (**(*current_element).job_pointer).cpu_time_consumed)) {
                    temp_array[j + 1] = temp_array[j];
                    j = j - 1; //Moves the index to check to the left by one
                }
                temp_array[j + 1] = current_element; //Stores the pointer for the current element in its properly sorted place in the array
            }
            break;
        }
        case MEMORY: {
            //Iterates through the array starting from the second element
            for (int i = 1; i < size; i++) {
                //Creates a Queue object to hold the current elemet of the array to be sorted
                Queue<DT>* current_element = temp_array[i];
                int j = i - 1;
                //Continues to move elements in the array to the right until the Memory Consumed of the current element is greater than the element that would be moved
                while ((j >= 0) && (((**(*temp_array[j]).job_pointer).memory_consumed) > (**(*current_element).job_pointer).memory_consumed)) {
                    temp_array[j + 1] = temp_array[j];
                    j = j - 1; //Moves the index to check to the left by one
                }
                temp_array[j + 1] = current_element; //Stores the pointer for the current element in its properly sorted place in the array
            }
            break;
        }
        default:
            cout << "Invalid command!" << endl;
    }
    //Sets the front element to be the first element in the sorted array
    front = temp_array[0];
    //Works through the sorted array to set the Next variable for each Queue to be the next element in the array
    for (int i = 1; i < size; i++) {
        (*temp_array[i - 1]).next = temp_array[i];
    }
    //Sets the rear of the NovelQueue to be the last pointer in the sorted array
    rear = temp_array[size - 1];
    //Sets the Next variable for the new rear to be NULL
    (*rear).next = NULL;
    //Displays the Reordered Queue in their new sorted order.
    cout << "Reordered Queue by attribute " << attribute_index << ":" << endl;
    (*front).display();
}

template <class DT>
int NovelQueue<DT>::count() {
    //Returns the number of elements in the array.
    return size;
}

template <class DT>
NovelQueue<DT>::~NovelQueue() {
    //Sets rear to NULL and deletes it as deleting front will handle the deletion of all Queue elements in the NovelQueue
    rear = NULL;
    delete rear;
    //Deletes all elements in the Novel Queue
    delete front;
    //Sets all the Node Pointer elements to be NULL and then deletes it.
    for (int i = 0; i < size; i++) {
        node_pointers[i] = NULL;
    }
    delete node_pointers;
}

int main() {
    int n;      //Number of Commands
    cin >> n;   //Read the numbers of commands

    //Instantiate a NovelQueue for CPUJob pointers
    NovelQueue<CPUJob*>* myNovelQueue = new NovelQueue<CPUJob*>();

    char command;   //Variable to store the command

    //Variables for job attributes
    int job_id, priority, job_type, cpu_time_consumed, memory_consumed;

    //Variables for modifying a job
    int new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed;
    int field_index, new_value;

    //Variable for the number of positions in the 'Promote' command
    int positions;
    int attribute_index;    //Variable for the 'Reorder' command

    /************** Read each command Process ***************/
    for (int i = 0; i < n; ++i) {
        cin >> command; //Read the command type

        switch(command) {
            case 'A': {     //Add (Enqueue)
                cin >> job_id >> priority >> job_type;
                cin >> cpu_time_consumed >> memory_consumed;
                CPUJob* newJob = new CPUJob(job_id, priority, job_type, cpu_time_consumed, memory_consumed);
                (*myNovelQueue).enqueue(newJob);
                break;
            }
            case 'R': {
                CPUJob* removedJob = (*myNovelQueue).dequeue();
                if (removedJob) {
                    cout << "Dequeued Job:" << endl;
                    (*removedJob).display();
                    delete removedJob;
                    cout << "Jobs after dequeue:" << endl;
                    (*myNovelQueue).display();
                }
                break;
            }
            case 'M': {
                cin >> job_id >> new_priority >> new_job_type;
                cin >> new_cpu_time_consumed >> new_memory_consumed;
                (*myNovelQueue).modify(job_id, new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed);
                break;
            }
            case 'C': {
                cin >> job_id >> field_index >> new_value;
                (*myNovelQueue).change(job_id, field_index, new_value);
                break;
            }
            case 'P': {
                cin >> job_id >> positions;
                (*myNovelQueue).promote(job_id, positions);
                break;
            }
            case 'O': {
                cin >> attribute_index;
                (*myNovelQueue).reorder(attribute_index);
                break;
            }
            case 'D': {
                cout << "Displaying all jobs in the queue:" << endl;
                (*myNovelQueue).display();
                break;
            }
            case 'N': {
                cout << "Number of elements in the queue: " << (*myNovelQueue).count() << endl;
                break;
            }
            case 'L': {
                cout << "List of jobs sorted by job IDs:" << endl;
                (*myNovelQueue).listJobs();
                break;
            }
            default:
                cout << "Invalid command!" << endl;
        }
    }
    
    delete myNovelQueue;
    return 0;
}

/*
LLM Usage Documentation:

    -Prompt #1: "When working with a linked list implementation of a queue, what variables are important to include?"
        -Rationale: I prompted the LLM with this question when I was first beginning to write the NovelQueue class as I was unsure of what other variables I should
        be using past the ones given to us in the project description. This ended up helping me figure out that including a pointer for the rear of the Queue
        would make enqueuing much simplier to do.

    -Prompt #2: "Why is my display method for the CPUJob class displaying a pointer and not the informatuon from the display method?"
        -Rationale: I prompted the LLM with this question as when I was attempting to display my CPUJob objects it was only pointing out the pointer information of those
        objects. One of the things the LLM told me upon asking was to make sure that everything was getting properly derefferenced, which upon further review of my code I realized
        that I should be derefferencing the Job Pointer of the Queue class twice.

    -Prompt #3: "I need to promote an item in a Queue by a given number of positions, how might I do so in c++? The class containing this Queue has a pointer to the front of
    the queue, the rear of the queue, and an array of queue elements that are kept sorted by each elements Job ID."
        -Rationale: I had been struggling to figure out exactly how I should code the promote method as I was struggling to wrap my head around how the object would move in the
        list upon being promoted. After looking over the code that the LLM had given me back, I was able to figure out how to determine the new spot in the list for the
        CPUJob after it was promoted, which allowed me to write the rest of the code for that method.

    -Prompt #4: "I have a list of CPUJob objects which each have 5 attributes, Job ID, Job Type, Priority, CPU Time Consumed, and Memory Consumed. I need to write c++ 
    code that will reorder this list based on one of those attributes which is given to you by the user. The method that will be called will look something 
    like CPUJob.reorder(int attribute_index). How might you go about writing this code?"
        -Rationale: I prompted the LLM with this question as I had spent a long time trying to decide the best way to handle sorting given the program that we had to write.
        Upon prompting the LLM it helped me finally determine that the best way to go about sorting in this case would be to use a switch statement to determine which element of
        the CPUJob class to sort by, and then having it go to a unique sort based on that switch statement. This allowed me to easily sort the array given the attribute index to
        sort by.

    -Prompt #5: "Why is my destructor method for the Novel Queue class not executing all the way through when I call it? Assume that front is a pointer to the front of the Queue,
    rear is a pointer to the rear, and node_pointers is an array of pointers to Queue objects."
        -Rationale: I was encountering a segmentation fault at this point of my program and I couldn't begin to figure out why, so I prompted the LLM for help with
        determining why that might be occuring. Upon doing so I realized that trying to delete the rear pointer after it had already been deleted by me deleting the front pointer
        was causing unexpected memory problems, and a quick change to that part of my code was enough to make the rest of it work.

    Incremental Development:
        To begin working on this project I started by getting the constructors and display methods working for each of the classes. Next I then moved on to the only other methods
        that were necessary for all the others to be coded, those being size and enqueue. Without enqueue the NovelQueue was forced to remain mostly empty, so that was the next
        most important method. After that I was able to pick and choose whichever method I would have liked to work on as they were all now able to be viewed and tested thanks to
        both the display and enqueue methods. I decided to work my way down the list of method prototypes as this seemed the most natural way to work through the methods so that I
        could easily test them as I go. Along the way I would promt the LLM where necessary to help me whenever I got stuck, as I seemed to with the promote and reorder methods. With
        the help of the LLM it didn't take me long to figure out any of my issues whenever they popped up. and it significantly increased my working pace in the face of these
        unknown issues as I was able to get quick answers from the LLM that put me on the right track to solving the problems.

---------------------------

Debugging and Testing Plan:

    -Test #1: Ensuring the constructors and display methods worked properly:
        To do this I wrote the constructors and display methods for each of the classes in this project, and then I created multiple Queue objects and tested its and the
        CPUJob classes display methods. The NovelQueue class had to wait until I wrote the Enqueue method before I would be able to check its display method.

    -Test #2: Testing the Enqueue method and ensuing NovelQueues display works:
        In order to do this I coded out the enqueue method for the NovelQueue class and began testing it by enqueuing different CPUJob objects to the NovelQueue and
        then calling the display method on the Queue to ensure that they were getting added in the proper order.

    -Test #3: Testing that the Dequeue method was dequeuing the proper object:
        To test the dequeue method I first coded it out, and then I took the document I used for the Enqueue method testing and added on some commands to the end that
        would call the Dequeue method. I would then display the CPUJob object returned by the Dequeue method in order to ensure that it was Dequeuing the correct object.

    -Test #4: Testing the Change and Modify methods:
        As these methods were both extremely similar, I wrote and tested them both side by side. In order to test them I edited the document that I was using for testing
        the methods to now include changing and modifying some of the elements in the Queue, and then displaying the modified elements to ensure that the changes made to
        it were correct.

    -Test #5: Testing the promote and list methods:
        In order to test this method after I had finished coding it, I had attempted to promote elements in different parts of the list by different positions. Once I saw that
        the elements were being promoted by the proper number of positions in the Queue, I called the List method on the the NovelQueue to ensure that the array was staying 
        properly sorted throught all of the editing of the Queue. Once I confirmed that it was displaying them in order based on Job ID, I moved on to writing the last part of
        my code.

    -Test #6: Testing that the reorder method properly reorders the list:
        In order to test this I attempted to reorder the Queue that I had from the document that I had been making alongside the testing of this program based on each of the
        different attributes. After each reorder was complete, I called the display method to check that they were properly sorted, and then I called the list method to ensure that
        the array was still staying sorted based on Job IDs.

    -Test #7: Final testing via gradescope:
        In order to ensure that the program was working as a whole I first tested it on my computer using each input file that was given to us. However with the length of the
        output files I ended up finding it easier to cross-check my output via uploading my project to geadescope. Upon doing so I was able to discover segmentation faults that
        I didn't know of, and I was then able to fix the rest of the issues with my code based on the output that was given by gradescope.

    -Issue #1: The Display method was displaying the pointers and not the actual information of the CPUJob object
        In order to fix this I had to take a careful look over my code and the error prompt that was being given to me. Upon further consideration and some help from
        a LLM I was able to realize that since the DT being passed to the NovelQueue and Queue was CPUJob*, it made Queue's DT* job_pointer need to be derefferenced
        twice in order to be able to access the CPUJob object and not the pointer.

    -Issue #2: Encountering Segmentation faults upon turning in the program.
        When I turned the project into the autograder it told me that it was encountering segmentation faults in the program. In order to figure out where these
        were coming from, I had my program print out statements at important points in the deletion process to see where the failure happened. Upon further consideration I realized
        that deleting the rear pointer after having deleted the front pointer was what was causing it, and a quick change to the way I handled deletion was able to fix my program.

    -Issue #3: Reorder method was displaying the Queue twice.
        After fixing the segmentation fault that was being caused in my program, I encountered a second problem with the Autograder, that being that it was not getting the correct
        output from my program. Upon looking over the output files again and comparing them more carefully I was able to realize that my reorder method was causing the Queue to
        be displayed twice, and a quick change was able to fix that.
    
    -Issue #4: Elements occasionally being lost during the promote method
        Upon fixing the issue caused by my reorder method, I went to turn my assignment in for the final time. Upon doing so I saw that it failed the first test, but passed the last
        two. Taking a closer look at the output files, I realized this was because I hadn't updated the rear when necessary, and upon making a change to my program so that
        it did so it no longer was losing elements and instead was passing all the tests.

*/