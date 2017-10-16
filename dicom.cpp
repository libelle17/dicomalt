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
	T_Importdatum,
	T_Arzt,
	T_Tabelle_fuer_dicom_Bilder,
	T_Fehler_beim_Pruefen_von_dictab,
	T_VorgbSpeziell,
	T_Quellverzeichnis_anstatt,
	T_Archivverzeichnis_anstatt,
	T_Zielverzeichnis_anstatt,
	T_Zweites_Zielverzeichnis_anstatt,
	T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,
	T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,
	T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string,
	T_verwendet_die_Datenbank_string_anstatt,
	T_verwendet_die_Tabelle_string_anstatt,
	T_Version_1_2_oder_3_Dateisuche_anstatt,
	T_Alle_wieviel_Minuten_soll,
	T_aufgerufen_werden_0_ist_gar_nicht,
	T_Programm_automatisch_aktualisieren,
	T_Bildschirmausgabe_mit_SQL_Befehlen,
	T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigten,
	T_keine_Rueckfragen_zB_aus_Cron,
	T_host_k,
	T_host_l,
	T_muser_k,
	T_muser_l,
	T_mpwd_k,
	T_mpwd_l,
	T_db_k,
	T_datenbank_l,
	T_tb_k,
	T_tb_l,
	T_find_k,
	T_find_l,
	T_sqlv_k,
	T_sql_verbose_l,
	T_rf_k,
	T_rueckfragen_l,
	T_krf_k,
	T_keinerueckfragen_l,
	T_cm_k,
	T_cronminuten_l,
	T_autoupd_k,
	T_autoupd_l,
	T_qvz_k,
	T_qvz_l,
	T_avz_k,
	T_avz_l,
	T_zvz_k,
	T_zvz_l,
	T_z2vz_k,
	T_z2vz_l,
	T_nicht_erkannt,
	T_Fertig_mit_Parsen_der_Befehlszeile,
	T_Gebrauch,
	T_ja,
	T_nein,
	T_Liest_Dicom_Dateien_aus,
	T_speichert_sie_als_png_Bilder_in,
	T_und,
	T_und_verschiebt_zuletzt_die_Orignale_nach,
	T_Optionen_die_nicht_gespeichert_werden,
	T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden,
	T_rufpruefsamba,
	T_DicomQuellVz,
	T_DicomArchivVz,
	T_DicomZielVz,
	T_DicomZiel2Vz,
	T_zeigvers,
	T_Host_fuer_MySQL_MariaDB_Datenbank,
	T_Benutzer_fuer_MySQL_MariaDB,
	T_Passwort_fuer_MySQL_MariaDB,
	T_Datenbankname_fuer_MySQL_MariaDB_auf,
	T_Tabellenname_fuer_MySQL_MariaDB_in,
	T_Linux_Benutzer_fuer_Verzeichnisse,
	T_Verzeichnis_mit_unverarbeiteten_Dicom_Dateien,
	T_Verzeichnis_mit_archivierten_Dicom_Dateien,
	T_Verzeichnis_mit_verarbeiteten_Dicom_Dateien,
	T_2_Verzeichnis_mit_verarbeiteten_Dicom_Dateien,
	T_rueckfragen,
	T_Sollen_neue_Programmversionen_von,
	T_automatisch_installiert_werden,
	T_Logverzeichnis,
	T_Logdateiname,
	T_oblog,
	T_Oblog,
	T_verzeichnisse,
	T_Logpfad,
	T_autokonfschreib,
	T_zu_schreiben,
	T_schreibe_Konfiguration,
	T_Zeigt_die_Programmversion_an,
	T_Konfigurations_u_Logdatei_bearbeiten_sehen,
	T_Quelldateien_bearbeiten,
	T_Erklaerung_haeufiger_Optionen,
	T_Erklaerung_aller_Optionen,
	T_info_k,
	T_version_l,
	T_vi_k,
	T_vi_l,
	T_vc_k,
	T_vc_l,
	T_vh_k,
	T_vh_l,
	T_vs_k,
	T_vs_l,
	T_h_k,
	T_lh_k,
	T_hilfe_l,
	T_lhilfe_l,
	T_fgz_k,
	T_fgz_l,
	T_duser_k,
	T_duser_l,
	T_verwendet_fuer_Samba_den_Linux_Benutzer_string_anstatt,
	T_Datensaetze_in_Tabelle,
	T_eingetragen,
	T_Dateien_in_Verzeichnis,
	T_erstellt,
	T_kopiert,
	T_Dicom_Dateien,
	T_gefunden,
	T_Keine,
	T_Alle,
	T_Dateien_von,
	T_nach_,
	T_verschoben,
	T_Nr,
	T_Fehler_beim_Datumsetzen_von,
	T_in_Datenbank,
	T_jahr,
	T_letzten_Import_rueckgaengig,
	T_rueck_k,
	T_rueck_l,
	T_Keine_Dateien_in,
	T_Gefunden,
	T_Erstellt,
	T_Dateien_in,
	T_MediaStorageSOPInstanceUID,
	T_MAX
}; // enum T_

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
 // T_Importdatum
 {"Importdatum","import date"},
 // T_Arzt
 {"Arzt","Physician"},
 // T_Tabelle_fuer_dicom_Bilder
 {"Tabelle fuer dicom-Bilder","table for dicom pictures"},
 // T_Fehler_beim_Pruefen_von_dictab
 {"Fehler eim Prüfen der Tabelle dictab","error checking table dictab"},
 // T_VorgbSpeziell
 {"VorgbSpeziell()","specificprefs()"},
 // T_Quellverzeichnis_anstatt
 {"Quellverzeichnis anstatt ","source directory instead of "},
 // T_Archivverzeichnis_anstatt
 {"Archiverzeichnis anstatt ","archive directory instead of "},
 // T_Zielverzeichnis_anstatt
 {"Zielverzeichnis anstatt ","target directory instead of "},
 // T_Zweites_Zielverzeichnis_anstatt
 {"Zweites Zielverzeichnis anstatt ","Second target directory instead of "},
 // T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf
 {"verwendet die Datenbank auf Host <string> anstatt auf","takes the database on host <string> instead of"},
 // T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt
 {"verwendet fuer MySQL/MariaDB den Benutzer <string> anstatt","takes the user <string> for MySQL/MariaDB instead of"},
	// T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string
	{"verwendet fuer MySQL/MariaDB das Passwort <string>","takes the password <string> for MySQL/MariaDB"},
	// T_verwendet_die_Datenbank_string_anstatt
	{"verwendet die Datenbank <string> anstatt","uses the database <string> instead of"},
	// T_verwendet_die_Tabelle_string_anstatt
	{"verwendet die Tabelle <string> anstatt","uses the table <string> instead of"},
	// T_Version_1_2_oder_3_Dateisuche_anstatt
	{"Version 1,2 oder 3 -Dateisuche (variable Performanceunterschiede) anstatt",
		"version 1,2 or 3 of filefind (variable performance differences instead of"},
	// T_Alle_wieviel_Minuten_soll
	{"alle wieviel Minuten soll ","every how many minutes shall "},
	// T_aufgerufen_werden_0_ist_gar_nicht]
	{" ueber crontab aufgerufen werden (0=gar nicht), anstatt ", " be called in crontab (0=not at all), instead of "},
	// T_Programm_automatisch_aktualisieren
	{"Programm automatisch aktualisieren","Update program automatically"},
	// T_Bildschirmausgabe_mit_SQL_Befehlen
	{"Bildschirmausgabe mit SQL-Befehlen","screen output with SQL commands"},
	// T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigten
	{"alle Parameter werden abgefragt (darunter einige hier nicht gezeigten)","all parameters will be prompted (some of them not shown here)"},
	// T_keine_Rueckfragen_zB_aus_Cron
	{"keine Rueckfragen, z.B. für Aufruf aus cron","no questions, e.g. for a call of " DPROG " within cron"},
	// T_host_k
	{"host","host"},
	// T_host_l
	{"host","host"},
	// T_muser_k
	{"muser","muser"},
	// T_muser_l
	{"muser","muser"},
	// T_mpwd_k
	{"mpwd","mpwd"},
	// T_mpwd_l
	{"mpwd","mpwd"},
	// T_db_k
	{"db","db"},
	// T_datenbank_l
	{"datenbank","database"},
	// T_tb_k
	{"tb","tb"},
	// T_tb_l
	{"tabelle","table"},
	// 	T_find_k,
	{"fd","fd"},
	// T_find_l,
	{"finde","find"},
	// T_sqlv_k
	{"sqlw","sqlv"},
	// T_sql_verbose_l
	{"sql-wortreich","sql-verbose"},
	// T_rf_k
	{"rf","ia"},
	// T_rueckfragen_l
	{"rueckfragen","interactive"},
	// T_krf_k
	{"krf","noia"},
	// T_keinerueckfragen_l
	{"keinerueckfragen","nointeraction"},
	// T_cm_k
	{"cm","cm"},
	// T_cronminuten_l
	{"cronminuten","cronminutes"},
	// 	T_autoupd_k,
	{"autoakt","autoupd"},
	// 	T_autoupd_l,
	{"autoaktual","autoupdate"},
	// T_qvz_k
	{"qvz","sdr"},
	// T_qvz_l
	{"quellvz","sourcedir"},
	// T_avz_k
	{"avz","adr"},
	// T_avz_l
	{"archvz","archdir"},
	// T_zvz_k
	{"zvz","tdr"},
	// T_zvz_l
	{"zielvz","targetdir"},
	// T_z2vz_k
	{"z2vz","t2dr"},
	// T_z2vz_l
	{"ziel2vz","target2dir"},
	// T_nicht_erkannt
	{" nicht erkannt!"," not identified!"},
	// T_Fertig_mit_Parsen_der_Befehlszeile
	{"Fertig mit Parsen der Befehlszeile, Konfiguration zu schreiben: ","Parsing the command line finished, about to write configuration: "},
	// T_Gebrauch
	{"Gebrauch: ","Usage: "},
	// T_ja
	{"ja","yes"},
	// T_nein
	{"nein","no"},
	// T_Liest_Dicom_Dateien_aus
	{"Liest Dicom-Dateien aus ","Reads dicom-files from "},
	// T_speichert_sie_als_png_Bilder_in
	{", speichert sie als png-Bilder in ",", saves them as png pictures in "},
	// T_und
	{" und "," and "},
	// T_und_verschiebt_zuletzt_die_Orignale_nach
	{" und verschiebt zuletzt die Originale nach "," and at last moves the original files to "},
	// T_Optionen_die_nicht_gespeichert_werden
	{"Optionen, die nicht gespeichert werden: ","Options which are not saved: "},
	// T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden,
	{"Optionen z.Speich. i.Konfigur'datei (vorausg. '1'=doch nicht speichern, 'no'=Gegenteil, z.B. '-noocra','-1noocri'):",
		"Options to be saved in the configuration file: (preced. '1'=don't save, 'no'=contrary, e.g. '-noocra','-1noocri'):"},
	// T_rufpruefsamba
	{"rufpruefsamba()","callchecksamba()"},
	// T_DicomQuellVz
	{"DicomQuellVz","dicomSourceDir"},
	// T_DicomArchivVz
	{"DicomArchivVz","dicomArchiveDir"},
	// T_DicomZielVz
	{"DicomZielVz","dicomTargetDir"},
	// T_DicomZiel2Vz
	{"DicomZiel2Vz","dicomTarget2Dir"},
	// T_zeigvers
	{"zeigvers","showvers"},
	// T_Host_fuer_MySQL_MariaDB_Datenbank
	{"Host fuer MySQL/MariaDB-Datenbank","host for mysql/mariadb-database"},
	// T_Benutzer_fuer_MySQL_MariaDB,
	{"Benutzer fuer MySQL/MariaDB:","user for mysql/mariadb:"},
	// T_Passwort_fuer_MySQL_MariaDB,
	{"Passwort fuer MySQL/MariaDB (Achtung: nur schwach verschluesselt!)","password for mysql/mariadb (caution: only weakly encrypted!)"},
	// T_Datenbankname_fuer_MySQL_MariaDB_auf
	{"Datenbankname fuer MySQL/MariaDB auf '","database name for mysql/mariabd on '"},
	// T_Tabellenname_fuer_MySQL_MariaDB_in
	{"Tabellenname fuer MySQL/MariaDB in '","table name for mysql/mariadb in '"},
	// T_Linux_Benutzer_fuer_Verzeichnisse
	{"Linux-Benutzer fuer Verzeichnisse","linux user for directories"},
	// T_Verzeichnis_mit_unverarbeiteten_Dicom_Dateien
	{"Verzeichnis mit unverarbeiteten Dicom-Dateien","directory with unprocessed dicom files"},
	// T_Verzeichnis_mit_archivierten_Dicom_Dateien
	{"Verzeichnis mit archivierten Dicom-Dateien","directory with archived dicom files"},
	// T_Verzeichnis_mit_verarbeiteten_Dicom_Dateien
	{"Verzeichnis mit verarbeiteten Dicom-Dateien","directory with processed dicom files"},
	// T_2_Verzeichnis_mit_verarbeiteten_Dicom_Dateien
	{"2. Verzeichnis mit verarbeiteten Dicom-Dateien","2nd directory with processed dicom files"},
	// T_rueckfragen
	{"rueckfragen()","callbacks()"},
	// T_Sollen_neue_Programmversionen_von
	{"Sollen neue Programmversionen von ","Shall new versions of "},
	// T_automatisch_installiert_werden
	{" automatisch installiert werden?"," be automatically installed?"},
	// T_Logverzeichnis
	{"Logverzeichnis","log directory"},
	// T_Logdateiname
	{"Logdateiname","log file name"},
	// T_oblog,
	{"' (oblog: ","' (with logging: "},
	// T_Oblog,
	{"Oblog (ausführliche Protokollierung): ","Log (detailled logging): "},
	// T_verzeichnisse
	{"verzeichnisse()","directories()"},
	// T_Logpfad,
	{"Logpfad: '","Log path: '"},
	// T_autokonfschreib
	{"autokonfschreib()","autoconfwrite()"},
	// T_zu_schreiben
	{"zu schreiben: ","must write: "},
	// T_schreibe_Konfiguration
	{"schreibe Konfiguration!","writing configuration!"},
	// T_Zeigt_die_Programmversion_an
	{"Zeigt die Programmversion an","shows the program version"},
	// T_Konfigurations_u_Logdatei_bearbeiten_sehen
	{"Konfigurations- u.Logdatei bearbeiten/sehen (beenden mit ':qa')","edit/view configuration and log file (finish with ':qa')"},
	// T_Quelldateien_bearbeiten
	{"Quelldateien bearbeiten (beenden mit ':qa')","edit source files (finish with ':qa')"},
	// 	T_Erklaerung_haeufiger_Optionen
	{"Erklärung häufiger Optionen","Explanation of frequent options"},
	// T_Erklaerung_aller_Optionen
	{"Erklärung aller Optionen","Explanation of all options"},
	// T_info_k
	{"info","info"},
	// T_version_l
	{"version","version"},
	// T_vi_k
	{"vi","vi"},
	// T_vi_l
	{"vi","vi"},
	// T_vc_k
	{"vc","vc"},
	// T_vc_l
	{"vc","vc"},
	// T_vh_k
	{"vh","vh"},
	// T_vh_l
	{"vh","vh"},
	// T_vs_k
	{"vs","vs"},
	// T_vs_l
	{"vs","vs"},
	// T_h_k
	{"h","h"},
	// T_lh_k
	{"lh","lh"},
	// T_hilfe_l
	{"hilfe","help"},
	// T_lhilfe_l
	{"langhilfe","longhelp"},
	// T_fgz_k
	{"?","?"},
	// T_fgz_l,
	{"??","??"},
	// T_duser_k
	{"duser","duser"},
	// T_duser_l
	{"duser","duser"},
	// T_verwendet_fuer_Samba_den_Linux_Benutzer_string_anstatt
	{"verwendet fuer Samba den Linux-Benutzer <string> anstatt", "takes the linux user <string> for samba instead of"},
	// T_Datensaetze_in_Tabelle
	{" Datensaetze in Tabelle '"," records inserted in table '"},
	// T_eingetragen
	{"' eingetragen,","',"},
	// T_Dateien_in_Verzeichnis
	{" Dateien in Verzeichnis '"," files created in directory '"},
	// T_erstellt
	{"' erstellt,","',"},
	// T_kopiert
	{"' kopiert,","',"},
	// T_Dicom_Dateien
	{" Dicom-Dateien in '"," dicom files found in '"},
	// T_gefunden
	{"' gefunden,","',"},
	// T_Keine
	{"Keine","   No"},
	// T_Alle
	{" Alle","  All"},
	// T_Dateien_von
	{" Dateien von '"," files moved from '"},
	// T_nach_
	{"' nach '","' to '"},
	// T_verschoben
	{"' verschoben.","'."},
	// T_Nr
	{"Nr: ","No: "},
	// T_Fehler_beim_Datumsetzen_von
	{"Fehler beim Datumsetzen von '","Error while setting the date for '"},
	// T_in_Datenbank
	{"' in Datenbank '","' in database '"},
	// T_jahr
	{"<jahr>","<year>"},
	// T_letzten_Import_rueckgaengig
	{"letzten Import rückgängig machen","revert last import"},
	// T_rueck_k
	{"rueck","back"},
	// T_rueck_l
	{"rueck","back"},
	// T_Keine_Dateien_in
	{"Keine Dateien in '","No files found in '"},
	// T_Gefunden
	{"' gefunden!","'!"},
	// T_Erstellt
	{" Erstellt: ","Made: "},
	// T_Dateien_in
	{" Dateien in '"," files found in '"},
	// T_MediaStorageSOPInstanceUID
	{"MediaStorageSOPInstanceUID","MediaStorageSOPInstanceUID"},
	{"",""} 
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=
class TxB Tx((const char* const* const* const*)DPROG_T);
const string& pwk = "8A490qdmjsaop4a89d0qÃ9m0943Ã09Ãax"; // fuer Antlitzaenderung
const DBSTyp myDBS=MySQL;
const int maxconz=1;

