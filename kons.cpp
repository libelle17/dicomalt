#include "kons.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/statvfs.h> // fuer statfs
#include <sys/stat.h>
#include <utime.h>
#include <sys/sendfile.h> // fuer sendfile64
//#include <typeinfo>
#define caus cout // nur zum Debuggen

#ifdef _WIN32
const char *dir = "dir ";
#elif linux
const char *dir = "ls -l ";
#endif
const char *tmmoegl[2]={"%d.%m.%y","%c"}; // Moeglichkeiten fuer strptime

#ifdef linux
#include <iomanip> // setprecision
const char *schwarz="\e[0m", *dgrau="\e[1;30m", *drot="\e[0;31m", *rot="\e[1;31m", *gruen="\e[0;32m", *hgruen="\e[1;32m",
      *braun="\e[0;33m",   *gelb="\e[1;33m",     *dblau="\e[0;34;1;47m",  *blau="\e[1;34m", *violett="\e[0;35m", *hviolett="\e[1;35m",
      *tuerkis="\e[0;36m", *htuerkis="\e[1;36m", *hgrau="\e[0;37m", *weiss="\e[1;37m", *umgek="\e[7m";
const char *_drot=drot, *_rot=rot, *_schwarz=schwarz, *_blau=blau, *_gelb=gelb, *_tuerkis=tuerkis, *_hgrau=hgrau;
#define _access access
#include <sys/time.h>  // für gettimeofday()
#elif defined _WIN32
const char *drot="", *rot="", *schwarz="", *blau="", *gelb="", *tuerkis="", *hgrau="";
printf(drot, unter windows escape-Sequenzen rausfielselen und durch SetConsoleTextAttribute-Aufrufe ersetzen)
  template <class _Elem, class _Traits>
  std::basic_ostream<_Elem,_Traits>& operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c){
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout,c.m_color);
    return i;
  }
#endif

// z.B. "/root/autofax"
const string& instvz=
#include "instvz" // wird in Makefile erstellt
;
uchar findv=3; // find-Version 1=system, 2=intern mit readdir, 3=intern mit nftw
const string& unindt=instvz+"/uninstallinv"; // # Name muss identisch sein mit Variabler UNF in install.sh
const string nix;
const string eins="1";
el2set::iterator it2;
set<elem3>::iterator it3;

cuscl::cuscl()
{
 cuid=getuid();
 passwd=getpwuid(cuid);
 cgid=passwd->pw_gid;
 cusstr=passwd->pw_name;
} // cuscl::cuscl()
cuscl cus;
const string sudc=(cus.cuid?"sudo ":nix);
const string sudhc=(cus.cuid?"sudo -H ":nix);

const char *kons_T[T_konsMAX+1][SprachZahl]=
{
  // T_pfad,
  {"pfad","path"},
  // T_kuerze_logdatei,
  {", kuerze logdatei: ",", shorten log file: "},
  // T_Logdatei,
  {"Logdatei ","Log file "},
  // T_gibt_es_noch_nicht_Kuerze_sie_daher_nicht,
  {" gibt es noch nicht. Kuerze sie daher nicht."," does not exist yet. Not shortening it therefore."},
  // T_Kann_Datei
  {"Kann Datei '","Cannot open file '"},
  //T_nicht_als_fstream_zum_Schreiben_oeffnen
  {"' nicht als fstream zum Schreiben oeffnen.","' as fstream for writing."},
  // T_nicht_als_fstream_zum_Lesen_oeffnen
  {"' nicht als fstream zum Lesen oeffnen.","' as fstream for reading."},
  // T_nicht_mit_fopen_zum_Schreiben_oeffnen 
  {"' nicht mit fopen zum Schreiben oeffnen.","' with fopen for writing."},
  // T_nicht_mit_fopen_zum_Lesen_oeffnen 
  {"' nicht mit fopen zum Lesen oeffnen.","' with fopen for reading."},
  // T_Variable_logdatei_leer
  {"Variable 'logdatei' leer!","Variable 'logdatei' empty!"},
	// T_Variable_logdatei_Verzeichnis
	{"'logdatei' ist Verzeichnis!","'logdatei' is a directory!"},
  // T_nicht_als_fstream_zum_Anhaengen_oeffnen
  {"' nicht als fstream zum Anhaengen oeffnen.","' as fstream for appending."},
	// T_nicht_mit_open_zum_Anhaengen_oeffnen
  {"' nicht mit open() zum Anhaengen oeffnen.","' with open() for appending."},
  // T_nicht_mit_fopen_zum_Anhaengen_oeffnen
  {"' nicht mit fopen zum Anhaengen oeffnen: ","' with fopen for appending."},
  // T_Bitte_mit
  {"Bitte mit '","Please exit with '"},
  // T_beenden
  {"' beenden ...","'"},
  // T_stern_zeile
  {"*zeile: ","*line: "},
  // T_Rueckmeldung
  {"Rueckmeldung: ","Feedback: "},
  // T_Suchbefehl
  {"Suchbefehl","Search command"},
  // T_Fuehre_aus
  {"Fuehre aus","Executing"},
  // T_fehlgeschlagen_bei
  {"fehlgeschlagen bei: ","failed at: "},
  // T_Fuehrte_aus
  {"Fuehrte aus","Executed "},
  // T_komma_Ergebnis
  {", Ergebnis: ",", result: "},
  // T_kein_Verzeichnis_nochmal
  {"' kein Verzeichnis, nochmal: ","' not a directory, once again: "},
  // T_nicht_gefunden_soll_ich_es_erstellen
  {"' nicht gefunden, soll ich es erstellen (","' not found, shall I create it ("},
  // T_Fehlender_Parameter_string_zu
  {"Fehlender Parameter <string> zu -","Missing Parameter <string> after -"},
  // T_oder
  {" oder --"," or --"},
  // T_Fehler_Parameter
  {"Fehler: Parameter -","Error: Stated Parameter -"},
  // T_ohne_gueltigen
  {"ohne gueltigen","without valid"},
  // T_mit_Datei_als
  {"mit Datei als","with file as"},
  // T_mit_falschem
  {"mit falschem","with wrong"},
  // T_Pfad_angegeben
  {" Pfad angegeben!"," path!"},
  // T_Nicht_numerischer
  {"Nicht-numerischer","Not-numeric"},
  // T_Fehlender
  {"Fehlender","Missing"},
  // T_Parameter_nr_zu
  {" Parameter <nr> zu -"," Parameter <no> after -"},
  // T_Fehler
  {"Fehler ","Error "},
  // T_Erfolg
  {"Erfolg","Success"},
  // T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden
  {"Weder zypper noch apt-get noch dnf noch yum als Installationspgramm gefunden!",
   "Neither zypper nor apt-get nor dnf nor yum found as installation programme!"},
  // T_Logdateidpp
  {"Logdatei:","Log file:"},
  // T_Lese_Konfiguration_aus
  {"Lese Konfiguration aus '","Reading configuration from '"},
  // T_j_k,
  {"j","y"},
  // T_Fehler_bei_auswert
  {"Fehler bei auwert(): ","Error at evaluate(): "},
  // T_nicht_gefunden
  {" nicht gefunden"," not found"},
  // T_Muss_Datei
  {"Muss Datei '","File '"},
  // T_fuer
  {"' fuer '","' must be made accessible for '"},
  // T_zugreifbar_machen
  {"' zugreifbar machen.","'"},
  // T_spruef_sname
  {"spruef(), sname: ","sprove(), sname: "},
  // T_lief_schon
  {" lief schon."," ran already."},
  // T_nicht_gefunden_versuche_ihn_einzurichten
  {" nicht gefunden, versuche ihn einzurichten"," not found, trying to install it"},
  // T_Aktiviere_Dienst
  {"Aktiviere Dienst: ","Activating service: "},
  // T_Program
  {"Programm '","Program '"},
  // T_laeuft_schon_einmal_Breche_ab
  {"' laeuft schon einmal. Breche ab.","' is running already once. Aborting."},
  // T_Wert
  {" Wert: "," Value: "},
  // T_Dauer
  {" Dauer: "," Duration: "},
  // T_Dienst
  {"Dienst ","Service "},
  // T_geladen
  {" geladen"," loaded"},
	// 	T_ermoeglicht
	{" ermoeglicht"," enabled"},
	// T_nicht_ermoeglicht
	{" nicht ermoeglicht"," not enabled"},
  // T_nicht_geladen
  {" nicht geladen"," not loaded"},
  // T_am
  {"' am ","' on "},
  // T_als_Dienst_eingerichtet_von
  {", als Dienst eingerichtet von '",", installed as service by '"},
  // T_Versuch
  {", Nr: ",", no.: "},
  // T_machfit
  {"machfit()","makefit()"},
  //   T_Loesche_Ausrufezeichen
  {"Loesche: ","Deleting: "},
  // T_Fehler_beim_Loeschen
  {"Fehler beim Loeschen","error deleting"},
  // T_nicht_geloescht_war_eh_nicht_mehr_da
  {" nicht geloescht, war eh nicht mehr da."," not deleted, was no more there."},
  // T_pruefpar
  {"pruefpar()","checkpar()"},
  // T_Konfiguration_fuer
  {"# Konfiguration fuer '","# Configuration for '"},
  // T_erstellt_automatisch_durch_dieses_am
  {"', erstellt automatisch durch dieses am: ","', generated automatically by itself at: "},
  // T_Fehler_bei_lstat
  {"Fehler_bei_lstat ","Error at lstat "},
  // T_Datum_nicht_gesetzt_bei
  {"Datum nicht gesetzt bei '","Date not set for '"},
  // T_Konnte_Datei
  {"Konnte Datei '","Could not open file '"},
  // T_nicht_zum_Lesen_oeffnen
  {"' nicht zum Lesen oeffen!","' for reading!"},
  // T_nicht_zum_Schreiben_oeffnen
  {"' nicht zum Schreiben oeffnen!","' for writing!"},
  // T_Zeilen
  {" Zeilen"," lines"},
	// T_oder_nicht
	{" oder nicht"," or not"},
	// T_nicht_einfuegbar
	{"nicht einfuegbar","not insertable"},
  // T_erneute_Eingabe
  {"erneute Eingabe","once more"},
	// T_obsvfeh
	{"obsvfeh()","ifsverr()"},
	// T_laeuft_jetzt
	{"laeuft jetzt","is running now"},
	// T_Dienst_inexistent
	{"Dienst inexistent","service not existant"},
	// T_Dienstdateiname_nicht_ermittelbar
	{"Dienstdateiname nicht ermittelbar","service file name not given"},
	// T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent
	{"Dienst laeuft noch, aber Dienstdatei inexistent","service still runs, but service file missing"},
	// T_Exec_Dateiname_nicht_ermittelbar
	{"Exec-Dateiname nicht ermittelbar","exec-file name not given"},
	// T_Exec_Datei_fehlt
	{"Exec-Datei fehlt","exec-file missing"},
	// T_activating
	{"'activating'","'activating'"},
	// T_Dienst_kann_gestartet_werden
	{"Dienst kann gestartet werden","service can be started"},
	// T_Sonstiges
	{"Sonstiges","other"},
	// T_Ergebnis_Dienst
	{"Ergebnis Dienst ","result service "},
	// T_Dienst_laeuft
	{"Dienst laeuft","service is running"},
	// T_Dienst_disabled
	{"Dienst 'disabled'","service disabled"},
	// T_stopdis_sname
	{"stopdis(), sname: ","stopdis(), sname: "},
	// T_enableggf
	{"enableggf()","enableifnecessary()"},
	// T_semodpruef
	{"semodpruef()","checksemod()"},
	// T_Exitcode
	{"Exitcode ","Exitcode "},
	// T_trenne
	{" trenne "," splitting "},
	// T_bei
	{" bei: "," at: "},
	// T_Konnte_regulaeren_Ausdruck_nicht_kompilieren
	{"Konnte regulären Ausdruck nicht kompilieren: ","Could not compile regular expression: "},
	// T_doinst
	{"doinst()","doinst()"},
	// T_Ins_Deinstallationsprogramm_wird_eingetragen
	{"Ins Deinstallationsprogramm wird eingetragen: ","Entered into the uninstall program: "},
	// T_fallsnichtda
	{", fallsnichtda: ",", ifnotthere: "},
	// T_ohneabh
	{" ohneabh: "," withoutdep: "},
	// T_Tiefe
	{", Tiefe: ",", depth: "},
	// T_Linkverzeichnis
	{"Linkverzeichnis: ","link directory: "},
  // T_Suche_in
	{"Suche in '","Seeking in '"},
  // T_nach
	{"' nach '","' for '"},
	// T_Typbit
	{"', Typbit: '","', typebit: '"},
	// T_Folge
	{"', Folge: '","', follow: '"},
	// T_noext
	{"', regnoext: '","', regnoext: '"},
	// T_Ergebnis
	{"', Ergebnis: ","', result: "},
	// T_Fehler_beim_Deferenzieren_von
	{"Fehler beim Dereferenzieren von: ","Error dereferencing: "},
	// T_Ende
	{"-Ende- ","-End- "},
	// T_startundenable
	{"startundenable()","startandenable()"},
  {"",""}
}; // const char *Txkonscl::TextC[T_konsMAX+1][SprachZahl]=

const int sfeh[]={ T_Dienst_laeuft,T_Dienst_inexistent, T_Dienst_disabled, T_Dienstdateiname_nicht_ermittelbar, T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent, T_Exec_Dateiname_nicht_ermittelbar, T_Exec_Datei_fehlt, T_activating, T_Dienst_kann_gestartet_werden, T_Sonstiges};


class TxB Txk((const char* const* const* const*)kons_T);


uchar nrzf=0; // nicht rueckzufragen, fuer Aufruf aus Cron

argcl::argcl(const int i,const char *const *const argv):argcs(argv[i])
{
  argcs=argv[i];
}

const string drots=drot, rots=rot, schwarzs=schwarz, blaus=blau, dblaus=dblau, gelbs=gelb, tuerkiss=tuerkis, violetts=violett, gruens=gruen;

perfcl::perfcl(const string& vvonwo): vonwo(vvonwo)
{
  zp0=zp1=clock(); 
  t0=time(NULL);
} // perfcl::perfcl(const string& vvonwo): vonwo(vvonwo)

void perfcl::ausgeb(const string& stelle,uchar obdauer)
{
  zp1alt=zp1;
  zp1=clock();
  t1=time(NULL);
  cout<<gruen;
  if (!vonwo.empty())
   cout<<vonwo<<Txk[T_Versuch]<<setw(4)<<++nr<<", "<<setw(22)<<stelle<<": ";
  cout<<Txk[T_Dauer]<<setprecision(7)<<setw(9)<<(long)(zp1-zp0)<<" clocks = "
    <<fixed<<(t1-t0)<<setprecision(0)<<" s, "
    "delta= "<<setprecision(7)<<setw(9)<<(long)(zp1-zp1alt)<<" clocks"<<fixed<<schwarz<<(obdauer?"\n":"\r");cout.flush();
} // void perfcl::ausgeb(const string& stelle)


void perfcl::ausgab1000(const string& stelle)
{
  zp1=clock();
  nr++;
  if (zp1-zp0>10000) {
    cout<<gruen<<vonwo<<" "<<stelle<<" "<<nr<<Txk[T_Dauer]<<setprecision(7)<<setw(9)<<(long)(zp1-zp0)<<" = "
      <<fixed<<((zp1-zp0)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s"<<endl;
    exit(102);
  }
} // void perfcl::ausgab1000(const string& stelle)

int perfcl::oberreicht(unsigned long sek)
{
 zp1=clock();
 return ((zp1-zp0)>(long)sek*CLOCKS_PER_SEC*0.1);
} // int perfcl::oberreicht(unsigned long sek)


string ersetzefuerdatei(const string& u) 
{
  static string ziel;
  ziel =u;
  ersetzAlle(&ziel,"*","");
  ersetzAlle(&ziel,":",".");
  return ziel;
} // string ersetzefuerdatei(const string& u) 

char* charersetze(char *u, char alt, char neu) 
{
  for(size_t i=0;i<strlen(u);i++)
    if (u[i]==alt) 
      u[i]=neu;
  return u;
} // charersetze(char *u, const char* alt, const char* neu)


string caseersetze(const string& u, const char* alt, const char* neu) 
{
  string erg;
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg=u;
  } else {
    for(char* p=(char*)u.c_str();p<(char*)u.c_str()+u.length();p++)  {
      char *pi = (char*)alt;
      int i=0,gleich=1;
      for(;*(pi+i);i++)
        if (tolower(*(pi+i))!=tolower(*(p+i)))
        {gleich=0;break;}
      if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
    }
  } //   if (alt[0]==0 || !strcmp(alt,neu)) else
  return erg;
} // ersetze(char *u, const char* alt, const char* neu)

string *loeschealleaus(string *u, const char* alt) 
{
  size_t len=strlen(alt);
  size_t pos;
  while ((pos=u->find(alt))!=string::npos) {
    u->erase(pos,len);
  }
  return u;
} // loeschealleaus(char *u, const char* alt, const char* neu)

string ersetzAllezu(const string& quelle, const string& alt, const string& neu) 
{
  if(!alt.empty()) {
    string zwi;
    zwi.reserve(quelle.length());
    size_t p0 = 0, pakt;
    while((pakt = quelle.find(alt, p0)) != string::npos) {
      zwi += quelle.substr(p0, pakt - p0);
      zwi += neu;
      pakt += alt.length();
      p0 = pakt;
    }
    zwi += quelle.substr(p0);
    return zwi;
  }
  return quelle;
} // string ersetzAllezu(string& quelle, const string& alt, const string& neu) 


void ersetzAlle(string& quelle, const string& alt, const string& neu) 
{
  if(!alt.empty()) {
    string zwi;
    zwi.reserve(quelle.length());
    size_t p0 = 0, pakt;
    while((pakt = quelle.find(alt, p0)) != string::npos) {
      zwi += quelle.substr(p0, pakt - p0);
      zwi += neu;
      pakt += alt.length();
      p0 = pakt;
    }
    zwi += quelle.substr(p0);
    quelle.swap(zwi); 
  }
} // void ersetzAlle(string& quelle, const string& alt, const string& neu) 


string ersetzAllezu(string *quelle, const char* alt, const char* neu) 
{
  if(*alt) {
    string zwi;
    zwi.reserve(quelle->length());
    size_t altlen = strlen(alt);
    size_t p0 = 0, pakt;
    while((pakt = quelle->find(alt, p0)) != string::npos) {
      zwi += quelle->substr(p0, pakt - p0);
      zwi += neu;
      pakt += altlen;
      p0 = pakt;
    }
    zwi += quelle->substr(p0);
    return zwi;
  }
  return *quelle;
} // string ersetzAllezu(string *quelle, const char* alt, const char* neu) 


string ersetzAllezu(const char *const quelle, const char* const alt, const char* const neu) 
{
  string erg;
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg=quelle;
  } else {
    for(char* p=(char*)quelle;p<quelle+strlen(quelle);p++)  {
      char *pi = (char*)alt;
      int i=0,gleich=1;
      for(;*(pi+i);i++)
        if (*(pi+i)!=*(p+i))
        {gleich=0;break;}
      if (gleich) {
			  erg+=neu;p+=i-1;
			} else {
        erg+=(*p);
      } // if (gleich) else
    } //     for(char* p=(char*)quelle;p<quelle+strlen(quelle);p++)
  } //   if (alt[0]==0 || !strcmp(alt,neu)) else
  return erg;
} // string ersetzAllezu(const char *quelle, const char* alt, const char* neu) 


void ersetzAlle(string *quelle, const char* const alt, const char* const neu) 
{
  if(*alt) {
    string zwi;
    zwi.reserve(quelle->length());
    size_t altlen = strlen(alt);
    size_t p0 = 0, pakt;
    while((pakt = quelle->find(alt, p0)) != string::npos) {
      zwi += quelle->substr(p0, pakt - p0);
      zwi += neu;
      pakt += altlen;
      p0 = pakt;
    }
    zwi += quelle->substr(p0);
    quelle->swap(zwi); 
  }
} // void ersetzAlle(string *quelle, const char* alt, const char* neu) 


void ersetzAlle(string *quelle, const string& alt, const string& neu) 
{
  if(!alt.empty()) {
    string zwi;
    zwi.reserve(quelle->length());
    size_t p0 = 0, pakt;
    while((pakt = quelle->find(alt, p0)) != string::npos) {
      zwi += quelle->substr(p0, pakt - p0);
      zwi += neu;
      pakt += alt.length();
      p0 = pakt;
    }
    zwi += quelle->substr(p0);
    quelle->swap(zwi); 
  }
} // void ersetzAlle(string *quelle, const string& alt, const string& neu) 


// ergibt die Zahl der Vorkommen von *was in *str
size_t zahlin(const string *str, const char* was) 
{
  size_t erg=0,pos=0;
  if (*was) {
    while ((pos=str->find(was,pos)+1)) {
      erg++;
    }
  }
  return erg;
} // size_t zahlin(string *str, const char* was) 


void chersetze(string str, string *wsRet, const string& from, const char to) 
{
  wsRet->clear();
  size_t start_pos = 0, pos;
  while((pos = str.find_first_of(from, start_pos)) != string::npos) {
    *wsRet += str.substr(start_pos, pos - start_pos);
    *wsRet += to;
    pos ++;
    start_pos = pos;
  }
  *wsRet += str.substr(start_pos);
} // void chersetze(string str, string *wsRet, const string& from, const char to) 


