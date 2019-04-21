#include <bits/stdc++.h>
using namespace std;
#define d(x)                cout << #x << " = " << (x) << endl;
#define fr                  freopen("in.txt", "r", stdin);
#define fw                  freopen("out.txt", "w", stdout);
#define mem(x)              memset((x), 0, sizeof((x)));
#define pb                  push_back
#define ll                  long long
#define fastIO              ios_base::sync_with_stdio(false)
#define sf                  scanf
#define pf                  printf
#define SQR(x)              ((x)*(x))
#define sc1(x)              scanf("%d", &x)
#define sc2(x, y)           scanf("%d %d", &x, &y)
#define sc3(x, y, z)        scanf("%d %d %d", &x, &y, &z)
#define FOR(i, x, y)        for(int i=int(x); i<int(y); i++)
#define ROF(i, x, y)        for(int i=int(x-1); i>=int(y); i--)
#define all(c)              (c.begin(), c.end())
#define unq(v)              sort(all(v)), (v).erase(unique(all(v)),v.end())
#define EPSILON    (1.0E-8)
#define siz 100000



int main(){
    #ifndef ONLINE_JUDGE
        clock_t tStart = clock();
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif 
        /* input structure
            1. server runtime (int)
            2. total customers (int)
            3. arrival_time for each customer (vector<int>)
            4. service_timer for each customer (vector<int>)
        */

        /* test input
            85
            20
            0 8 14 15 23 26 34 41 43 46 47 48 53 59 62 70 71 73 77 82
            4 1 4 3 2 4 5 4 5 3 3 5 4 1 5 4 3 3 2 3 
        */

        int run_time;
        cin >> run_time;

        int customer;
        cin >> customer;
        
        vector<int> arrival_time(customer);
        vector<int> service_time(customer);


        // printf("Input Arrival times:");
        for(int i = 0; i < customer; i++){
            cin >> arrival_time[i];
        }


        // printf("Input Service times:");
        for(int i = 0; i < customer; i++){
            cin >> service_time[i];
        }

        //in case of random (1-10 gap arrival time)

        // arrival_time[0] = rand() % 10; 
        // for(int i = 1; i < customer; i++){
        //     arrival_time[i] = arrival_time[i-1]+ (rand()%10);
        // }

        // service_time[0] = rand() % 10; 
        // for(int i = 1; i < customer; i++){
        //     service_time[i] = (rand()%10);
        // }



        //initializing vectors;
        vector<int> service_begins;
        vector<int> wait_in_queue;
        vector<int> service_ends;
        vector<int> time_in_system;
        vector<int> idle_server_time;
        
        //for the first input we calculate without loop;
        //for the first customer the service begins at time 0;
        service_begins.push_back(0);
        //the first customer has no waiting time;
        wait_in_queue.push_back(0);
        //first customer's service ends as soon as service time ends;
        service_ends.push_back(service_time[0]);
        //first customer spends 'service time' amount of time in the system;
        time_in_system.push_back(service_time[0]);
        //for the first customer there is no idle time;
        idle_server_time.push_back(0);
   

        //printing pretty table and the first value
            printf("No---AT---ST---SB---Q---SE---TIS---IDLE\n");
            cout << right
            << setw(2) << 0+1
            << setw(5) << arrival_time[0]
            << setw(5) << service_time[0] 
            << setw(5) << service_begins[0]
            << setw(4) << (wait_in_queue[0])
            << setw(5) << (service_ends[0])
            << setw(6) << (time_in_system[0])
            << setw(7) << (idle_server_time[0]) 
            << endl;
        

        //actual calculation of remaining table starts
        for(int i = 1; i < customer; i++){
            //run time of server check (if over, break, done, tata)
            if(arrival_time[i] > run_time){
                printf("Shop Closed at %d\n", run_time);
                break;
            }
            //else--if

            // arrival time is greater than the previous customer service end time
            if(arrival_time[i] >= service_ends[i-1]){
                service_begins.push_back(arrival_time[i]);
                //so customer doesn't have to wait.
                wait_in_queue.push_back(0);
                //customer will get service as soon as he gets in and leave when service time ends.
                service_ends.push_back(arrival_time[i]+service_time[i]);
                //he will not wait in queue, so only the service time of this customer counts here.
                time_in_system.push_back(service_time[i]);
                //the server had to wait after ending the service of previous customer
                // so the arrival time of this customer is after the service end of the previous customer
                // in between these time the server was idle.
                idle_server_time.push_back(arrival_time[i]-service_ends[i-1]);

                //for debugging purporse.
                // d(wait_in_queue[i])
                // d(service_ends[i])
                // d(time_in_system[i])
                // d(idle_server_time[i]);
            }
            // arrival time is less than the previous customer service end time
            else{

                service_begins.push_back(service_ends[i-1]);

                //so the new customer has to wait untill the previous customer is done.
                //so if he arrived in x time and the previous customer leavs at y time
                //the waiting time of him will be y-x
                wait_in_queue.push_back(service_ends[i-1]-arrival_time[i]);
                //now this customer enters the server at the end of the previous customer.
                //so his service time wil be counted from the end of the prevous customer.
                //if the end of the previous customer is y and the service time of this customer is p.
                //the sevice will end after y+p time.
                service_ends.push_back(service_ends[i-1]+service_time[i]);
                //total time in system will be queue_time+service_time of this customer.
                time_in_system.push_back(wait_in_queue[i]+service_time[i]);
                //the service gave servicec as soon as the prevoious customer ended. so there is no delay.
                idle_server_time.push_back(0);

                //for debugging purporse.
                // d(wait_in_queue[i])
                // d(service_ends[i])
                // d(time_in_system[i])
                // d(idle_server_time[i]);
            }

            cout << right
            << setw(2) << i+1
            << setw(5) << arrival_time[i]
            << setw(5) << service_time[i] 
            << setw(5) << service_begins[i]
            << setw(4) << (wait_in_queue[i])
            << setw(5) << (service_ends[i])
            << setw(6) << (time_in_system[i])
            << setw(7) << (idle_server_time[i]) 
            << endl;

        }

        // Simulation Done

        //Calculating the values from simulation
        int total_service_time = 0;
        int total_wait_in_queue = 0;
        int total_time_spent_in_system = 0;
        int total_idle_server_time = 0;
        int number_of_customer_who_wait = 0;
        int total_run_time_of_simulation = service_ends[customer-1];


        for(int i = 0; i < customer; i++){
            total_service_time += service_time[i];
            total_wait_in_queue += wait_in_queue[i];
            total_time_spent_in_system += time_in_system[i];
            total_idle_server_time += idle_server_time[i];
            if(wait_in_queue[i] > 0) number_of_customer_who_wait++;
        }

        //Printing the values from simulation
        cout << "total_service_time = " << total_service_time << endl;
        cout << "total_wait_in_queue = " << total_wait_in_queue << endl;
        cout << "total_time_spent_in_system = " << total_time_spent_in_system << endl;
        cout << "total_idle_server_time = " << total_idle_server_time << endl;
        cout << "number_of_customer_who_wait = " << number_of_customer_who_wait << endl;

        printf("-----------------\n");


        //Doing mathmatics from the values of simulation
        double avg_waiting_time = (total_wait_in_queue*1.0)/(customer*1.0);
        double avg_service_time = (total_service_time*1.0)/(customer*1.0);
        double probability_of_waiting = (number_of_customer_who_wait*1.0)/(customer*1.0);
        double probability_of_idle_server = (total_idle_server_time*1.0)/(total_run_time_of_simulation*1.0);
        double probability_of_busy_server = 1.0-probability_of_idle_server;

        //Printing mathmatics value of simulation
        cout << "avg_waiting_time = " << avg_waiting_time << endl;
        cout << "avg_service_time = " << avg_service_time << endl;
        cout << "probability_of_waiting = " << probability_of_waiting << endl;
        cout << "probability_of_idle_server = " << probability_of_idle_server << endl;
        cout << "probability_of_busy_server = " << probability_of_busy_server << endl;


    #ifndef ONLINE_JUDGE
        printf("\n>>Time taken: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}