// wird aufgerufen in: main
void paramcl::rufpruefsamba()
{
	Log(violetts+Tx[T_rufpruefsamba]);
	vector<const string*> vzn;
	svec abschni,suchs;
	const int ISambaName[4]={T_DicomQuellVz,T_DicomArchivVz,T_DicomZielVz,T_DicomZiel2Vz}; 
	////={&zufaxenvz,&wvz,&nvz,&empfvz};
	if (!qvz.empty()) vzn.push_back(&qvz);
	if (!avz.empty()) vzn.push_back(&avz);
	if (!zvz.empty()) vzn.push_back(&zvz);
	if (!z2vz.empty()) vzn.push_back(&z2vz);
	for(unsigned k=0;k<vzn.size();k++) {
		string suchstr;
		abschni<<Tx[ISambaName[k]];
		Sprache altSpr=Tx.lgn;
		for(int akts=0;akts<SprachZahl;akts++) {
			Tx.lgn=(Sprache)akts;
			suchstr=string("\\[")+Tx[ISambaName[k]]+"\\]\\|";
		} //         for(int akts=0;akts<SprachZahl;akts++)
		Tx.lgn=altSpr;
		suchs<<suchstr;
	} // 	for(unsigned k=0;k<vzn.size();k++)
	pruefsamba(vzn,abschni,suchs,DPROG,duser);
} // pruefsamba


