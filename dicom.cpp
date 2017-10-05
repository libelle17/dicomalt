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
	T_VorgbSpeziell,
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
	// T_VorgbSpeziell
	{"VorgbSpeziell()","specificprefs()"},
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

// wird aufgerufen in: main
int paramcl::initDB()
{
 My=new DB(myDBS,linstp,host,muser,mpwd,maxconz,dbq,/*port=*/0,/*unix_socket=*/0,/*client_flag=*/0,obverb,oblog);
 if (My->ConnError) {
  delete My;
	My=0;
 } else {
  My->lassoffen=1;
 }
 return 0;
} // int paramcl::initDB()

void paramcl::pruefdictab(int aktc)
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
  Feld("PerformingPhysicianName","varchar","1","",Tx[T_Arzt],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("TransducerData","varchar","1","",Tx[T_TransducerData],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("ProcessingFunction","varchar","1","",Tx[T_ProcessingFunction],/*obind=*/1,/*obauto=*/0,/*nnuull=*/0),
  Feld("Aufnahmedatum","datetime","0","0",Tx[T_Aufnahmedatum],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
 };
 Tabelle tad(My,tbn,felder,sizeof felder/sizeof *felder,/*indices=*/0,/*index size*/0,Tx[T_Tabelle_fuer_dicom_Bilder]);
 if (tad.prueftab(aktc,obverb)) {
  Log(rots+Tx[T_Fehler_beim_Pruefen_von_dictab]+schwarz,1,1);
	exit(11);
 }
} // void paramcl::pruefdictab(int aktc)

paramcl::paramcl(const int argc, const char *const *const argv)
{
	cl=argv[0];
	for(int i=1;i<argc;i++)
		if (argv[i][0]) {
			argcmv.push_back(argcl(i,argv)); 
			cl+=" ";
			cl+=argv[i];
		} //     if (argv[i][0])
	tstart=clock();
	langu=holsystemsprache(obverb);
	//  akonfdt.clear();
} // paramcl::paramcl()

// wird aufgerufen in: main
void paramcl::getcommandl0()
{
	Log(violetts+"getcommandl0()"+schwarz);
	// Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
	agcnfA.init(16, "language","host","muser","mpwd","datenbank","findvers","duser",
			"cronminut","autoupd","logvz","logdname","oblog","qvz","avz","zvz","z2vz");
	gcl0();
} // void paramcl::getcommandl0(int argc, char** argv)

constexpr const unsigned datcl::dim;
constexpr const char *datcl::knz[dim];
constexpr const unsigned datcl::pnnr, datcl::itnr, datcl::rpnr, datcl::tdnr, datcl::pfnr, datcl::adnr;

void datcl::inDB(paramcl& pm,const int& aktc)
{
			systemrueck("dcmdump '"+name+"' 2>/dev/null",pm.obverb,pm.oblog,&ir);
			string erg[dim];
			gibaus=0;
			int fehltzahl=dim;
			for(size_t zl=0;zl<ir.size();zl++) {
				for(unsigned j=0;j<dim;j++) {
					if (ord[j].empty()) {
						if (ir[zl].find(knz[j])!=string::npos) {
							size_t p1=ir[zl].find('[');
							if (p1!=string::npos) {
								size_t p2=ir[zl].find(']',p1);
								if (p2!=string::npos) {
									string roh=ir[zl].substr(p1+1,p2-p1-1);
									if (j==tdnr) if ((p1=roh.find('\\'))!=string::npos) roh.erase(p1);
									if ((p1=roh.find('\''))!=string::npos) roh.erase(p1);
									if ((p1=roh.find('\"'))!=string::npos) roh.erase(p1);
									if (j==itnr) if ((p1=roh.rfind('\\'))!=string::npos) roh.erase(0,p1+1); // ImageType
									if (j==adnr) if ((p1=roh.rfind('.'))!=string::npos) roh.erase(p1); // AcquisitionDateTime
									if (j==pnnr) ersetzAlle(&roh,"^",","); // PatientName
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
			RS rins(pm.My);
			vector<instyp> einf;
			for(unsigned j=0;j<dim;j++) {
				if (j==pnnr || j==pfnr) {
					char vor=0; //// (j==pnnr?0:1);
					for(unsigned jj=0;jj<ord[j].length();jj++) {
						if (vor&&vor!=','&&vor!='-') ord[j][jj]=tolower(ord[j][jj]);
						vor=ord[j][jj];
					}
				}
			}
			einf.push_back(instyp(pm.My->DBS,"PatientName",&ord[pnnr]));
			struct tm tmg={0};
			strptime(ord[1].c_str(),"%Y%m%d",&tmg);
			einf.push_back(instyp(pm.My->DBS,"Geburtsdatum",&tmg));
			einf.push_back(instyp(pm.My->DBS,"PatientID",&ord[2]));
			einf.push_back(instyp(pm.My->DBS,"Geschlecht",&ord[3]));
			einf.push_back(instyp(pm.My->DBS,"Bildtyp",&ord[itnr]));
			einf.push_back(instyp(pm.My->DBS,"ReferringPhysicianName",&ord[rpnr]));
			einf.push_back(instyp(pm.My->DBS,"PerformingPhysicianName",&ord[6]));
			einf.push_back(instyp(pm.My->DBS,"TransducerData",&ord[tdnr]));
			einf.push_back(instyp(pm.My->DBS,"ProcessingFunction",&ord[8]));
			struct tm tma={0};
			strptime(ord[adnr].c_str(),"%Y%m%d%H%M%S",&tma);
			einf.push_back(instyp(pm.My->DBS,"Aufnahmedatum",&tma));
			ord[adnr].insert(8,"_");
			svec eindfeld;
			eindfeld<<"PatientName";
			eindfeld<<"Geburtsdatum";
			eindfeld<<"PatientID";
			eindfeld<<"Aufnahmedatum";
			int ZDB=0;
			rins.tbins(tbn,einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,&id,/*eindeutig=*/0,eindfeld);
			Log("ID: '"+violetts+id+schwarz+"'",pm.obverb,pm.oblog);
} // void datcl::inDB(paramcl& pm., const int& aktc)


datcl::datcl(string& name): name(name)
{
}

void datcl::aufPlatte(paramcl& pm,const int& aktc,const size_t& nr)
{
			for(unsigned j=0;j<dim;j++) {
				if (j!=itnr && j!=rpnr) {
					bname+=ord[j];
					if (j<dim-1) bname+='_';
				} // 			if (j!=itnr && j!=rpnr)
			} // 		for(int j=0;j<dim;j++)
			if (id.empty()) {
				Log(rots+bname+schwarz+" schon da!",pm.obverb,pm.oblog);
			} else {
				string neuname=pm.zvz+"/"+bname+".png";
				systemrueck("dcmj2pnm +on2 '"+name+"' > '"+neuname+"'",pm.obverb,pm.oblog);
				struct stat nst={0};
				if (!lstat(neuname.c_str(),&nst)) {
					struct tm tm={0};
					strptime(ord[adnr].c_str(),"%Y%m%d%H%M%S",&tm);
					tm.tm_isdst=-1;
					time_t modz=mktime(&tm);
					struct utimbuf ub={0};
					ub.modtime=modz;
					ub.actime=modz;
					if (utime(neuname.c_str(),&ub)) {
						Log(rots+"Fehler beim Datumsetzen von '"+blau+neuname+schwarz,pm.obverb,pm.oblog);
					}
					systemrueck("chown sturm:praxis '"+neuname+"'",pm.obverb,pm.oblog);
					const string jahr=ord[adnr].substr(0,4);
					string cmd="cp -a '"+neuname+"' '"+pm.z2vz+"/"+jahr+"/'";
					systemrueck(cmd,pm.obverb,pm.oblog);
				} else {
					RS weg(pm.My,"DELETE FROM `"+tbn+"` WHERE ID="+id,aktc,ZDB);
				}
				//		systemrueck("touch -r '"+rueck[nr]+"' '"+neuname+"'",pm.obverb,pm.oblog); // = zu spaet
				if (gibaus)
					Log(bname,pm.obverb,pm.oblog);
				Log("Nr: "+blaus+ltoan(nr)+schwarz+", "+blau+name+schwarz+" "+blau+(ir.size()?ir[0]:"")+schwarz,pm.obverb,pm.oblog);
			}
}

// Musterfunktion, die von einer Funktion in gesonderter,fakultativer Datei,z.B. 'vgb.cpp' ueberschrieben werden kann
void paramcl::VorgbSpeziell() 
{
	Log(violetts+Tx[T_VorgbSpeziell]+schwarz);
	setzbenutzer(&duser);
	qvz="/var/spool/dicomneu";
	avz="/var/spool/dicomalt";
	zvz="/var/spool/dicomziel";
	z2vz="/var/spool/dicomziel2";
} // void paramcl::VorgbSpeziell() 

void paramcl::verschieb()
{
		time_t jetzt;
		time(&jetzt);
		struct tm *jtp;
		jtp=localtime(&jetzt);
		char zbuf[16];
		strftime(zbuf,16,"%Y%m%d_%H%M%S",jtp);
		const string nvz=avz+vtz+zbuf;
		pruefverz(nvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1);
		const string cmd="mv -n '"+qvz+vtz+"'* '"+nvz+vtz+"'";
		systemrueck(cmd,obverb,oblog);
		ret=0;
} // void paramcl::verschieb()

int main(int argc, char** argv)
{
	paramcl pm(argc,argv); // Programmparameter
	pm.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
	pm.obverb=1;
	pm.oblog=0;
	linst_cl linst(pm.obverb,pm.oblog);
	pm.linstp=&linst;
	pm.VorgbSpeziell();//die Vorgaben, die in einer zusaetzlichen Datei mit einer weiteren Funktion "void paramcl::VorgbSpeziell()" ueberladbar sind
	const int aktc=0;
	linstp=&linst;
	//	pruefverz(zvz,obverb,0,1,1,"sturm","sturm");
	if (pm.initDB())
		return 10;
	if (!pm.My) exit(5); // Datenbankverbindung nicht erstellbar
	pm.pruefdictab(aktc);
	svec rueck;
	systemrueck("find "+pm.qvz+" -type f -not -path '*\\.*' -not -path '*DICOMDIR*'",pm.obverb,pm.oblog,&rueck);
	if (!rueck.size()) {
	 Log(rots+"Keine Dateien in '"+blau+pm.qvz+rot+"' gefunden!",1,0);
	 pm.ret=1;
	} else {
		for(size_t nr=0;nr<rueck.size();nr++) {
			datcl dat(rueck[nr]);
			dat.inDB(pm,aktc);
			dat.aufPlatte(pm,aktc,nr);
		} // 	for(size_t nr=0;nr<rueck.size();nr++)
		pm.verschieb();
	} // 	if (!rueck.size())
	return pm.ret;
} // int main(int argc, char** argv)