string ersetze(const char *const u, const char *const alt, const char *const neu) 
{
  string erg;
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg.append(u);
  } else {
    for(char* p=(char*)u;*p;p++)  {
      char *pi = (char*)alt;
      int i=0,gleich=1;
      for(;*(pi+i);i++)
        if (*(pi+i)!=*(p+i))
        {gleich=0;break;}
      if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
    }
  }
  return erg;
} // ersetze(char *u, const char* alt, const char* neu)

string *sersetze(string* src, string const& target, string const& repl) 
{
  if (target.length()) {
    if (src->length()) {
      size_t idx = 0;
      for (;;) {
        idx = src->find( target, idx);
        if (idx == string::npos)  break;
        src->replace( idx, target.length(), repl);
        idx += repl.length();
      } //       for (;;)
    } //     if (src->length())
  } // if (target.length())
  return src;
} // sersetze( string src, string const& target, string const& repl)

void getstammext(const string *const ganz, string *stamm, string *exten) 
{
  size_t posp = ganz->rfind('.');
  if (posp!=std::string::npos) {
    *exten=ganz->substr(posp+1);
    *stamm=ganz->substr(0,posp);
  } else {
    *exten=nix;
    *stamm=string(*ganz);
  } //   if (posp!=std::string::npos) else
} // void getstammext(string *ganz, string *stamm, string *exten) 

#if defined(__MINGW32__) || defined(_MSC_VER)
int getcols() 
{
  CONSOLE_SCREEN_BUFFER_INFO info; 
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
  return info.dwSize.X;
} // int getcols() 
#elif linux
int getcols() 
{
  winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
} // int getcols() 
#endif

string holsystemsprache(int obverb/*=0*/)
{
	schlArr cglangA; // Systemsprach-Konfiguration
	string ret;
	// OpenSuse, Fedora, Debian
	const char* const langdt[]={"/etc/sysconfig/language","/etc/locale.conf","/etc/default/locale","/etc/sysconfig/i18n"};
	const char* const langvr[]={"RC_LANG","LANG","LANG","LANG"};
	for (size_t lind=0;lind<sizeof langdt/sizeof *langdt;lind++) {
		struct stat langstat;
		if (!lstat(langdt[lind],&langstat)) {
			cglangA.init(1, langvr[lind]);
			confdat langcd(langdt[lind],&cglangA,obverb);
			if (!cglangA[0].wert.empty()) {
				ret= cglangA[0].wert[0];
				break;
			} // 			if (!cglangA[0].wert.empty())
		} //     if (!lstat(hylacdt.c_str(),&hstat))
	} // 	for(size_t lind=0;lind<langdt.size())
	return ret;
} // string holsystemsprache()


// Achtung: Wegen der Notwendigkeit der Existenz der Datei zum Aufruf von setfacl kann die Datei erstellt werden!
mdatei::mdatei(const string& name, ios_base::openmode modus/*=ios_base::in|ios_base::out*/,uchar faclbak/*=1*/,int obverb/*=0*/, int oblog/*=0*/)
{
  uchar mehralslesen=(modus&ios_base::out||modus&ios_base::app||modus&ios_base::trunc||modus&ios_base::app);
  for(int iru=0;iru<3;iru++) {
    open(name,modus);
    if (is_open()) {
      oboffen=1;
      break;
    } //     if (is_open())
		if (mehralslesen) {
			pruefverz(dir_name(name),obverb,oblog,1,0);
			if (!touch(name,obverb,oblog)) {
				setfaclggf(name,obverb,oblog,falsch,modus&ios::out||modus&ios::app?6:4,falsch,faclbak);
			} // if (!systemrueck(sudc+"test -f '"+name+"' || "+sudc+"touch '"+name+"'",obverb,oblog)) 
		} // 		if (mehralslesen)
	} // for(int iru=0;iru<3;iru++) 
} // mdatei::mdatei (const string& name, ios_base::openmode modus)


#ifdef falsch
#ifdef obfstream
fstream*
#else
FILE*
#endif
oeffne(const string& datei, uchar art, uchar* erfolg,int obverb/*=0*/, int oblog/*=0*/,uchar faclbak/*=1*/)
{
#ifdef obfstream	
	ios_base::openmode mode;
	switch (art) {
		case 0: mode=ios_base::in; break;
		case 1: mode=ios_base::out; break;
		case 2: mode=ios_base::out | ios_base::app; break;
		case 3: mode=ios_base::out; break; // text mode, default
	} // 	switch (art)
	fstream *sdat;
	for(int iru=0;iru<2;iru++) {
		sdat = new fstream(datei,mode);
		if (sdat) if (!sdat->is_open()) sdat=0;
		if (sdat) {
#else
			const char *mode;
			switch (art) {
				case 0: mode="r"; break;
				case 1: mode="w"; break;
				case 2: mode="a"; break;
				case 3: mode="wt"; break; // text mode, default
			} // 			switch (art)
			FILE *sdat;
			for(int iru=0;iru<2;iru++) {
				if ((sdat= fopen(datei.c_str(),mode))) {
#endif
					*erfolg=1;
					setfaclggf(datei,obverb,oblog,falsch,art?6:4,falsch,faclbak);
					break;
				} 
				if (!*erfolg) {
					int erg __attribute__((unused))=
					touch(datei,obverb,oblog);
				}
			} // oeffne
			return sdat;
		} // 		if (sdat)
#endif	


int kuerzelogdatei(const char* logdatei,int obverb)
{
#ifdef false
	uchar erfolg=0;
#endif

	char Zeile[256]; //Die maximale Zeilenlänge beträgt 255 Zeichen, weil ein String mit einer Null endet
	if (obverb>1) {
		cout<<"obverb: "<<(int)obverb<<Txk[T_kuerze_logdatei]<<drot<<logdatei<<schwarz<<endl;
	}
	struct stat stat={0};
	if (lstat(logdatei,&stat)){
		if (obverb>1) {
			cout<<Txk[T_Logdatei]<<drot<<logdatei<<schwarz<<Txk[T_gibt_es_noch_nicht_Kuerze_sie_daher_nicht]<<endl;
		}
		return 1;
	}
	if (obverb>1) {
		cout<<rot<<Txk[T_Logdateidpp]<<endl<<schwarz; 
		int erg __attribute__((unused))=system((string(dir) + "\"" + logdatei + "\"").c_str());
	}
	const string ofil=string(logdatei)+"tmp";
	int abhier=0;
	mdatei outfile(ofil,ios::out,0);
	if (!outfile.is_open()) {
		perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_als_fstream_zum_Schreiben_oeffnen]).c_str());
		return 1;
	}
	mdatei logf(logdatei,ios::in,0);
	if (!logf.is_open()) {
		perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+logdatei+Txk[T_nicht_als_fstream_zum_Lesen_oeffnen]).c_str());
		return 1;
	}
	while (logf.getline (Zeile, sizeof(Zeile))) {
#ifdef false
#ifdef obfstream	
		fstream *outfile=oeffne(ofil,2,&erfolg);
		if (!erfolg) {
			perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_als_fstream_zum_Schreiben_oeffnen]).c_str());
			return 1;
		}
		fstream *logf=oeffne(logdatei,0,&erfolg); //Die Zeilen dieser Datei sollen in einen Vektor geschrieben werden.
		if (!erfolg) {
			perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+logdatei+Txk[T_nicht_als_fstream_zum_Lesen_oeffnen]).c_str());
			return 1;
		}
		while (logf->getline (Zeile, sizeof(Zeile))) {
#else	
			FILE *outfile=oeffne(ofil,2,&erfolg);
			if (!erfolg) {
				perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_mit_fopen_zum_Schreiben_oeffnen]).c_str());
				return 1;
			}
			FILE *logf=oeffne(logdatei,0,&erfolg);
			if (!erfolg) {
				Log(string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+logdatei+Txk[T_nicht_mit_fopen_zum_Lesen_oeffnen],1,0);
				return 1;
			}
			while (fgets(Zeile, sizeof Zeile, logf)) {
#endif	
#endif	
				if (!abhier) {
					tm *atm = new tm; // int aktz;
					int verwertbar=0, index;
					for(unsigned j=0;j<2;j++) {
						if (verwertbar) {
							index = verwertbar-1;
							j=2;
						} else {
							index = j;
						}
						switch (index) {
							case 0: 
								if (sscanf(Zeile,"%2d.%2d.%2d %2d:%2d:%2d%*s",&atm->tm_mday,&atm->tm_mon,&atm->tm_year,&atm->tm_hour,&atm->tm_min,&atm->tm_sec)==6) {
									if (!verwertbar) {
										verwertbar=1;
										j=2;
									}
									atm->tm_mon--;
									atm->tm_year+=100; // 2000-1900
									atm->tm_isdst=-1; // sonst wird ab und zu eine Stunde abgezogen
								} else if (verwertbar) verwertbar=0;
								break;
							case 1:
								if (strptime(Zeile,"%a %b %d %T %Y", atm)) {
									if (!verwertbar) {
										verwertbar=2;
										j=2;
									} //                   if (!verwertbar)
								} else if (verwertbar) verwertbar=0;
						} //             switch (index)
					} //           for(unsigned j=0;j<2;j++)
					if (verwertbar) {
						time_t gesz=mktime(atm);
						time_t jetzt=time(0);
						long sekunden=(long)(jetzt-gesz);
						if (sekunden<1209600) {// jünger als zwei Wochen => behalten
							abhier=1;
						}
					} // if (sscanf(Zeile
					delete[] atm;
				} // (!abhier)
				if (abhier) {
					outfile<<Zeile<<endl;
				} //         if (abhier)
			} //         if (!abhier)
			outfile.close();
#ifdef false
#ifdef obfstream
			*outfile<<Zeile<<endl;
		} // 		while (logf->getline (Zeile, sizeof(Zeile)))
	} // 	while (logf.getline (Zeile, sizeof(Zeile)))
	logf->close();
	outfile->close();
#else
	fputs(Zeile,outfile);
} // (abhier)
} // while (fgets(Zeile
fclose(logf);
fclose(outfile);
#endif
#endif
if (abhier) {
	remove(logdatei);
	rename(ofil.c_str(),logdatei);
}else{
	remove(ofil.c_str());
} // if (abhier) else
return 0;
}	 // int kuerzelogdatei(const char* logdatei,int obverb)

// aufgerufen in Log, setzbemv, aschreib
string* loeschefarbenaus(string *zwi)
{
  loeschealleaus(zwi,schwarz);
  loeschealleaus(zwi,dgrau); 
  loeschealleaus(zwi,drot); 
  loeschealleaus(zwi,rot); 
  loeschealleaus(zwi,gruen); 
  loeschealleaus(zwi,hgruen); 
  loeschealleaus(zwi,braun); 
  loeschealleaus(zwi,gelb); 
  loeschealleaus(zwi,blau); 
  loeschealleaus(zwi,dblau); 
  loeschealleaus(zwi,violett); 
  loeschealleaus(zwi,hviolett); 
  loeschealleaus(zwi,tuerkis); 
  loeschealleaus(zwi,htuerkis); 
  loeschealleaus(zwi,hgrau); 
  loeschealleaus(zwi,weiss); 
  return zwi;
} // void loeschefarbenaus(string *zwi)

int Log(const short screen,const short file, const bool oberr,const short klobverb, const char *format, ...)
{
  int erg=0;
	if (screen||file) {
		va_list args;
		va_start(args,format);
//#define vagenau
#ifdef vagenau		
		va_list a2;
		va_copy(a2,args);
		auto groe=vsnprintf(0,0,format,a2)+1;
		char *buf=new char[groe];
#else
		int groe=256; 
		char buf[groe];
#endif
		vsnprintf(buf,groe,format,args);
		erg=Log(buf,1,1);
#ifdef vagenau		
		delete buf;
#endif
		va_end(args);
	} // 	if (screen||file)
	return erg;
} // int Log(const short screen,const short file, const bool oberr,const short klobverb, const char *format, ...)

int Log(const string& text, const short screen/*=1*/, const short file/*=1*/, const bool oberr/*=0*/, const short klobverb/*=0*/)
{
	static unsigned int cols=0;
	static bool letztesmaloZ;
	const bool naechstezeile=0;
#ifdef false
	uchar erfolg=0;
#endif  
  // screen=0 = schreibt nicht auf den Bildschirm, 1 = schreibt, -1 = schreibt ohne Zeilenwechsel, -2 = schreibt bleibend ohne Zeilenwechsel
  if (file || screen) {
    if (screen) {
      if (!cols) cols=getcols();
      cout<<text;
      if (letztesmaloZ && (cols>=text.length())) {
        cout<<string(cols-text.length(),' ');
      }	
      if (screen==-2); else if (screen==-1 && !naechstezeile) 
			  {cout<<"\r";cout.flush();} 
			else cout<<endl; 
      letztesmaloZ = (screen==-1);
    } // if (screen) 
    if (file) {
      if (!logdt || !*logdt|| !strcmp(logdt,"/")) {
        cerr<<rot<<Txk[T_Variable_logdatei_leer]<<schwarz<<endl;
			}
			struct stat logst={0};
			if (!lstat(logdt,&logst) && S_ISDIR(logst.st_mode)) {
        cerr<<rot<<Txk[T_Variable_logdatei_Verzeichnis]<<schwarz<<endl;
      } else {
        static bool erstaufruf=1;
        char tbuf[20];
        time_t jetzt=time(0);
        strftime(tbuf,sizeof tbuf,"%d.%m.%y %X: ",localtime(&jetzt));
        string zwi=tbuf+text; 
        loeschefarbenaus(&zwi);

        if (erstaufruf) {
          kuerzelogdatei(logdt,klobverb); // screen
          erstaufruf=0;
        }	  
        mdatei logf(logdt,ios::out|ios::app,0);
        if (!logf.is_open()) {
          perror((string("\nLog: ")+Txk[T_Kann_Datei]+logdt+Txk[T_nicht_mit_open_zum_Anhaengen_oeffnen]).c_str());
          return 1;
        } else {
          logf<<zwi<<endl; 
          logf.close();
        }
#ifdef false        
#ifdef obfstream
        fstream *logf=oeffne(logdt,2,&erfolg);
        if (!erfolg) {
          perror((string("\nLog: ")+Txk[T_Kann_Datei]+logdt+Txk[T_nicht_als_fstream_zum_Anhaengen_oeffnen]).c_str());
          return 1;
        } else {
          *logf<<zwi<<endl; 
          logf->close();
        }
#else	
        FILE *logf=oeffne(logdt,2,&erfolg);
        if (!erfolg) {
          cerr<<"\nLog: "<<Txk[T_Kann_Datei]<<logdt<<Txk[T_nicht_mit_fopen_zum_Anhaengen_oeffnen]<<strerror(errno)<<endl;
          return 1;
        } else {
          fputs((string(tbuf)+zwi).c_str(),logf);
          fputs("\n",logf);
          fclose(logf);
        } // if (!erolg) else
#endif
#endif

      } // if (!logdt || !*logdt) _gKLA_ _gKLZ_ else _gKLA_
      if (oberr) {
        // wenn cerr woanders hingeht als cout oder die Meldung gar nicht an screen gerichtet ist, hier ohne Berücks.v.screen==-1
        if (isatty(fileno(stdout))!=isatty(fileno(stderr)) || !screen) {
          cerr<<text<<endl; 
        }
        errno=0;
      } //       if (oberr)
    } // (file)
  } // if (file || screen) 
  return 0;
} // Log(string text)


#ifdef _MSC_VER
inline void wait () 
{
  cout<<Txk[T_Bitte_mit]<<_drot<<"return"<<_schwarz<<Txk[T_beenden];
  // Löscht etwaige Fehlerzustände, die das Einlesen verhindern könnten
  cin.clear();
  // (= ignoriert alle Zeichen die derzeit im Puffer sind)
  cin.ignore(cin.rdbuf()->in_avail());
  // Füge alle eingelesenen Zeichen in den Puffer bis ein Enter gedrückt wird
  // cin.get() liefert dann das erste Zeichen aus dem Puffer zurück, welches wir aber ignorieren (interessiert uns ja nicht)
  cin.get();
}  // inline void wait () 
#endif

// braucht nur 1/300 von FindStringInBuffer
long cmpmem( char* feld, const char* search, int len_feld) 
{
  long i=0;
  int j=-1;
  int len_search=strlen(search);
  for(; i<len_feld-len_search; feld++,i++){
    j=memcmp(feld, search, len_search);
    if (!j) 
      break;
  }
  return !j?i:-1;
}    // long cmpmem( char* feld, const char* search, int len_feld) // , int len_search


char* ltoan(long value, int base, uchar obtz, uchar minstel) 
{
  /**
   * C++ version 0.4 char* style "itoa":
   * Written by Lukás Chmela
   * Released under GPLv3.
   */
  const uchar resultlenge=30;
  static char result[resultlenge];
  // check that the base is valid
  if (base < 2 || base > 36) { *result = '\0'; return result; }

  char* ptr = result, *ptr1 = result, tmp_char;
  long tmp_value;

  uchar stelle=0,stellen=0;
  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    stellen++;
    if (obtz) if (value) if (++stelle==3) {*ptr++ ='.';stelle=0;stellen++;}
  } while ( value );
  while (stellen++<minstel && stellen<resultlenge) *ptr++ = ' ';

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  } //   while(ptr1 < ptr)
  return result;
} // ltoan(long value, char* result, int base)

char* ltoa_(long value, char* result, int base=10) 
{
  /**
   * C++ version 0.4 char* style "itoa":
   * Written by Lukás Chmela
   * Released under GPLv3.
   */
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; return result; }

  char* ptr = result, *ptr1 = result, tmp_char;
  long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
} // ltoa_(long value, char* result, int base)

double verszuzahl(const string vers)
{
 string vneu;
 uchar obkomma=0;
 for(size_t i=0;i<vers.size();i++) {
  if (strchr("0123456789",vers[i])) {
	 vneu+=vers[i];
	} else if (vers[i]=='.'||vers[i]==',') {
	 if (!obkomma) {
	  vneu+='.';
		obkomma=1;
	 } // 	 if (!obkomma)
	} //   if (strchr("0123456789",vers[i]))  else if ..
 } //  for(size_t i=0;i<vers.size();i++)
 if (vneu.empty()) return 0; else return atof(vneu.c_str());
} // double verstozahl(string vers)

// Programmversion, falls diese beim Programm mit " --version" abrufbar ist
double progvers(const string& prog,int obverb/*=0*/, int oblog/*=0*/)
{
	double vers=0;
	string pfad;
	if (obprogda(prog,obverb,oblog,&pfad)) {
		svec urueck;
		systemrueck(pfad+" --version",obverb,oblog,&urueck);
		if (urueck.size()) vers=verszuzahl(urueck[0].c_str());
	} // 	if (obprogda(prog,obverb,oblog,&pfad))
	return vers;
} // double progvers(string prog,int obverb, int oblog)

#ifdef notwendig
void kopierm(const string *quelle, const string *ziel)
{
  mdatei fileIn(quelle->c_str(),ios::in|ios::binary,0);
  mdatei fileOut(ziel->c_str(),ios::out | ios::trunc | ios::binary,0);
  fileOut<<fileIn.rdbuf();
} // void kopierm(const string *quelle, const string *ziel)
#endif

// von http://chris-sharpe.blogspot.de/2013/05/better-than-systemtouch.html
int touch(const string& pfad,int obverb/*=0*/,int oblog/*=0*/)
{
	struct stat tstat;
  int fehler=lstat(pfad.c_str(),&tstat);
	if (fehler) {
		int fd = open(pfad.c_str(), O_WRONLY|O_CREAT|O_NOCTTY|O_NONBLOCK, 0666);
		if (fd<0) { // Couldn't open that path.
			if (obverb) std::cerr<<__PRETTY_FUNCTION__<<": Couldn't open() path \""<<pfad<<"\"\n";
		} else {
			int rc = utimensat(AT_FDCWD, pfad.c_str(), nullptr, 0);
			if (rc) {
				if (obverb) std::cerr<<__PRETTY_FUNCTION__<<": Couldn't utimensat() path \""<<pfad<<"\"\n";
			} else {
			if (obverb||oblog) 
			  std::clog<<violett<<__PRETTY_FUNCTION__<<schwarz<<": erfolgreich fuer \""<<blau<<pfad<<schwarz<<"\"\n";
			 fehler=0;
			} // 			if (rc) else
		} // 		if (fd<0) else
		if (fehler)
			fehler=systemrueck(sudc+"touch '"+pfad+"'",obverb,oblog);
	} // 	if (fehler)
	return fehler;
} // int touch(const std::string& pfad,int obverb/*=0*/,int oblog/*=*/)


void aufSplit(vector<string> *tokens, const char* const text, char sep/*=' '*/,bool auchleer/*=1*/)
{
  aufSplit(tokens,string(text),sep,auchleer);
} // void aufSplit(vector<string> *tokens, const char *text, char sep/*=' '*/, bool auchler/*=1*/)

void aufSplit(vector<string> *tokens, const string& text, char sep/*=' '*/,bool auchleer/*=1*/)
{
	size_t start = 0, end = 0;
	tokens->clear();
	while ((end = text.find(sep, start)) != string::npos) {
		if (end!=start || auchleer) {
			tokens->push_back(text.substr(start,end-start));
		} // 		if (!akttok.empty() || auchleer)
		start = end + 1;
	} //   while ((end = text.find(sep, start)) != (int)string::npos)
	if (text.length() !=start || auchleer)
		tokens->push_back(text.substr(start));
} // void aufSplit(vector<string> *tokens, const string& text, char sep,bool auchleer/*=1*/)