// wird aufgerufen in: main
int paramcl::initDB()
{
	My=new DB(myDBS,linstp,host,muser,mpwd,maxconz,dbn,/*port=*/0,/*unix_socket=*/0,/*client_flag=*/0,obverb,oblog);
 if (My->ConnError) {
  delete My;
	My=0;
 } else {
  My->lassoffen=1;
 }
 return 0;
} // int paramcl::initDB()

void paramcl::pruefdictab()
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
  Feld("MediaStorageSOPInstanceUID","varchar","1","",Tx[T_MediaStorageSOPInstanceUID],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
  Feld("Aufnahmedatum","datetime","0","0",Tx[T_Aufnahmedatum],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
  Feld("Importdatum","datetime","0","0",Tx[T_Importdatum],/*obind=*/1,/*obauto=*/0,/*nnuull=*/1),
 };
 Tabelle tad(My,tbn,felder,sizeof felder/sizeof *felder,/*indices=*/0,/*index size*/0,Tx[T_Tabelle_fuer_dicom_Bilder]);
 if (tad.prueftab(aktc,obverb)) {
  Log(rots+Tx[T_Fehler_beim_Pruefen_von_dictab]+schwarz,1,1);
	exit(11);
 }
} // void paramcl::pruefdictab()

int paramcl::dorueck()
{
	int erg=0;
		char ***cerg;
	RS ldat(My,"select date_format(max(aufnahmedatum),'%Y%m%d_%k%i%S') p0 from fotosinp.dictab",aktc,ZDB);
		if (cerg=ldat.HolZeile(),cerg?*cerg:0) {
			//// <<cjj(cerg,0)<<endl;
		} else {
			erg=10;
		}
 return erg;
}

