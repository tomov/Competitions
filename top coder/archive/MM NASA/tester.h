#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <math.h>
#include <stack>
#include <deque>
#include <numeric>
#include <ctime>


#define mpair make_pair
#define all(v) v.begin(),v.end()
using namespace std;
typedef long long ll;
typedef double ld;
const ld epsylon = 1e-9;

struct Resource{
    bool consumable;
    ld mass;
    ld volume;
    Resource(){//Default constuctor sets invalid value for mass
        mass = -1;
    }
    friend istream& operator >> (istream& in,Resource& r);
};


istream& operator >> (istream& in,Resource& r){
    in>>r.consumable>>r.mass>>r.volume;
    return in;
}
struct needed{
    int rid;//the id of the required resource;
    vector<ld> amount;//amount[0] is the amount needed in the best sceanario and amount[1] in the worst
    needed():amount(2,-1.0){
    }
    friend istream& operator >> (istream& in,needed& n);
};
istream& operator >> (istream& in,needed& n){
    in>>n.rid>>n.amount[0]>>n.amount[1];
    return in;
}
struct mission_entry{
    int mid;
    int worst;
    int treated;
    int untreated;
    friend istream& operator>>(istream& in, mission_entry& e);
};
istream& operator>>(istream& in, mission_entry& e){

    in>>e.mid>>e.worst>>e.treated>>e.untreated;
    return in;
}

string get_rid(int id)
{
    string res = "";
    while(id){
        res.push_back('0' + id%10);
        id/=10;
    }
    reverse(all(res));
    return "R"+res;
}
vector<Resource> parse_resources(const vector<string>& res){
    vector<Resource> a(10002);
    for(int i=0;i<(int)res.size();i++)
    {
        int id;
        istringstream in(res[i].c_str()+1);
        in>>id;
        in>>a[id];
    }
    return a;
}
vector<vector<mission_entry> > parse_missions(const vector<string>& train){
    vector<vector<mission_entry> > res(100002);
    char buf[20];
    int mission_id;
    int order;
    mission_entry temp;
    for(int i=0;i<(int)train.size();i++){
        sscanf(train[i].c_str(),"%d %d %s %d %d %d",&mission_id,&order,buf,&temp.worst,&temp.treated,&temp.untreated);
        sscanf(buf+2,"%d",&temp.mid);
        res[mission_id].push_back(temp);
    }
    return res;
}
vector<vector<needed> > parse_events(const vector<string>& required){
    vector<vector<needed> > a(10002);
    int mid;
    needed _needed;
    for(int i=0;i<(int)required.size();i++){
        sscanf(required[i].c_str()+2,"%d R%d %lf %lf",&mid,&_needed.rid,&_needed.amount[0],&_needed.amount[1]);
        a[mid].push_back(_needed);
    }
    return a;
}
/*---------------------------------------------------------------------------------//
									TESTER
//---------------------------------------------------------------------------------*/
///////////////////////////////Randomc
#ifndef RANDOMC_H
#define RANDOMC_H


// Define 32 bit signed and unsigned integers.
// Change these definitions, if necessary, to match a particular platform
#if defined(_WIN16) || defined(__MSDOS__) || defined(_MSDOS) 
// 16 bit systems use long int for 32 bit integer
typedef long int           int32;   // 32 bit signed integer
typedef unsigned long int  uint32;  // 32 bit unsigned integer
#else
// Most other systems use int for 32 bit integer
typedef int                int32;   // 32 bit signed integer
typedef unsigned int       uint32;  // 32 bit unsigned integer
#endif

// Define 64 bit signed and unsigned integers, if possible
#if (defined(__WINDOWS__) || defined(_WIN32)) && (defined(_MSC_VER) || defined(__INTEL_COMPILER))
// Microsoft and other compilers under Windows use __int64
typedef __int64            int64;   // 64 bit signed integer
typedef unsigned __int64   uint64;  // 64 bit unsigned integer
#define INT64_DEFINED               // Remember that int64 is defined
#elif defined(__unix__) && (defined(_M_IX86) || defined(_M_X64))
// Gnu and other compilers under Linux etc. use long long
typedef long long          int64;   // 64 bit signed integer
typedef unsigned long long uint64;  // 64 bit unsigned integer
#define INT64_DEFINED               // Remember that int64 is defined
#else
// 64 bit integers not defined
// You may include definitions for other platforms here
#endif

void EndOfProgram(void);               // System-specific exit code (userintf.cpp)

void FatalError(char * ErrorText);     // System-specific error reporting (userintf.cpp)