void aufSplit(vector<string> *tokens, const string& text, char* sep, bool auchleer/*=1*/)
{
  const size_t len=strlen(sep);
  size_t start=0, end=0;
  tokens->clear();
  while ((end = text.find(sep, start)) != string::npos) {
		if (end!=start || auchleer) {
				tokens->push_back(text.substr(start,end-start));
		} // 		if (!akttok.empty() || auchleer)
    start=end+len;
  } //   while ((end = text.find(sep, start)) != (int)string::npos)
	if (text.length()!=start || auchleer)
		tokens->push_back(text.substr(start));
} // void aufSplit(vector<string> *tokens, const string& text, char* sep,bool auchleer/*=1*/)

void aufiSplit(vector<string> *tokens, const string& text, const char* sep,bool nichtmehrfach/*=1*/,int obverb/*=0*/,int oblog/*=0*/) 
{
	size_t start=0, end=0,len=strlen(sep),k=0,l2;
	char* usep = new char[len];
	if (obverb)
		::Log(string(Txk[T_trenne])+"'"+blaus+text+schwarz+"'"+Txk[T_bei]+"'"+blau+sep+schwarz+"':",obverb,oblog);
	strcpy(usep,sep);
	for (char *p=usep ; *p; ++p) *p = toupper(*p);
	string utext;
	transform(text.begin(),text.end(),std::back_inserter(utext),::toupper);
	tokens->clear();
	while (1) {
		end=utext.find(usep,start);
		if (end!=string::npos) l2=end-start; else l2=string::npos;
		if (end==string::npos || nichtmehrfach || l2) {
			tokens->push_back(text.substr(start,l2));
			if (obverb)	
				::Log(tuerkiss+" tok["+ltoan(k)+"]: "+tokens->at(k)+schwarz,obverb,oblog);
			k++;
			if (end==string::npos) {
				break;
			} // 		 if (end==string::npos)
		} // 	 if (l2==string::npos || nichtmehrfach || l2)
		start=end+len;
	} // 	while (1)
	delete usep;
} // void aufiSplit(vector<string> *tokens, const string& text, const char* sep,bool nichtmehrfach) 

// suche in einem String von hinten ohne Groß- und Klein-Unterscheidung
size_t irfind(const string& wo, const string& was)
{
	string wou, wasu;
	transform(wo.begin(),wo.end(),std::back_inserter(wou),::toupper);
	transform(was.begin(),was.end(),std::back_inserter(wasu),::toupper);
	return wou.rfind(wasu);
} // size_t irfind(const string& wo, const string& was)

// Anfuehrungszeichen weg
string* anfzweg(string& quel) {
	if (quel.length()>1) {
		if (quel[0]==quel[quel.length()-1] && strchr("\"'",quel[0])) {
			quel.erase(quel.length()-1,1);
			quel.erase(0,1);
		}
	} // 	if (quel.length()>1)
	return &quel;
} // string* anfzweg(

char ers(char roh)
{
 switch(roh) {
  case '|': return 'u';
  case '<': return '(';
  case '>': return ')';
  case ':': return ';';
  case '"': return '\'';
  case '\\': return '`';
  case '/': return '´';
  case '*': return '°';
  case '?': return '~';
	default: return roh;
 } //  switch(roh)
} // char ers(char roh)

void fuersamba(string& roh)
{
  transform(roh.begin(),roh.end(),roh.begin(),ers);
} // void fuersamba(string& roh)

lsysen lsyscl::getsys(int obverb/*=0*/,int oblog/*=0*/)
{
      if (sys==usys) {
        if (!systemrueck("cat /proc/version | grep SUSE",obverb-2,oblog)) return sus;
        if (!systemrueck("cat /proc/version | grep 'Ubuntu\\|ebian'",obverb-2,oblog)) return deb;
        if (!systemrueck("cat /proc/version | grep edora",obverb-2,oblog)) return fed;
      } //       if (sys==usys)
      return usys;
} // lsysen lsyscl::getsys(int obverb/*=0*/,int oblog/*=0*/)

string& lsyscl::getlib64(int obverb/*=0*/,int oblog/*=0*/)
{
	if (usr_lib64_vz.empty()){
		if (getsys()==deb) {
			usr_lib64_vz="/usr/lib/x86_64-linux-gnu";
		} else {
			usr_lib64_vz="/usr/lib64";
		} // 		if (getsys()==deb) else
	} // 	if (usr_lib64_vz.empty())
	return usr_lib64_vz;
} // string& lsyscl::getlib64(int obverb/*=0*/,int oblog/*=0*/)

class lsyscl lsys;


// erg=1: gibt es fuer den aktuellen Benutzer; erg=2: gibt es fuer root; erg=0: nicht gefunden
int obprogda(const string& prog,int obverb, int oblog, string *pfad/*=0*/)
{
  if (prog.empty())
	  return 0;
	const int maxz=8;
  for(int iru=0;iru<maxz;iru++) {
    struct stat fstat={0};
    string verz;
		if (prog[0]=='/') iru=maxz; // z.B. <instvz>/ocrv/bin/ocrmypdf
    switch (iru) {
      case 0: verz="/usr/local/bin/"; break;
      case 1: verz="/usr/bin/"; break;
      case 2: verz="/usr/local/sbin/"; break;
      case 3: verz="/usr/sbin/"; break;
      case 4: verz="/sbin/"; break;
      case 5: verz="/bin/"; break;
			case 6: verz="/usr/libexec/"; break;
			case 7: verz="/run/"; break;
      default: break;
    } //     switch (iru)
    verz+=prog;
    if (!lstat(verz.c_str(),&fstat)) {
      if (pfad) *pfad=verz;
      return 1;
    }
  } // for(int iru=0;iru<3;iru++) 
  svec rueck;
  if (!systemrueck("which "+prog+" 2>/dev/null",obverb,oblog,&rueck)) {
    if (pfad) *pfad=rueck[0];
    return 2;
  } // if (!systemrueck("which "+prog+" 2>/dev/null",obverb,oblog,&rueck))
	// wenn nicht root
  if (cus.cuid) {
    if (!systemrueck(sudc+"which \""+prog+"\" 2>/dev/null ||"+sudc+"env \"PATH=$PATH\" which \""+prog+"\" 2>/dev/null",obverb,oblog,&rueck)) {
      if (pfad) *pfad=rueck[0];
      return 3;
    }
	} // if (!cus.cuid)
  if (pfad) pfad->clear();
  return 0; 
} // string obprogda(string prog,int obverb, int oblog)

linst_cl::linst_cl(int obverb,int oblog)
{
// inhaltlich parallel getIPR() in install.sh
		if (obprogda("rpm",obverb-1,oblog)) {
			dev="devel";
			schau="rpm -q";
			udpr=sudc+"rpm -e --nodeps ";
			if (obprogda("zypper",obverb-1,oblog)) { // opensuse
				// heruntergeladene Dateien behalten
				ipr=zypper;
				instp=sudc+"zypper -n --gpg-auto-import-keys in ";
				instyp=instp+"-y -f ";
				upr=sudc+"zypper -n rm -u ";
				uypr=upr+"-y ";
				upd=sudc+"zypper patch";
				repos=sudc+"zypper lr | grep 'g++\\|devel_gcc'>/dev/null 2>&1 || "+
				      sudc+"zypper ar http://download.opensuse.org/repositories/devel:/gcc/`cat /etc/*-release |"
							"grep ^NAME= | cut -d'\"' -f2 | sed 's/ /_/'`_`cat /etc/*-release | grep ^VERSION_ID= | cut -d'\"' -f2`/devel:gcc.repo;";
				compil="gcc gcc-c++ gcc6-c++";
			} else { // dann fedora oder mageia
				if (obprogda("dnf",obverb-1,oblog)) {
					ipr=dnf;
					instp=sudc+"dnf install ";
					instyp=sudc+"dnf -y install ";
					upr=sudc+"dnf remove ";
					uypr=sudc+"dnf -y remove ";
					upd=sudc+"dnf update";
				} else if (obprogda("yum",obverb-1,oblog)) {
					ipr=yum;
					instp=sudc+"yum install ";
					instyp=sudc+"yum -y install ";
					upr=sudc+"yum remove ";
					uypr=sudc+"yum -y remove ";
					upd=sudc+"yum update";
				} else if (obprogda("urpmi.update",obverb-1,oblog)) {
					ipr=urp;
					instp="urpmi --auto ";
					instyp="urpmi --auto --force ";
					upr=sudc+"urpme ";
					uypr=sudc+"urpme --auto --force ";
					upd=sudc+"urpmi.update -a";
				} // 				if (obprogda("dnf",obverb-1,oblog))
				compil="make automake gcc-c++ kernel-devel";
			} // 			if (obprogda("zypper",obverb-1,oblog)) KLZ // opensuse
		} else if (obprogda("apt-get",obverb-1,oblog)) {
			// Repositories: Frage nach cdrom ausschalten
			// genauso in: configure
			// wenn cdrom-Zeile vorkommt, vor ftp.-debian-Zeile steht und www.debian.org erreichbar ist, dann alle cdrom-Zeilen hinten anhängen
			systemrueck(sudc+"sh -c \"S=/etc/apt/sources.list;F='^[^#]*cdrom:';grep -qm1 \\$F \\$S && "
			    "test 0\\$(sed -n '/^[^#]*ftp.*debian/{=;q}' \\$S) -gt 0\\$(sed -n '/'\\$F'/{=;q}' \\$S) && "
					"ping -qc 1 www.debian.org >/dev/null 2>&1 && sed -i.bak '/'\\$F'/{H;d};\\${p;x}' \\$S;true\"",obverb,oblog);
			// hier werden die Dateien vorgabemaessig behalten
			ipr=apt;
			schau="dpkg -s";
			instp=sudc+"apt-get install "; 
			instyp=sudc+"apt-get -y --force-yes --reinstall install "; 
			upr=sudc+"apt-get -f install;"+sudc+"apt-get --auto-remove purge ";
			udpr=sudc+"apt-get -f install;"+sudc+"dpkg -r --force-depends ";
			uypr=sudc+"apt-get -f install;"+sudc+"apt-get -y --auto-remove purge ";
			upd=sudc+"apt update;"+sudc+"apt upgrade;";
			compil="install build-essential linux-headers-`uname -r`";
			dev="dev";
		} else if (obprogda("pacman",obverb-1,oblog)) {
			ipr=pac;
			schau="pacman -Qi";
			instp=sudc+"pacman -S ";
			instyp=sudc+"pacman -S --noconfirm ";
			upr=sudc+"pacman -R -s ";
			udpr=sudc+"pacman -R -d -d ";
			uypr=sudc+"pacman -R -s --noconfirm "; 
			upd=sudc+"pacman -Syu";
			compil="gcc linux-headers-`uname -r`";
		} else {
			cerr<<Txk[T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden]<<endl;
		} // 		if (obprogda("rpm",obverb-1,oblog))
    svec qrueck;
		if (findv==1) {
			systemrueck("find /usr -maxdepth 1 -type d -name 'lib*'",obverb,oblog,&qrueck);
		} else findfile(&qrueck,findv,obverb,oblog,0,"/usr","lib[^/]*$",1,34,1);
		for(size_t iru=0;iru<qrueck.size();iru++) libs+=qrueck[iru]+" ";
} // linst_cl::linst_cl(int obverb,int oblog)

const string& absch::suche(const char* const sname)
{
	static const string nix;
  for (size_t i=0;i<av.size();i++) {
    if (av[i].name==sname) {
      return av[i].wert;
    }
  } //   for (size_t i=0;i<av.size();i++)
  return nix;
} // const string& absch::suche(const char* const sname)

const string& absch::suche(const string& sname)
{
  return suche(sname.c_str());
} // const string& absch::suche(const string& sname)

// Achtung: Wegen der Notwendigkeit zur Existenz der Datei zum Aufruf von setfacl kann die Datei erstellt werden!
int confdat::lies(const string& fname, int obverb)
{
  string zeile;
  if (fname.empty()) 
    return 2;
  mdatei f(fname,ios::in);
  if (f.is_open()) {
    if (obverb>0) cout<<"confdat::lies(fname...), fname: "<<blau<<fname<<schwarz<<endl;
    while (getline(f,zeile)) {
      zn<<zeile;
    }
    obgelesen=1;
		if (obverb>0) cout<<"confdat::lies fertig 0"<<endl;
    return 0;
  }
	if (obverb>0) cout<<"confdat::lies fertig 1"<<endl;
	return 1;
} // lies(const string& fname, int obverb)

void absch::clear()
{
 aname.clear();
 av.clear();
} // void absch::clear()


void confdat::Abschn_auswert(int obverb, char tz)
{
  absch abp;
  for(size_t i=0;i<zn.size();i++) {
    string *zeile=&zn[i];
    size_t pos=zeile->find('#');
    if (pos!=string::npos) zeile->erase(pos);
    gtrim(zeile);
    if (zeile->length()) {
      if (zeile->at(0)=='[' && zeile->at(zeile->length()-1)==']') {
        zeile->erase(zeile->length()-1);
        zeile->erase(0,1);
        if (/*!abp.aname.empty() && */abp.av.size()) {
           abschv.push_back(abp);
           abp.clear();
        }
        abp.aname=*zeile;
      } else {
        pos=zeile->find(tz);
        if (pos!=string::npos && pos>0) { 
          string name,wert;
          name=zeile->substr(0,pos);
          gtrim(&name);
          wert=zeile->substr(pos+1);
          gtrim(&wert);
          anfzweg(wert);
          abp.av.push_back(abSchl(name,wert));
        } //         if (pos!=string::npos && pos>0) 
      } //       if (zeile->at(0)=='[' && zeile->at(zeile->length()-1)==']') 
    } //     if (zeile->length()) 
  } //   for(size_t i=0;i<zn.size();i++) 
  if (!abp.aname.empty() && abp.av.size()) {
    abschv.push_back(abp);
  }
} // void confdat::Abschn_auswert(int obverb, char tz)

// aufgerufen in: confdat::confdat(const string& fname, schlArr *sA, int obverb, char tz):name(fname)
void confdat::auswert(schlArr *sA, int obverb, char tz)
{
  richtige=0;
  sA->reset();
  if (obgelesen) {
    string ibemerk;
    for(size_t i=0;i<zn.size();i++) {
      string *zeile=&zn[i];
      size_t pos=zeile->find('#');
      if (pos!=string::npos) {
        // wir nehmen an, die Kommentarzeile gehoert zum naechsten Parameter, wenn sie vorne beginnt
        if (!pos) {
        // Ueberschrift am Anfang  weglassen
          if (!richtige && zeile->find("onfigura")!=string::npos && zeile->find("automati")!=string::npos) {
          } else {
            if (!ibemerk.empty()) ibemerk+='\n';
            ibemerk+=zeile->substr(pos);
          } // if (!richtige ... else
        } // if (!pos)
        zeile->erase(pos);
      } // if (pos!=string::npos)
      ltrim(zeile);
      if (!zeile->empty()) {
        if (obverb>1) Log(Txk[T_stern_zeile]+*zeile,obverb);
        pos=zeile->find(tz);
        if (pos!=string::npos && pos>0) { 
          size_t ii=sA->zahl,gef;
          while( ii-- ) {
            gef=zeile->find((*sA)[ii].name);
            if (!gef) { // conf[ii].name muss am Zeilenanfang anfangen, sonst Fehler z.B.: number, faxnumber
              (*sA)[ii].gelesen=1;
              if (strchr((string(" ")+(char)9+tz).c_str(),zeile->at(gef+(*sA)[ii].name.length()))) {
                ++richtige;
                (*sA)[ii].wert=zeile->substr(pos+1);
                gtrim(&(*sA)[ii].wert); // Leerzeichen entfernen
                // Anfuehrungszeichen entfernen
                anfzweg((*sA)[ii].wert);
                (*sA)[ii].bemerk=ibemerk;
                ibemerk.clear();
              } // if (strchr((string(" ")+(char)9+tz).c_str(),gef+(*sA)[ii].name.length())) 
              break;
            } // if( !strcmp(sA[i].name.c_str(),zeile->c_str()) ) 
            if (!gef)
              Log(rots+Txk[T_Fehler_bei_auswert]+schwarz+(*sA)[ii].name+rot+Txk[T_nicht_gefunden],obverb+1);
          } // while( ii-- ) 
        } // if (pos!=string::npos && 1==sscanf(zeile->c_str(),scs.c_str(),zeile->c_str())) 
      } // if (!zeile->empty()) 
    } // for(size_t i=0;i<zn.size();i++) 
  } // if (obgelesen) 
} // void sAdat::auswert(cppSchluess *sA, size_t csize, int obverb, char tz)


confdat::confdat(const string& fname,int obverb):name(fname)
{
  if (!fname.empty())
  lies(fname,obverb);
} // confdat::confdat(const string& fname,int obverb):name(fname)

confdat::confdat(const string& fname, schlArr *sA, int obverb, char tz):name(fname)
{
  if (obverb>0) 
    cout<<violett<<Txk[T_Lese_Konfiguration_aus]<<blau<<fname<<violett<<"':"<<schwarz<<endl;
  if (!fname.empty()) {
    lies(fname,obverb);
    auswert(sA,obverb,tz);
  } //   if (!fname.empty())
} // confdat::confdat(const string& fname, schlArr *sA, int obverb, char tz):name(fname)


void schlArr::ausgeb()
{
  for(size_t i=0;i<zahl;i++) {
   cout<<"i: "<<gruen<<i<<schwarz<<" Name: "<<blau<<schl[i].name<<schwarz<<Txk[T_Wert]<<blau<<schl[i].wert<<schwarz<<endl;
  }
} // void schlArr::ausgeb()

void schlArr::reset()
{
  for(size_t i=0;i<zahl;i++) {
    schl[i].wert.clear();
    schl[i].gelesen=0;
  }
} // void schlArr::reset()

schlArr::schlArr()
{
 schl=0;
 zahl=0;
} // schlArr::schlArr()


void schlArr::neu(size_t vzahl)
{
 if (schl) delete[] schl;
 zahl=vzahl;
 schl=new cppSchluess[zahl];
} // void schlArr::neu(size_t vzahl)


void schlArr::init(vector<cppSchluess*> *sqlvp)
{
  if (schl) delete[] schl;
  zahl=sqlvp->size();
  schl = new cppSchluess[zahl];
  for(size_t sqli=0;sqli<zahl;sqli++) {
    schl[sqli].name=sqlvp->at(sqli)->name;
    schl[sqli].wert=sqlvp->at(sqli)->wert;
  }
} // void schlArr::init(vector<cppSchluess*> *sqlvp)


void schlArr::init(size_t vzahl, ...)
{
 va_list list;
 va_start(list,vzahl);
 zahl=vzahl;
 if (schl) delete[] schl;
 schl = new cppSchluess[zahl];
 for(size_t i=0;i<zahl;i++) {
  schl[i].name=va_arg(list,const char*);
 }
 va_end(list);
} // void schlArr::init(size_t vzahl, ...)

// das Setzen auch der Bemerkung wird bisher nicht benoetigt
int schlArr::setze(const string& name, const string& wert/*, const string& bem*/)
{
	for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
      schl[ind].wert=wert;
      return 0;
    } //     if (schl[ind].name==name)
  } //   for(size_t ind=0;ind<zahl;ind++)
  return 1;
} // int schlArr::setze(const string& name, const string& wert)
 
const string& schlArr::hole(const string& name)
{
  static const string nix;
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
      return schl[ind].wert;
    }
  } //   for(size_t ind=0;ind<zahl;ind++)
  return nix;
} // const string* schlArr::hole(const string& name)

void cppSchluess::hole (struct tm *tmp) {
	if (!wert.empty()) {
		for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++) {
			if (strptime(wert.c_str(), tmmoegl[im], tmp)) break;
		}
	} // 	if (!wert.empty())
} // void cppSchluess::hole (struct tm *tmp)

// wenn die bisherige Bemerkung in einer Sprache mit der zu setzenden identisch, also nicht zwischenzeitlich manuell geaendert, 
// dann in aktueller Sprache uebernehmen
// fertige wird nur aufgerufen aus optioncl::setzebem(
void schlArr::setzbemv(const string& name,TxB *TxBp,size_t Tind,uchar obfarbe,svec *fertige)
{
  string bemst; 
  svec bemv, *vp;
  if (fertige) {
    vp=fertige;
	} else {
	  Sprache altSpr=TxBp->lgn;
		for(int akts=0;akts<SprachZahl;akts++) {
			TxBp->lgn=(Sprache)akts;
			bemst=(*TxBp)[Tind];
			if (obfarbe) loeschefarbenaus(&bemst);
			bemv<<bemst;
		} //         for(int akts=0;akts<SprachZahl;akts++)
		TxBp->lgn=altSpr;
		vp=&bemv;
	} // if fertige else
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
     uchar gefunden=0;
     if (schl[ind].bemerk.empty())
       gefunden=1;
     else {
       const string bv=schl[ind].bemerk.substr(2);
       for(int aktsp=0;aktsp<SprachZahl;aktsp++) {
         if (bv==(*vp)[aktsp]) {
           gefunden=(aktsp!=TxBp->lgn); // wenn aktuelle Sprache, nichts tun
           break;
         } // if (bv==bemv[aktsp]) 
       } // for(int aktsp=0;aktsp<SprachZahl;aktsp++) 
     } // (schl[ind].bemerk.empty) else
     if (gefunden) {
      schl[ind].bemerk="# "+(*vp)[TxBp->lgn];
     }
    } //     if (schl[ind].name==name)
  } //   for(size_t ind=0;ind<zahl;ind++)
} // void schlArr::setzbemv(const string& name,const string& bem)