paramcl::paramcl(const int argc, const char *const *const argv,const int obverb/*=0*/, const int oblog/*=0*/):haupt(argc,argv)
{
	//  akonfdt.clear();
} // paramcl::paramcl()

// wird aufgerufen in: main
void paramcl::getcommandl0()
{
	Log(violetts+"getcommandl0()"+schwarz);
	// Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
	agcnfA.init(17, "language","host","muser","mpwd","dbn","tbn","findvers","duser",
			"cronminut","autoupd","logvz","logdname","oblog","qvz","avz","zvz","z2vz");
	gcl0();
} // void paramcl::getcommandl0(int argc, char** argv)

void paramcl::lieskonfein()
{
	haupt::lieskonfein();
	lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&host); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&muser); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) mpwd=XOR(string(agcnfA[lfd].wert),pwk); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&dbn); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&tbn); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&findvers); else findvers="3"; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&duser); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&cronminut); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&autoupd); else rzf=1; lfd++;
	if (logvneu) agcnfA[lfd].setze(&logvz);
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&logvz); else rzf=1; lfd++;
	if (logdneu) agcnfA[lfd].setze(&logdname);
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&logdname); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&oblog); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&qvz); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&avz); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&zvz); else rzf=1; lfd++;
	if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&z2vz); else rzf=1; lfd++;
	setzlog();
	if (nrzf) rzf=0;
} // void paramcl::lieskonfein()

