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
	DB *My=0;
	string duser; // ="sturm";
	string qvz; // ="/DATA/Patientendokumente/HDneu";
	string avz; // ="/DATA/Patientendokumente/HDalt";
	string zvz; // ="/DATA/Patientendokumente/test";
	string z2vz; // ="/DATA/Patientendokumente/eingelesen";
		int ret=0; // Rueckgabewert
	public:
		paramcl(const int argc, const char *const *const argv);
		void getcommandl0();
		int  initDB();
		void pruefdictab(int aktc);
    #ifdef DPROGcpp
    void VorgbSpeziell() __attribute__((weak)); // implementationsspezifische Vorgaben (aber nur Quellcodeaenderung aenderbar, Modul vgb.cpp)
    #else // DPROGcpp
    void VorgbSpeziell(); // implementationsspezifische Vorgaben (aber nur Quellcodeaenderung aenderbar, Modul vgb.cpp)
    #endif // DPROGcpp else
		void verschieb();
}; // class paramcl