void schlArr::aschreib(mdatei *const f)
{
  for (size_t i = 0;i<zahl;i++) {
    if (!schl[i].bemerk.empty()) *f<<(schl[i].bemerk[0]=='#'?"":"# ")<<*loeschefarbenaus(&schl[i].bemerk)<<endl;
    *f<<schl[i].name<<" = \""<<schl[i].wert<<"\""<<endl;
  } //   for (size_t i = 0;i<zahl;i++)
} // void schlArr::aschreib(mdatei *f)

int schlArr::fschreib(const string& fname)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    aschreib(&f);
    return 0;
  } //   if (f.is_open())
  return 1;
} // int schlArr::fschreib(const string& fname)

schlArr::~schlArr()
{
  if (schl) delete[] schl;
}

int multischlschreib(const string& fname, schlArr *const *const mcnfApp, const size_t cszahl,const string& mpfad)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    if (!mpfad.empty()) {
      char buf[30];
      time_t jetzt=time(0);
      tm *ltm = localtime(&jetzt);
      strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", ltm);
      const string ueberschr=Txk[T_Konfiguration_fuer]+mpfad+Txk[T_erstellt_automatisch_durch_dieses_am]+buf;
      if (!ueberschr.empty()) f<<ueberschr<<endl;
    } //     if (!mpfad.empty())
    for (size_t j=0;j<cszahl;j++) {
     mcnfApp[j]->aschreib(&f);
    }
    return 0;
  } //   if (f.is_open())
  return 1;
} // int multischlschreib(const string& fname, schlArr **mcnfApp, size_t cszahl)

string XOR(const string& value, const string& key)
{
  string retval(value);
  short unsigned int klen=key.length(), vlen=value.length(), k=0, v;
  for(v=0;v<vlen;v++) {
    retval[v]=value[v]^key[k];
    k=(++k<klen?k:0);
  } //   for(v=0;v<vlen;v++)
  return retval;
} // string XOR(const string& value, const string& key)

int cppschreib(const string& fname, cppSchluess *conf, size_t csize)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    for (size_t i = 0;i<csize;i++) {
      f<<conf[i].name<<" = \""<<conf[i].wert<<"\""<<endl;
    } //     for (size_t i = 0;i<csize;i++)
    return 0;
  } //   if (f.is_open())
  return 1;
} // int cppschreib(const string& fname, cppSchluess *conf, size_t csize)


#ifdef notcpp
int Schschreib(const char *fname, Schluessel *conf, size_t csize)
{
#ifdef false
  uchar erfolg=0;
#endif
  mdatei f(fname,ios::out);
  if (!f.is_open()) { return 1; }
  for(size_t i=0;i<csize;i++) {
    f<<conf[i].key<<" = \""<<conf[i].val<<"\""<<endl;
  }
#ifdef false
#ifdef obfstream 
  fstream *f=oeffne(fname,3,&erfolg);
  if (!erfolg) return 1;
  for(size_t i=0;i<csize;i++) {
    *f<<conf[i].key<<" = \""<<conf[i].val<<"\""<<endl;
  }
#else
  FILE *f=oeffne(fname,3,&erfolg);
  if (!erfolg) return 1;
  for (size_t i = 0;i<csize;i++) {
    fprintf(f,"%s = \"%s\"\n",conf[i].key,conf[i].val);
  }
  fclose(f);
#endif
#endif	
  return 0;
} 
#endif

// Dateiname ohne Pfad
std::string base_name(const std::string& path)
{
  return path.substr(path.find_last_of("/\\",path.find_first_of("><")) + 1);
} // std::string base_name(std::string const & path)

// Pfadname einer Datei
std::string dir_name(const std::string& path)
{
  size_t letzt=path.find_last_of("/\\");
	if (letzt==string::npos) return "";
  return path.substr(0,letzt);
} // std::string dir_name(std::string const & path)

// soll fuer den Fall eines uebergebenen 'rueck'-Zeigers den Rueckgabewert der aufgerufenen Funktion zuruckliefern,
// ausser bei 'find', da die Zahl der Funde
// bei rueck==0 liefert es das Ergebnis der system(..)-Funktion zurueck
// obverb: 1 = Befehl anzeigen, 2 = auch Rueckgabezeilen anzeigen
// obergebnisanzeig: 1=falls Fehler und obverb>1, >1=falls Fehler
int systemrueck(const string& cmd, char obverb/*=0*/, int oblog/*=0*/, vector<string> *rueck/*=0*/, 
    int verbergen/*=0*/, int obergebnisanzeig/*wahr*/, const string& ueberschr/*=nix*/,vector<errmsgcl> *errm/*=0*/,uchar obincron/*=0*/)
{
// verbergen: 0 = nichts, 1= '2>/dev/null' anhaengen + true zurueckliefern, 2='>/dev/null 2>&1' anhaengen + Ergebnis zurueckliefern
  binaer ob0heissterfolg=wahr;
  uchar neurueck=0;
  uchar weiter=0;
  int erg=-111;
  string hcmd=cmd;
  uchar obfind=(cmd.substr(0,4)=="find" || cmd.substr(0,9)==sudc+"find");
  if (verbergen==1 || (obfind && (obverb<1 || cus.cuid))) {
    if (obverb<=1) 
      hcmd+=" 2>/dev/null; true";
  } else if (verbergen==2) {
    if (obverb<=1)
      hcmd+=" >/dev/null 2>&1";
  } //   if (verbergen==1 || (obfind && (obverb<1 || strcmp(curruser(),"root")))) else iff
	if (obincron) {
    vector<string> tok;
    aufSplit(&tok,hcmd);
		if (tok.size()>0) {
		 if (obprogda(tok[0],obverb,oblog,&hcmd)) {
			for(unsigned j=1;j<tok.size();j++) {
			 hcmd+=' ';
			 hcmd+=tok[j];
			} // 			for(unsigned j=1;j<tok.size();j++)
		 } // 		 if (obprogda(tok[0],obverb,oblog,&hcmd))
		} // 		if (tok.size()>0)
	} // 	if (obincron)
  string meld(Txk[T_Rueckmeldung]);
  string aktues;
  if (ueberschr.empty()) { 
    if (obfind) {
      aktues=Txk[T_Suchbefehl];
    } else {
      aktues=Txk[T_Fuehre_aus];
      weiter=1;
    } //     if (obfind)
  } else {
    aktues=ueberschr;
  } //   if (ueberschr.empty())
  Log(aktues+": "+blau+hcmd.substr(0,getcols()-7-aktues.length())+schwarz+" ...",obverb>0?-1:0,oblog);
  if (!rueck) if (obergebnisanzeig) {neurueck=1;rueck=new vector<string>;}
// #define systemrueckprofiler
#ifdef systemrueckprofiler
  perfcl prf("systemrueck");
#endif
  if (rueck) {
    if (FILE* pipe = popen(hcmd.c_str(), "r")) {
#ifdef systemrueckprofiler
      prf.ausgeb();
#endif
      while(1) {
#ifdef systemrueckprofiler
        prf.ausgab1000("in while");
#endif
        if (feof(pipe)) break;
        char buffer[1280];
				// hier braucht er lang, wenn das System langsam ist
        if (fgets(buffer, sizeof buffer, pipe)) { 
          size_t posi;
          if (buffer[posi=strlen(buffer)-1]==10) buffer[posi]=0;
          rueck->push_back(string(buffer));
        } // if(fgets(buffer, sizeof buffer, pipe) != NULL)
        if (feof(pipe)) break;
      } // while(1) 
#ifdef systemrueckprofiler
      prf.ausgab1000("nach while");
#endif
      if (obverb>1 || oblog || obergebnisanzeig) if (rueck->size()) {
        for(unsigned i=0;i<rueck->size();i++) {
#ifdef systemrueckprofiler
#endif
          meld=meld+"\n"+tuerkis+rueck->at(i)+schwarz;
        } //         for(unsigned i=0;i<rueck->size();i++)
      } //       if (obverb>1 || oblog || obergebnisanzeig) if (rueck->size())
#ifdef systemrueckprofiler
      Log(rots+"Rueck.size: "+ltoan(rueck->size())+", obergebnisanzeig: "+(obergebnisanzeig?"ja":"nein"),1,oblog);
      Log(hcmd,1,oblog);
			prf.ausgab1000("vor pclose");
#endif
			erg = pclose(pipe);
			if (obfind) {
        erg=rueck->size();
      } else 
			  erg/=256;
#ifdef systemrueckprofiler
      prf.ausgab1000("nach pclose");
#endif
    } else {
      perror((string("popen() ")+Txk[T_fehlgeschlagen_bei]+hcmd).c_str());
      erg=1;
    } //     if (FILE* pipe = popen(hcmd.c_str(), "r"))  else 
  } else {
    erg= system(hcmd.c_str());
  } // if (rueck) else
#ifdef systemrueckprofiler
  prf.ausgab1000("vor weiter");
#endif
	if (weiter) aktues=Txk[T_Fuehrte_aus];
	if (obverb>0 || oblog) {
		string ergebnis;
		if (errm) {
			for(size_t i=0;i<errm->size();i++) {
				if (erg==errm->at(i).errnr) {
					ergebnis=(erg?rots:gruens)+ltoan(erg)+": "+gruen+errm->at(i).msg;
					break;
				} // 				if (erg==errm->at(i).errnr)
			} // for(size_t i=0;i<errm->size();i++) 
		}  // if (errm)
		if (ergebnis.empty()) {
			if (obfind) {
				ergebnis=gruens+ltoan(erg)+blau+Txk[T_Zeilen];
			} else {
				if (ob0heissterfolg) {
					if (erg) {
						if (cmd.substr(0,6)=="rpm -q" || cmd.substr(0,7)=="dpkg -s" || 
						    cmd.substr(0,5)=="which" || cmd.substr(0,10)==sudc+"which" || cmd.substr(0,16)==sudc+"iptables -L" ||
								(cmd.find("grep")!=string::npos && cmd.find(" -q <("+sudc+"crontab -l")!=string::npos) ||
							  cmd.substr(0,7)=="test -f" || cmd.substr(0,12)==sudc+"test -f" ||
								cmd.substr(0,20)=="systemctl list-units" || cmd.substr(0,15)==sudc+"pdbedit -L" ||
                cmd.find("faxstat|grep")!=string::npos
								) {
							ergebnis=gruens+Txk[T_nicht_gefunden];
						} else if (cmd.substr(0,14)==sudc+"modprobe ") {
						  ergebnis=gruens+Txk[T_nicht_einfuegbar];
						} else {
							ergebnis=rots+Txk[T_Exitcode]+ltoan(erg);
						}
						if (obverb>=0) obergebnisanzeig=wahr;
						obverb++;
					} else {
						ergebnis=Txk[T_Erfolg];
					} // ob0heissterfolg else
				} else {
					ergebnis=ltoan(erg);
				} // 				if (ob0heissterfolg) else
			} // 			if (obfind) else
		} //     if (ergebnis.empty()
#ifdef systemrueckprofiler
    prf.ausgab1000("vor log");
#endif
    Log(aktues+": "+blau+hcmd+schwarz+Txk[T_komma_Ergebnis]+blau+ergebnis+schwarz,obverb>0?obverb:0,oblog);
  } // if (obverb>0 || oblog)
  if (obergebnisanzeig) if (rueck->size()) 
    Log(meld,obverb>1||(ob0heissterfolg && erg && obergebnisanzeig>1),oblog);
  if (neurueck) delete rueck;
  return erg; 
} // int systemrueck(const string& cmd, char obverb, int oblog, vector<string> *rueck, binaer ...

void pruefplatte()
{
  struct statvfs fp={0};
  const string platte="/";
  statvfs(platte.c_str(),&fp);   
  if (fp.f_bsize * fp.f_bfree < 100000) { // wenn weniger als 100 MB frei sind ...
    systemrueck(sudc+"pkill postdrop");
  }
} // pruefplatte

// ob das aktuelle Programm mehrfach laeuft
void pruefmehrfach(const string& wen,uchar obstumm/*=0*/)
{
  svec rueck;
	const string iwen=wen.empty()?base_name(meinpfad()):wen;
  systemrueck("ps -eo comm|grep '^"+iwen+"'",0,0,&rueck);
  if (rueck.size()>1) {
	  if (obstumm)
			exit(0);
		cout<<Txk[T_Program]<<blau<<iwen<<schwarz<<Txk[T_laeuft_schon_einmal_Breche_ab]<<endl;
    exit(98);
  } //   if (rueck.size()>1) {
} // void pruefmehrfach(char* ich)

int untersuser(string uname,__uid_t *uidp/*=0*/, __gid_t *gidp/*=0*/)
{
	struct passwd pwd;
	struct passwd *result;
	char *buf;
	ssize_t bufsize;
	int erg=1;
	if ((bufsize = sysconf(_SC_GETPW_R_SIZE_MAX))==-1) bufsize=16384;
	if ((buf = (char*)malloc(bufsize))) {
		getpwnam_r(uname.c_str(), &pwd, buf, bufsize, &result);
		if (result) {
			if (uidp) *uidp=pwd.pw_uid;
			//if (gidp) *gidp=pwd.pw_gid;
			if (gidp) {
			 *gidp=pwd.pw_gid;
			  int ngroups=20;
				gid_t *groups=0;
				for(uchar iru=0;iru<2;iru++) {
					groups=(gid_t*)malloc(ngroups*sizeof *groups);
					if (getgrouplist(uname.c_str(), pwd.pw_uid, groups, &ngroups)!=-1) break;
					free(groups);
				}
			  // die Gruppe mit der groessten Nummer verwenden	
        for(int iru=0;iru<ngroups;iru++) {
				  if (groups[iru]>*gidp) *gidp=groups[iru];
				}
				free(groups);
			}
		}	
		free(buf);
	} else {
		erg=1;
		perror("malloc");
	} // 	if ((buf = (char*)malloc(bufsize))) else 
	return erg;
} // int untersuser(string uname,__uid_t *uid/*=0*/, __gid_t *gid/*=0*/)


// <datei> kann auch Verzeichnis sein
// obunter = mit allen Unterverzeichnissen
// obimmer = immer setzen, sonst nur, falls mit getfacl fuer datei Berechtigung fehlt (wichtig fuer Unterverzeichnisse)
void setfaclggf(const string& datei,int obverb/*=0*/,int oblog/*=0*/,const binaer obunter,const int mod/*=4*/,uchar obimmer/*=0*/,
               uchar faclbak/*=1*/,const string& user/*=nix*/,uchar fake/*=0*/)
{
	int altobv=obverb;
	if (fake) obverb=2;
	uid_t cuid;
	gid_t cgid;
	string cuser;
	if (user.empty()) {
		cuser=cus.cusstr;
		cuid=cus.cuid;
		cgid=cus.cgid;
	} else {
		cuser=user;
		untersuser(cuser.c_str(),&cuid,&cgid);
	} // 	if (user.empty())
	// fuer root braucht's es ned
	if (cuid) {
		static int obsetfacl=obprogda("setfacl",obverb-1,0);
		if (obsetfacl) {
			string aktdat=datei;
			svec pfade;
			do {
				pfade<<aktdat;
				aktdat=dir_name(aktdat);
			} while (!aktdat.empty());
			for(ssize_t i=pfade.size()-1;i>-1;--i) {
				struct stat st={0};
				int ergmod=0;
				uchar obhier=obimmer;
				if (lstat(pfade[i].c_str(),&st)) 
					break;
				if (i) {
					if (!((st.st_mode&S_IXOTH)||((st.st_gid==cgid)&&(st.st_mode&S_IXGRP))||((st.st_uid==cuid)&&(st.st_mode&S_IXUSR)))) {
						// erteile Ausfuehr-Rechte fuer Verzeichnis, sonst geht darunter nichts
						ergmod=1;
					} // if (!((st.st_mode ...
				} else {
					if (((mod&1) &&
								(!((st.st_mode&S_IXOTH)||((st.st_gid==cgid)&&(st.st_mode&S_IXGRP))||((st.st_uid==cuid)&&(st.st_mode&S_IXUSR))))
							) || ((mod&2) &&
								(!((st.st_mode&S_IWOTH)||((st.st_gid==cgid)&&(st.st_mode&S_IWGRP))||((st.st_uid==cuid)&&(st.st_mode&S_IWUSR))))
								) || ((mod&4) &&
									(!((st.st_mode&S_IROTH)||((st.st_gid==cgid)&&(st.st_mode&S_IRGRP))||((st.st_uid==cuid)&&(st.st_mode&S_IRUSR))))
									) ) {
						ergmod=mod;
					} // if (((mod&1 ...
				} // if (i) else
				if (ergmod) {
					string modbuch;
					if (ergmod&4) modbuch+="r"; else modbuch+=" ";
					if (ergmod&2) modbuch+="w"; else modbuch+=" ";
					if (ergmod&1) modbuch+="x"; else modbuch+=" ";
					// bei hinfuehrenden Verzeichnissen fehlende Rechte immer ueberpruefen
					if (i||!obhier) {
						svec gstat;
						systemrueck("getfacl -e -t '"+pfade[i]+"' 2>/dev/null | grep 'user[ \t]*"+cuser+"[ \t]*"+modbuch+"'||:",obverb,oblog,&gstat);
						obhier = !gstat.size();// wenn keine Berechtigung gefunden => erstellen
					} //        if (i||!obhier)
					if (obhier) {
						if (obverb) systemrueck(sudc+"sh -c 'ls -ld \""+pfade[i]+"\"'",2,0);
						if (faclbak) {
							const string sich=base_name(pfade[i])+"."+base_name(meinpfad())+".perm";
							const string bef=sudc+"sh -c 'cd \""+dir_name(pfade[i])+"\";test -f \""+sich+"\"||getfacl -R \""+base_name(pfade[i])+"\">\""+sich+"\"'";
							systemrueck(bef,obverb,oblog);
							struct stat st={0};
							string para="setfacl --restore=\""+sich+"\"";
							if (lstat(sich.c_str(),&st) || !st.st_size) {
								para=string(sudc+"setfacl -")+(!i && obunter?"R":"")+"b \""+pfade[i]+"\"";
							}
							anfgg(unindt,sudc+"sh -c 'cd \""+dir_name(pfade[i])+"\";"+para+"'",bef,obverb,oblog);
						} // 					if (faclbak)
						const string cmd=string(sudc+"setfacl -")+(!i && obunter?"R":"")+"m 'u:"+cuser+":"+ltoan(ergmod)+"' '"+pfade[i]+"'";
						if (fake) Log(rots+cmd+schwarz,obverb,oblog);
						else systemrueck(cmd,obverb,oblog);
						if (obverb) systemrueck(sudc+"sh -c 'ls -ld \""+pfade[i]+"\"'",2,0);
					} //        if (obhier)
				} // 				if (ergmod)
			} // 			for(size_t i=pfade.size()-1;i>-1;--i)
		} // 			if (obsetfacl)
	} // 	if (cuid)
	if (fake) obverb=altobv;
} // int setfaclggf(const string& datei, const binaer obunter, const int mod, binaer obimmer,int obverb, int oblog)


// obmitfacl: 1= setzen, falls noetig, >1= immer setzen
// falls Benutzer root
int pruefverz(const string& verz,int obverb/*=0*/,int oblog/*=0*/, uchar obmitfacl/*=0*/,uchar obmitcon/*=0*/,
              const string& besitzer/*=nix*/, const string& benutzer/*=nix*/,const uchar obmachen/*=1*/)
{
	static int obselinux=-1;
	struct stat sverz={0};
	int fehlt=1;
	// wenn nicht root
	mode_t altmod=022;
	if(!besitzer.empty()){
		altmod=umask(0);
	} // 	if(!besitzer.empty())
	if (!verz.empty()) {
		if (!lstat(verz.c_str(), &sverz)) {
			if(S_ISDIR(sverz.st_mode)) {
				fehlt=0;
			} // 			if(S_ISDIR(sverz.st_mode))
		} //     if (!lstat(verz.c_str(), &sverz))
		if (obmachen) {
			if (fehlt) {
				string aktv=verz;
				svec stack;
				while (1) {
					if (aktv.empty()) break;
					if (!lstat(aktv.c_str(),&sverz)) break;
					stack<<aktv;
					aktv=dir_name(aktv);
				} // 			while (1)
				while(1) {
					if (!stack.size()) {
						fehlt=0;
						break;
					} // 				if (!stack.size())
					mode_t mod=S_IRWXU;
					if (!besitzer.empty()) mod=0777;
					if (mkdir(stack[stack.size()-1].c_str(),mod)) 
						break;
					stack.erase(stack.end());
				} // while(1)
			} // if (fehlt)
			if (fehlt) {
				string bef="mkdir -p '"+verz+"' 2>/dev/null||"+sudc+"mkdir -p '"+verz+"'";
				if (!besitzer.empty()) bef+="&&chmod 777 '"+verz+"' 2>/dev/null||"+sudc+"chmod 777 '"+verz+"'";
				fehlt=systemrueck(bef,obverb,oblog);
				if (unindt.find(verz)) // wenn der Anfang nicht identisch ist, also nicht das Verzeichnis von unindt geprueft werden soll
					anfgg(unindt,sudc+"rmdir '"+verz+"'",bef,obverb,oblog);
			} //     if (fehlt)
		} // obmachen
		if (!fehlt) {
			if (!besitzer.empty()) {
				uid_t uid;
				gid_t gid;
				untersuser(besitzer,&uid,&gid);
				chown(verz.c_str(),uid,gid);
				umask(altmod);
			} // 		if (!besitzer.empty())
			if (obmitfacl) {
				setfaclggf(verz,obverb,oblog, wahr, 7, (obmitfacl>1),1,benutzer);
			}
			if (obmitcon) {
				if (obselinux==-1) 
					obselinux=obprogda("sestatus",obverb,oblog);
				if (obselinux)
					systemrueck(sudc+"chcon -R -t samba_share_t '"+verz+"'",obverb,oblog);
			} // 		if (obmitcon)
		} // 		if (!fehlt)
	} // if (!verz.empty())
	return fehlt;
} // void pruefverz(const string& verz,int obverb,int oblog)