int paramcl::getcommandline()
{
	Log(violetts+"getcommandline()"+schwarz);
	// s.a. haupt::getcl0()
	////  uchar plusverb=0;
	opts.push_back(/*2*/optioncl(T_host_k,T_host_l,&Tx, T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,0,&host,psons,&agcnfA,"host",&obkschreib));
	opts.push_back(/*2*/optioncl(T_muser_k,T_muser_l,&Tx, T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,0,&muser,psons,&agcnfA,
				"muser",&obkschreib));
	opts.push_back(/*2*/optioncl(T_mpwd_k,T_mpwd_l,&Tx, T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string,0,&mpwd,psons,&agcnfA,"mpwd",&obkschreib));
	opts.push_back(/*2*/optioncl(T_db_k,T_datenbank_l,&Tx, T_verwendet_die_Datenbank_string_anstatt,0,&dbn,psons,&agcnfA,"dbn",&obkschreib));
	opts.push_back(/*2*/optioncl(T_tb_k,T_tb_l,&Tx, T_verwendet_die_Tabelle_string_anstatt,0,&tbn,psons,&agcnfA,"tbn",&obkschreib));
	opts.push_back(/*4*/optioncl(T_find_k,T_find_l,&Tx, T_Version_1_2_oder_3_Dateisuche_anstatt,0,&findvers,pzahl,&agcnfA,"findvers",&obkschreib));
	opts.push_back(/*2*/optioncl(T_duser_k,T_duser_l,&Tx, T_verwendet_fuer_Samba_den_Linux_Benutzer_string_anstatt,0,&duser,psons,
				&agcnfA,"duser",&obkschreib));
	opts.push_back(/*3*/optioncl(T_cm_k,T_cronminuten_l,&Tx,T_Alle_wieviel_Minuten_soll,1,&meinname,T_aufgerufen_werden_0_ist_gar_nicht,&cronminut,
				pzahl, &agcnfA,"cronminut",&obkschreib));
	opts.push_back(/*4*/optioncl(T_autoupd_k,T_autoupd_l, &Tx, T_Programm_automatisch_aktualisieren,1,&autoupd,1,&agcnfA,"autoupd",&obkschreib));
	opts.push_back(/*4*/optioncl(T_rueck_k,T_rueck_l, &Tx, T_letzten_Import_rueckgaengig, 1, &obrueck,1));
	////  opts.push_back(optioncl("l","log", &Tx, T_protokolliert_ausfuehrlich_in_Datei+drot+loggespfad+schwarz+Tx[T_sonst_knapper],0,&oblog,1));
	////  logdt=&loggespfad.front();
	////  opts.push_back(optioncl("lvz","logvz",&Tx, T_waehlt_als_Logverzeichnis_pfad_anstatt,0,&logvz,pverz));
	////  opts.push_back(optioncl("ld","logdname",&Tx, T_logdatei_string_im_Pfad+drot+logvz+schwarz+Tx[T_wird_verwendet_anstatt],0,&logdname,psons));
	////  opts.push_back(optioncl("ldn","logdateinew", &Tx, T_logdatei_vorher_loeschen,0,&logdateineu,1));
	////  opts.push_back(optioncl("v","verbose", &Tx, T_Bildschirmausgabe_gespraechiger,1,&plusverb,1));
	opts.push_back(/*4*/optioncl(T_sqlv_k,T_sql_verbose_l, &Tx, T_Bildschirmausgabe_mit_SQL_Befehlen,1,&ZDB,1));
	opts.push_back(/*4*/optioncl(T_rf_k,T_rueckfragen_l, &Tx, T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigten,1,&rzf,1));
	opts.push_back(/*4*/optioncl(T_krf_k,T_keinerueckfragen_l, &Tx, T_keine_Rueckfragen_zB_aus_Cron,1,&nrzf,1));
	opts.push_back(/*2a*/optioncl(T_qvz_k,T_qvz_l, &Tx, T_Quellverzeichnis_anstatt,1,&qvz,pverz,&agcnfA,"qvz",&obkschreib));
	opts.push_back(/*2a*/optioncl(T_avz_k,T_avz_l, &Tx, T_Archivverzeichnis_anstatt,1,&avz,pverz,&agcnfA,"avz",&obkschreib));
	opts.push_back(/*2a*/optioncl(T_zvz_k,T_zvz_l, &Tx, T_Zielverzeichnis_anstatt,1,&zvz,pverz,&agcnfA,"zvz",&obkschreib));
	opts.push_back(/*2a*/optioncl(T_z2vz_k,T_z2vz_l, &Tx, T_Zweites_Zielverzeichnis_anstatt,1,&z2vz,pverz,&agcnfA,"z2vz",&obkschreib));
	opts.push_back(/*4*/optioncl(T_info_k,T_version_l, &Tx, T_Zeigt_die_Programmversion_an, 1, &zeigvers,1));
	opts.push_back(/*4*/optioncl(T_vi_k,T_vi_l, &Tx, T_Konfigurations_u_Logdatei_bearbeiten_sehen, 1, &obvi,1));
	opts.push_back(/*4*/optioncl(T_vs_k,T_vs_l, &Tx, T_Quelldateien_bearbeiten, 1, &obvs,1));
	opts.push_back(/*4*/optioncl(T_h_k,T_hilfe_l, &Tx, T_Erklaerung_haeufiger_Optionen, 1, &obhilfe,1));
	opts.push_back(/*4*/optioncl(T_lh_k,T_lhilfe_l, &Tx, T_Erklaerung_aller_Optionen, 1, &obhilfe,2));
	opts.push_back(/*4*/optioncl(T_fgz_k,T_fgz_l, &Tx, -1, 1, &obhilfe,1));

	// hier wird die Befehlszeile ueberprueft:
	for(;optslsz<opts.size();optslsz++) {
		for(size_t i=0;i<argcmv.size();i++) {
			if (opts[optslsz].pruefpar(&argcmv,&i,&obhilfe,Tx.lgn)) {
				if (opts[optslsz].kurzi==T_cm_k) { // cronminuten
					keineverarbeitung=1;
					cmeingegeben=1;
				}
				else if (opts[optslsz].kurzi==T_mpwd_k) {
					const string pwdstr=XOR(mpwd,pwk);
					agcnfA.setze(string(Tx[T_mpwd_k]),pwdstr);
				} // 				if (opts[optslsz].kurzi==T_mpwd_k)
				else if (opts[optslsz].kurzi==T_find_k) {
					findv=atol(findvers.c_str());
				} // 				if (opts[optslsz].kurzi==T_find_k)
				break;
			} //       if (opts[optslsz].pruefpar(&argcmv,&i,&obhilfe,Tx.lgn))
		} // for(size_t i=0;i<argcmv.size();i++) 
	} //   for(;optslsz<opts.size();optslsz++)
	if (nrzf||obhilfe==3) rzf=0;
	for(size_t i=0;i<argcmv.size();i++) {
		if (!argcmv[i].agef) {
			::Log(rots+"Parameter: "+gruen+argcmv[i].argcs+rot+Tx[T_nicht_erkannt]+schwarz,1,1);
			if (!obhilfe) obhilfe=1;
		} //     if (!argcmv[i].agef)
	} //   for(size_t i=0;i<argcmv.size();i++)
	Log(string(Tx[T_Fertig_mit_Parsen_der_Befehlszeile])+(obkschreib?Tx[T_ja]:Tx[T_nein]));

	// Ausgabe der Hilfe
	if (obhilfe) {
		if (obhilfe<3) {
			cout<<blau<<Tx[T_Gebrauch]<<drot<<meinname<<" [-<opt>|--<longopt> [<content>]] ..."<<schwarz<<endl; 
			cout<<Tx[T_Liest_Dicom_Dateien_aus]<<blau<<qvz<<schwarz<<Tx[T_speichert_sie_als_png_Bilder_in]<<blau<<zvz<<schwarz<<
				Tx[T_und]<<blau<<z2vz<<vtz<<Tx[T_jahr]<<schwarz<<Tx[T_und_verschiebt_zuletzt_die_Orignale_nach]<<blau<<avz<<schwarz<<endl;
		}
		cout<<blau<<Tx[T_Optionen_die_nicht_gespeichert_werden]<<schwarz<<endl;
		for(size_t j=0;j<opts.size();j++) {
			if (!opts[j].obschreibp && (obhilfe>1 || opts[j].wi))
				opts[j].hilfezeile(Tx.lgn);
		} //     for(size_t j=0;j<opts.size();j++)
		cout<<blau<<Tx[T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden]<<schwarz<<endl;
		for(size_t j=0;j<opts.size();j++) {
			if (opts[j].obschreibp && (obhilfe>1 || opts[j].wi))
				opts[j].hilfezeile(Tx.lgn);
		} //     for(size_t j=0;j<opts.size();j++)
		return 1;
	} // if (obhilfe)
	Log(violetts+Txk[T_Ende]+"getcommandline()"+schwarz);
	return 0;
} // int paramcl::getcommandline()


constexpr const unsigned datcl::dim;
constexpr const char *datcl::knz[dim];
constexpr const unsigned datcl::pnnr, datcl::itnr, datcl::rpnr, datcl::tdnr, datcl::pfnr, datcl::adnr;

