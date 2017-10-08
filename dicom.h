#define caus cout


class paramcl;
class datcl
{
	private:
		static constexpr const unsigned dim=10;
		static constexpr const char *knz[dim]={"PatientName","PatientBirthDate","PatientID","PatientSex","ImageType",
			"ReferringPhysicianName","PerformingPhysicianName","TransducerData","ProcessingFunction","AcquisitionDateTime"};
		static constexpr const unsigned pnnr=0, itnr=4, rpnr=5, tdnr=7, pfnr=8, adnr=9;
		string id; // Rueckgabe: ID
		svec ir;
	public:
		string name;
		uchar gibaus;
		string bname;
		string ord[dim];
	public:
		void inDB(paramcl& pm, const int& aktc);
		void aufPlatte(paramcl& pm,const int& aktc,const size_t& nr);
		datcl(string& name);
};

class paramcl: public haupt // Programmparameter 
{
	public:
		const int aktc=0;
    string host="localhost";  // fuer MySQL/MariaDB
    string muser; // Benutzer fuer Mysql/MariaDB
    string mpwd;  // Passwort fuer Mysql/MariaDB
		uchar autoupd;  // 1=Programm automatisch updadaten
		DB *My=0;
    string dbn; // Datenbank
    string tbn; // Tabellenname
		string findvers; // find-Version (1=linux fund 2=intern mit readdir, 3=intern mit nftw 
		int ifindv; // integer-Variante der find-Version
		string duser; // ="sturm";
		string qvz; // Quellverzeichnis // ="/DATA/Patientendokumente/HDneu";
		string avz; // Verzeichnis alter Übertragungen // ="/DATA/Patientendokumente/HDalt";
		string zvz; // Zielverzeichnis // ="/DATA/Patientendokumente/test";
		string z2vz; // 2. Zielverzeichnis // ="/DATA/Patientendokumente/eingelesen";
    string suchstr;  // Wortteil, nach dem in alten Uebertragungen gesucht werden soll
		uchar keineverarbeitung=0; // wenn cronminuten geaendert werden sollen, vorher abkuerzen
    uchar obvi=0;   // ob Konfigurationsdatei editiert werden soll
		uchar obvs=0;   // ob Quelldateien bearbeitet werden sollen
    uchar anhl=0;    // <DPROG> anhalten
		int ret=0; // Rueckgabewert
	public:
		paramcl(const int argc, const char *const *const argv,const int obverb=0, const int oblog=0);
    void pruefggfmehrfach();
		void getcommandl0();
    void rufpruefsamba();
		int  initDB();
		void pruefdictab(const int aktc);
    void autofkonfschreib();
		void MusterVorgb();
		void VorgbSpeziell() 
#ifdef DPROGcpp
			__attribute__((weak)) // implementationsspezifische Vorgaben (aber nur Quellcodeaenderung aenderbar, Modul vgb.cpp)
#endif // DPROGcpp
			;
		void lieskonfein();
		int  getcommandline();
		void rueckfragen();
		void verschieb();
		void zeigdienste();
		void pruefdcmj();
		void verzeichnisse();
}; // class paramcl