string aktprogverz()
{
  char pBuf[300];
#if defined(__MINGW32__) || defined(_MSC_VER)
  int bytes = GetModuleFileName(NULL, pBuf, sizeof pBuf);
  if(bytes == 0) pBuf[0]=0;
#elif linux
  char szTmp[32];
  sprintf(szTmp, "/proc/%d/exe", getpid());
  ssize_t bytes = MIN(readlink(szTmp, pBuf, sizeof pBuf), sizeof pBuf - 1);
  if(bytes >= 0) pBuf[bytes] = 0;
#endif
  return pBuf;
} // string aktprogverz()

char Tippbuchst(const string& frage, const string& moegl,const char *berkl[], const char* erlaubt, const char *vorgabe) 
{
  string input;
  if (!erlaubt) erlaubt=moegl.c_str();
  while(1) {
    cout<<blau<<frage<<schwarz<<" (";
    for(unsigned i=0;i<moegl.length();i++) {
      cout<<"'"<<drot<<moegl[i]<<schwarz<<"'";
      if (berkl) cout<<" = "<<blau<<berkl[i]<<schwarz;
      if (i<moegl.length()-1) cout<<", ";
    } //     for(unsigned i=0;i<moegl.length();i++)
    cout<<")"<<(!vorgabe?"":"['"+tuerkiss+vorgabe+schwarz+"']")<<"?: ";
    input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && vorgabe) {input=vorgabe;break;}
    if (input[0]) if (strchr(erlaubt,(int)input[0])) break;
  } //   while(1)
  return input[0];
} // char Tippbuchst(const string& frage, const string& moegl,const char *berkl[], const char* erlaubt, const char *vorgabe) 


// vorgabe fur vorgabe = T_j_k; alternativ='n'
uchar Tippob(const string& frage,const char *vorgabe) 
{
  char erg=Tippbuchst(frage, string(Txk[T_j_k])+"n",0,"jJyYoOsSnN",vorgabe);
  return (!!strchr("jyJYoOsS",(int)erg));
} // uchar Tippob(const string& frage,const char *vorgabe) 

// bisher nicht verwendet, 15.12.15
string Tippstrs(const char *frage, char* moegl[], char *vorgabe/*=0*/)
  // das letzte Element von moegl muss 0 sein
{
  string input;
  while(1) {
    char passt=0;
    cout<<blau<<frage<<schwarz<<" (";
    for(unsigned i=0;moegl[i];i++) {
      if (i) cout<<", ";
      cout<<"'"<<drot<<moegl[i]<<schwarz<<"'";
    }
    cout<<")"<<(vorgabe?"":"['"+tuerkiss+vorgabe+schwarz+"']")<<"?: ";
    input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && vorgabe) {input=vorgabe;break;}
    if (input[0]) {
      for(unsigned i=0;moegl[i];i++) {
        if (!strcmp(moegl[i],input.c_str())) {passt=1;break;}
      }
    } //     if (input[0])
    if (passt) break; 
  } //   while(1)
  return input;
} // Tippstrs

string Tippstrs(const char *frage, vector<string> *moegl, string *vorgabe/*=0*/)
{
  string input;
  while(1) {
    char passt=0;
    cout<<blau<<frage<<schwarz<<" (";
    for(unsigned i=0;i<moegl->size();i++) {
      if (i) cout<<",";
      cout<<drot<<moegl->at(i)<<schwarz;
    } //     for(unsigned i=0;i<moegl->size();i++)
    cout<<")"<<(vorgabe->empty()?"":"['"+tuerkiss+*vorgabe+schwarz+"']")<<"?: ";
		input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && !vorgabe->empty()) {input=*vorgabe;break;}
    if (input[0]) {
      for(unsigned i=0;i<moegl->size();i++) {
        if (moegl->at(i)==input) {passt=1;break;}
      }
    } //     if (input[0])
    if (passt) break; 
  } //   while(1)
  return input;
} // Tippstrs


string Tippzahl(const char *frage, const char *vorgabe) 
{
  string input;
  while(1) {
    cout<<blau<<frage<<schwarz<<(!vorgabe?"":" ["+tuerkiss+vorgabe+schwarz+"]")<<"? ";
    input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && vorgabe) {input=vorgabe;break;}
    if (isnumeric(input)) break;
  } //   while(1)
  return input;
} // Tippzahl

string Tippzahl(const char *frage, const string *vorgabe) 
{
  return Tippzahl(frage,(vorgabe?vorgabe->c_str():0)); 
}
string Tippzahl(const string& frage, const string *vorgabe)
{
 return Tippzahl(frage.c_str(),(vorgabe?vorgabe->c_str():0));
}
string Tippstr(const char *frage, const string *vorgabe) 
{
  return Tippstr(string(frage), vorgabe);
} // Tippstr

string Tippstr(const string& frage, const string *vorgabe) 
{
  string input;
  while(1) {
    cout<<blau<<frage<<schwarz<<(!vorgabe || vorgabe->empty()?"":" [\""+tuerkiss+*vorgabe+schwarz+"\"]")<<"? ";
    input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && vorgabe) {
     input=*vorgabe;
     break;
    } //     if (input.empty() && vorgabe)
    break;
  } //   while(1)
  return input;
} // Tippstr

string Tippverz(const char *frage,const string *vorgabe) 
{
  string input, vg2="n"; uchar fertig=0;
  while(1) {
    cout<<blau<<frage<<schwarz<<(!vorgabe || vorgabe->empty()?"":" [\""+tuerkiss+*vorgabe+schwarz+"\"]")<<"? ";
    input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && vorgabe) {input=*vorgabe;}
    struct stat st={0};
    while (1) {
      if (!lstat(input.c_str(), &st)) {
        if(S_ISDIR(st.st_mode)) {
          fertig=1;
          break;
        } else {
          cout<<"'"<<rot<<input<<schwarz<<Txk[T_kein_Verzeichnis_nochmal];
          break;
        } //         if(S_ISDIR(st.st_mode)) else
      } else {
        string inpi;
        cout<<" '"<<rot<<input<<schwarz<<Txk[T_nicht_gefunden_soll_ich_es_erstellen]<<drot<<Txk[T_j_k]<<schwarz;
        cout<<"/"<<drot<<"n"<<schwarz<<")(\""<<tuerkis<<vg2<<schwarz<<"\")?";
        getline(cin,inpi);
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
        if (inpi.empty()) {inpi=vg2;break;}
        if (strchr("jyJY",inpi[0])) {
          pruefverz(input,0,0,1,1);
        } else {
          break;
        } //         if (strchr("jyJY",inpi[0])) else
      } //       if (!lstat(input.c_str(), &st)) else
    } //     while (1)
    if (fertig) break;
  } //   while(1)
  return input;
} // Tippverz

uchar VerzeichnisGibts(const char* vname)
{
  DIR *verz;
  if ((verz=opendir(vname))){
    closedir(verz);
    return 1;
  } //   if ((verz=opendir(vname)))
  return 0;
} // VerzeichnisGibts

int optioncl::pruefpar(vector<argcl> *const argcvm , size_t *const akt, uchar *hilfe, Sprache lg) // 1 = das war der Parameter, 0 = nicht
// argcvm = Vektor der Kommandozeilenparameter
// *akt = Index auf aktuell zu untersuchenden
// *hilfe = Aussage, ob Hilfe aufgerufen werden muss
// vorangestellte "1" => opschreibp auf 0 setzen
// vorangestelltes "un" => bei binaeren Operatoren nicht
{
  uchar nichtspeichern=0;
  uchar gegenteil=0;
// wenn der Index noch im Bereich und der zugehoerige Kommandozeilenparameter noch nicht unter den Programmparametern gefunden wurde ...
  if (*akt<argcvm->size()) if (!argcvm->at(*akt).agef) {
    const char *acstr=argcvm->at(*akt).argcs;
    int aclen=strlen(acstr);
    if (aclen>1) {
      if (aclen>2 && acstr[0]=='-'&&acstr[1]=='-') {
        acstr+=2;
        aclen-=2;
        if (aclen>1 && *acstr=='1') {
         nichtspeichern=1; 
         acstr++;
         aclen--;
        }
        if (aclen>2 && acstr[0]=='n'&&acstr[1]=='o') {
         gegenteil=1;
         acstr+=2;
         aclen-=2;
        }
				if (langi) {
					Sprache altSpr=TxBp->lgn;
					for(int akts=0;akts<SprachZahl;akts++) {
						TxBp->lgn=(Sprache)akts;
						if (!strcmp(acstr,(*TxBp)[langi])) {
							argcvm->at(*akt).agef=1;
						}
					} //         for(int akts=0;akts<SprachZahl;akts++)
					TxBp->lgn=altSpr;
				}
      } else if (strchr("-/",acstr[0])) {
        acstr+=1;
        aclen-=1;
        if (aclen>1 && *acstr=='1') {
         nichtspeichern=1; 
         acstr++;
         aclen--;
        }
        if (aclen>2 && acstr[0]=='n'&&acstr[1]=='o') {
         gegenteil=1;
         acstr+=2;
         aclen-=2;
        }
				if (kurzi) {
					Sprache altSpr=TxBp->lgn;
					for(int akts=0;akts<SprachZahl;akts++) {
						TxBp->lgn=(Sprache)akts;
						if (!strcmp(acstr,(*TxBp)[kurzi])) {
							argcvm->at(*akt).agef=1;
						}
					} //         for(int akts=0;akts<SprachZahl;akts++)
					TxBp->lgn=altSpr;
				} // if (kurzi) else
      } //       if (strchr("-/",acstr[0])
    } // if (strlen(acstr)>1) 
    // wenn Kommandozeilenparameter gefunden ...
    if (argcvm->at(*akt).agef) {
      // ... und zu setzender binaerer Parameter hinterlegt ...
      if (pptr) {
        // ggf. auf Gegenteil korrigieren
        if (gegenteil) wert=!wert;
        // ... und dieser noch nicht richtig gesetzt ist ...
        if (*pptr!=wert) {
          // ... dann setzen ...
          *pptr=wert;
          // ... merken, dass die Konfigurationsdatei geschrieben werden muss ...
          if (!nichtspeichern) {
            if (obschreibp) *obschreibp=1;
            // ... und wenn ein Konfigurationsarray uebergeben wurde und ein Elementname dazu ...
            if (cpA && pname) {
              // ... dann diesen auch auf den Wert setzen
              cpA->setze(pname,ltoan(wert));
            } //             if (cpA && pname)
          } // if (!nichtspeichern)
        } // if (*pptr!=wert) 
        // wenn also kein binaerer Parameter hinterlegt (=> Textparameter)
      } else {
        const char *pstr=0;
        uchar wiefalsch=0;
        // und hinter dem aktuellen Parameter noch einer kommt ...
        if (*akt<argcvm->size()-1) {
          const char *nacstr=argcvm->at(*akt+1).argcs;
          struct stat entryarg={0};
          switch (art) {
              // und das ein "sonstiger Parameter" ist, ...
            case psons:
            // er also nicht mit '-' oder '/' anfaengt ...
              if (!strchr("-/",nacstr[0])) {
                // ... dann zuweisen
                pstr=nacstr;
              }
              break;
              // wenn es ein Verzeichnis oder eine Datei sein soll ...
            case pverz:
            case pfile:
              // ... die also nicht mit '-' anfaengt
              if (nacstr[0]!='-') {
                // ... und sie bestimmte existentielle Bedingungen erfuellt ...
                if (stat(nacstr,&entryarg)) wiefalsch=1;  // wenn inexistent
                else if ((art==pverz)^(S_ISDIR(entryarg.st_mode))) wiefalsch=2; // Datei fuer Verzeichnis o.u.
                // ... dann zuweisen
                else pstr=nacstr;
              } //               if (nacstr[0]!='-')
              break;
              // oder wenn es eine Zahl sein soll ...
            case pzahl:
            // und sie nicht mit '-' oder '/' anfaengt ...
              if (!strchr("-/",nacstr[0])) {
                // und tatsaechlich numerisch ist ...
                if (!isnumeric(nacstr)) wiefalsch=1;
                // dann zuweisen
                else pstr=nacstr;
              } // if (!strchr("-/",nacstr[0])) 
              break;
          } // switch (art) 
        } // if (*akt<argcvm->size()-1)
        /// wenn nacstr als Zusatzparameter bestaetigt
        if (pstr) {
          // ... und dessen Inhalt sich von zptr unterscheidet ...
          if (*zptr!=pstr) {
            // ... dann zuweisen ...
            *zptr=pstr; 
            // ... und ggf. Konfigurationsdatei speichern, 
            if (!nichtspeichern) {
              if (obschreibp) *obschreibp=1;
              // wenn Konfigurationsarray und ein Indexname dort uebergeben ... 
              if (cpA && pname) {
                // dann Inhalt dort zuweisen
                cpA->setze(pname,pstr);
              } // if (cpA && pname)
            } // if (!nichtspeichern)
          } // if (*zptr!=pstr) 
          argcvm->at(++(*akt)).agef=1;
        } else {
          // wenn kein Zusatzparameter erkennbar, dann melden
          switch (art) {
            case psons:
              Log(drots+Txk[T_Fehlender_Parameter_string_zu]+(*TxBp)[kurzi]+Txk[T_oder]+(*TxBp)[langi]+"!"+schwarz,1,1);
              break;
            case pverz:
            case pfile:
              Log(drots+Txk[T_Fehler_Parameter]+(*TxBp)[kurzi]+Txk[T_oder]+(*TxBp)[langi]+" "+(wiefalsch==1?Txk[T_ohne_gueltigen]:wiefalsch==2?
                    Txk[T_mit_Datei_als]:Txk[T_mit_falschem])+Txk[T_Pfad_angegeben]+schwarz,1,1);
              break;
            case pzahl:
              Log(drots+(wiefalsch==1?Txk[T_Nicht_numerischer]:Txk[T_Fehlender])+Txk[T_Parameter_nr_zu]
							     +(*TxBp)[kurzi]+Txk[T_oder]+(*TxBp)[langi]+"!"+schwarz,1,1);
              break;
          } // switch (art)
          if (!*hilfe) *hilfe=1;
        } // if (pstr) else
      } // if (pptr) else
      return 1;
    } // if (argcvm->at(*akt).agef)
  } // if (*akt<argcvm->size()) if (!argcvm->at(*akt).agef) 
  return 0;
} // pruefpar

string& optioncl::machbemerkung(Sprache lg,binaer obfarbe)
{
	static const string nix; // =""
	bemerkung.clear();
	if (TxBp) {
		if (Txi!=-1) {
			if (TxBp->TCp[Txi][lg]) {
				TCtp *hilf = reinterpret_cast<TCtp*>(TxBp->TCp);
				bemerkung= (const char*)hilf[Txi][lg];
				if (rottxt) bemerkung+=(obfarbe?blaus:nix)+*rottxt+(obfarbe?schwarz:nix);
				if (Txi2!=-1) bemerkung+=(const char*)hilf[Txi2][lg]; 
				if (zptr && bemerkung.find("assw")==string::npos) bemerkung+=" '"+(obfarbe?blaus:nix)+*zptr+(obfarbe?schwarz:nix)+"'";
				if (obno) bemerkung+=(obfarbe?violetts:nix)+Txk[T_oder_nicht]+(obfarbe?schwarz:nix);
			} // if (TxBp->TCp[Txi][lg])
		} // if (Txi!=-1)
	} // if (TxBp)
	return bemerkung;
} // string& optioncl::machbemerkung(Sprache lg,binaer obfarbe)

void optioncl::hilfezeile(Sprache lg)
{
  if (TxBp) {
    if (Txi!=-1) {
      if (TxBp->TCp[Txi][lg]) {
        cout<<drot<<" -"<<(*TxBp)[kurzi]<<", --"<<(*TxBp)[langi];
        if (zptr) {if (art==psons || art==pfile) cout<<" <string>"; else if (art==pverz) cout<<" <"<<Txk[T_pfad]<<">"; else cout<<" <zahl>";}
        cout<<schwarz<<": "<< machbemerkung(lg)<<endl;
      } // if (TxBp->TCp[Txi][lg])
    } // if (Txi!=-1)
  } // if (TxBp)
} // hilfezeile


string linst_cl::ersetzeprog(const string& prog) 
{
  switch(ipr) {
    case apt:
      if (prog=="mariadb") return "mariadb-server";
      if (prog=="hylafax") return "hylafax-server";
      if (prog=="hylafax+") return "hylafax+-server";
      if (prog=="hylafax hylafax-client") return "hylafax-server hylafax-client";
      if (prog=="hylafax+ hylafax+-client") return "hylafax+-server hylafax+-client";
      if (prog=="kernel-source") return "linux-source-$(uname -r|cut -d- -f1)";
      if (prog=="tiff") return "libtiff-tools";
      if (prog=="libxslt-tools") return "xsltproc";
      if (prog=="imagemagick") return "imagemagick imagemagick-doc";
      if (prog=="libreoffice-base") return "libreoffice-common libreoffice-base";
      if (prog=="libcapi20-2") return "libcapi20-dev";
      if (prog=="python-devel") return "python-dev";
      if (prog=="python3-devel") return "python3-dev";
      if (prog=="tesseract-ocr-traineddata-english") return "tesseract-ocr-eng";
      if (prog=="tesseract-ocr-traineddata-german") return "tesseract-ocr-deu";
      if (prog=="tesseract-ocr-traineddata-orientation_and_script_detection") return "tesseract-ocr-osd";
      if (prog=="libavformat-devel") return "libavformat-dev";
      if (prog=="poppler-tools") return "poppler-utils";
			if (prog=="libffi-devel") return "libffi-dev";
			if (prog=="boost-devel") return "libboost-dev";
      break;
    case dnf: case yum:
      if (prog=="mariadb") return "mariadb-server";
      if (prog=="kernel-source") return "kernel-devel-$(uname -r)";
      if (prog=="tiff") return "libtiff-tools";
      if (prog=="libcapi20-2") return "isdn4k-utils";
      if (prog=="libcapi20-3") return "";
      if (prog=="capiutils") return "";
      if (prog=="imagemagick") return "ImageMagick ImageMagick-doc";
      if (prog=="libxslt-tools") return "libxslt";
      if (prog=="libreoffice-base") return "libreoffice-filters libreoffice-langpack-de";
      if (prog=="tesseract-ocr") return "tesseract";
      if (prog=="tesseract-ocr-traineddata-english") return "";
      if (prog=="tesseract-ocr-traineddata-german") return "tesseract-langpack-deu tesseract-langpack-deu_frak";
      if (prog=="tesseract-ocr-traineddata-orientation_and_script_detection") return "tesseract-osd";
      if (prog=="poppler-tools") return "poppler-utils";
      if (prog=="libwbclient0") return "libwbclient";
      break;
	  case zypper:
		  if (prog=="redhat-rpm-config") return "";
			if (prog=="libffi-devel") return "libffi$(gcc --version|head -n1|sed \"s/.*) \\(.\\).\\(.\\).*/\\1\\2/\")-devel";
      if (prog=="kernel-source") return "kernel-devel";
			break;
		case pac:
			if (prog=="libwbclient0") return "libwbclient";
			break;
    default: break;
  } //   switch(linst.pruefipr())
  return prog;
} // string linst_cl::ersetzeprog(const string& prog) 

// wird aufgerufen in int linst_cl::doinst
std::string string_to_hex(const std::string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();
	string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i) {
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	} // 	for (size_t i = 0; i < len; ++i)
	return output;
} // std::string string_to_hex(const std::string& input)