ulong datcl::inDB(paramcl& pm,const int& aktc)
{
	ulong zl=0;
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
						} // 								if (p2!=string::npos)
					} // 							if (p1!=string::npos)
				} // 						if (ir[zl].find(knz[j])!=string::npos)
			} // 					if (ord[j].empty())
		} // 				for(unsigned j=0;j<dim;j++)
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
			} // 			for(unsigned jj=0;jj<ord[j].length();jj++)
		} // 		if (j==pnnr || j==pfnr)
	} // 	for(unsigned j=0;j<dim;j++)
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
	einf.push_back(instyp(pm.My->DBS,"ProcessingFunction",&ord[pfnr]));
	einf.push_back(instyp(pm.My->DBS,"MediaStorageSOPInstanceUID",&ord[uidnr]));
	if (ord[adnr].empty()) {
		struct stat st={0};
		if (!lstat(name.c_str(),&st)) {
			memcpy(&tma,localtime(&st.st_mtime),sizeof tma);
		}
	} else {
		strptime(ord[adnr].c_str(),"%Y%m%d%H%M%S",&tma);
	}
	einf.push_back(instyp(pm.My->DBS,"Aufnahmedatum",&tma));
	einf.push_back(instyp(pm.My->DBS,"Importdatum",&pm.jt));
	if (ord[adnr].length()>7) ord[adnr].insert(8,"_");
	svec eindfeld;
	eindfeld<<"PatientName";
	eindfeld<<"Geburtsdatum";
	eindfeld<<"PatientID";
	eindfeld<<"Aufnahmedatum";
	eindfeld<<"MediaStorageSOPInstanceUID";
	int ZDB=(pm.obverb?pm.obverb-1:0);
	zl=rins.tbins(pm.tbn,einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,&id,/*eindeutig=*/0,eindfeld);
	pm.dbz+=zl;
	Log("ID: '"+violetts+id+schwarz+"', affected rows: "+violett+ltoan(zl)+schwarz,pm.obverb,pm.oblog);
	return zl;
} // void datcl::inDB(paramcl& pm., const int& aktc)


datcl::datcl(string& name): name(name)
{
}

// aufgerufen in main
void datcl::aufPlatte(paramcl& pm,const int& aktc,const size_t& nr)
{
	for(unsigned j=0;j<dim;j++) {
		if (j!=itnr && j!=rpnr) {
			if (j==uidnr && ord[j].length()>10) { // die Nummer is a bisserl z lang, der hintere Teil is guad
				bname+=ord[j].substr(ord[j].length()-10);
			} else {
				bname+=ord[j];
			}
			if (j<dim-1) bname+='_';
		} // 			if (j!=itnr && j!=rpnr)
	} // 		for(int j=0;j<dim;j++)
	if (id.empty()) {
		Log(rots+bname+schwarz+" schon da!",pm.obverb,pm.oblog);
	} else {
		const string neuname=pm.zvz+"/"+bname+".png";
		for(int iru=0;iru<2;iru++) {
			svec srueck;
			systemrueck("dcmj2pnm +on2 '"+name+"' > '"+neuname+"'",pm.obverb,pm.oblog,&srueck);
			if (srueck.size()) {
				if (srueck[0].find("no version information")==string::npos)
							break;
			} else {
				break;
			}
			// hier dcmt installieren
		} // 		for(int iru=0;iru<2;iru++)
		struct stat nst={0};
		if (!lstat(neuname.c_str(),&nst)) {
			::Log(blaus+ltoan(nr)+schwarz+") "+Tx[T_Erstellt]+blau+neuname+schwarz,1,pm.oblog);
			pm.umz++;
			const string jahr=ord[adnr].substr(0,4);
			tma.tm_isdst=-1;
			time_t modz=mktime(&tma);
			struct utimbuf ub={0};
			ub.modtime=modz;
			ub.actime=modz;
			if (utime(neuname.c_str(),&ub)) {
				Log(rots+Tx[T_Fehler_beim_Datumsetzen_von]+blau+neuname+"'"+schwarz,pm.obverb,pm.oblog);
			}
			uid_t duid;
			gid_t dgid;
			untersuser(pm.duser,&duid,&dgid);
			systemrueck("chown "+pm.duser+":"+ltoan(dgid)+" '"+neuname+"'",pm.obverb,pm.oblog);
			const string z2vzj=pm.z2vz+vtz+jahr;
			if (!pruefverz(z2vzj,pm.obverb,pm.oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/pm.duser,/*benutzer=*/pm.duser,/*obmachen=*/1)) {
				const string cmd="cp -a '"+neuname+"' '"+z2vzj+"'";
				pm.u2z+=!systemrueck(cmd,pm.obverb,pm.oblog);
			} // 			if (!pruefverz(z2vzj,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1))
		} else {
			RS weg(pm.My,"DELETE FROM `"+pm.tbn+"` WHERE ID="+id,aktc,ZDB);
		} // 		if (!lstat(neuname.c_str(),&nst)) else
		//		systemrueck("touch -r '"+rueck[nr]+"' '"+neuname+"'",pm.obverb,pm.oblog); // = zu spaet
		if (gibaus)
			Log(bname,pm.obverb,pm.oblog);
		Log(Tx[T_Nr]+blaus+ltoan(nr)+schwarz+", "+blau+name+schwarz+" "+blau+(ir.size()?ir[0]:"")+schwarz,pm.obverb,pm.oblog);
	} // 			if (id.empty())
} // void datcl::aufPlatte(paramcl& pm,const int& aktc,const size_t& nr)

// Musterfunktion, die von einer Funktion in gesonderter,fakultativer Datei,z.B. 'vgb.cpp' ueberschrieben werden kann
void paramcl::MusterVorgb() 
{
	Log(violetts+Tx[T_VorgbSpeziell]+schwarz);
	setzbenutzer(&duser);
	findvers="3";
	qvz="/var/spool/dicomneu";
	avz="/var/spool/dicomalt";
	zvz="/var/spool/dicomziel";
	z2vz="/var/spool/dicomziel2";
} // void paramcl::MusterVorgb() 

// Musterfunktion, die von einer Funktion in gesonderter,fakultativer Datei,z.B. 'vgb.cpp' ueberschrieben werden kann
void paramcl::VorgbSpeziell() 
{
	Log(violetts+Txk[T_VorgbSpeziell]+schwarz);
	MusterVorgb();
} // void paramcl::VorgbSpeziell() 

