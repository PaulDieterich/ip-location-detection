#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <list>
#include <arpa/inet.h>
#include <math.h>
#include <vector>
#include "GPXData.h"
#include <bits/stdc++.h>
using namespace std;

struct GPXData{
	unsigned long ip;
	unsigned long startIP;
	unsigned long endIP;
	string country; 
	string region; 
	string city; 
	unsigned long latitude; 
	unsigned long longitude;
};

unsigned long convertIpToInteger(std::string);
set<string> readFile();
list<long> calcLocation(set<string>);
void readCSVandGetLocationToVector(string);
int main() {
	set<string> iplist;
	list<long> locationNumber; 
	iplist = readFile();
	locationNumber = calcLocation(iplist);
   
	string tarpit = "tarpit.csv";
	string ip2location = "IP2LOCATION-LITE-DB5.csv";
	iplist = readTarpitFileToSet(tarpit);
 	vector<string> row = readCSVandGetLocationToVector(ip2location);
	for(auto const& ip : iplist){
		//cout << ip << " - " <<  to_string(convertIpToInteger(ip)) << endl;
	} 
return 0;
}

set<string> readTarpitFileToSet(string filename) {
	ifstream file("tarpit.csv");
    set<string> iplist;
	string line;
	struct sockaddr_in sa; 
	if(!file.is_open()){ 
		cout << "cant open file" << endl;
		return iplist; 
	}
	while (getline(file, line, ',')) {
		if(inet_pton(AF_INET, line.c_str(), &(sa.sin_addr))){
			iplist.insert(line);
		}
	}
	return iplist;
}

unsigned long convertIpToInteger(std::string ipv4Str){
	const char *ip = ipv4Str.c_str();
	unsigned int a, b, c, d;
	sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d );
	unsigned long ipAddr =(a*pow(2,24)) + (b*pow(2,16)) + (c*pow(2,8)) + d;
    //2^24 = 16777216  2^16 = 65536 2^8 = 256 2^0 = 1
    return ipAddr;
}

list<long> calcLocation(set<string> iplist){
list<long> locationNumber; 
	for(auto const& ip : iplist){
		locationNumber.push_back(convertIpToInteger(ip));
	}
	return locationNumber;
}


// Speicherere alle gebrauchten standorte in eine neue datei. 
// wenn eingehende locationNumber einem ISP zugeordnert werden konnte dann wird dieser in die datei gespeichert. 
// wenn diese IPnumber range schon vorhanden ist dann wird es nicht nochmal gespeichert 

//multithreadete einlesen der csv dateien. 

vector<string> readCSVandGetLocationToVector(string filename){
	ifstream csv(filename);
	string cell; 
	vector<string> data = vector<string>();
	//vector<GPXData> gpxData = vector<GPXData>(); 
	
	if(!csv.is_open()){
		cout <<  "cant open csv-file" << endl;
	}
	std::string::size_type sz; 
	while(getline(csv,cell,",")){
		data.push_back(cell);
	}
	return data;
}

/*
		stringstream lineStream(line);
		string cell; 
		vector<string> row = vector<string>();
		GPXData g; 
        while(getline(lineStream,cell,','))
        {
            row.push_back(cell);
			cout << row[0] << endl;
        }
	/*	g.startIP = stol(row[0]);
		g.endIP = stol("123");
		g.country = row[3];
		g.region = row[4];
		g.city = row[5];
		g.latitude = stol("123");
		g.longitude = stol("123");

		gpxData.push_back(g);
		*/	
	
	
	//for(GPXData g: gpxData){
//		cout << g.startIP << "-" << g.country << endl;
//	}