// wird aufgerufen in: linst_cl::doinst
void linst_cl::ziehraus(svec srueck, string *ustringp)
{
	uchar obanf=0;
	// siehe ausricht in configure
	switch (ipr) {
		case dnf: case yum:
			// Folgendes sollte u.a. fuer Fedora gehen
			for(unsigned i=0;i<srueck.size();++i) {
				if (obanf==1) obanf=2;
				if (!srueck[i].find("Installed:")||!srueck[i].find("Installiert:")) obanf=1;
				if (!srueck[i].length()) obanf=0;
				if (obanf==2) {
					const string source=srueck[i].c_str();
					const size_t maxGroups=2;
					regex_t rCmp;
					regmatch_t groupArray[maxGroups];
					while(1) {
						// jeden zweiten String verwerfen = (das letzte [^ ]+ ohne die runden Klammern)
						// rm_eo = Ende des Fundes, rm_es = Beginn
						const string regex=string(".{")+ltoan(groupArray[0].rm_eo)+"}([^ ]+)[ ][^ ]+";
						groupArray[0].rm_eo=0;
						if (regcomp(&rCmp, regex.c_str(), REG_EXTENDED)) {
							Log(Txk[T_Konnte_regulaeren_Ausdruck_nicht_kompilieren]+blaus+regex+schwarz,1,1);
						} else if (regexec(&rCmp, source.c_str(), maxGroups, groupArray, groupArray[0].rm_eo) == 0) {
							string zudeinst;
							for (unsigned g=1;g<maxGroups;g++) {
								if (groupArray[g].rm_so == (signed)(size_t)-1)
									break;  // No more groups
								if (!zudeinst.empty()) zudeinst+=" ";
								zudeinst+=source.substr(groupArray[g].rm_so,groupArray[g].rm_eo-groupArray[g].rm_so);
							} // 									for (unsigned g=1;g<maxGroups;g++)
							*ustringp=" "+zudeinst+*ustringp;
						} else {
							break; // while(1)
						} //            if (regcomp(&rCmp, regex.c_str(), REG_EXTENDED)) else else
					} // while(1)
					regfree(&rCmp);
				} //            if (obanf==2)
			} //          for(unsigned i=0;i<srueck.size();++i;)
			break;
		case zypper:
			for(unsigned i=0;i<srueck.size();++i) {
				if (obanf==1) obanf=2;
				if (srueck[i].find("NEW package")!=string::npos ||
						srueck[i].find("NEUEN Pakete")!=string::npos ||
						srueck[i].find("reinstalled:")!=string::npos) obanf=1;
				if (!srueck[i].length()) obanf=0;
				if (obanf==2) {
					gtrim(&srueck[i]);
					*ustringp=" "+srueck[i]+*ustringp;
				} // 						if (obanf==2)
			} // 					for(unsigned i=0;i<srueck.size();++i)
			break;
			// Folgende Zeile fuer Debian gut
		case apt:
			for(unsigned i=0;i<srueck.size();++i) {
				if (obanf==1) obanf=2;
				if (srueck[i].find("NEW package")!=string::npos ||
						srueck[i].find("NEUEN Pakete")!=string::npos) obanf=1;
				if (obanf==2) {
					if (srueck[i][0]!=' ') obanf=0;
					else {
						gtrim(&srueck[i]);
						*ustringp=" "+srueck[i]+*ustringp;
					} // 					if (srueck[i][0]!=' ') obanf=0; else
				} // 						if (obanf==2)
			} // 					for(unsigned i=0;i<srueck.size();++i)
			break;
		default: break;
	} //      switch (linst.pruefipr())
} // void linst_cl::ziehraus(svec srueck, string *ustringp)

// Problem: bei obyes erscheint die Rueckfrage dem Benutzer nicht, statt dessen wartet das Programm
int linst_cl::doinst(const string& prog,int obverb/*=0*/,int oblog/*=0*/,const string& fallsnichtda/*=nix*/,uchar ohneabh/*=0*/)
{
	Log(violetts+Txk[T_doinst]+schwarz+" prog: "+violett+prog+schwarz+Txk[T_fallsnichtda]+violett+fallsnichtda+schwarz+Txk[T_ohneabh]+
	    violett+(ohneabh?"1":"0")+schwarz,obverb,oblog);
	int ret=2;
	// eprog kann auch von aussen vor Programmaufruf gesetzt werden
	if (eprog.empty()) eprog=ersetzeprog(prog);
	if (!fallsnichtda.empty()) {
		if (obprogda(fallsnichtda,obverb,oblog)) {
			eprog.clear();
			return 0;
		} //     if (obprogda(fallsnichtda,obverb,oblog))
	} // if (!fallsnichtda.empty()) 
	if (!eprog.empty()) {
		switch (ipr) {
			case zypper:
				if (obnmr) {
					obnmr=0;
					systemrueck(sudc+"zypper mr -k -all",obverb,oblog);
				} //         if (obnmr)
			default: break;
		} // switch (linst.pruefipr()) 
		const uchar obyes=1;
		svec srueck;
		const string bef=(obyes?instyp:instp)+eprog;
		if (!(ret=systemrueck(bef,obverb+1,oblog,&srueck))) {
			 string ustring; 
		  ziehraus(srueck,&ustring);

			// s. ausricht() in configure
			if (!pruefverz(instvz,obverb,oblog,1,0)) {
				mdatei uniff(instvz+"/inst.log",ios::app,0);
				if (uniff.is_open()) {
					uniff<<endl<<"Rueckmeldung zu: '"<<bef<<"':"<<endl;
					for(unsigned i=0;i<srueck.size();i++) {
						uniff<<srueck[i]<<endl;
					}
					uniff<<"ustring: '"<<ustring<<"'"<<endl;
					uniff<<"ustring: '"<<string_to_hex(ustring)<<"'"<<endl;
				} // 			if (uniff.is_open())
			} // 		  if (!pruefverz(instvz,obverb,oblog))
			size_t p1,p2;
			const char* const weg[7]={"libgcc","libselinux.","libselinux-utils","libselinux-python3","libsepol","libsemanage","libstdc++"};
			for(size_t wnr=0;wnr<sizeof weg/sizeof *weg;wnr++) {
				while ((p1=ustring.find(weg[wnr]))!=string::npos && (!p1||ustring[p1-1]==' ')) {
					p2=ustring.find_first_of(" \n",p1+1); //  auch string::npos
					ustring.erase(p1,p2-p1);
				} // 				while ((p1=ustring.find(weg[wnr]))!=string::npos && (!p1||ustring[p1-1]==' '))
			} // 			for(size_t wnr=0;wnr<sizeof weg/sizeof *weg;wnr++)
			if (!ustring.empty()) {
				Log(Txk[T_Ins_Deinstallationsprogramm_wird_eingetragen]+violetts+udpr+ustring+schwarz,obverb,oblog);
				anfgw(unindt,udpr,ustring,bef,obverb,oblog);
			} // 			if (!ustring.empty())



		} // 		if (!(ret=systemrueck((obyes?instyp:instp)+eprog,obverb+1,oblog)))
		eprog.clear();
	} // if (!eprog.empty()) 
	return ret;
} // uchar linst_cl::doinst(const string& prog,int obverb,int oblog) 

// fuege an, wenn noch nicht enthalten
// anfuegen nach wortweiser Pruefung, ob schon enthalten
void anfgw(const string& datei, const string& udpr, const string& inhalt, const string& comment, int obverb/*=0*/, int oblog/*=0*/)
{
	Log(violetts+"anfgw: '"+udpr+blau+inhalt+"'",obverb,oblog);
	svec wvec;
	uchar obda=0;
	aufSplit(&wvec,inhalt); 
	for(size_t wind=0;wind<wvec.size();wind++) {
		if (wvec[wind].length()) wvec[wind]=" "+wvec[wind];
	} // 	for(size_t wind=0;wind<wvec.size();wind++)
	mdatei uni0(datei,ios::in,0);
	if (uni0.is_open()) {
		string zeile;
		while (getline(uni0,zeile)) {
			obda=1;
			for(size_t wind=0;wind<wvec.size();wind++) {
				if (wvec[wind].length()) {
					if (zeile.find(wvec[wind])==string::npos) {
						obda=0;
						break;
					} else {
					}
				} else {
					obda=1;
				} // 				if (zeile.find(wvec[wind])==string::npos)
			} // 			for(size_t wind=0;wind<wvec.size();wind++)
			if (obda) break;
		} // 					while (getline(uni0,zeile))
	} // 				if (uni0.is_open())
	if (!obda) {
	 doanfg(datei,udpr+inhalt,comment);
	} // 			if (!obda)
} // void anfgggf(string datei, string inhalt)

// anfuegen nach gemeinsamer Pruefung, ob schon enthalten
void anfgg(const string& datei, const string& inhalt, const string& comment, int obverb/*=0*/, int oblog/*=0*/)
{
	Log(violetts+"anfgg: '"+inhalt+"'",obverb,oblog);
	uchar obda=0;
	mdatei uni0(datei,ios::in,0);
	if (uni0.is_open()) {
		string zeile;
		while (getline(uni0,zeile)) {
			if (zeile.find(inhalt)!=string::npos) {
				obda=1;
				break;
			} // if (zeile.find(inhalt)!=string::npos)
		} // 					while (getline(uni0,zeile))
	} // 				if (uni0.is_open())
	if (!obda) {
	 doanfg(datei,inhalt,comment);
	} // 			if (!obda)
} // void anfgggf(string datei, string inhalt)

void doanfg(const string& datei, const string& inhalt, const string& comment)
{
	mdatei uniff(datei,ios::app,0);
	if (uniff.is_open()) {
		// s. ausricht() in configure
		time_t rohz=time(0);
		struct tm *zeiti=localtime(&rohz);
		char buf[80];
		strftime(buf,sizeof buf,"%F %T",zeiti);
		uniff<<inhalt<<"\n# "<<comment<<"\nprintf \"(Inst: "<<buf<<"): $blau%s$reset\\n\" \""<<
			ersetzAllezu(inhalt,"\"","\\\"")<<"\""<<endl;
	} else {
		perror((string("\n")+Txk[T_Kann_Datei]+datei+Txk[T_nicht_mit_open_zum_Anhaengen_oeffnen]).c_str());
	} // 			if (uniff.is_open())
} // void doanfg(const string& datei, const string& inhalt, const string& comment)

int linst_cl::doggfinst(const string& prog,int obverb,int oblog,uchar ohneabh/*=0*/)
{
  if (!(eprog=ersetzeprog(prog)).empty()) {
    if (obfehlt(eprog,obverb,oblog)) {
      return doinst(prog,obverb,oblog,nix,ohneabh);
    }
    eprog.clear();
  } // if (!(eprog=ersetzeprog(prog)).empty()) 
  return 0;
} // uchar linst_cl::doggfinst(const string& prog,int obverb,int oblog)

int linst_cl::douninst(const string& prog,int obverb/*=0*/,int oblog/*=0*/,uchar obyes/*=1*/) 
{
	int ret=2;
	if (eprog.empty()) eprog=ersetzeprog(prog);
	if (!eprog.empty()) {
		ret=systemrueck((obyes?uypr:upr)+prog,obverb,oblog);
		eprog.clear();
	}
	return ret;
} // uchar linst_cl::douninst(const string& prog,int obverb,int oblog) 


int linst_cl::obfehlt(const string& prog,int obverb,int oblog)
{
  switch (ipr) {
    case zypper: case dnf: case yum: 
      return systemrueck("rpm -q "+prog+" 2>/dev/null",obverb,oblog);
    case apt:
      return systemrueck("dpkg -s "+ersetzeprog(prog)+" 2>/dev/null",obverb,oblog);
    default: break;
  }
  return 2;
} // uchar linst_cl::obfehlt(const string& prog,int obverb,int oblog)


string meinpfad() {
  char buff[PATH_MAX];
  buff[0]=0;
  ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
  }
  return string(buff);
} // meinpfad

string gethome()
{
 static string erg;
 if (erg.empty()) {
//   erg=getenv("HOME");
//   svec rue;
//	 systemrueck("getent passwd $(logname)|cut -d: -f6",0,0,&rue);
    size_t pos=instvz.rfind('/');
    if (pos>1&&pos!=string::npos) {
		  erg=instvz.substr(0,pos);
		} else {
		  erg=instvz; // sollte nicht vorkommen
		}
 } //  if (erg.empty())
 return erg;
} // string gethome()

servc::servc(const string& vsname,const string& vename,int obverb, int oblog): sname((vsname.empty()?vename:vsname)),ename(vename) 
{
  machfit(obverb,oblog);
} // servc::servc(const string& vsname,const string& vename,int obverb, int oblog): sname((vsname.empty()?vename:vsname)),ename(vename)

void servc::semodpruef(linst_cl *linstp,int obverb/*=0*/,int oblog/*=0*/)
{
  static uchar obse=2;
	Log(violetts+Txk[T_semodpruef]+schwarz+sname,obverb,oblog);
	string sepfad;
	if (obprogda("sestatus",obverb,oblog,&sepfad)) {
		if (obse==2) {
			obse=0;
			svec sr2;
			systemrueck("sestatus",obverb,oblog,&sr2);
			for(size_t j=0;j<sr2.size();j++) {
				if (!sr2[j].find("Current mode:"))
					if (sr2[j].find("enforcing")!=string::npos) {
						obse=1; 
						break;
					} // 				if (sr2[j].find("enforcing")!=string::npos)
			} //       for(size_t j=0;j<sr2.size();j++)
		} // 		if (obse==2)
		if (obse) {
			linstp->doinst("policycoreutils-python-utils",obverb+1,oblog,"audit2allow");
			// falls "Nothing to do" zurueckgemeldet wird, muesste (sudo) dnf -y reinstall p... aufgerufen werden fuer das Deinstallationsprogramm
			// => wird der perfekten Version vorbehalten
			systemrueck(sudc+"setenforce 0",obverb,oblog);
			restart(obverb,oblog);
			const string selocal=sname+"_selocal";
			systemrueck(sudc+"grep \""+ename+"\" /var/log/audit/audit.log | audit2allow -M "+selocal,obverb,oblog);
			systemrueck(sudc+"setenforce 1",obverb,oblog);
			struct stat sstat={0};
			const string mod=instvz+vtz+selocal+".pp";
			if (!lstat(mod.c_str(),&sstat)) {
				linstp->doinst("policycoreutils",obverb+1,oblog,"semodule");
				const string bef=sudc+"semodule -i \""+mod+"\"";
				systemrueck(bef,obverb,oblog);
				anfgg(unindt,sudc+"semodule -r \""+mod+"\"",bef,obverb,oblog);
			} // 					if (!lstat((instvz+vtz+selocal+".pp").c_str(),&sstat)
		}  // if (obse)
	} // 			if (obprogda("sestatus",obverb,oblog,&sepfad))
} // int servc::sepruef(int obverb,int oblog)


void servc::semanpruef(int obverb/*=0*/,int oblog/*=0*/,const string& mod/*="getty_t*/)
{
	string sepfad;
	if (ename.find("faxgetty")!=string::npos) {
		if (obprogda("sestatus",obverb,oblog,&sepfad)) {
		  const string bef=sudc+"semodule -l|grep permissive_"+mod+" >/dev/null||"+sudc+"semanage permissive -a "+mod;
			systemrueck(bef,obverb,oblog);
			anfgg(unindt,sudc+"semanage permissive -d "+mod,bef,obverb,oblog);
		} // 	if (obprogda("sestatus",obverb,oblog,&sepfad))
	} // 		if (ename.find("faxgetty")!=string::npos)
} // int servc::semanpruef(const string& mod/*="getty_t*/, int obverb/*=0*/,int oblog/*=0*/)

int servc::machfit(int obverb/*=0*/,int oblog/*=0*/, binaer nureinmal/*=falsch*/)
{
	Log(violetts+Txk[T_machfit]+schwarz+" sname: "+violett+sname+schwarz+" svfeh: "+blau+ltoan(svfeh)+schwarz, obverb,oblog);
	// ueberpruefen, ob in systemctl status service Datei nach ExecStart existiert
	for(int iru=0;iru<2;iru++) {
		obsvfeh(obverb,oblog);
		// wenn restart nicht gebraucht wird oder nichts bringt, also alles außer activating und nicht gestartet ...
		if (!svfeh||svfeh==1||svfeh==3||svfeh==4||svfeh==5||svfeh==6) {
			break;
		} else {
			restart(obverb,oblog);
			if (!svfeh) break;
		}
	} // for(int iru=0;iru<2;iru++) 
	if (!svfeh&&!obenabled)
		enableggf(obverb,oblog);
	Log(violetts+"Ende "+Txk[T_machfit]+schwarz+" sname: "+violett+sname+schwarz+" svfeh: "+blau+ltoan(svfeh)+schwarz, obverb,oblog);
	return !svfeh;
} // int servc::machfit(int obverb,int oblog)

// wird aufgerufen in: hservice_faxq_hfaxd, hservice_faxgetty, cservice
uchar servc::spruef(const string& sbez, uchar obfork, const string& parent, const string& sexec, const string& CondPath, const string& After, 
                    linst_cl *linstp,int obverb/*=0*/,int oblog/*=0*/, uchar mitstarten/*=1*/)
{
	Log(violetts+Txk[T_spruef_sname]+schwarz+sname,obverb,oblog);
	if (!obsvfeh(obverb-1,oblog)) {
		Log(("Service ")+blaus+sname+schwarz+Txk[T_lief_schon],obverb,oblog);
	} else {
		systemd="/etc/systemd/system/"+sname+".service";
		for(uchar iru=0;iru<2;iru++) {
			if (mitstarten && svfeh>5)
				restart(obverb,oblog); // svfeh wird hier auch gesetzt
			if (!svfeh) {
				Log(("Service ")+blaus+sname+schwarz+" "+Txk[T_laeuft_jetzt],obverb,oblog);
				break;
			} // 			if (!svfeh)
			Log(blaus+systemd+Txk[T_nicht_gefunden_versuche_ihn_einzurichten]+schwarz,1,0);
			mdatei syst(systemd,ios::out);
			if (syst.is_open()) {
				syst<<"[Unit]"<<endl;
				char buf[80];
				time_t jetzt = time(0);
				struct tm *tmp = localtime(&jetzt);
				strftime(buf, sizeof(buf), "%d.%m.%y %H:%M:%S", tmp);
				syst<<"Description="<<sbez<<Txk[T_als_Dienst_eingerichtet_von]<<parent<<Txk[T_am]<<buf<<endl;
				if (!CondPath.empty()) 
					syst<<"ConditionPathExists="<<CondPath<<endl;
				if (!After.empty())
					syst<<"After="<<After<<endl;
				syst<<endl;
				syst<<"[Service]"<<endl;
				if (obfork) 
					syst<<"Type=forking"<<endl;
				syst<<"User=root"<<endl;
				syst<<"Group=root"<<endl;
				syst<<"Restart=always"<<endl;
				syst<<"RestartSec=30"<<endl;
				syst<<"ExecStart="<<sexec<<endl;
				syst<<endl;
				syst<<"[Install]"<<endl;
				syst<<"WantedBy=multi-user.target "<<endl;
				syst.close();
				daemon_reload(obverb-1,oblog);
				anfgg(unindt,"N="+sname+";C=\""+sudc+"systemctl\";$C stop $N;$C disable $N;rm -r '"+systemd+"';$C daemon-reload;$C reset-failed;",systemd,
				        obverb,oblog);
				syst.close();
				restart(obverb-1,oblog);
				obsvfeh(obverb-1,oblog);
				semodpruef(linstp,obverb,oblog);
				semanpruef(obverb,oblog);
			} // if (syst.is_open()) 
		} // if (!svgibts || !obslaeuft(obverb,oblog)) 
	} // if (servicelaeuft) else
	if (!svfeh&&!obenabled) { 
		enableggf(obverb,oblog);
	} // 	if (!svfeh&&!obenabled)
	return !svfeh;
} // void servc::spruef() 

int servc::startbar()
{
 return !svfeh||svfeh==7||svfeh==8;
}

int servc::laeuft()
{
 return !svfeh||svfeh==4;
}

int servc::lief()
{
 return !svf0||svf0==4;
}