void paramcl::schlussanzeige()
{
	::Log(blaus+ltoan(dcz,10,0,5)+schwarz+Tx[T_Dicom_Dateien]+blau+qvz+schwarz+Tx[T_gefunden],1,1);
	::Log(blaus+ltoan(dbz,10,0,5)+schwarz+Tx[T_Datensaetze_in_Tabelle]+blau+tbn+schwarz+Tx[T_in_Datenbank]+blau+dbn+schwarz+Tx[T_eingetragen],1,1);
	::Log(blaus+ltoan(umz,10,0,5)+schwarz+Tx[T_Dateien_in_Verzeichnis]+blau+zvz+schwarz+Tx[T_erstellt],1,1);
	::Log(blaus+ltoan(u2z,10,0,5)+schwarz+Tx[T_Dateien_in_Verzeichnis]+blau+z2vz+vtz+Tx[T_jahr]+schwarz+Tx[T_kopiert],1,1);
	::Log(blaus+(pfehler?Tx[T_Keine]:Tx[T_Alle])+schwarz+Tx[T_Dateien_von]+blau+qvz+schwarz+Tx[T_nach_]+blau+avz+vtz+impvz+schwarz+Tx[T_verschoben],1,1);
	haupt::schlussanzeige();
} // void paramcl::schlussanzeige()

void paramcl::machimpvz()
{
	time_t jetzt;
	time(&jetzt);
	memcpy(&jt,localtime(&jetzt),sizeof jt);
	strftime(impvz,16,"%Y%m%d_%H%M%S",&jt);
	nvz=avz+vtz+impvz;
} // void paramcl::machimpvz()

void paramcl::pruefimpvz()
{
		pfehler= pruefverz(nvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1);
} // void paramcl::pruefimpvz()

void paramcl::verschieb()
{
	if (!pfehler) {
		const string cmd="mv -n '"+qvz+vtz+"'* '"+nvz+vtz+"'";
		pfehler=systemrueck(cmd,obverb,oblog);
	} // 	if (!pfehler) 
} // void paramcl::verschieb()

// wird aufgerufen in: main
void paramcl::pruefggfmehrfach()
{
	if (!obhilfe &&!obvi &&!obvs
			&&!zeigvers && suchstr.empty() &&!anhl ) {
		pruefmehrfach(meinname,nrzf);
	}
} // void paramcl::pruefggfmehrfach()

void paramcl::pruefdcmj()
{
}

void paramcl::rueckfragen()
{
	Log(violetts+Tx[T_rueckfragen]+schwarz);
	if (rzf) {
		int lfd=-1;
		const char *const locale = setlocale(LC_CTYPE,"");
		if (langu.empty()) if (locale) if (strchr("defi",locale[0])) langu=locale[0];
		vector<string> sprachen={"e","d"/*,"f","i"*/};
		if (agcnfA[++lfd].wert.empty() || rzf) {
			langu=Tippstrs(sprachstr.c_str()/*"Language/Sprache/Lingue/Lingua"*/,&sprachen, &langu);
			lgnzuw();
			agcnfA[lfd].setze(&langu);
		} //     if (agcnfA[++lfd].wert.empty() || rzf)
		if (agcnfA[++lfd].wert.empty() || rzf) {
			host=Tippstr(Tx[T_Host_fuer_MySQL_MariaDB_Datenbank],&host);
			agcnfA[lfd].setze(&host);
		} //     if (agcnfA[++lfd].wert.empty() || rzf)
		if (agcnfA[++lfd].wert.empty() || rzf) {
			const string Frage=Tx[T_Benutzer_fuer_MySQL_MariaDB];
			muser=Tippstr(Frage.c_str(),&muser);
			agcnfA[lfd].setze(&muser);
		} //     if (agcnfA[++lfd].wert.empty() || rzf)
		if (agcnfA[++lfd].wert.empty() || rzf) {
			string mpw2;
			mpwd.clear();
			while (1) {
				mpwd=Tippstr(string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Txk[T_fuer_Benutzer]+dblau+muser+schwarz+"'",&mpwd);
				mpw2=Tippstr(string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Txk[T_fuer_Benutzer]+dblau+muser+schwarz+"'"+" ("+Txk[T_erneute_Eingabe]+")",&mpw2);
				if (mpwd==mpw2) break;
			} //         while (1)
			while (mpwd.empty());
			const string pwdstr=XOR(mpwd,pwk);
			agcnfA[lfd].setze(&pwdstr);
		} // 		if (agcnfA[++lfd].wert.empty() || rzf)
		if (agcnfA[++lfd].wert.empty() || rzf) {
			dbn=Tippstr(string(Tx[T_Datenbankname_fuer_MySQL_MariaDB_auf])+dblau+host+schwarz+"'",&dbn);
			agcnfA[lfd].setze(&dbn);
		} //     if (agcnfA[++lfd].wert.empty() || rzf)
		if (agcnfA[++lfd].wert.empty() || rzf) {
			tbn=Tippstr(string(Tx[T_Tabellenname_fuer_MySQL_MariaDB_in])+dblau+dbn+schwarz+"'",&tbn);
			agcnfA[lfd].setze(&tbn);
		} //     if (agcnfA[++lfd].wert.empty() || rzf)
		if (agcnfA[++lfd].wert.empty() || rzf) {
			findvers="3";
			ifindv=findv=atol(findvers.c_str());
			agcnfA[lfd].setze(&findvers);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			////        string bliste, tmpcuser;
			setzbenutzer(&duser);
			duser=Tippstrs(Tx[T_Linux_Benutzer_fuer_Verzeichnisse],&benutzer,&duser);
			agcnfA[lfd].setze(&duser);
		} // if (agcnfA[++lfd].wert.empty() || rzf) 
		if (agcnfA[++lfd].wert.empty() || rzf) {
			cronminut=Tippzahl(Tx[T_Alle_wieviel_Minuten_soll]+meinname+Tx[T_aufgerufen_werden_0_ist_gar_nicht],&cronminut);
			agcnfA[lfd].setze(&cronminut);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			autoupd=Tippob(Tx[T_Sollen_neue_Programmversionen_von]+meinname+Tx[T_automatisch_installiert_werden],autoupd?Txk[T_j_af]:"n");
			agcnfA[lfd].setze(&autoupd);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			logvz=Tippverz(Tx[T_Logverzeichnis],&logvz);
			agcnfA[lfd].setze(&logvz);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			logdname=Tippstr(Tx[T_Logdateiname],&logdname);
			agcnfA[lfd].setze(&logdname);
		}
		loggespfad=string(logvz)+vtz+logdname;
		logdt=&loggespfad.front();
		if (agcnfA[++lfd].wert.empty() || rzf) {
			oblog=Tippzahl(Tx[T_Oblog],oblog);
			agcnfA[lfd].setze(&oblog);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			qvz=Tippverz(Tx[T_Verzeichnis_mit_unverarbeiteten_Dicom_Dateien],&qvz);
			agcnfA[lfd].setze(&qvz);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			avz=Tippverz(Tx[T_Verzeichnis_mit_archivierten_Dicom_Dateien],&avz);
			agcnfA[lfd].setze(&avz);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			zvz=Tippverz(Tx[T_Verzeichnis_mit_verarbeiteten_Dicom_Dateien],&zvz);
			agcnfA[lfd].setze(&zvz);
		}
		if (agcnfA[++lfd].wert.empty() || rzf) {
			z2vz=Tippverz(Tx[T_2_Verzeichnis_mit_verarbeiteten_Dicom_Dateien],&z2vz);
			agcnfA[lfd].setze(&z2vz);
		}
	} // if (rzf)
	// die Verzeichnisnamen standardisieren
	kuerzevtz(&qvz);
	kuerzevtz(&avz);
	kuerzevtz(&zvz);
	kuerzevtz(&z2vz);
	kuerzevtz(&logvz);
} // void paramcl::rueckfragen()