class CRandomMersenne {                // Encapsulate random number generator
#if 0
	// Define constants for type MT11213A:
#define MERS_N   351
#define MERS_M   175
#define MERS_R   19
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   17
#define MERS_A   0xE4BD75F5
#define MERS_B   0x655E5280
#define MERS_C   0xFFD58000
#else    
	// or constants for type MT19937:
#define MERS_N   624
#define MERS_M   397
#define MERS_R   31
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   18
#define MERS_A   0x9908B0DF
#define MERS_B   0x9D2C5680
#define MERS_C   0xEFC60000
#endif
public:
	CRandomMersenne(uint32 seed) {      // Constructor
		RandomInit(seed); LastInterval = 0;}
	void RandomInit(uint32 seed);       // Re-seed
	void RandomInitByArray(uint32 seeds[], int length); // Seed by more than 32 bits
	int IRandom (int min, int max);     // Output random integer
	int IRandomX(int min, int max);     // Output random integer, exact
	double Random();                    // Output random float
	uint32 BRandom();                   // Output random bits
private:
	void Init0(uint32 seed);            // Basic initialization procedure
	uint32 mt[MERS_N];                  // State vector
	int mti;                            // Index into mt
	uint32 LastInterval;                // Last interval length for IRandomX
	uint32 RLimit;                      // Rejection limit used by IRandomX
	enum TArch {LITTLE_ENDIAN1, BIG_ENDIAN1, NONIEEE}; // Definition of architecture
	TArch Architecture;                 // Conversion to float depends on architecture
};    


class CRandomMother {             // Encapsulate random number generator
public:
	void RandomInit(uint32 seed);       // Initialization
	int IRandom(int min, int max);      // Get integer random number in desired interval
	double Random();                    // Get floating point random number
	uint32 BRandom();                   // Output random bits
	CRandomMother(uint32 seed) {   // Constructor
		RandomInit(seed);}
protected:
	uint32 x[5];                        // History buffer
};

#endif

void CRandomMersenne::Init0(uint32 seed) {
	// Detect computer architecture
	union {double f; uint32 i[2];} convert;
	convert.f = 1.0;
	if (convert.i[1] == 0x3FF00000) Architecture = LITTLE_ENDIAN1;
	else if (convert.i[0] == 0x3FF00000) Architecture = BIG_ENDIAN1;
	else Architecture = NONIEEE;

	// Seed generator
	mt[0]= seed;
	for (mti=1; mti < MERS_N; mti++) {
		mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
	}
}

void CRandomMersenne::RandomInit(uint32 seed) {
	// Initialize and seed
	Init0(seed);

	// Randomize some more
	for (int i = 0; i < 37; i++) BRandom();
}


void CRandomMersenne::RandomInitByArray(uint32 seeds[], int length) {
	// Seed by more than 32 bits
	int i, j, k;

	// Initialize
	Init0(19650218);

	if (length <= 0) return;

	// Randomize mt[] using whole seeds[] array
	i = 1;  j = 0;
	k = (MERS_N > length ? MERS_N : length);
	for (; k; k--) {
		mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL)) + seeds[j] + j;
		i++; j++;
		if (i >= MERS_N) {mt[0] = mt[MERS_N-1]; i=1;}
		if (j >= length) j=0;}
	for (k = MERS_N-1; k; k--) {
		mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL)) - i;
		if (++i >= MERS_N) {mt[0] = mt[MERS_N-1]; i=1;}}
	mt[0] = 0x80000000UL;  // MSB is 1; assuring non-zero initial array

	// Randomize some more
	mti = 0;
	for (int i = 0; i <= MERS_N; i++) BRandom();
}