int servc::obsvfeh(int obverb/*=0*/,int oblog/*=0*/) // ob service einrichtungs fehler
	// svfeh=1: Dienst inexistent, 2: Dienst 'disabled' 3: Dienstdatei nicht ermittelbar, 4: Dienst laeuft noch, aber Dienstdatei inexistent
	// svfeh=5: Exe-Datei nicht ermittelbar, 6: Exe-Datei fehlt, 7: activating 8: Dienst kann gestartet werden, 9: Sonstiges
{
	Log(violetts+Txk[T_obsfveh]+schwarz+" sname: "+violett+sname+schwarz+", obverb: "+ltoan(obverb),obverb>0?obverb:0,oblog); // nicht die Loeschanzeige
	string sdatei;
	fehler=0;
	svfeh=-1;
	obenabled=1;
	for(int iru=0;iru<2;iru++) {
		svec statrueck;
		systemrueck("systemctl -n 0 status '"+sname+"'",obverb,oblog,&statrueck,1);
		for(size_t j=0;j<statrueck.size();j++) {
			const string *sp=&statrueck[j];
			if (sp->find("Loaded:")!=string::npos) {
				size_t p2=string::npos,p1=sp->find("("); if (p1!=string::npos) p2=sp->find(";",p1);
				if (p2==string::npos) if (sp->find("loaded")!=string::npos) p2=sp->find(")",p1);
				if (p2!=string::npos) {
					sdatei=sp->substr(p1+1,p2-p1-1);
					if (systemd.empty()) systemd=sdatei;
				}
				if (sp->find("disabled")!=string::npos) {
					obenabled=0;
				} else if (sp->find("not-found")!=string::npos) {
					svfeh=1;
				}
			} else if (sp->find("active (running)")!=string::npos) {
				svfeh=0;
				break;
			} else if (sp->find("activating")!=string::npos) {
			  svfeh=7;
			 // z.B.: Process: 10126 ExecStartPre=/usr/share/samba/update-apparmor-samba-profile (code=exited, status=0/SUCCESS)
			} else if (svfeh && (sp->find("code=exited")!=string::npos||sp->find("(exited)")!=string::npos)) {
				// z.B. Exe-Datei bricht ab
				// z.B.: 'Main PID: 17031 (code=exited, status=255)'
				// oder:
				//   Loaded: loaded (/etc/systemd/system/aout.service; disabled; vendor preset: disabled)
			  //   Active: activating (auto-restart) (Result: exit-code) since Thu 2017-02-16 15:08:33 CET; 1s ago
				//  Process: 24594 ExecStart=/root/a.aout (code=exited, status=203/EXEC)
			  // Main PID: 24594 (code=exited, status=203/EXEC)
				// 11.9.16: dann muss evtl. selinux angepasst werden
				size_t gpos=sp->rfind('=');
				if (gpos<sp->length()-1)
					fehler=atol(sp->substr(gpos+1).c_str());
				else 
					fehler=1;
			} // if (sp->find("exited")!=string::npos) 
		} //  									for(size_t j=0;j<statrueck.size();j++)
		if (svfeh==7&&!fehler) { // 16.2.17: nur noch bei activating ohne exited
			// Dienst existent, Dienstdatei bekannt und existent, Exe-Datei bekannt und existent, Dienst laeuft aber nicht
			perfcl prf(Txk[T_Aktiviere_Dienst]+sname);
			while (!prf.oberreicht(3)) {}
			if (obverb) prf.ausgeb();
		} else {
			break;
		} // 									if (!fehler)
	} // 	for(int iru=0;iru<2;iru++)
	if (svfeh) {
		if (sdatei.empty()) {
			svfeh=3; // Dienstdatei nicht ermittelbar
		} else {
			// Dienst existent, Dienstdatei bekannt
			struct stat svst={0};
			if ((svfeh=lstat(systemd.c_str(),&svst))) { 
				svfeh=4; // Dienst laeuft evtl. noch, aber Dienstdatei inexistent
			} else {
			  string execf;
				svec srueExe;
				if (systemd.find("init.d")!=string::npos) {
				  systemrueck(sudc+"cat '"+systemd+"'",obverb,oblog,&srueExe);
					if (srueExe.size()) {
					 // z.B.:  if ! start-stop-daemon --start --quiet --oknodo --exec /usr/sbin/smbd -- -D; then
					 for(size_t z=0;z<srueExe.size();z++) {
					  size_t p1=srueExe[z].find(" --exec ");
						if (p1!=string::npos) {
	           size_t p2=srueExe[z].find(" ",p1+8);
						 if (p2!=string::npos) {
							 execf=srueExe[z].substr(p1+8,p2-p1-8);
							 break;
						 } // 						 if (p2!=string::npos)
						} // 						if (p1!=string::npos)
					 } // 					 for(size_t z=0;z<srueExe.size();z++)
					} else {
						svfeh=4;// Dienst laeuft evtl. noch, aber Dienstdatei leer
					} // 					if (srueExe.size()) else
				} else {
					// Dienst existent, Dienstdatei bekannt und existent
					systemrueck(sudc+"cat '"+systemd+"'|grep ExecStart=|cut -d= -f2|cut -d' ' -f1",obverb,oblog,&srueExe);
					if (srueExe.size()) {
						execf=srueExe[0];
					} // 			if (!srueExe.size()) else
				} // 			  if (systemd.find("init.d")!=string::npos)
				if (execf.empty()) {
					svfeh=5; // Exec-Datei nicht ermittelbar
				} else {
					if (ename.empty()) ename=base_name(execf); // stimmt z.B. nicht bei /usr/lib/mysql/mysql-systemd-helper
					// Dienst existent, Dienstdatei bekannt und existent, Exe-Datei bekannt
					struct stat lst={0};
					if (lstat(execf.c_str(),&lst)) {
						svfeh=6; // Exec-Datei fehlt, hier auch: activating
					} else {// 				if (lstat(srueExe.c_str(),&lst))
						svfeh=8; // Sonstiges
					} // 						if (lstat(srueExe[0].c_str(),&lst)) else
				} // 				if (execf.empty())
			} // 			if ((svfeh=lstat(systemd.c_str(),&svst))) 
		} // if (sdatei.empty()) else
	} // if (svfeh)

	//	const int sfeh[]={ T_Dienst_laeuft,T_Dienst_inexistent, T_Dienst_disabled, T_Dienstdateiname_nicht_ermittelbar, T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent, T_Exec_Dateiname_nicht_ermittelbar, T_Exec_Datei_fehlt, T_activating, T_Dienst_kann_gestartet_werden, T_Sonstiges};
	Log(Txk[T_Ergebnis_Dienst]+blaus+sname+schwarz+": "+gruen+Txk[sfeh[svfeh]]+schwarz,/*akt*/obverb>0?obverb:0,oblog);
	//	Log(violetts+"Ende "+Txk[T_obsfveh]+schwarz+" sname: "+violett+sname+schwarz,obverb,oblog);
	if (svf0==-1) svf0=svfeh; // Einstellung nach der ersten Untersuchung
	return svfeh;
} // int servc::obsvfeh(int obverb,int oblog)

void servc::pkill(int obverb/*=0*/,int oblog/*=0*/)
{
	systemrueck((sudc+"pkill '")+ename+"'",obverb-1,oblog,0,1);
} // void servc::pkill(int obverb/*=0*/,int oblog/*=0*/)

int servc::restart(int obverb/*=0*/,int oblog/*=0*/)
{
	for(int i=0;i<2;i++) {
		uchar obbreak=0;
		daemon_reload(obverb,oblog);
		systemrueck(sudc+"systemctl restart '"+sname+"'",obverb,oblog,0,2);
		obsvfeh(obverb,oblog);
		switch (sfeh[svfeh]) {
			case T_Dienst_laeuft: 
			case T_Dienst_inexistent: 
			case T_Dienstdateiname_nicht_ermittelbar:
			case T_Exec_Dateiname_nicht_ermittelbar: 
			case T_Exec_Datei_fehlt:
			 obbreak=1; break;
			case T_Dienst_disabled: 
			case T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent: 
			case T_activating:
			case T_Dienst_kann_gestartet_werden:
			case T_Sonstiges:
			default: break;
		}
		if (obbreak) break;
    if (i) break;
    pkill(obverb,oblog);
  } //   for(int i=0;i<2;i++)
  return !svfeh;
} // int servc::restart(int obverb,int oblog)

void servc::start(int obverb/*=0*/,int oblog/*=0*/)
{
  systemrueck(sudc+"systemctl start '"+sname+"'",obverb,oblog,0,2);
} // int servc::start(int obverb,int oblog)

int servc::startundenable(int obverb/*=0*/,int oblog/*=0*/)
{
	Log(violetts+Txk[T_startundenable]+schwarzs+sname,obverb,oblog);
	start(obverb,oblog);
  enableggf(obverb,oblog);
  return !obsvfeh(obverb,oblog);
} // int servc::start(int obverb,int oblog)

void servc::stop(int obverb/*=0*/,int oblog/*=0*/,uchar mitpkill/*=0*/)
{
  systemrueck(sudc+"systemctl stop '"+sname+"'",obverb,oblog,0,2);
  if (mitpkill) {
    pkill(obverb,oblog);
  } //   if (mitpkill)
} // int servc::stop(int obverb,int oblog)

void servc::stopggf(int obverb/*=0*/,int oblog/*=0*/,uchar mitpkill/*=0*/)
{
 obsvfeh(obverb,oblog);
 if (!svfeh||svfeh==7) {
  stop(obverb,oblog,mitpkill);
 } //  if (!svfeh||svfeh==7)
} // void servc::stopggf(int obverb/*=0*/,int oblog/*=0*/,uchar mitpkill/*=0*/)

void servc::stopdis(int obverb/*=0*/,int oblog/*=0*/,uchar mitpkill)
{
    Log(violetts+Txk[T_stopdis_sname]+schwarzs+sname,obverb,oblog);
	if (!obsvfeh(obverb,oblog)) {
		stop(obverb,oblog);
	} // 	if (!obsvfeh(obverb,oblog))
	if (svfeh!=1&&obenabled)
		systemrueck(sudc+"systemctl disable '"+sname+"'",obverb,oblog,0,2);
} // int servc::stop(int obverb,int oblog)

int servc::enableggf(int obverb/*=0*/,int oblog/*=0*/)
{
    Log(violetts+Txk[T_enableggf]+schwarzs+": "+sname,obverb,oblog);
    vector<errmsgcl> errv;
    const string froh=schwarzs+Txk[T_Dienst]+blau+sname+schwarz;
    const string f0=froh+Txk[T_ermoeglicht];
    const string f1=froh+Txk[T_nicht_ermoeglicht];
    errv.push_back(errmsgcl(0,f0));
    errv.push_back(errmsgcl(1,f1));
    errv.push_back(errmsgcl(6,f1));
 return systemrueck("systemctl is-enabled '"+sname+"' >/dev/null 2>&1 ||"+sudc+"systemctl enable '"+sname+"'",obverb,oblog,0,2,wahr,"",&errv);
} // int servc::enableggf(int obverb,int oblog)


void servc::daemon_reload(int obverb/*=0*/, int oblog/*=0*/)
{
 systemrueck(sudc+"systemctl daemon-reload",obverb,oblog);
}

// Rueckgabe: Zahl der nicht Geloeschten
// wird aufgerufen in: loeschecapi, untersuchespool
int tuloeschen(const string& zuloe,const string& cuser, int obverb, int oblog)
{
  struct stat entryzuloe={0};
  if (!lstat(zuloe.c_str(),&entryzuloe)) {
    Log(Txk[T_Loesche_Ausrufezeichen]+gruens+zuloe+schwarz,obverb,oblog);
    int erg=-1;
    for(uchar iru=1;iru<3;iru++) {
      if ((erg=remove(zuloe.c_str()))) {
        if(cuser.empty()) iru++;
        if(iru==1) {
          setfaclggf(zuloe,obverb,oblog, falsch, 6, falsch,0);
        } else {
          if (errno) if (errno!=13) perror((string(Txk[T_Fehler_beim_Loeschen])+" "+ltoan(errno)).c_str()); // Permission denied
          const string cmd=sudc+"rm -rf \""+zuloe+"\"";
          erg=systemrueck(cmd,obverb+1,1);
        } // if(iru) else
      } else {
        erg=0;
        break;
      } //       if ((erg=remove(zuloe.c_str())))
    } // for(uchar iru=1;iru>-1;iru--)
    return erg;
  } // if (!lstat(zuloe.c_str(),&entryzuloe)) 
  Log(rot+zuloe+schwarz+Txk[T_nicht_geloescht_war_eh_nicht_mehr_da],obverb,oblog);
  return 0;
} // int tuloeschen(string zuloe,int obverb, int oblog)

// in optioncl::optioncl
void optioncl::setzebem(schlArr *cpA,const char *pname)
{
  if (cpA && pname) {
    svec bems;
    for(int akts=0;akts<SprachZahl;akts++) bems<<machbemerkung((Sprache)akts,falsch);
    cpA->setzbemv(pname,&Txk,0,0,&bems);
  } //   if (cpA && pname)
} // void optioncl::setzebem(TxB *TxBp,schlArr *cpA,const char *pname)

// /*2*/optioncl::optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,string *zptr, par_t art,schlArr *cpA, const char *pname,uchar* obschreibp) : kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),zptr(zptr),art(art),cpA(cpA),pname(pname),obschreibp(obschreibp) { setzebem(cpA,pname); }

/*2a*/optioncl::optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,string *zptr,par_t art,schlArr *cpA,const char *pname,uchar* obschreibp) : 
  kurzi(kurzi), langi(langi), TxBp(TxBp), Txi(Txi), wi(wi), zptr(zptr), art(art), cpA(cpA), pname(pname), obschreibp(obschreibp) 
{
  setzebem(cpA,pname);
}

// /*3*/optioncl::optioncl(string kurz, string lang, TxB *TxBp,long Txi,uchar wi,const string *rottxt, long Txi2, string *zptr, par_t art,schlArr *cpA, const char *pname,uchar* obschreibp) : kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),rottxt(rottxt),Txi2(Txi2),zptr(zptr),art(art),cpA(cpA),pname(pname),obschreibp(obschreibp) { setzebem(cpA,pname); }

/*3a*/optioncl::optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,const string *rottxt,long Txi2,string *zptr,par_t art,schlArr *cpA, 
    const char *pname,uchar* obschreibp) : 
  kurzi(kurzi),langi(langi),TxBp(TxBp),Txi(Txi),wi(wi),rottxt(rottxt),Txi2(Txi2),zptr(zptr),art(art),cpA(cpA),pname(pname),obschreibp(obschreibp) 
{
  setzebem(cpA,pname);
}

// /*4a*/optioncl::optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,uchar *pptr, int wert,schlArr *cpA,const char *pname,uchar* obschreibp) : kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),pptr(pptr),wert(wert),cpA(cpA),pname(pname),obschreibp(obschreibp),obno(obschreibp?1:0) { setzebem(cpA,pname); }

/*4*/optioncl::optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,uchar *pptr,int wert,schlArr *cpA, const char *pname,uchar* obschreibp) :
  kurzi(kurzi),langi(langi),TxBp(TxBp),Txi(Txi),wi(wi),pptr(pptr),wert(wert),art(psons),cpA(cpA),pname(pname),obschreibp(obschreibp),obno(obschreibp?1:0)
{
  setzebem(cpA,pname);
}

// gleicht das Datum von <zu> an <gemaess> an, aehnlich touch
int attrangleich(const string& zu, const string& gemaess,int obverb, int oblog)
{
  struct stat statgm={0};
  if (lstat(gemaess.c_str(),&statgm)) {
    Log(rots+Txk[T_Fehler_bei_lstat]+schwarz+gemaess,obverb,oblog);
    return 1;
  } //   if (lstat(gemaess.c_str(),&statgm))
  struct stat statzu={0};
  if (lstat(zu.c_str(),&statzu)) {
    Log(rots+Txk[T_Fehler_bei_lstat]+schwarz+zu,obverb,oblog);
    return 1;
  } //   if (lstat(zu.c_str(),&statzu))
  if (chmod(zu.c_str(),statgm.st_mode)) {
   systemrueck(sudc+"chmod --reference=\""+gemaess+"\" \""+zu+"\"",obverb,oblog);
  } //   if (chmod(zu.c_str(),statgm.st_mode))
  if (chown(zu.c_str(),statgm.st_uid,statgm.st_gid)) {
   systemrueck(sudc+"chown --reference=\""+gemaess+"\" \""+zu+"\"",obverb,oblog);
  } //   if (chown(zu.c_str(),statgm.st_uid,statgm.st_gid))
  struct utimbuf ubuf={0};
  ubuf.actime=ubuf.modtime=statgm.st_mtime;
  if (utime(zu.c_str(),&ubuf)) {
   systemrueck(sudc+"touch -r \""+gemaess+"\" \""+zu+"\"",obverb,oblog);
  } //   if (utime(zu.c_str(),&ubuf))
  lstat(zu.c_str(),&statzu);
  if (memcmp(&statgm.st_mtime, &statzu.st_mtime,sizeof statzu.st_mtime)) {
    Log(rots+Txk[T_Datum_nicht_gesetzt_bei]+schwarz+zu+rot+"'"+schwarz,1,1);
  } //   if (memcmp(&statgm.st_mtime, &statzu.st_mtime,sizeof statzu.st_mtime))
  return 0;
} // int attrangleich(const string& zu, const string& gemaess,int obverb, int oblog)

// liefert 0, wenn Erfolg
int kopier(const string& quel, const string& ziel, int obverb, int oblog)
{
  int erg=-1;
  int fehler=1;
  int source=open(quel.c_str(),O_RDONLY,0);
  if (source==-1) {
  } else {
    struct stat statq={0};
    if (!fstat(source,&statq)) {
      int dest=open(ziel.c_str(),O_WRONLY|O_CREAT,statq.st_mode);
      if (dest==-1) {
        fehler=2;
      } else {
        erg=sendfile64(dest,source,0,statq.st_size);
        close(dest);
        if (erg==-1) {
          fehler=3;
        } else {
          fehler=0;
          bool chmerg __attribute__((unused))=chmod(ziel.c_str(),statq.st_mode);
          bool choerg __attribute__((unused))=chown(ziel.c_str(),statq.st_uid,statq.st_gid);
          struct utimbuf ubuf={0};
          ubuf.actime=ubuf.modtime=statq.st_mtime;
          utime(ziel.c_str(),&ubuf);
        } // if (erg==-1)
      } // if (dest==-1) else 
      close(source);
    } // if (!fstat(source,&statq)) 
  } // if (source==-1) else 
  if (fehler)
    return systemrueck(sudc+"test -f \""+quel+"\" &&"+sudc+"sh -c 'cp -a \""+quel+"\" \""+ziel+"\"'",obverb,oblog);
  return 0;
} // int kopier(const string& quel, const string& ziel, int obverb, int oblog)

#ifdef altfind
// Binaerausgabe, fuer Debugging
void printBits(size_t const size, void const * const ptr)
{
  uchar *b = (uchar*) ptr;
  uchar byte;
  int i, j;
  puts("\r");
  for (i=size-1;i>=0;i--) {
    for (j=7;j>=0;j--) {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    } //     for (j=7;j>=0;j--)
  } //   for (i=size-1;i>=0;i--)
} // void printBits(size_t const size, void const * const ptr)


const bool elem2::operator<(const elem2& el) const {return (this->pfad<el.pfad);}

elem2::elem2(const string& mutter,const string& name) 
{
  init(mutter,name);
}

void elem2::init(const string& vmutter, const string& name) {
  pfad=(name[0]=='/'||vmutter.empty()?"":vmutter+(vmutter[vmutter.length()-1]=='/'?"":"/"))+name;
  sterg=0;
  if (name[0]=='.') {
    if (char* actp=realpath(pfad.c_str(),NULL)) {
      pfad=actp;
      free(actp);
    } else {
      sterg=REALPATHFEHLER;
    } //     if (char* actp=realpath(pfad.c_str(),NULL)) else
  } //   if (name[0]=='.')
  if (!sterg) sterg=lstat(pfad.c_str(), &dst);
} // void elem2::init(const string& vmutter, const string& name)

find2cl::find2cl(int _obverb/*=0*/,int _oblog/*=0*/,find2cl *stamm/*=0*/):obverb(_obverb),oblog(_oblog)
{
  if (stamm) {
    ergp=stamm->ergp;
    vznp=stamm->vznp;
    nrp=stamm->nrp;
    zuloeschen=0;
  } else {
    weiszu();
  } // if (stamm) else
} // find2cl::find2cl(find2cl *stamm/*=0*/)

find2cl::~find2cl()
{
  if (zuloeschen && 0) {
    if (ergp){ delete ergp;ergp=0;}
    if (vznp) {delete vznp;vznp=0;}
    if (nrp) {delete nrp;nrp=0;}
  }
} // find2cl::~find2cl()

void find2cl::weiszu()
{
  if (!ergp) ergp=new el2set;
  if (!vznp) vznp=new set<string>;
  if (!nrp) nrp=new ull;
} // void find2cl::weiszu()