void paramcl::verzeichnisse()
{
	Log(violetts+Tx[T_verzeichnisse]);
	pruefverz(qvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1);
	pruefverz(avz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1);
	pruefverz(zvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1);
	pruefverz(z2vz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/duser,/*benutzer=*/duser,/*obmachen=*/1);
} // paramcl:: verzeichnisse()

// wird aufgerufen in: main
void paramcl::autofkonfschreib()
{
	Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Tx[T_ja]:Tx[T_nein]));
	if (rzf||obkschreib) {
		Log(gruens+Tx[T_schreibe_Konfiguration]+schwarz);
		schlArr *ggcnfAp[1]={&agcnfA};
		multischlschreib(akonfdt, ggcnfAp, sizeof ggcnfAp/sizeof *ggcnfAp, mpfad);
	} // if (rzf||obkschreib) 
} // void paramcl::autofkonfschreib()


int main(int argc, char** argv)
{
	//// <<TIFFGetVersion()<<endl;
	paramcl pm(argc,argv,/*obverb=*/0,/*oblog=*/0); // Programmparameter
	if (0) {
		caus<<pm.progvers("dcmdump")<<endl;
		caus<<pm.progvers("dcmj2pnm")<<endl;
		caus<<pm.progvers("unpaper")<<endl;
		caus<<pm.progvers("/root/autofax/ocrv/bin/ocrmypdf")<<endl;
		caus<<pm.progvers("python3")<<endl;
	}
	pm.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
	if (pm.obhilfe==3) { // Standardausgabe gewaehrleisten
		pm.MusterVorgb();
	} else {
		pm.VorgbSpeziell();//die Vorgaben, die in einer zusaetzlichen Datei mit einer weiteren Funktion "void paramcl::VorgbSpeziell()" ueberladbar sind
		pm.lieskonfein();
	}
	pm.lieszaehlerein(&pm.aufrufe,&pm.tagesaufr,&pm.monatsaufr,&pm.laufrtag);

	if (pm.getcommandline()) 
		exit(8); // Hilfe angezeigt
	if (pm.obvi) pm.dovi(); 
	if (pm.obvs) exit(systemrueck("cd \""+instvz+"\"; sh viall"+devtty,/*obverb=*/0,/*oblog=*/0,/*rueck=*/0,/*obsudc=*/1));
	if (pm.zeigvers) {
		pm.zeigversion();
		pm.zeigkonf();
		Log(violetts+Txk[T_Ende]+Tx[T_zeigvers]+schwarz,pm.obverb,pm.oblog);
		exit(7);
	} //   if (pm.zeigvers)
//	pm.pruefcron(); // soll vor Log(Tx[T_Verwende ... stehen
	if (!pm.keineverarbeitung) {
		pm.pruefdcmj();
		// Rueckfragen koennen auftauchen in: rueckfragen, rufpruefsamba
		pm.rueckfragen();
		// als Kompromiss blockieren wir hier
		pm.pruefggfmehrfach();
		pm.verzeichnisse();
		if (!pm.anhl && pm.suchstr.empty())
			pm.rufpruefsamba();

		if (pm.logdateineu) tuloeschen(logdt,"",pm.obverb,pm.oblog);
		pm.Log(Tx[T_Logpfad]+drots+pm.loggespfad+schwarz+Tx[T_oblog]+drot+ltoan((int)pm.oblog)+schwarz+")");
		if (pm.initDB())
			return 10;
		// pruefe Tabelle <spooltab> und stelle sie ggf. her
		pm.pruefdictab();
	} // 	if (!pm.keineverarbeitung)
	//	pruefverz(zvz,obverb,0,1,1,"sturm","sturm");
	if (pm.initDB())
		return 10;
	if (!pm.My) exit(5); // Datenbankverbindung nicht erstellbar
	if (pm.obrueck) 
		return pm.dorueck();
	pm.machimpvz();
	svec rueck;
	systemrueck("find "+pm.qvz+" -type f -not -path '*\\.*' -not -path '*DICOMDIR*'",pm.obverb,pm.oblog,&rueck);
	if (!rueck.size()) {
	 Log(rots+Tx[T_Keine_Dateien_in]+blau+pm.qvz+rot+Tx[T_Gefunden]+schwarz,1,0);
	 pm.pfehler=1;
	} else {
		pm.pruefimpvz();
		pm.dcz=rueck.size();
		Log(blaus+ltoan(rueck.size())+schwarz+Tx[T_Dateien_in]+blau+pm.qvz+schwarz+Tx[T_Gefunden],1,0);
		for(size_t nr=0;nr<rueck.size();nr++) {
			datcl dat(rueck[nr]);
			if (dat.inDB(pm,pm.aktc))
			dat.aufPlatte(pm,pm.aktc,nr);
		} // 	for(size_t nr=0;nr<rueck.size();nr++)
		pm.verschieb();
	} // 	if (!rueck.size())
	pm.autofkonfschreib();
	// ggf. beim 2. Aufruf am Tag Update installieren
	if (pm.autoupd && pm.tagesaufr == 2) {
		pm.update(DPROG);
	} // 	if (pm.autoupd && pm.tagesaufr == 2)
	pm.schlussanzeige();
	Log(violetts+Txk[T_Ende]+schwarz,pm.obverb,pm.oblog);
	return pm.pfehler;
} // int main(int argc, char** argv)
