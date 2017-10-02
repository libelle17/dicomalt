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
// "dieses Programm", hier definiert, waehrend "meinname" sich durch umbenennen aendert
#define DPROG "dicom"

uchar ZDB=0; // fuer Zusatz-Debugging (SQL): ZDB 1, sonst: 0
const char sep = 9; // geht auch: "[[:blank:]]"

#define DPROGcpp
#include "dicom.h"
const char *logdt="/var/log/" DPROG "vorgabe.log";
enum T_
{/*{{{*/
	T_pruefdictab,
	T_eindeutige_Identifikation,
	T_Patientenname,
	T_Geburtsdatum,
	T_Patientennr,
	T_Geschlecht,
	T_Bildtyp,
	T_TransducerData,
	T_ProcessingFunction,
	T_Aufnahmedatum,
	T_Arzt,
	T_Tabelle_fuer_dicom_Bilder,
	T_Fehler_beim_Pruefen_von_dictab,
	T_MAX
};
char const *DPROG_T[T_MAX+1][SprachZahl]={
 // T_pruefdictab
 {"pruefdictab()","checkdictab()"},
 // T_eindeutige_Identifikation
 {"eindeutige Identifikation","unique identification number"},
 // T_Patientenname
 {"Patientenname","Name of the patient"},
 // T_Geburtsdatum
 {"Geburtsdatum","Birth date"},
 // T_Patientennr
 {"Patientennr","Pat.-ID"},
 // T_Geschlecht
 {"Geschlecht","sex"},
 // T_Bildtyp
 {"Bildtyp","image type"},
 // T_TransducerData
 {"Schallkopf","transducer"},
 // T_ProcessingFunction
 {"Programm","program"},
 // T_Aufnahmedatum
 {"Aufnahmedatum","acquisition date"},
 // T_Arzt
 {"Arzt","Physician"},
 // T_Tabelle_fuer_dicom_Bilder
 {"Tabelle fuer dicom-Bilder","table for dicom pictures"},
 // T_Fehler_beim_Pruefen_von_dictab
 {"Fehler eim Prüfen der Tabelle dictab","error checking table dictab"},
 {"",""}
};
class TxB Tx((const char* const* const* const*)DPROG_T);
const DBSTyp myDBS=MySQL;
const string host="localhost";
const string muser="praxis";
const string mpwd="sonne";
const string dbq="fotosinp";
const string tbn="dictab";
const int maxconz=1;
linst_cl *linstp=0;
DB *My=0;

void initdb(int obverb/*=0*/,int oblog/*=0*/)
{
 My=new DB(myDBS,linstp,host,muser,mpwd,maxconz,dbq,/*port=*/0,/*unix_socket=*/0,/*client_flag=*/0,obverb,oblog);
 if (My->ConnError) {
  delete My;
	My=0;
 } else {
  My->lassoffen=1;
 }
}