void find2cl::init(const string& mutter, const string& name, regex_t *reg, const int folge,const long maxdepth, const int& typbit,
    vector<string> stack,time_t ab, time_t bis,int nurexec)
{
  dir=0;
  eingefuegt=0;
  verzneu=0;
  weiszu();
  elem2::init(mutter,name);
  elem2* letztel=(elem2*)this, *aktel=(elem2*)this;
  elem2 neuel;
//  cout<<"hier init,mutter: '"<<blau<<mutter<<schwarz<<"', name: '"<<blau<<name<<schwarz<<"', letztel->sterg: "<<letztel->sterg<<endl;
  while (!letztel->sterg && S_ISLNK(letztel->dst.st_mode)) {
    ssize_t r;
//    cout <<pfad<<" "<<sterg<<" "<<dst.st_size<<endl;
    char linkname[letztel->dst.st_size?letztel->dst.st_size:FILENAME_MAX+1];
		r=readlink(letztel->pfad.c_str(),linkname,sizeof linkname);
		if (r>0) {
			if ((size_t)r<=sizeof linkname)
				linkname[r]='\0';
//      cout<<rot<<letztel->pfad<<schwarz<<","<<linkname<<" ("<<letztel->dst.st_size<<")"<<schwarz<<endl;
    } else {
			Log(rots+Txk[T_Fehler_beim_Deferenzieren_von]+schwarz+pfad,1,1);
      break;
    }
//    cout<<"letztel->pfad: "<<letztel->pfad<<" linkname: "<<linkname<<endl;
    string link=linkname;
    if (link==letztel->pfad) exit(0);
    neuel.init(dir_name(letztel->pfad),linkname);
    //if (0)
    for(size_t j=0;j<stack.size();j++) {
      // <<"j: "<<j<<" "<<stack[j]<<endl;
      if (neuel.pfad==stack[j]) {
        return;
      } //       if (neuel.pfad==stack[j])
    } //     for(size_t j=0;j<stack.size();j++)
    if (neuel.pfad==letztel->pfad) break;
    letztel=&neuel;
  }
//  cout<<" -> "<<blau<<letztel->pfad<<schwarz<<" sterg: "<<sterg<<" "<<endl;
  if (!letztel->sterg && S_ISDIR(letztel->dst.st_mode)) {
    if (!(dir = opendir(letztel->pfad.c_str()))) {
      letztel->sterg=DIRFEHLER;
    }
  }

  if (!sterg) {
    if (
        (typbit&B_Datei && S_ISREG(dst.st_mode)) ||
        (typbit&B_Verzn && S_ISDIR(dst.st_mode)) ||
        (typbit&B_Chdev && S_ISCHR(dst.st_mode)) ||
        (typbit&B_Block && S_ISBLK(dst.st_mode)) ||
        (typbit&B_FIFO && S_ISFIFO(dst.st_mode)) ||
        (typbit&B_Link && S_ISLNK(dst.st_mode)) ||
        (typbit&B_Sock && S_ISSOCK(dst.st_mode))) {
      /*
         cout<<" tb1 ";
         printf("%i ",ltypbit);
         printBits(2,&ltypbit);
         printBits(2,&letztel->dst.st_mode);
         printf(" letztel->sterg: %i",letztel->sterg);
         cout<<"S_ISREG: "<<S_ISREG(letztel->dst.st_mode)<<endl;
         cout<<"S_ISDIR: "<<S_ISDIR(letztel->dst.st_mode)<<endl;
         cout<<"S_ISCHR: "<<S_ISCHR(letztel->dst.st_mode)<<endl;
         cout<<"S_ISBLK: "<<S_ISBLK(letztel->dst.st_mode)<<endl;
         cout<<"S_ISFIFO: "<<S_ISFIFO(letztel->dst.st_mode)<<endl;
         cout<<"S_ISLNK: "<<S_ISLNK(letztel->dst.st_mode)<<endl;
         cout<<"S_ISSOCK: "<<S_ISSOCK(letztel->dst.st_mode)<<endl;
       */
      if (letztel==(elem2*)this ||(!letztel->sterg &&(
              (typbit&B_Datei && S_ISREG(letztel->dst.st_mode)) ||
              (typbit&B_Verzn && S_ISDIR(letztel->dst.st_mode)) ||
              (typbit&B_Chdev && S_ISCHR(letztel->dst.st_mode)) ||
              (typbit&B_Block && S_ISBLK(letztel->dst.st_mode)) ||
              (typbit&B_FIFO && S_ISFIFO(letztel->dst.st_mode)) ||
              (typbit&B_Link && S_ISLNK(letztel->dst.st_mode)) ||
              (typbit&B_Sock && S_ISSOCK(letztel->dst.st_mode))))) {

        if (folge & Fol_Mus) aktel=letztel; else aktel=(elem2*)this;
				if ((!ab||aktel->dst.st_mtime>=ab)&&(!bis||aktel->dst.st_mtime<=bis))
					//        cout<<"Prüfe Muster: "<<blau<<aktel->pfad<<schwarz<<endl;
				 if (!nurexec || (aktel->dst.st_mode & S_IXUSR || aktel->dst.st_mode & S_IXGRP || aktel->dst.st_mode & S_IXOTH))
					if (!regexec(reg, aktel->pfad.c_str(), 0, 0, 0)) {
						if (folge & Fol_Dat) aktel=letztel; else aktel=(elem2*)this;
						//          cout<<"gefunden: "<<rot<<aktel->pfad<<schwarz<<endl;
#ifdef mitset
						eingefuegt=(ergp->insert(*aktel).second==true);
#else
						eingefuegt=(ergp->insert(make_pair(*aktel,nr)).second==true);
#endif
					} // 					if (!regexec(reg, aktel->pfad.c_str(), 0, 0, 0))
			} //       if (letztel==(elem2*)this ||(!letztel->sterg &&( ...
		} // if (      (typbit&B_Datei && S_ISREG(dst.st_mode)) || ..
	} //   if (!sterg) 
	//    cout<<endl;
	if (0) {
		(*nrp)++;
		cout<<"Tiefe: "<<stack.size()<<" Zahl: "<<*nrp<<", Pfad: "<<blau<<pfad<<schwarz;
		if (letztel->pfad!=pfad) {
			cout<<" -> "<<rot<<letztel->pfad<<schwarz;
		}
		cout<<endl;
		//        cout<<"letztel->pfad: "<<blau<<letztel->pfad<<schwarz<<endl;
		//        cout<<"aktel->pfad: "<<blau<<aktel->pfad<<schwarz<<endl;
	}
	//  cout<<"Stelle 1, dir?: "<<(!!dir)<<" maxdepth: "<<maxdepth<<endl;
	if (dir&&maxdepth) {
		//    cout<<"Stelle 2, folge: "<<folge<<" !S_ISLNK(dst.st_mode): "<<!S_ISLNK(dst.st_mode)<<endl;
		if ((folge & Fol_Ver) || !S_ISLNK(dst.st_mode)) {
			// Extra-Vergleichsliste der bisher eingelesenen Verzeichnisse
			if ((verzneu=(vznp->insert(letztel->pfad).second)==true)) {
				stack.push_back(letztel->pfad);
				while ((dent = readdir(dir))) {
					if (strcmp(dent->d_name, ".") && strcmp(dent->d_name, "..")) {
						//            cout<<"Stelle 5: dent->d_name: "<<blau<<dent->d_name<<schwarz<<endl;
						find2cl tochter(obverb,oblog,this);
						tochter.init(letztel->pfad,dent->d_name,reg,folge,maxdepth-1,typbit,stack,ab,bis,nurexec);
						//            cout<<"nach tochter.init"<<endl;
					} // 					if (strcmp(dent->d_name, ".") && strcmp(dent->d_name, ".."))
				} // 				while ((dent = readdir(dir)))
			} // 			if ((verzneu=(vznp->insert(letztel->pfad).second)==true))
		} // 		if ((folge & Fol_Ver) || !S_ISLNK(dst.st_mode))
		closedir(dir);
	}
} // void find2cl::init(const string& mutter, const string& name, regex_t *reg, const int folge,const long maxdepth, const int& typbit, ...

void find2cl::ausgeb()
{
	if (ergp) {
		el2set::iterator it=ergp->begin();
		ull nr=0;
		while (it!=ergp->end()) {
#ifdef mitset
			//string tue="bash -c \"test -z \\\"$(sed -n '\\$"+it->pfad+"\\$${p;q;}' /root/alle)\\\"&&echo '"+it->pfad+"'\"";cout<<tue<<endl;system(tue.c_str());
			cout<<blau<<++nr<<": "<<rot<<setprecision(9)<<setw(11)<<it->sterg<<schwarz<<" "<<it->pfad<<endl;
#else
			cout<<blau<<it->second<<": "<<rot<<setprecision(9)<<setw(11)<<(int)it->first.sterg<<schwarz<<" "<<(string)it->first.pfad<<endl;
#endif
			it++;
		} // 		while (it!=ergp->end())
	} // 	if (ergp)
} // void find2cl::ausgeb()

int find2cl::finde(svec *wovp,const string& muster/*=nix*/,const long tiefe/*=-1*/,int typbit/*=B_Alle*/,int folge/*=Fol_Dat*/,
		time_t ab/*=0*/, time_t bis/*=0*/,int obicase/*=0*/,int nurexec/*=0*/,int obnoext/*=0*/)
{
	regex_t reg;
	if (regcomp(&reg, muster.c_str(),(obnoext?0:REG_EXTENDED)|REG_NOSUB|(obicase?REG_ICASE:0))) 
		return REGFEHLER;
	vector<string> stack;
	string wo;
	for(size_t iv=0;iv<wovp->size();iv++) {
	  wo+=(*wovp)[iv];wo+=" ";
		init("",(*wovp)[iv], &reg, folge, tiefe, typbit,stack,ab,bis,nurexec);
		//    cout<<"nach finde.init, wo: "<<blau<<wo<<schwarz<<endl;
	} //   for(size_t iv=0;iv<*wovp.size();iv++)
	if (obverb|oblog) {
		Log(obverb,oblog,0,0,"%s%s%s%s%s%s%s%s'%s%s'%s%lu%s%s%s%d%s%s%s%d%s%s%s%d%s%s%s%zu%s",
		Txk[T_Suche_in],blau,wo.c_str(),schwarz,Txk[T_nach],blau,muster.c_str(),schwarz,obicase?"(ic)":"",Txk[T_Tiefe],blau,tiefe,schwarz,
		Txk[T_Typbit],blau,typbit,schwarz,Txk[T_Folge],blau,folge,schwarz,Txk[T_noext],blau,obnoext,schwarz,Txk[T_Ergebnis],
		gruen,ergp->size(),schwarz);
	} // 	if (obverb|oblog)
	if (obverb>1) ausgeb();
	return 0;
} // int find2cl::finde(svec *wovp,string& muster/*=nix*/,const long tiefe/*=-1*/,int typbit/*=B_Alle*/,int folge/*=Fol_Dat*/,

void find2cl::zuvec(svec *zu,uchar anteil/*=0*/)
{
	for(set<elem2>::iterator jt=ergp->begin();jt!=ergp->end();jt++) {
		if (anteil)
			zu->push_back(base_name(jt->pfad));
		else
			zu->push_back(jt->pfad);
	} // 	for(set<elem2>::iterator jt=ergp->begin();jt!=ergp->end();jt++)
} // void find2cl::zuvec(svec *zu,uchar anteil/*=0*/)
#endif

#ifdef neufind
const bool elem3::operator<(const elem3& el) const {return (this->pfad<el.pfad);}
const bool wele::operator<(const wele& el) const {return (this->pfad<el.pfad);}

set<wele>::iterator find3cl::it;
set<wele> *find3cl::wurzp;
set<elem3> *find3cl::ergp;
long *find3cl::maxdepthp;
int *find3cl::folgep;
regex_t *find3cl::regp;
int *find3cl::typbitp;
time_t *find3cl::mabp,*find3cl::mbisp;
int *find3cl::obverbp, *find3cl::oblogp;
int *find3cl::nurexecp;

int find3cl::verarbeit(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
	if (
			(*typbitp&B_Datei && S_ISREG(sb->st_mode)) ||
			(*typbitp&B_Verzn && S_ISDIR(sb->st_mode)) ||
			(*typbitp&B_Chdev && S_ISCHR(sb->st_mode)) ||
			(*typbitp&B_Block && S_ISBLK(sb->st_mode)) ||
			(*typbitp&B_FIFO && S_ISFIFO(sb->st_mode)) ||
			(*typbitp&B_Link && S_ISLNK(sb->st_mode)) ||
			(*typbitp&B_Sock && S_ISSOCK(sb->st_mode))) {
		string pfad;
		char buff[FILENAME_MAX];
		buff[0]=0;
		struct stat lst={0};
		if (tflag==FTW_SL) {
			ssize_t len = readlink(fpath, buff, sizeof(buff)-1);
			if (len==-1) {
				//          pfad=fpath;
			} else {
				buff[len] = '\0';
				if (char* actp=realpath(((buff[0]=='/'?"":dir_name(fpath)+'/')+buff).c_str(),NULL)) {
					pfad=actp;
					free(actp);
					if (!lstat(pfad.c_str(),&lst)) {
						if (S_ISDIR(lst.st_mode)) {
							if (*folgep&Fol_Ver) {
								if (*obverbp>2) Log(blaus+Txk[T_Linkverzeichnis]+schwarz+pfad,*obverbp,*oblogp);
								wurzp->insert(wele(pfad,it->maxd-ftwbuf->level));
							} //               if (*folgep&Fol_Ver)
						} //             if (S_ISDIR(lst.st_mode))
					} //           if (!lstat(pfad.c_str(),&lst))
				} //         if (char* actp=realpath(((buff[0]=='/'?"":dir_name(fpath)+'/')+buff).c_str(),NULL))
			} //       if (len==-1)
			if (pfad.empty()) pfad="?????";
		} //     if (tflag==FTW_SL)
		const char *vgl=(tflag==FTW_SL&&*folgep&Fol_Mus)?pfad.c_str():fpath;
		if (!regexec(regp, vgl, 0, 0, 0)) {
			if ( tflag!=FTW_SL ||
					(*typbitp&B_Datei && S_ISREG(lst.st_mode)) ||
					(*typbitp&B_Verzn && S_ISDIR(lst.st_mode)) ||
					(*typbitp&B_Chdev && S_ISCHR(lst.st_mode)) ||
					(*typbitp&B_Block && S_ISBLK(lst.st_mode)) ||
					(*typbitp&B_FIFO && S_ISFIFO(lst.st_mode)) ||
					(*typbitp&B_Link && S_ISLNK(lst.st_mode)) ||
					(*typbitp&B_Sock && S_ISSOCK(lst.st_mode))) {
				const int obt=*folgep&Fol_Dat&&!pfad.empty()?1:0;
				const struct stat *sp=obt?&lst:sb;
				if ((!*mabp||sp->st_mtime>=*mabp)&&(!*mbisp||sp->st_mtime<=*mbisp))
				 if (!*nurexecp || (sp->st_mode & S_IXUSR || sp->st_mode & S_IXGRP || sp->st_mode & S_IXOTH))
					ergp->insert(elem3(obt?pfad:fpath,sp,tflag,ftwbuf,obt?fpath:pfad,obt?*sb:lst));
			} //       if ( tflag!=FTW_SL || ...
		} //     if (!regexec(regp, vgl, 0, 0, 0))
	} //   if ( .. ||.. (*typbitp&B_Datei && S_ISREG(sb->st_mode)) ||
	if (*maxdepthp>=0 && ftwbuf->level>=it->maxd) {
		return FTW_SKIP_SUBTREE;
	}
	if (*obverbp>2||*oblogp>2) Log("fpath: "+blaus+fpath+schwarz,*obverbp,*oblogp);
	return FTW_CONTINUE;
} //     static int verarbeit(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)

find3cl::find3cl(int _obverb/*=0*/,int _oblog/*=0*/):obverb(_obverb),oblog(_oblog)
{
	obverbp=&obverb;
	oblogp=&oblog;
}

int find3cl::dofind()
{
	// aeussere Schleife so lange durchlaufen, bis in der inneren Schleife nichts mehr zu tun ist; dort wird ggf. wurz erweitert
	while (1) {
		int gearbeitet=0;
		for(it=wurz.begin();it!=wurz.end();it++) {
			if (fertige.find(*it)!=fertige.end()) continue;
			if (it->pfad.empty()) continue;
			struct stat st;
			if (lstat(it->pfad.c_str(),&st)) continue;
			gearbeitet=1;
			if (obverb>2||oblog>1) Log("Iterator: "+blaus+it->pfad+schwarz+Txk[T_Tiefe]+blau+ltoan(it->maxd)+schwarz,obverb,oblog);
			if (nftw(it->pfad.c_str(), this->verarbeit, 20, flags) == -1) {
				perror((rots+Txk[T_Fehler]+"nftw ('"+it->pfad+"')"+schwarz).c_str());
//				exit(EXIT_FAILURE);
			} //       if (nftw(it->pfad.c_str(), this->verarbeit, 20, flags) == -1)
			fertige.insert(*it);
		} //     for(it=wurz.begin();it!=wurz.end();it++)
		if (!gearbeitet) break;
	} //   while (1)
	return 0;
} //     int dofind()

int find3cl::ausgeb()
{
	size_t j=0;
	for(set<elem3>::iterator jt=erg.begin();jt!=erg.end();jt++) {
		j++;
		printf("%7ld) %-3s %2d ",j,
				(jt->tflag == FTW_D) ?   "d"   : (jt->tflag == FTW_DNR) ? "dnr" :
				(jt->tflag == FTW_DP) ?  "dp"  : (jt->tflag == FTW_F) ?   "f" :
				(jt->tflag == FTW_NS) ?  "ns"  : (jt->tflag == FTW_SL) ?  "sl" :
				(jt->tflag == FTW_SLN) ? "sln" : "???", jt->ftw.level);

		if (jt->tflag == FTW_NS)
			printf("-------");
		else
			printf(" %7jd",(intmax_t) jt->sb.st_size);
		struct tm *tm=localtime(&jt->sb.st_mtime);
		char buf[80];
		strftime(buf, sizeof buf,"%F %X",tm);
		//        printf(" %s %-40s %5d %s",buf, jt->pfad.c_str(), jt->ftw.base, jt->pfad.c_str()+jt->ftw.base);
		printf(" %s %-40s",buf, jt->pfad.c_str());
		if (jt->tflag==FTW_SL) {
			tm=localtime(&jt->lst.st_mtime);
			strftime(buf, sizeof buf,"%F %X",tm);
			printf(" %s %s %s",folge&Fol_Dat?"<-":"->",buf,jt->lnk.c_str());
		}
		printf("\n");
	} //       for(set<elem3>::iterator jt=erg.begin();jt!=erg.end();jt++)
	return 0;
} //     int ausgeb()

int find3cl::finde(svec *wovp,const string& muster/*=nix*/,long tiefe/*=-1*/,
		int _typbit/*=B_Alle*/,int _folge/*=Fol_Dat*/,time_t _mab/*=0*/,time_t _mbis/*=0*/,int obicase/*=0*/,int _nurexec/*=0*/,int obnoext/*=0*/)
{
	int ret=0;
	maxdepthp=&maxdepth;
	*maxdepthp=tiefe;
	string wo;
	for(size_t iv=0;iv<wovp->size();iv++) {
	  wo+=(*wovp)[iv];wo+=" ";
		if (char* actp=realpath((*wovp)[iv].c_str(),NULL)) {
			const string pfad=actp;
			free(actp);
			wurz.insert(wele(pfad,maxdepth));
		} else {
			wurz.insert(wele((*wovp)[iv],maxdepth));
		} //     if (char* actp=realpath(*wovp[iv].c_str(),NULL)) else
	} //   for(size_t iv=0;iv<*wovp.size();iv++)
	wurzp=&wurz;
	ergp=&erg;
	regp=&reg;
	folgep=&folge;
	*folgep=_folge;
	typbitp=&typbit;
	*typbitp=_typbit;
	mabp=&mab;
	*mabp=_mab;
	mbisp=&mbis;
	*mbisp=_mbis;
	nurexec=_nurexec;
	nurexecp=&nurexec;
	// if (argc > 2 && strchr(argv[2], 'd') != NULL) f.flags |= FTW_DEPTH; // erst Unterverzeichnisse, dann aktuelles Verzeichnis
	// if (argc > 2 && strchr(argv[2], 'p') != NULL)
	flags |= FTW_ACTIONRETVAL;
	flags |= FTW_PHYS;
	if (regcomp(&reg, muster.c_str(),(obnoext?0:REG_EXTENDED)|REG_NOSUB|(obicase?REG_ICASE:0))) 
		return REGFEHLER;
	ret=dofind();
	if (obverb|oblog) {
		Log(obverb,oblog,0,0,"%s%s%s%s%s%s%s%s'%s%s'%s%lu%s%s%s%d%s%s%s%d%s%s%s%d%s%s%s%zu%s",
		Txk[T_Suche_in],blau,wo.c_str(),schwarz,Txk[T_nach],blau,muster.c_str(),schwarz,obicase?"(ic)":"",Txk[T_Tiefe],blau,tiefe,schwarz,
		Txk[T_Typbit],blau,typbit,schwarz,Txk[T_Folge],blau,folge,schwarz,Txk[T_noext],blau,obnoext,schwarz,Txk[T_Ergebnis],
		gruen,ergp->size(),schwarz);
	} // 	if (obverb|oblog)
	if (obverb>1) ausgeb();
	return ret;
} // int find3cl::finde(

void find3cl::zuvec(svec *zu,uchar anteil/*=0*/)
{
	for(set<elem3>::iterator jt=erg.begin();jt!=erg.end();jt++) {
		if (anteil)
			zu->push_back(base_name(jt->pfad));
		else
			zu->push_back(jt->pfad);
	} // 	for(set<elem3>::iterator jt=erg.begin();jt!=erg.end();jt++)
} // void find3cl::zuvec(svec *zu,uchar anteil/*=0*/)
#endif

#if defined(altfind) && defined(neufind)
void findfile(svec *qrueckp,uchar findv,int obverb/*=0*/,int oblog/*=0*/,uchar anteil/*=0*/,
	const string& wo/*="."*/,const string& muster/*=nix*/,long tiefe/*=-1*/,int _typbit/*=B_Alle*/,
	int _folge/*=Fol_Dat*/, time_t _mab/*=0*/,time_t _mbis/*=0*/,int obicase/*=0*/,int nurexec/*=0*/,int obnoext/*=0*/)
{
	svec wov;
	switch (findv) {
		case 2: case 3:
			aufSplit(&wov, wo);
			setfaclggf(wov[wov.size()-1],obverb,oblog,wahr,4,falsch,1,"");
			break;
	} // 	switch (findv)
	if (findv==2) {
		find2cl f(obverb,oblog);
		f.finde(&wov,muster,tiefe,_typbit,_folge,_mab,_mbis,obicase,nurexec,obnoext);
		f.zuvec(qrueckp,anteil);
	} else if (findv==3) {
		find3cl f(obverb,oblog);
		f.finde(&wov,muster,tiefe,_typbit,_folge,_mab,_mbis,obicase,nurexec,obnoext);
		f.zuvec(qrueckp,anteil);
	} // 	if (findv==2) else if (findv==3)
} // void findfile(svec *qrueckp,uchar findv,int obverb/*=0*/,int oblog/*=0*/,uchar anteil/*=0* ...
#endif