uint32 CRandomMersenne::BRandom() {
	// Generate 32 random bits
	uint32 y;

	if (mti >= MERS_N) {
		// Generate MERS_N words at one time
		const uint32 LOWER_MASK = (1LU << MERS_R) - 1;       // Lower MERS_R bits
		const uint32 UPPER_MASK = 0xFFFFFFFF << MERS_R;      // Upper (32 - MERS_R) bits
		static const uint32 mag01[2] = {0, MERS_A};

		int kk;
		for (kk=0; kk < MERS_N-MERS_M; kk++) {    
			y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
			mt[kk] = mt[kk+MERS_M] ^ (y >> 1) ^ mag01[y & 1];}

		for (; kk < MERS_N-1; kk++) {    
			y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
			mt[kk] = mt[kk+(MERS_M-MERS_N)] ^ (y >> 1) ^ mag01[y & 1];}      

		y = (mt[MERS_N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[MERS_N-1] = mt[MERS_M-1] ^ (y >> 1) ^ mag01[y & 1];
		mti = 0;
	}

	y = mt[mti++];

#if 1
	// Tempering (May be omitted):
	y ^=  y >> MERS_U;
	y ^= (y << MERS_S) & MERS_B;
	y ^= (y << MERS_T) & MERS_C;
	y ^=  y >> MERS_L;
#endif

	return y;
}


double CRandomMersenne::Random() {
	// Output random float number in the interval 0 <= x < 1
	union {double f; uint32 i[2];} convert;
	uint32 r = BRandom();               // Get 32 random bits
	// The fastest way to convert random bits to floating point is as follows:
	// Set the binary exponent of a floating point number to 1+bias and set
	// the mantissa to random bits. This will give a random number in the 
	// interval [1,2). Then subtract 1.0 to get a random number in the interval
	// [0,1). This procedure requires that we know how floating point numbers
	// are stored. The storing method is tested in function RandomInit and saved 
	// in the variable Architecture.

	// This shortcut allows the compiler to optimize away the following switch
	// statement for the most common architectures:
#if defined(_M_IX86) || defined(_M_X64) || defined(__LITTLE_ENDIAN__)
	Architecture = LITTLE_ENDIAN1;
#elif defined(__BIG_ENDIAN__)
	Architecture = BIG_ENDIAN1;
#endif

	switch (Architecture) {
   case LITTLE_ENDIAN1:
	   convert.i[0] =  r << 20;
	   convert.i[1] = (r >> 12) | 0x3FF00000;
	   return convert.f - 1.0;
   case BIG_ENDIAN1:
	   convert.i[1] =  r << 20;
	   convert.i[0] = (r >> 12) | 0x3FF00000;
	   return convert.f - 1.0;
   case NONIEEE: default: ;
	} 
	// This somewhat slower method works for all architectures, including 
	// non-IEEE floating point representation:
	return (double)r * (1./((double)(uint32)(-1L)+1.));
}


int CRandomMersenne::IRandom(int min, int max) {
	// Output random integer in the interval min <= x <= max
	// Relative error on frequencies < 2^-32
	if (max <= min) {
		if (max == min) return min; else return 0x80000000;
	}
	// Multiply interval with random and truncate
	int r = int((max - min + 1) * Random()) + min; 
	if (r > max) r = max;
	return r;
}


int CRandomMersenne::IRandomX(int min, int max) {
	// Output random integer in the interval min <= x <= max
	// Each output value has exactly the same probability.
	// This is obtained by rejecting certain bit values so that the number
	// of possible bit values is divisible by the interval length
	if (max <= min) {
		if (max == min) return min; else return 0x80000000;
	}
#ifdef  INT64_DEFINED
	// 64 bit integers available. Use multiply and shift method
	uint32 interval;                    // Length of interval
	uint64 longran;                     // Random bits * interval
	uint32 iran;                        // Longran / 2^32
	uint32 remainder;                   // Longran % 2^32

	interval = uint32(max - min + 1);
	if (interval != LastInterval) {
		// Interval length has changed. Must calculate rejection limit
		// Reject when remainder = 2^32 / interval * interval
		// RLimit will be 0 if interval is a power of 2. No rejection then
		RLimit = uint32(((uint64)1 << 32) / interval) * interval - 1;
		LastInterval = interval;
	}
	do { // Rejection loop
		longran  = (uint64)BRandom() * interval;
		iran = (uint32)(longran >> 32);
		remainder = (uint32)longran;
	} while (remainder > RLimit);
	// Convert back to signed and return result
	return (int32)iran + min;

#else
	// 64 bit integers not available. Use modulo method
	uint32 interval;                    // Length of interval
	uint32 bran;                        // Random bits
	uint32 iran;                        // bran / interval
	uint32 remainder;                   // bran % interval

	interval = uint32(max - min + 1);
	if (interval != LastInterval) {
		// Interval length has changed. Must calculate rejection limit
		// Reject when iran = 2^32 / interval
		// We can't make 2^32 so we use 2^32-1 and correct afterwards
		RLimit = (uint32)0xFFFFFFFF / interval;
		if ((uint32)0xFFFFFFFF % interval == interval - 1) RLimit++;
	}
	do { // Rejection loop
		bran = BRandom();
		iran = bran / interval;
		remainder = bran % interval;
	} while (iran >= RLimit);
	// Convert back to signed and return result
	return (int32)remainder + min;

#endif
}


vector<vector<mission_entry> > missions_given(100002);
vector<string> missions_s;


vector<vector<needed> > events_given(10000);
vector<string> events_s;

vector<Resource> resources_given;
vector<string> resources_s;

void parse_missions_from_file()
{
	FILE *f = fopen("train.txt","r");
	if( f == NULL)
	{
		cerr<<"The file train.txt was not found! Please downlaod it and put it in the current directory!"<<endl;
		exit(1);
	}
	char buf[100];
	while(fgets(buf,100,f)){
		missions_s.push_back(buf);
	}
	missions_given = parse_missions(missions_s);
	fclose(f);
}

void parse_events_from_file()
{
	FILE *f = fopen("events.txt","r");
	if( f == NULL)
	{
		cerr<<"The file events.txt was not found! Please downlaod it and put it in the current directory!"<<endl;
		exit(1);
	}
	char buf[30];
	while(fgets(buf,100,f)){
		events_s.push_back(buf);
	}
	events_given = parse_events(events_s);
	fclose(f);
}
void parse_resources_from_file(){
	FILE *f = fopen("resources.txt","r");
	if( f == NULL)
	{
		cerr<<"The file resources.txt was not found! Please downlaod it and put it in the current directory!"<<endl;
		exit(1);
	}
	char buf[100];
	while(fgets(buf,100,f)){
		resources_s.push_back(buf);
	}
	resources_given = parse_resources(resources_s);
	fclose(f);
}
int eval(vector<ld> MedicKit, vector<mission_entry> mission){
	int evacs = 0;
	const vector<vector<needed> > &events = events_given;
//	const vector<vector<mission_entry> > &missions = missions_given;
	const vector<Resource> &resources = resources_given;

	for(int i = 0; i<(int)mission.size(); i++){//iterate events
		bool supplied = true;
		for(int j = 0; j < (int)events[mission[i].mid].size();j++){
			if(MedicKit[events[mission[i].mid][j].rid] + 1e-12 < events[mission[i].mid][j].amount[mission[i].worst]){
				supplied = false;
				break;
			}
		}

		if(supplied){
			for(int j = 0; j < (int)events[mission[i].mid].size();j++){
				if(resources[events[mission[i].mid][j].rid].consumable){
					MedicKit[events[mission[i].mid][j].rid] -= events[mission[i].mid][j].amount[mission[i].worst];
				}
			}
			evacs += mission[i].treated;
		}else{
			evacs += mission[i].untreated;
		}
	}
	return evacs;
}

vector<ld> get_med_kit(const vector<string>& output){
	vector<ld> resource(10000);
	for(int i=0;i<(int)output.size();i++){
		int id;
		double quant;
		sscanf(output[i].c_str()+1,"%d %lf",&id,&quant);
		if(id <= 0 || id> 10000){
			cerr<<"Wrong resource number given: R"<<id<<endl;
			exit(1);
		}
		if(quant < 1e-12){
			cerr<<"Wrong amount of resource R"<<id<<" is given:"<<quant<<endl;
			exit(1);
		}
		if(resource[id] > 1e-12){
			cerr<<"Resource with id R"<<id<<" selected more then once"<<endl;
			exit(1);
		}
		resource[id] += quant;
	}
	return resource;
}
template<class T >
string to_s(const vector<T>& a,char delim = ' ')
{
	ostringstream out;
	for(int i=0;i<(int)a.size();i++)
	{
		out<<a[i];
		if(i!= (int)a.size()-1)
			out<<delim;
	}
	return out.str();
}
double do_test(int seed , int run){
	SpaceMedkit sp;
	CRandomMersenne rand(seed);
	double P = 0.01 + rand.Random()*0.04;
	double C = rand.Random()*0.001;
//	const vector<vector<needed> > &events = events_given;
	const vector<vector<mission_entry> > &missions = missions_given;
	const vector<Resource> &resources = resources_given;
	double tim = (double)clock() / (double)CLOCKS_PER_SEC;
	vector<string> output = sp.getMedkit(resources_s,events_s,missions_s,P,C);
	double tim2 = (double)clock() / (double)CLOCKS_PER_SEC;;
	vector<ld> mk = get_med_kit(output);
	vector<int> sample;
	vector<bool> used(missions.size(),false);
	if ( !run ) return 0.;
	while(sample.size() < 10000){
		int idx = rand.IRandom(0,(int)missions.size()-1);
		if(!used[idx] && missions[idx].size() > 0){
			used[idx] = true;
			sample.push_back(idx);
		}
	}
	int evac = 0;
	for(int i=0;i<(int)sample.size();i++){
		evac += eval(mk,missions[sample[i]]);
	}
	printf ( "runtime    %lf\n" , tim2 - tim );
	printf("Evacuated %d\n",evac);
	printf("P*10^4: %lf C: %lf\n",P*10000,C);
	if(evac <= P * 10000){
		double score = 0;
		double m = 0, v = 0;
		for(int i = 0; i<(int)mk.size(); i++){
			if(mk[i] > 1e-12){
				m += resources[i].mass * mk[i];
				v += resources[i].volume * mk[i];
			}
		}
		score = C * v + m;
		printf("Total mass: %lf\n",m);
		printf("Total volume: %lf\n",v);
		printf("Score: %lf\n",(double)1000/score);
		return (double)1000/score;
	}else {
		printf("Evacutions exceeded allowed rate! \n");
		return 0;
	}
};