void pruefdictab(int aktc,int obverb,int oblog)
{
 Log(violetts+Tx[T_pruefdictab]+schwarz,obverb,oblog);
 Feld felder[]= {
  Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1),
  Feld("PatientName","varchar","1","",Tx[T_Patientenname],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
  Feld("Geburtsdatum","datetime","0","0",Tx[T_Geburtsdatum],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
  Feld("PatientID","varchar","1","",Tx[T_Patientennr],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
  Feld("Geschlecht","varchar","1","",Tx[T_Geschlecht],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("Bildtyp","varchar","1","",Tx[T_Bildtyp],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("ReferringPhysicianName","varchar","1","",Tx[T_Arzt],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("TransducerData","varchar","1","",Tx[T_TransducerData],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("ProcessingFunction","varchar","1","",Tx[T_ProcessingFunction],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("Aufnahmedatum","datetime","0","0",Tx[T_Aufnahmedatum],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
 };
 Tabelle tad(My,tbn,felder,sizeof felder/sizeof *felder,/*indices=*/0,/*index size*/0,Tx[T_Tabelle_fuer_dicom_Bilder]);
 if (tad.prueftab(aktc,obverb)) {
  Log(rots+Tx[T_Fehler_beim_Pruefen_von_dictab]+schwarz,1,1);
	exit(11);
 }
}

int main(int argc, char** argv)
{
	int obverb=2,oblog=0;
	if(argc>1) {
	 string besitzer=(argc>2?argv[2]:"");
	 string benutzer=(argc>3?argv[3]:"");
	 int mitfacl=(argc>4?!strcmp(argv[4],"1")?1:0:0);
	 pruefverz(argv[1],obverb,/*oblog=*/0,/*obmitfacl=*/mitfacl,/*obmitcron=*/1,besitzer,benutzer); 
	}
	const int aktc=0;
	const string qvz="/DATA/Patientendokumente/HDneu";
	const string avz="/DATA/Patientendokumente/HDalt";
	const string zvz="/DATA/Patientendokumente/test";
	const string z2vz="/DATA/Patientendokumente/eingelesen";
	linst_cl linst(obverb,oblog);
	linstp=&linst;
	//	pruefverz(zvz,obverb,0,1,1,"sturm","sturm");
	initdb(obverb,oblog);
	if (!My) exit(5); // Datenbankverbindung nicht erstellbar
	pruefdictab(aktc,obverb,oblog);
	svec rueck;
	systemrueck("find "+qvz+" -type f -not -path '*\\.*' -not -path '*DICOMDIR*'",obverb,oblog,&rueck);
	if (!rueck.size()) {
	 Log(rots+"Keine Dateien in '"+blau+qvz+rot+"' gefunden!",1,0);
	}
	for(size_t nr=0;nr<rueck.size();nr++) {
		svec ir;
		systemrueck("dcmdump '"+rueck[nr]+"' 2>/dev/null",obverb,oblog,&ir);
		const auto dim=9;
		string erg[dim];
		const char *knz[dim]={"PatientName","PatientBirthDate","PatientID","PatientSex",
			                    "ImageType","ReferringPhysicianName","TransducerData","ProcessingFunction","AcquisitionDateTime"};
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
								if ((p1=roh.find('\''))!=string::npos) roh.erase(p1);
								if ((p1=roh.find('\"'))!=string::npos) roh.erase(p1);
								if (j==4) if ((p1=roh.rfind('\\'))!=string::npos) roh.erase(0,p1+1); // ImageType
								if (j==8) if ((p1=roh.rfind('.'))!=string::npos) roh.erase(p1); // AcquisitionDateTime
								if (j==0) ersetzAlle(&roh,"^",","); // PatientName
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
		RS rins(My);
		vector<instyp> einf;
		char vor=0;
	  for(unsigned j=1;j<ord[0].length();j++) {
		 if (vor&&vor!=',') ord[0][j]=tolower(ord[0][j]);
		 vor=ord[0][j];
		}
		einf.push_back(instyp(My->DBS,"PatientName",&ord[0]));
		struct tm tmg={0};
		strptime(ord[1].c_str(),"%Y%m%d",&tmg);
		einf.push_back(instyp(My->DBS,"Geburtsdatum",&tmg));
		einf.push_back(instyp(My->DBS,"PatientID",&ord[2]));
		einf.push_back(instyp(My->DBS,"Geschlecht",&ord[3]));
		einf.push_back(instyp(My->DBS,"Bildtyp",&ord[4]));
		einf.push_back(instyp(My->DBS,"ReferringPhysicianName",&ord[5]));
		einf.push_back(instyp(My->DBS,"TransducerData",&ord[6]));
		einf.push_back(instyp(My->DBS,"ProcessingFunction",&ord[7]));
		struct tm tma={0};
		strptime(ord[6].c_str(),"%Y%m%d%H%M%S",&tma);
		const string jahr=ord[6].substr(0,4);
		einf.push_back(instyp(My->DBS,"Aufnahmedatum",&tma));
		svec eindfeld;
		eindfeld<<"PatientName";
		eindfeld<<"Geburtsdatum";
		eindfeld<<"PatientID";
		eindfeld<<"Aufnahmedatum";
		int ZDB=0;
		string id; // Rueckgabe: ID
		rins.tbins(tbn,einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,&id,/*eindeutig=*/0,eindfeld);
		Log("ID: '"+violetts+id+schwarz+"'",obverb,oblog);
		for(int j=0;j<dim;j++) {
			bname+=ord[j]+'_';
		}
		if (id.empty()) {
			Log(rots+bname+schwarz+" schon da!",obverb,oblog);
		} else {
			string neuname=zvz+"/"+bname+".png";
			systemrueck("dcmj2pnm +on2 '"+rueck[nr]+"' > '"+neuname+"'",obverb,oblog);
			struct stat nst={0};
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
				systemrueck("chown sturm:praxis '"+neuname+"'",obverb,oblog);
				string cmd="cp -a '"+neuname+"' '"+z2vz+"/"+jahr+"/'";
				systemrueck(cmd,obverb,oblog);
			} else {
			 RS weg(My,"DELETE FROM `"+tbn+"` WHERE ID="+id,aktc,ZDB);
			}
			//		systemrueck("touch -r '"+rueck[nr]+"' '"+neuname+"'",obverb,oblog); // = zu spaet
			if (gibaus)
				Log(bname,obverb,oblog);
			Log("Nr: "+blaus+ltoan(nr)+schwarz+", "+blau+rueck[nr]+schwarz+" "+blau+(ir.size()?ir[0]:"")+schwarz,obverb,oblog);
		}
	}
}
