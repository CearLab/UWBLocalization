#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <signal.h>
#include <cstring>
#include <pthread.h>
#include <malloc.h>

#include <list>

using namespace std;

//#include "uwb.h"
#include "UwbApi.h"

//#define WITH_UWB


#define DIST
//#define MATRIX 


// To be changed according to real UWB setup
#define NODENUMBER 3
#define TAGNUMBER 1
#define THRESHOLD 2000 // Assume that maximum distance is 20 m
#define ALL (NODENUMBER + TAGNUMBER)

double UWB_FREQUENCY = 15.0;
/*
TAG 1 : 0x0E9E
TAG 2 : 0x00B3

ANCHOR 1 : 0x45BB
ANCHOR 2 : 0x4890
ANCHOR 3 : 0x0C16
ANCHOR 4 : 0x5C12
ANCHOR 5 : 0x800C
ANCHOR 6 : 0x0712
ANCHOR 7 : 0x1C93
ANCHOR 8 : 0x1C0A
*/

const node_id_t slaves[8] = {0x45BB, 0x4890, 0x0C16, 0x5C12, 0x800C, 0x0712, 0x1C93, 0x1C0A};
extern node_id_t uwb_master_id = 0x0E9E; 
extern node_id_t uwb_master_id2 = 0x00B3;
const node_id_t nodes[10] = {/*tag(s)*/ 0x00B3, 0x0E9E, /*anchors*/ 0x45BB, 0x4890, 0x0C16, 0x5C12, 0x800C, 0x0712, 0x1C93, 0x1C0A};

extern node_id_t *uwb_slave_ids = (node_id_t*)malloc((NODENUMBER + 1) * sizeof(uint16_t));
extern node_id_t *all_nodes = (node_id_t*)malloc((ALL + 1) * sizeof(uint16_t));

int cnt;
int id;
pthread_spinlock_t epsilon_lock_;
double epsilon;

vector<double> uwbTimestamps;
vector<vector<uint16_t>> uwbReadings;
double uwbTimestampsOld = 0.0;

// double mean;
// int counter = 0;
//int delay = 200; // ms
int pkg = 0;

void create_spinlock(pthread_spinlock_t * lock);
void saveUWBreadings(const string &, vector<double>, vector<vector<uint16_t>>);
void initialization(void);

 
#ifdef DIST
  int mode = 0; //DIST mode
  static void distanceFromUWBs(rall_descr_t* rall) {
    printf("TAG %d\n",id);
    vector<uint16_t> tmp;
    bool check = false;
  
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double t0 = (double)nanoseconds / 1000000.0;
  
    for(int i = 0; i < NODENUMBER; i++) {
      if(rall->distances[i] > THRESHOLD) check = true; 

      tmp.push_back(rall->distances[i]);
      printf("Tag %d - Anchor %d:\t%d\n", id, i+1, rall->distances[i]);
    }      
  


    if (check) { //error in trasmission
/*       pthread_spin_lock(&epsilon_lock_);
      if(id == 1){
        cnt++;
        //epsilon += ((1.0/UWB_FREQUENCY)/15.0);
        //usleep(delay*1000); //ms
       } 
      if(id == 2) {
        cnt++;
        //epsilon += ((1.0/UWB_FREQUENCY)/17.0);
        //UWB_FREQUENCY = 5.0; 
      } 
      pthread_spin_unlock(&epsilon_lock_); */
      cnt++;
    } else {
      //if(UWB_FREQUENCY < 2.0) UWB_FREQUENCY += 1.0;
    }
    
    
    uwbReadings.push_back(tmp);
    auto nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double millis = (double)nanoseconds_since_epoch / 1000000.0;
    uwbTimestamps.push_back(millis);

    double et = millis-uwbTimestampsOld; //elapsed time in ms
    // counter += 1;
    // mean += (1.0/counter*((1.0/(et/1000.0))-mean));
    //printf("e.t.: %f ms\n", et);
    uwbTimestampsOld = millis;
    // printf("%f\n",millis);

    printf("\nfrequency: %f Hz \n\n", 1.0/(et/1000.0));

    auto nanoseconds1 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double t1 = (double)nanoseconds1 / 1000000.0;

    double t_cb = (t1-t0);  //callback duration
    // double f_cb = 1.0/t_cb; //callback frequency

    //printf("id: %d\tcheck: %d\n", id, check);
    //printf("epsilon:\t%lf ms\n",epsilon);
    printf("failure counter:\t%d/%d\n", cnt, pkg);
    // printf("failure percentage:\t%d\n", cnt/pkg);
    //printf("callback duration:\t%lf ms\n", t_cb);

}

#endif
#ifdef MATRIX
  int mode = 1; //MATRIX mode
  static void distanceFromUWBs(adjm_descr_t* rall) {
  printf("Adjacency Matrix:\n");
  
  vector<uint16_t> tmp;
  
  for(int i = 0; i < (ALL*ALL); i++) {
    tmp.push_back(rall->matrix[i].distance);

    printf("\t%u", rall->matrix[i].distance);
    if(((i+1)%ALL) == 0) printf("\n");
  }
  
  uwbReadings.push_back(tmp);
  auto nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  double millis = (double)nanoseconds_since_epoch / 1000000.0;
  uwbTimestamps.push_back(millis);

  double et = millis-uwbTimestampsOld; //elapsed time in ms
  //counter += 1;
  //mean += (1.0/counter*((1.0/(et/1000.0))-mean));
  printf("e.t.: %f s\n", et/1000.0);
  uwbTimestampsOld = millis;

  printf("\nfrequency: %f Hz \n\n", 1.0/(et/1000.0));

}
#endif



