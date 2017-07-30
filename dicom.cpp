// Namenskonvention: 
// erste Praeferenz wurde darauf gelegt, dass mit der Editor-Suchfunktion moeglichst alle gleichen Bezeichner gefunden werden koennen, 
// zweite Praeferenz darauf, dass deutsche und englische Namenbestandteile moeglichst gut gemischt werden
#ifdef linux
#include <utime.h> // utime(
#include <tiffio.h> // fuer empfarch
#include <iomanip> // setprecision
#elif __MINGW32__ || _MSC_VER
#include <sys/utime.h>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

// #include <iostream>
// #include <fstream> // jetzt in kons.h
// #include <sstream>
// #include <dirent.h> // DIR, dirent, opendir, readdir, PATH_MAX
// #include <boost/algorithm/string.hpp> // clock // jetzt in kons.h
#include "kons.h"
#include "DB.h"
// fuer die Prozessliste
#define PROC_VERZ "/proc/"
#ifdef linux
#include <sys/utsname.h> // utsname
#endif
#include <fcntl.h> // fuer fd_reopen usw.
#include <termios.h> // fuer tcgetattr
#include <regex>
#include <sys/wait.h> // fuer waitpid
#include <chrono> // fuer sleep_for 
#include <thread> // fuer sleep_for

#include <set>
// aktuelle Programmversion
const double& versnr=
#include "versdt"
;
// Verzeichnis auf Github
const string& gitv=
#include "gitvdt"
;
// "dieses Programm", hier definiert, waehrend "meinname" sich durch umbenennen aendert
#define DPROG "dicom"

uchar ZDB=0; // fuer Zusatz-Debugging (SQL): ZDB 1, sonst: 0
const char sep = 9; // geht auch: "[[:blank:]]"

const string s_true="true";
const string s_dampand="&&";
const string s_gz="gz";
#define DPROGcpp
#include "dicom.h"
const char *logdt="/var/log/" DPROG "vorgabe.log";

int main(int argc, char** argv)
{
	int obverb=0,oblog=0;
	const string qvz="/DATA/Patientendokumente/HDneu";
	const string zvz="/DATA/Patientendokumente/test";
	svec rueck;
	systemrueck("find "+qvz+" -type f -not -path '*\\.*' -not -path '*DICOMDIR*'",obverb,oblog,&rueck);
	for(size_t nr=0;nr<rueck.size();nr++) {
		svec ir;
		systemrueck("dcmdump '"+rueck[nr]+"' 2>/dev/null",obverb,oblog,&ir);
		const auto dim=7;
		string erg[dim];
		const char *knz[7]={"PatientName","PatientBirthDate","PatientID","PatientSex","ImageType","ReferringPhysicianName","AcquisitionDateTime"};
		uchar gibaus=0;
		string ord[dim];
		string bname;
		int fehltzahl=dim;
		for(size_t zl=0;zl<ir.size();zl++) {
			for(int j=0;j<dim;j++) {
				if (ord[j].empty()) {
					if (ir[zl].find(knz[j])!=string::npos) {
						size_t p1=ir[zl].find('[');
						if (p1!=string::npos) {
							size_t p2=ir[zl].find(']',p1);
							if (p2!=string::npos) {
								string roh=ir[zl].substr(p1+1,p2-p1-1);
								if (j==4) if ((p1=roh.rfind('\\'))!=string::npos) roh.erase(0,p1+1);
								if (j==6) if ((p1=roh.rfind('.'))!=string::npos) roh.erase(p1);
								if (j==0) ersetzAlle(&roh,"^",",");
								ord[j]=roh;
								fehltzahl--;
								gibaus=1;
							}
						}
					}
				}
			}
			if (!fehltzahl) break;
		} // 	for(size_t zl=0;zl<ir.size();zl++)
		for(int j=0;j<dim;j++) {
			bname+=ord[j]+'_';
		}
		string neuname=zvz+"/"+bname+".png";
		systemrueck("dcmj2pnm +on2 '"+rueck[nr]+"' > '"+neuname+"'",obverb,oblog);
		struct stat nst;
		if (!lstat(neuname.c_str(),&nst)) {
		  struct tm tm={0};
		  strptime(ord[6].c_str(),"%Y%m%d%H%M%S",&tm);
			tm.tm_isdst=-1;
		  time_t modz=mktime(&tm);
			struct utimbuf ub={0};
			ub.modtime=modz;
			ub.actime=modz;
			if (utime(neuname.c_str(),&ub)) {
			 Log(rots+"Fehler beim Datumsetzen von '"+blau+neuname+schwarz,obverb,oblog);
			}
		}
		//		systemrueck("touch -r '"+rueck[nr]+"' '"+neuname+"'",obverb,oblog); // = zu spaet
		if (gibaus)
			caus<<bname<<endl;
		caus<<"Nr: "<<blau<<nr<<schwarz<<", "<<blau<<rueck[nr]<<schwarz<<" "<<blau<<(ir.size()?ir[0]:"")<<schwarz<<endl;
	}
}