bool runFlag = true;

void ctrl_c_handler(int s){
  s = s;
  pthread_spin_destroy(&epsilon_lock_);
  runFlag = false;
}

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    cerr << endl << "Usage: ./main" << endl 
                 << "         specify device file name [e.g. /dev/ttyACM0]" << endl
                 << "Example: ./main /dev/ttyACM0" << endl;
    return 1;
  }

  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = ctrl_c_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  
  try {
    init(argv[1]);
    id = (atoi(&argv[1][strlen(argv[1])-1]) + 1);
    initialization();

    if(id == 2) epsilon = (1.0/UWB_FREQUENCY)*1000.0;
    if(id == 1) epsilon = 0.0;
    sleep(1);

    // Registering callback to get distances from UWBs  
    #ifdef DIST 
      register_rall_cb(distanceFromUWBs);
      multi_range_with(uwb_master_id, uwb_slave_ids, NODENUMBER);
    #endif
    #ifdef MATRIX
      register_adjm_cb(distanceFromUWBs);
      build_adjm(all_nodes, ALL);  
    #endif


    double elapsedTime = 0.0;  //1.0/UWB_FREQUENCY; // time elapsed for synching UWB with odometry 
    double tUwb_prev = 0.0, tUwb_now = 0.0;
    tUwb_prev = std::chrono::steady_clock::now().time_since_epoch().count();
    bool skip = true;
    
    // Main loop
    while(runFlag)
    {
      tUwb_now = std::chrono::steady_clock::now().time_since_epoch().count();
      elapsedTime = ((tUwb_now - tUwb_prev) / 1000000.0);
      //usleep((1.0/UWB_FREQUENCY)*1000000.0);
      //cout << "elapsedTime: " << elapsedTime << "ms" << endl;
      //cout << tUwb_now.time_since_epoch().count << endl;
      if(elapsedTime >= ((1.0/UWB_FREQUENCY * 1000.0)) + epsilon)
      { 
        
        elapsedTime = 0.0;
        epsilon = 0.0;
        tUwb_prev = tUwb_now;

        skip = !skip;
        
        if(skip) continue;

        if(mode == 0){
          // auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
          // double t0 = (double)nanoseconds / 1000000.0;
          pkg++;
          multi_range_with(uwb_master_id, uwb_slave_ids, NODENUMBER);

          // auto nanoseconds1 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
          // double t1 = (double)nanoseconds1 / 1000000.0;
  
          // double t_cb = (t1-t0);  //API duration
          // printf("API duration:\t%lf ms\n\n", t_cb);
        } 
        else build_adjm(all_nodes, ALL);
      }
      else
      {
        //elapsedTime += chrono::duration_cast<chrono::duration<double> >(tUwb_now - tUwb_prev).count();
        //cout << "elapsedTime: " << elapsedTime << "s" << endl;
      }

      //tUwb_prev = tUwb_now; //chrono::steady_clock::now();
    }

    // Save UWB readings
    string filename = "UWBReadings_" + std::to_string(id) + ".dat";
    
    saveUWBreadings(filename, uwbTimestamps, uwbReadings);
    free(uwb_slave_ids);
    free(all_nodes);
  }
  catch(exception& ex) {
    cout << ex.what() << endl;
  }

  return EXIT_SUCCESS;
}

void saveUWBreadings(const string &filename, vector<double> timestamps, vector<vector<uint16_t>> readings)
{
  ofstream f;

  f.open(filename.c_str());
  
  f << fixed;

  vector<vector<uint16_t>>::iterator itReadings = readings.begin();

  for(vector<double>::iterator itTimestamps = timestamps.begin(); itTimestamps != timestamps.end(); itTimestamps++, itReadings++)
  {
    vector<uint16_t> _readings = *itReadings;
    f << setprecision(6) << *itTimestamps << " " <<  setprecision(9);

    for(int i=0; i < NODENUMBER;i++){
      f << _readings.at(i) << " "; 
    }
    f << endl;
  }
  f.close();
  cout << endl << "UWB readings saved!" << endl;
}


void initialization(){
  for(int i = 0; i < NODENUMBER; i++) {
    uwb_slave_ids[i] = slaves[i];
    printf("Anchor %d:\t%04X\n",i,uwb_slave_ids[i]);
  }

  for(int i = TAGNUMBER%2; i <= ALL; i++){
      all_nodes[i] = nodes[i];
      if(i == 2) printf(" | ");
      printf("%04X ", all_nodes[i]);
  } 
    printf("\n");
/*     if(id == 1) {
      for(int i = 0; i < 3; i++) {
        uwb_slave_ids[i] = slaves[i];
        printf("Anchor %d:\t%04X\n",i,uwb_slave_ids[i]);
      }
    } 
    //uwb_slave_ids = {0x45BB, 0x4890, 0x0C16};
    
    if(id == 2) {
      for(int i = 3; i < 5; i++) {
        uwb_slave_ids[i] = slaves[i];
        printf("Anchor %d:\t%04X\n",i,uwb_slave_ids[i]);
      }
      uwb_master_id = uwb_master_id2;
    }
    //uwb_slave_ids = {0x5C12, 0x800C}; */
}

void create_spinlock(pthread_spinlock_t * lock)
{
  if (pthread_spin_init(lock, PTHREAD_PROCESS_PRIVATE)) {
    throw std::runtime_error("Failed to initialize spinlock");
  }
}