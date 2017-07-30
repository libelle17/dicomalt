#include "kons.h"
#include "DB.h"
#define caus cout // nur zum Debuggen
#define caup cout // zum Debuggen von Postgres

//const char *Txdbcl::TextC[T_dbMAX+1][SprachZahl]={
const char *DB_T[T_dbMAX+1][SprachZahl]={
  // T_DB_wird_initialisiert
  {"DB wird initialisiert","DB is being initialized"},
  // T_Fehler_db
  {"Fehler ","Error "},
  // T_beim_Initialisieren_von_MySQL
  {" beim Initialisieren von MySQL: "," initializing MySQL: "},
  // T_Fehler_dp
  {"Fehler: ","Error: "},
  // T_bei_Befehl
  {" bei Befehl: "," at command: "},
  // T_Versuche_mysql_zu_starten
  {": => Versuche mysql zu starten ...",": => trying to start mysql ..."},
  // T_MySQL_erfolgreich_gestartet
  {"MySQL erfolgreich gestartet.","Started MySQL successfully."},
  // ": => Versuche Datenbank `"
  {": => Versuche Datenbank `",": => Trying to install database `"},
  // T_zu_erstellen
  {"` zu erstellen ...","` ..."},
  // T_Fehler_beim_Verbinden
  {"Fehler beim Verbinden: ","Error connecting: "},
  // T_Erfolg_beim_Initialisieren_der_Verbindung_zu_mysql
  {"Erfolg beim Initialisieren der Verbindung zu MySQL!","Success initializing the connection to MySQL!"},
	// T_MySQL_Passwort
	{"MySQL-Passwort","MySQL password"},
	// T_fuer_Benutzer
	{" fuer Benutzer '"," for user '"},
	// T_wird_benoetigt_fuer_Befehl
	{"' (wird benoetigt fuer Befehl: ","' (is needed for command: "},
  // T_ist_leer_Wollen_Sie_eines_festlegen
  {"' ist leer. Wollen Sie eines festlegen?", "' is empty. Do You want to give one?"},
  // T_j
  {"j","y"},
  // T_Bitte_geben_Sie_ein_MySQL_Passwort_fuer_Benutzer_root_ein
  {"Bitte geben Sie ein MySQL-Passwort fuer Benutzer 'root' ein: ","Please indicate a mysql password for user 'root': "},
  // T_Fuehre_aus_db
  {"Fuehre aus: ","Executing: "},
  // T_falsche_Fehlernr
  {"falsche Fehlernr ","wrong Errorno "},
  // T_bei_der_Abfrage_der_Spaltenlaenge_bei_Tabelle
  {" bei der Abfrage der Spaltenlaenge bei Tabelle: "," during query of the column width at table: "},
  // T_und_Feld,
  {" und Feld: "," and field: "},
  // T_mit
  {" mit: "," with: "},
  // T_bei_Abfrage
  {" bei Abfrage: "," in query: "},
  // T_Fehler_beim_Pruefen_auf_Vorhandensein_des_Datensatzes
  {"Fehler beim Pruefen auf Vorhandensein des Datensatzes: ","Error while checking the existence of entry: "},
  // T_Datenbank_nicht_zu_oeffnen
  {"Datenbank nicht zu oeffnen","could not open database"},
  // T_Erweitere_Feld
  {"Erweitere Feld: ","Enlarging field: "},
  // T_von
  {" von: "," from: "},
  // T_auf
  {" auf: "," to: "},
  // T_Aendere_Feld
  {"Aendere Feld: ","Changing field: "},
  // T_Pruefe_Tabelle
  {"Pruefe Tabelle: '","Checking table: '"},
  // T_Lesespalten
  {"lesespalten()","readcolumns()"},
	// T_Vor_restart
	{"Vor restart, ","Before restart, "},
	// T_Versuch_Nr
	{"Versuch Nr. ","try no. "},
	// T_bei_sql_Befehl
	{" bei sql-Befehl: "," at sql-command: "},
	// T_PostgreSQL_musste_neu_eingerichtet_werden
	{"PostgreSQL musste neu eingerichtet werden. ",
	 "Postgresql had to be installed newly. "},
	// T_Bitte_geben_Sie_ein_Passwort_fuer_Benutzer_postgres_ein
	{"Bitte geben Sie das Passwort fuer Benutzer `postgres` ein",
	 "Please enter the password for user `postgres`"},
	// T_Welches_Passwort_soll_der_Benutzer_postgres_haben
	{"Welches Passwort soll der Benutzer `postgres` haben",
   "Which password shall the user `postgres` have"},
	// T_Ende_Gelaende
	{"Ende Gelaende!","That's it!"},
	// T_Verbindung_zu
	{"Verbindung zu '","Connection to '"},
	// T_gelungen
	{"' gelungen, user '","' succeeded, user '"},
	// T_prueffunc
	{"prueffunc()","checkfunc()"},
	{"",""}
};
// Txdbcl::Txdbcl() {TCp=(const char* const * const * const *)&TextC;}
// class Txdbcl Txd;
// class TxB Txd(DB_T);
class TxB Txd((const char* const* const* const*)DB_T);

// Datenbanknamen aus sql-String extrahieren
svec holdbaussql(string sql) 
{
  svec erg;
  string db;
  size_t runde=0;
  while (1) {
    runde++;
    string SQL;
    transform(sql.begin(),sql.end(),std::back_inserter(SQL),::toupper);
    size_t pfrom=SQL.find("FROM ");
    size_t pjoin=SQL.find("JOIN ");
    size_t ab=pfrom<pjoin?pfrom:pjoin;
    if (ab!=string::npos) {
      ab+=5;
      size_t bis=string::npos;
      if (sql[ab]=='`' || sql[ab]=='[' || sql[ab]=='\"') ab++;
      bis=SQL.find_first_of((string(" .,;()'\"`]:{}")+(char)9+(char)10+(char)13).c_str(),ab);
      if (bis!=string::npos) 
        db=sql.substr(ab,bis-ab);
      else
        db=sql.substr(ab);
      if (!db.empty()) {
        uchar alt=0;
        for(size_t j=0;j<erg.size();j++) {
          if (erg[j]==db) {alt=1;break;}
        }
        if (!alt) erg<<db;
      } // if (!db.empty()) 
      if (bis==string::npos) break;
      sql=sql.substr(bis);
    } else break; // if (ab!=string::npos) 
  } // while (1)
  return erg;
} // holdbaussql

Feld::Feld()
{}

Feld::Feld(const string& name, string typ/*=""*/, const string& lenge/*=""*/, const string& prec/*=""*/, 
    const string& comment/*=""*/, bool obind/*=0*/, bool obauto/*=0*/, bool nnull/*=0*/, const string& vdefa/*=""*/, bool unsig/*=0*/):
  name(name)
  ,typ(typ)
  ,lenge(lenge)
  ,prec(prec)
  ,comment(comment)
  ,obind(obind)
  ,obauto(obauto)
  ,nnull(nnull)
  ,defa(vdefa) // Namensdifferenz hier noetig, sonst wird im Konstruktur die falsche Variable bearbeitet
  ,unsig(unsig)
{
  if (!obauto) if (defa.empty()) {
    transform(typ.begin(),typ.end(),typ.begin(),::toupper);
    if (typ.find("INT")!=string::npos || typ=="LONG" || typ=="DOUBLE" ||typ=="FLOAT"  )
      defa="0";
    else if (typ=="DATE" || typ=="DATETIME" || typ=="TIME" ||typ=="TIMESTAMP")
      defa="0000-00-00";
    else if (typ=="YEAR")
      defa="0000";
		else
		  defa=""; // char- usw.Felder
  }
} // Feld(const string& name, const string& typ, const string& lenge, const string& prec, string comment, bool vind, bool vobauto, bool vnnull, string vdefa):

// Feld::Feld(Feld const& copy) { }


Index::Index(const string& name, Feld *felder, int feldzahl) :
  name(name),
  feldzahl(feldzahl),
  felder(felder)
{}

  Tabelle::Tabelle(const std::string& name, Feld *vfelder, int vfeldzahl, Index *vindices, int vindexzahl, string comment, const string& engine,
                   const string& charset, const string& collate, const string& rowformat)
:   name(name),
  comment(comment),
  felder(vfelder),
  feldzahl(vfeldzahl),
  indices(vindices),
  indexzahl(vindexzahl),
  engine(engine),
  charset(charset),
  collate(collate),
  rowformat(rowformat)
{
}

// statische Variable, 1= mariadb=geprueft
uchar DB::oisok=0;

DB::DB(linst_cl *linstp):linstp(linstp)
{
}

DB::DB(DBSTyp nDBS, linst_cl *linstp, const string& phost, const string& puser, const string& ppasswd, size_t conz, const string& uedb, 
       unsigned int port, const char *const unix_socket, unsigned long client_flag,
    int obverb,int oblog,int versuchzahl, uchar ggferstellen):linstp(linstp),conz(conz)
{
  init(nDBS,phost.c_str(),puser.c_str(),ppasswd.c_str(),conz,uedb.c_str(),port,unix_socket,client_flag,obverb,oblog,versuchzahl,
  ggferstellen);
} // DB::DB(DBSTyp nDBS, linst_cl *linstp, const string& phost, const string& puser, const string& ppasswd, size_t conz, const string& uedb

DB::DB(DBSTyp nDBS, linst_cl *linstp, const char* const phost, const char* const puser,const char* const ppasswd, 
      const char* const prootpwd, size_t conz, const char* const uedb, unsigned int port, const char *const unix_socket, unsigned long client_flag,
		  int obverb,int oblog, int versuchzahl, uchar ggferstellen): linstp(linstp),rootpwd(prootpwd),conz(conz)
{
  init(nDBS,phost,puser,ppasswd,conz,uedb,port,unix_socket,client_flag,obverb,oblog,versuchzahl,ggferstellen);
}

DB::DB(DBSTyp nDBS, linst_cl *linstp, const char* const phost, const char* const puser,const char* const ppasswd, size_t conz, const char* const uedb, 
       unsigned int port, const char *const unix_socket, unsigned long client_flag,int obverb,int oblog,int versuchzahl,uchar ggferstellen)
			 :linstp(linstp),conz(conz)
{
  init(nDBS,phost,puser,ppasswd,conz,uedb,port,unix_socket,client_flag,obverb,oblog,versuchzahl,ggferstellen);
}

// 2 x in DB::init
void DB::instmaria(int obverb, int oblog)
{
	if (linstp->ipr==apt) {
		systemrueck(sudc+"sh -c 'apt-get -y install apt-transport-https; apt-get update && DEBIAN_FRONTEND=noninteractive apt-get --reinstall install -y mariadb-server'",1,1);
	} else {
		linstp->doinst("mariadb",obverb,oblog);
		if (linstp->ipr==pac)
		 systemrueck(sudc+"mysql_install_db --user="+mysqlben+" --basedir=/usr/ --ldata=/var/lib/mysql",obverb,oblog);
	} // 					if (ipr==apt) else
} // void DB::instmaria()

void DB::init(DBSTyp nDBS, const char* const phost, const char* const puser,const char* const ppasswd, const size_t conz/*=1*/, 
							const char* const uedb/*=""*/, unsigned int port/*=0*/, const char *const unix_socket/*=NULL*/, 
							unsigned long client_flag/*=0*/,int obverb/*=0*/,int oblog/*=0*/,unsigned versuchzahl/*=3*/, uchar ggferstellen/*=1*/)
{
	DBS = nDBS;
	fehnr=0;
	string Frage;
	Log(Txd[T_DB_wird_initialisiert],obverb>1,oblog);
	host=phost;
	user=puser;
	passwd=ppasswd;
	uchar installiert=0;
	uchar datadirda=0;
	const string mysqld="mysqld";
	switch (DBS) {
		case MySQL:
#ifdef linux
			switch (linstp->ipr) {
				case zypper: case apt:
					db_systemctl_name="mysql";
					break;
				case dnf: case yum:
					db_systemctl_name="mariadb";
					break;
				default: break;
			} //       switch (ipr)
			if (!dbsv) dbsv=new servc(db_systemctl_name,mysqld,obverb,oblog);
			if (!oisok) {
				// schauen, ob die Exe-Datei da ist 
				for (int iru=0;iru<2;iru++) {
					installiert=1;
					// wenn nicht gefunden ...
					if (!obprogda(mysqld,obverb,oblog)) {
						svec frueck;
						// .. und auch hier nicht gefunden ...
						systemrueck("find /usr/sbin /usr/bin /usr/libexec -executable -size +1M -name "+mysqld,obverb,oblog, &frueck);
						if (!frueck.size()) 
							// .. dann wohl nicht installiert
							installiert=0;
					} //           if (!obprogda("mysqld",obverb,oblog))
					if (installiert) {
						if (!obprogda(mysqlbef,obverb,oblog))
							installiert=0;
						else if (systemrueck("grep \"^"+mysqlben+":\" /etc/passwd",obverb,oblog))
							installiert=0;
						else if (systemrueck(mysqlbef+" -V",obverb,oblog))
							installiert=0;
					} //           if (installiert)
					if (installiert) break;
					instmaria(obverb, oblog);
				} //         for (int iru=0;iru<2;iru++)
				// Datenverzeichnis suchen und pruefen
				if (installiert) {
					svec zrueck;
					if (!systemrueck("sed 's/#.*$//g' `"+mysqlbef+" --help | sed -n '/Default options/{n;p}'` 2>/dev/null "
								"| grep datadir | cut -d'=' -f2",obverb,oblog,&zrueck)) {
						if (zrueck.size()) {
							datadir=zrueck[zrueck.size()-1];  
						} else {
							svec zzruck, zincldir;
							systemrueck("find /etc /etc/mysql ${MYSQL_HOME} -name my.cnf -printf '%p\\n' -quit", obverb,oblog,&zzruck);
							if (!zzruck.size())
								systemrueck("find "+gethome()+" -name .my.cnf -printf '%p\\n' -quit",obverb,oblog,&zzruck);
							if (zzruck.size()) {
								systemrueck(sudc+"cat "+zzruck[0]+" | sed 's/#.*$//g' | grep '!includedir' | sed 's/^[ \t]//g' | cut -d' ' -f2-", 
										obverb,oblog,&zincldir); 
								for(size_t i=0;i<zincldir.size();i++) {
									svec zzruck2;
									systemrueck(sudc+"find "+zincldir[i]+" -not -type d",obverb,oblog,&zzruck2); // auch links
									for(size_t i=0;i<zzruck2.size();i++) {
										zzruck<<zzruck2[i];
									}
								} //                 for(size_t i=0;i<zincldir.size();i++)
							} //               if (zzruck.size())
							if(zzruck.size()) {
								for(size_t i=0;i<zzruck.size();i++) {
									svec zrueck;
									if (!systemrueck((sudc+"sed 's/#.*$//g' '")+zzruck[i]+"' | grep datadir | cut -d'=' -f2",
												obverb,oblog,&zrueck)) {
										if (zrueck.size()) {
											datadir=zrueck[zrueck.size()-1];  
											break;
										} // if (zrueck.size()) 
									} // if (!systemrueck(("cat ")+zzruck[i]+" | sed 's/#.*$//g' | grep datadir | cut -d'=' -f2",obverb-1,oblog,&zrueck)) 
								} // for(size_t i=0;i<zzruck.size();i++) 
							} // if(zzruck.size()) 
						} // if (zrueck.size()) else
					} // if (!systemrueck("sed 's/#.*$//g' `"+mysqlbef+"--help | sed -n '/Default options/KLAn;pKLZ'` 2>/dev/null " ...
					gtrim(&datadir);
					if (datadir.empty()) {
						datadir="/var/lib/mysql";
					}
					if (obverb) Log("datadir: "+blaus+datadir+schwarz,obverb,oblog);
					struct stat datadst={0};
					if (!lstat(datadir.c_str(), &datadst)) {
						if(S_ISDIR(datadst.st_mode)) {
							datadirda=1;
						} else {
							systemrueck(sudc+"rm -f '"+datadir+"'",1,1);
						}
					} //           if (!lstat(datadir.c_str(), &datadst))
					if (!datadirda) {
						systemrueck(sudc+"`find /usr/local /usr/bin /usr/sbin -name mysql_install_db"+string(obverb?"":" 2>/dev/null")+"`",1,1);
						dbsv->start(obverb,oblog);
					}
					oisok=1;
				} // if (installiert)
			} // if (!oisok)

#endif
			conn=new MYSQL*[conz];
			this->ConnError=NULL;
			for(size_t aktc=0;aktc<conz;aktc++) {
				conn[aktc] = mysql_init(NULL);
				if (!conn[aktc]) {
					this->ConnError=mysql_error(conn[aktc]);
					cerr<<Txd[T_Fehler_db]<<mysql_errno(conn[aktc])<<Txd[T_beim_Initialisieren_von_MySQL]<<this->ConnError<<endl;
				} else {
					RS *rs;
					for(unsigned versuch=0;versuch<versuchzahl;versuch++) {
						fehnr=0;
						if (mysql_real_connect(conn[aktc], host.c_str(), user.c_str(), passwd.c_str(), uedb, port, unix_socket, client_flag)) {
							break;
						} else {
							switch ((fehnr=mysql_errno(conn[aktc]))) {
								case 1044: // Access denied for user '<user>'@'<host>' to database '...' (Ubuntu)
								case 1045: // Access denied for user '<user>'@'<host>' (using password: YES)
								case 1698: // dasselbe auf Ubuntu
									for(unsigned aru=0;aru<1;aru++) {
										for(unsigned iru=0;iru<2;iru++) {
											cmd=sudc+mysqlbef+" -uroot -h'"+host+"' "+(rootpwd.empty()?"":"-p"+rootpwd)+" -e \"GRANT ALL ON "+uedb+".* TO '"+
												user+"'@'"+myloghost+"' IDENTIFIED BY '"+ersetze(passwd.c_str(),"\"","\\\"")+"' WITH GRANT OPTION\" 2>&1";
											if (iru) break;
											pruefrpw(cmd, versuchzahl);
										} //                   for(unsigned iru=0;iru<2;iru++) 
										myr.clear();
										systemrueck(cmd,1,1,&myr);
										miterror=1;
										if (!myr.size()) miterror=0; else if (!strcasestr(myr[0].c_str(),"error")) miterror=0;
										else {
											Log(Txd[T_Fehler_dp]+rots+myr[0]+schwarz+Txd[T_bei_Befehl]+blau+cmd+schwarz,1,1);
										}
										if (!miterror) break;
									} // while (1)
									break;
								case 2006: // Server has gone away
								case 2002: // Can't connect to local MySQL server through socket '/var/lib/mysql/mysql.sock' (2 "No such file or directory"):
									if (!strcasecmp(host.c_str(),"localhost")) {
										Log(Txd[T_Fehler_db]+drots+mysql_error(conn[aktc])+schwarz+Txd[T_Versuche_mysql_zu_starten],1,1);
#ifdef linux
										dbsv->enableggf(1,1);
										setfaclggf(datadir,obverb,oblog,wahr,7,0,0,mysqlben);
										Log(blaus+Txd[T_Vor_restart]+Txd[T_Versuch_Nr]+schwarz+ltoan(versuch),1,oblog);
										for(int iiru=0;iiru<2;iiru++) {
											if (dbsv->restart(1,1)) {
												Log(Txd[T_MySQL_erfolgreich_gestartet],1,1);
												break;
											} // 									 if (dbsv-restart(1,1))
											instmaria(obverb,oblog);
										} // 									for(int iiru=0;iiru<2;iiru++)
										continue;
#endif
									} //                 if (!strcasecmp(host.c_str(),"localhost")) 
									break;
								case 1049:
									if (ggferstellen) {
										Log(Txd[T_Fehler_db]+drots+mysql_error(conn[aktc])+schwarz+Txd[T_Versuche_Datenbank]+drot+uedb+schwarz+Txd[T_zu_erstellen],1,1);
										mysql_real_connect(conn[aktc], host.c_str(), user.c_str(), passwd.c_str(), 0, port, unix_socket, client_flag);
										fehnr=mysql_errno(conn[aktc]);
										if (!fehnr) {
											rs=new RS(this,string("CREATE DATABASE IF NOT EXISTS `")+uedb+"`",aktc,obverb);
											fehnr=mysql_errno(conn[aktc]);
											if (!fehnr) {
												usedb(uedb,aktc);
												fehnr=mysql_errno(conn[aktc]);
												if (!fehnr) {
													delete(rs);
												}
											}
										} else {
											Log(string(Txd[T_Fehler_beim_Verbinden])+ltoan(fehnr),1,1);
										} //                   if (!fehnr) 
									} else {
										Log(Txd[T_Fehler_db]+drots+mysql_error(conn[aktc])+schwarz,obverb,oblog);
									} // if (ggferstellen)
									break;
								case 0:
									break;
								default:
									Log(Txd[T_Fehler_db]+drots+ltoan(mysql_errno(conn[aktc]))+schwarz+" "+blau+mysql_error(conn[aktc])+schwarz,1,1);
							} //             switch ((fehnr=mysql_errno(conn[aktc]))) 
							if (!fehnr) break;
						} //           if (mysql_real_connect(conn[aktc], host.c_str(), user.c_str(), passwd.c_str(), uedb, port, unix_socket, client_flag))  else 
					} //         for(unsigned versuch=0;versuch<versuchzahl;versuch++) 
					if (!fehnr && conn[aktc]) {
						Log(Txd[T_Erfolg_beim_Initialisieren_der_Verbindung_zu_mysql],obverb>1,oblog);
					} else {
						this->ConnError=mysql_error(conn[aktc]);
						mysql_close(conn[aktc]);
						conn[aktc]=0;
						//			throw "Fehler beim Verbinden mit MySQL";
					} // if (mysql_real_connect(conn[aktc], host, user, passwd.c_str(), uedb, port, unix_socket, client_flag))
				} // if (!conn[aktc]) 
			} // 			for(size_t aktc=0;aktc<conz;aktc++)
			dnb = '`'; dne = '`'; dvb = '\''; dve = '\'';
			db=uedb;
			break;
		case Postgres:
#ifdef mitpostgres 
			uchar neu=0;
			if (!dbsv) { 
				if (!obprogda("postgres",obverb,oblog)) {
				  caup<<"Programm postgres nicht da"<<endl;
					systemrueck("V0=/usr/bin/postgres; V1=${V0}_alt; V2=${V0}_uralt; test -d $V0 &&{ test -d $V1 && "+sudc+
					            "mv $V1 $V2; "+sudc+"mv $V0 $V1;}; true;",
					            obverb,oblog);
					linstp->doinst("postgresql-server",obverb,oblog);// postgresql-contrib
					neu=1;
				} // 				if (!obprogda("postgres",obverb,oblog))
				dbsv=new servc("postgresql","postgres",obverb,oblog);
				datadir.clear();
				for(int iru=0;iru<2;iru++) {
					if (!dbsv->machfit(obverb,oblog)||neu) {
						if (!iru) setzrpw(obverb,oblog);
						neu=0;
					}
				}
				if (!dbsv->obslaeuft(obverb,oblog)) {
				  systemrueck("journalctl -xe --no-pager -n 9",2,2);
					Log(Txd[T_Ende_Gelaende],obverb,oblog);
					exit(21);
				} // 				if (!dbsv->obslaeuft(obverb,oblog))
			} // 			if (!dbsv)
			const string ip_a="127.0.0.1";
			port=5432;
			const string constr ="user='"+puser+"' password='"+ppasswd+"' dbname='" + uedb + "' hostaddr='"+ip_a+"' port='"+ltoan(port)+"'";
			caup<<constr<<endl;
			do {
				pconn = PQconnectdb(constr.c_str()); 
				if ((fehnr=PQstatus(pconn)) != CONNECTION_OK) {
					while (rootpwd.empty()) {
						rootpwd=Tippstr({}+Txd[T_Bitte_geben_Sie_ein_Passwort_fuer_Benutzer_postgres_ein],&rootpwd);
					}
					const string mconstr ="user='postgres' password='"+rootpwd+/*"' dbname='" + uedb */+ "' hostaddr='"+ip_a+"' port='"+ltoan(port)+"'";
					pmconn = PQconnectdb(mconstr.c_str()); 
					if (PQstatus(pmconn) != CONNECTION_OK) {
						caup<<"Connection-String: "<<rot<<mconstr<<schwarz<<endl;
						Log("\aVerbindung zur Standarddatenbank '"+rots+uedb+schwarz+"' gescheitert!",1,1);
						pconn=NULL;
						break;
					}
					caup<<"jetzt Benutzererstellung"<<endl<<endl;
		      PGconn *zwi=pconn;
					pconn=pmconn;
			    RS p1(this,"CREATE USER "+puser+" CREATEDB CREATEUSER INHERIT REPLICATION PASSWORD '"+ppasswd+"'",obverb);
			    RS p2(this,string("CREATE DATABASE \"")+uedb+"\" ENCODING 'LATIN1' TEMPLATE template0 LC_CTYPE 'de_DE.ISO88591' LC_COLLATE 'de_DE.ISO88591'",obverb);
          pconn=zwi;
				} else {
					Log(Txd[T_Verbindung_zu]+blaus+uedb+schwarz+Txd[T_gelungen]+blau+user+schwarz+"', host: '"+blau+ip_a+schwarz+"', port: '"+blau+ltoan(port)+schwarz+"'",obverb,oblog);
					caup<<"is gangen"<<endl;
					break;
				} // 				if ((fehnr=PQstatus(pconn)) != CONNECTION_OK) else
			} while (1);
#endif
			break;
	} // switch (DBS) 
} // DB::DB(DBSTyp nDBS, const char* host, const char* user,const char* passwd, const char* db, unsigned int port, const char *unix_socket, unsigned long client_flag,const char** erg)

int DB::usedb(const string& db,const size_t aktc/*=0*/)
{
  int fehler=0; 
  switch (DBS) {
    case MySQL:
      fehler = mysql_select_db(conn[aktc],db.c_str());    
      break;
    case Postgres:
		  caup<<"hier usedb"<<endl;
			exit(22);
      RS cdb(this,"\\c "+db,aktc,/*obverb=*/1);		   
      break;
  } //   switch (DBS)
  return fehler;
} // usedb

// in: DB::init
void DB::pruefrpw(const string& wofuer, unsigned versuchzahl)
{
  myloghost=!strcasecmp(host.c_str(),"localhost")||!strcmp(host.c_str(),"127.0.0.1")||!strcmp(host.c_str(),"::1")?"localhost":"%";
  for(unsigned versuch=0;versuch<versuchzahl;versuch++) {
    cmd=sudc+mysqlbef+" -uroot -h'"+host+"' "+(rootpwd.empty()?"":"-p"+rootpwd)+" -e \"show variables like 'gibts wirklich nicht'\" 2>&1";
    myr.clear();
    systemrueck(cmd,-1,0,&myr);
    miterror=1;
    if (!myr.size()) miterror=0; else if (!strcasestr(myr[0].c_str(),"error")) miterror=0;
    else {
    }
    if (miterror) {
      if (!nrzf) {
				rootpwd=Tippstr(string(Txd[T_MySQL_Passwort])+Txd[T_fuer_Benutzer]+dblau+"root"+schwarz+
				                          Txd[T_wird_benoetigt_fuer_Befehl]+"\n"+tuerkis+wofuer+schwarz+")",0);
        if (user=="root") passwd=rootpwd;
      }
    } else {
      break; // naechster Versuch
    } // if (miterror) KLA KLZ else KLA
  }
  if (rootpwd.empty()) setzrpw();
} // pruefrpw

// in: DB::init
void DB::setzrpw(int obverb/*=0*/,int oblog/*=0*/) // Setze root-password
{
	if (!nrzf) {
		string rootpw2;
		switch (DBS) {
			case MySQL:
				if (Tippob(Txd[T_MySQL_Passwort]+(Txd[T_fuer_Benutzer]+dblaus)+"root"+schwarz+Txd[T_ist_leer_Wollen_Sie_eines_festlegen])) {
					while (1) {
						do {
							rootpwd=Tippstr(Txd[T_Bitte_geben_Sie_ein_MySQL_Passwort_fuer_Benutzer_root_ein],&rootpwd);
						} while (rootpwd.empty());	
						rootpw2=Tippstr(string(Txd[T_Bitte_geben_Sie_ein_MySQL_Passwort_fuer_Benutzer_root_ein])+" ("+Txk[T_erneute_Eingabe]+")",&rootpw2);
						if (rootpw2==rootpwd) break;
					} //         while (1)
					// 7.7.17: neuer Fehler "ERROR 1819 (HY000) at line 1: Your password does not satisfy the current policy requirements" auf fedora
					const string verbot="/etc/my.cnf.d/cracklib_password_check.cnf",
					             plugin="plugin-load-add=cracklib_password_check.so";
					struct stat st;
					uchar gef=0;
					if (!lstat(verbot.c_str(),&st)) {
						mdatei f(verbot,ios::in,0);
						if (f.is_open()) {
							string zeile;
							while(getline(f,zeile)) {
							 if (!zeile.find(plugin)) {
							  gef=1;
								break;
							 } // 							 if (!zeile.find(plugin))
							} // 							while(getline(f,zeile))
							f.close();
						} // 						if (f.is_open())
						if (gef) {
						 cmd=sudc+"sed -i 's/^\\("+plugin+"\\)/;\\1/g' "+verbot+";";
						 systemrueck(cmd.c_str(),obverb,oblog);
						 dbsv->restart(obverb,oblog);
						 const string rcmd=sudc+"sed -i 's/^;\\("+plugin+"\\)/\\1/g' "+verbot+";";
						 anfgg(unindt,rcmd,cmd,obverb,oblog);
						} // 						if (gef)
					} // 					if (!lstat(verbot.c_str(),&st))
					const string cmd=sudc+mysqlbef+" -uroot -h'"+host+"' -e \"GRANT ALL ON *.* TO 'root'@'"+myloghost+
						"' IDENTIFIED BY '"+ersetzAllezu(rootpwd,"\"","\\\"")+"' WITH GRANT OPTION\"";
					Log(Txd[T_Fuehre_aus_db]+blaus+cmd+schwarz,1,1);
					int erg __attribute__((unused))=system(cmd.c_str());
				} // if (Tippob(Txd[T_Das_MySQL_Passwort_fuer_Benutzer_root_ist_leer_Wollen_Sie_eines_festlegen])) 
				break;
			case Postgres:
				while (1) {
					do {
						rootpwd=Tippstr(string(Txd[T_PostgreSQL_musste_neu_eingerichtet_werden])+
								Txd[T_Welches_Passwort_soll_der_Benutzer_postgres_haben]+": ",&rootpwd);
					} while (rootpwd.empty());
					rootpw2=Tippstr(string(Txd[T_Welches_Passwort_soll_der_Benutzer_postgres_haben])+" ("+Txk[T_erneute_Eingabe]+"): ",&rootpw2);
					if (rootpw2==rootpwd) break;
				} // while (1)
				uchar geht=0;
				for(int iru=0;iru<2;iru++) {
					svec irueck;
					systemrueck("echo "+rootpwd+"|su - postgres -c \"psql -c 'select datname from pg_database order by datname'\"",obverb,oblog,&irueck);
					for(unsigned zeile=0;zeile<irueck.size();zeile++) {
						if (irueck[zeile].find("template0")!=string::npos) {
							geht=1;
							break;
						} // 					 if (irueck[zeile].find("template0")!=string::npos)
					} // 					for(unsigned zeile=0;zeile<irueck.size();zeile++)
					if (geht) break;
					linstp->doinst("passwd",obverb,oblog,"chpasswd"); 
					systemrueck("sh -c 'echo \"postgres:"+rootpwd+"\"|"+sudc+"chpasswd'",obverb,oblog);
					svec rueck;
					systemrueck("ps aux|grep postgres|grep -- -D|rev|cut -d' ' -f1|rev",obverb,oblog,&rueck);
					if (rueck.size()) {
						datadir=rueck[0];
						caup<<"Datadir: "<<datadir<<endl;
					} else
						datadir="/var/lib/pgsql/data";
					systemrueck("sh -c 'V="+dir_name(datadir)+";mkdir -p $V;chown postgres:postgres -R $V'",obverb,oblog);
					rueck.clear();	
					if (systemrueck("sh -c 'echo \""+rootpwd+"\"|su - postgres -c \"initdb -D "+datadir+"\" 2>&1'",obverb,oblog,&rueck,0,2)) {
						// dann laeuft es wahrscheinlich schon
						Log(Txd[T_Ende_Gelaende],obverb,oblog);
						exit(23);
					}
				} // 				for(int iru=0;iru<2;iru++) 
		} // 		switch (DBS) 
	} // if (!nrzf)
} // setzrpw

DB::~DB(void)
{
if (0) {
	switch (DBS) {
		case MySQL:
			if (!this->ConnError) {
				if (!lassoffen) {
					for(size_t aktc=0;aktc<conz;aktc++) {
						mysql_close(conn[aktc]);
					}
				} // 				if (!lassoffen)
			} // 			if (!this->ConnError)
			for(size_t aktc=0;aktc<conz;aktc++) {
				conn[aktc]=0;
			}
			break;
		case Postgres:
			caup<<"hier ~DB"<<endl;
			exit(24);
			break;
	} // 	switch (DBS)
	if (dbsv) delete dbsv;
 }
} // DB::~DB(void)

// wird aufgerufen in: prueftab
void DB::lesespalten(Tabelle *ltab,size_t aktc,int obverb/*=0*/,int oblog/*=0*/)
{
  Log(violetts+Txd[T_Lesespalten]+blau+": "+ltab->name+"'"+schwarz,obverb,oblog);
  char ***cerg;
  delete spalt;
  spalt=new RS(this,"SELECT column_name p0,"
        "MID(column_type,INSTR(column_type,'(')+1,INSTR(column_type,')')-INSTR(column_type,'(')-1) p1, column_type p2 "
        "FROM information_schema.columns WHERE table_name = '"+ltab->name+"' AND table_schema = '"+db+"' ORDER BY ordinal_position",aktc,0);
  if (!spalt->obfehl) {
    delete[] spnamen;
    spnamen= new char*[spalt->num_rows];
    delete[] splenge;
    splenge= new char*[spalt->num_rows];
    delete[] sptyp;
    sptyp= new char*[spalt->num_rows];
    int spnr=0;
    while (cerg=spalt->HolZeile(),cerg?*cerg:0) {
      spnamen[spnr]=*(*cerg);
      splenge[spnr]=*(*cerg+1);
      sptyp[spnr]=*(*cerg+2);
      spnr++;
    }
    if (obverb) {
		  Log(blaus+"spalt->num_rows: "+schwarz+ltoan(spalt->num_rows),obverb,oblog);
      for(size_t j=0;j<spalt->num_rows;j++) {
       Log(blaus+"spanmen["+ltoan(j)+"]: "+schwarz+spnamen[j]);
       Log(blaus+"splenge["+ltoan(j)+"]:  "+schwarz+splenge[j]);
       Log(blaus+"sptyp["+ltoan(j)+"]:    "+schwarz+sptyp[j]);
      }
    } //     if (obverb)
	} else if (obverb||oblog) {
    Log(blaus+"spalt->obfehl: "+ltoan(int(spalt->obfehl)),obverb,oblog);
  }
  Log(violetts+Txk[T_Ende]+Txd[T_Lesespalten]+blau+": "+ltab->name+"'"+schwarz,obverb,oblog);
} // lesespalten

int DB::machind(const string& tname, Index* indx,const size_t aktc, int obverb/*=0*/, int oblog/*=0*/)
{
	// steht aus: Namen nicht beruecksichtigen, nur Feldreihenfolge und ggf. -laenge
	uchar obneu=0;
	RS rind(this,"SHOW INDEX FROM `"+tname+"` WHERE KEY_NAME = '"+indx->name+"'",aktc,obverb);
	if (rind.obfehl) {
		obneu=1;
	} else {
		if (!rind.result->row_count){
			obneu=1;
		} else {
			for(int j=0;j<indx->feldzahl;j++) {
				char*** erg= rind.HolZeile();
				if (!*erg) {
					obneu=1;break;
				} else if (strcasecmp(indx->felder[j].name.c_str(),*(*erg+4))) { 
					// 0 = Tabelle, 1 = non_unique (0,1), 2 = Key_name, 3 = seq_in_index, 4 = column_name, 5 = Collation ('A','D'), 6=Cardinality(0,1), 
					// 7= sub_part(NULL,<ziffer>), 8=packed(null), 9=NULL("Yes"),10=index_type("BTREE"),11=comment(""),12=index_comment("")
					obneu=1;break;
				} else if (indx->felder[j].lenge!="" && *(*erg+7)) {
					if (indx->felder[j].lenge!=*(*erg+7)) { 
						obneu=1;break;
					}
				} //                 if (!*erg) else ...
			} //               for(int j=0;j<indx->feldzahl;j++)
			if (!obneu) {    // Wenn zu viele Zeilen da sind, auch loeschen
				char*** erg= rind.HolZeile();
				if (*erg) {
					obneu=1;
				}
			} //               if (!obneu)    // Wenn zu viele Zeilen da sind, auch loeschen
			if (obneu) {
				RS rloesch(this,"DROP INDEX `"+indx->name +"` ON `"+tname+"`",aktc,obverb);
			}
		} //             if (!rind.result->row_count) else
	} // if (obneu) 
	if (obneu) {
		RS rindins(this);
		//sql.str(std::string()); sql.clear();
		std::stringstream sql;
		sql<<"CREATE INDEX `"<<indx->name<<"` ON `"<<tname<<"`(";
		for(int j=0;j<indx->feldzahl;j++) {
			sql<<"`"<<indx->felder[j].name<<"`";
			for(unsigned spnr=0;spnr<spalt->num_rows;spnr++) { // reale Spalten
				if (!strcasecmp(indx->felder[j].name.c_str(),spnamen[spnr])) { // Feldnamen identisch
					long numsplen=atol(splenge[spnr]);
					long numinlen=indx->felder[j].lenge.empty()?0:atol(indx->felder[j].lenge.c_str());
					if (!numinlen || !numsplen) { // numsplen ist 0 z.B. bei varbinary
						// das sollte reichen
						if (numsplen>50 || !numsplen) indx->felder[j].lenge="50"; 
					} else if (numinlen>numsplen) {
						// laenger darf ein MariadB-Index z.Zt. nicht sein
						if (numsplen>767) indx->felder[j].lenge="767";
						else indx->felder[j].lenge=splenge[spnr];
					}
				}
			}
			if (indx->felder[j].lenge!="0" && indx->felder[j].lenge!="") {
				sql<<"("<<indx->felder[j].lenge<<")";
			}
			if (j<indx->feldzahl-1) {
				sql<<",";
			}
		} // for(int j=0;j<indx->feldzahl;j++) 
		sql<<")";
		rindins.Abfrage(sql.str(),aktc,obverb?-1:1);
	} // if (!rind.obfehl) 
	return 0;
} // int DB::machind(const string& tname, Index* indx,int obverb/*=0*/, int oblog/*=0*/)


int DB::prueftab(Tabelle *ptab,const size_t aktc,int obverb/*=0*/,int oblog/*=0*/) 
{
  Log(violetts+Txd[T_Pruefe_Tabelle]+blau+ptab->name+"'"+schwarz,obverb,oblog);
  int gesfehlr=0;
  RS rs(this);
  std::stringstream sql;
  // eine Indexfeldlaenge groesser als die Feldlaenge fuehrt zu Fehler (zumindest bei MariaDB)
  for(int i=0;i<ptab->indexzahl;i++){
    for(int j=0;j<ptab->indices[i].feldzahl;j++){
      for(int k=0;k<ptab->feldzahl;k++){
        if (!ptab->felder[k].lenge.empty()) if (!ptab->indices[i].felder[j].lenge.empty())
          if (!strcasecmp(ptab->felder[k].name.c_str(),ptab->indices[i].felder[j].name.c_str())) 
            if (atol(ptab->felder[k].lenge.c_str())<atol(ptab->indices[i].felder[j].lenge.c_str())){
              ptab->felder[k].lenge=ptab->indices[i].felder[j].lenge;
            }
      } //       for(int k=0;k<ptab->feldzahl;k++)
    } //     for(int j=0;j<ptab->indices[i].feldzahl;j++)
  } //   for(int i=0;i<ptab->indexzahl;i++)
  vector<string> fstr;
  vector<string> istr;
  const char* def_engine="InnoDB";
  const char* def_charset="latin1";
  const char* def_collate="latin1_german2_ci";
  const char* def_rowformat="DYNAMIC";
  switch (DBS){
    case MySQL:
      {
        if (conn[aktc]==0) conn[aktc] = mysql_init(NULL);
        lesespalten(ptab,aktc,obverb>1,oblog);
        for(int i=0;i<ptab->feldzahl;i++) {
					if (!spalt->obfehl)
            for(unsigned j=0;j<spalt->num_rows;j++) {
              if (!strcasecmp(ptab->felder[i].name.c_str(),spnamen[j])) {
                if (splenge[j]) 
                  if (atol(splenge[j]) > atol(ptab->felder[i].lenge.c_str())) 
                    ptab->felder[i].lenge=splenge[j];
                break;
              } //               if (!strcasecmp(ptab->felder[i].name.c_str(),spnamen[j]))
            } //             for(unsigned j=0;j<spalt->num_rows;j++)
          fstr.resize(fstr.size()+1);
          istr.resize(istr.size()+1);
          ersetzAlle(ptab->felder[i].comment,"'","\\'");
          fstr[i]= "`" + ptab->felder[i].name + "` "+
            ptab->felder[i].typ+
            ((ptab->felder[i].typ=="DATE"||ptab->felder[i].lenge==""||ptab->felder[i].lenge=="0")?"":
             ("("+ptab->felder[i].lenge+
              ((ptab->felder[i].typ.find("INT")!=string::npos||
								ptab->felder[i].typ.find("CHAR")!=string::npos||
								ptab->felder[i].typ.find("TEXT")!=string::npos||
								ptab->felder[i].prec=="")?"":
               (","+ptab->felder[i].prec))
              +")"))
						+(ptab->felder[i].unsig  ?  " UNSIGNED ":"")
            +(ptab->felder[i].nnull  ?  " NOT NULL ":"")
            +(ptab->felder[i].defa.empty()&&!ptab->felder[i].nnull?"":" DEFAULT '"+ptab->felder[i].defa+"'")
            +(ptab->felder[i].obauto?" AUTO_INCREMENT":" ")
            +(ptab->felder[i].obind && ptab->felder[i].obauto?" PRIMARY KEY":" ")
            +((ptab->felder[i].comment.empty())?"":
                (" COMMENT '"+ptab->felder[i].comment+"'"));
          if (ptab->felder[i].obind && !ptab->felder[i].obauto) {
            istr[i]=", ADD INDEX `"+ptab->felder[i].name+"`(`"+ptab->felder[i].name+"`)";
          }
        } // for(int i=0;i<ptab->feldzahl;i++)
        MYSQL_RES *dbres = mysql_list_tables(conn[aktc],ptab->name.c_str());
        if (dbres && !dbres->row_count) {
          /*ptab->comment=**/sersetze(&ptab->comment,string("'"),string("\\'"));
          sql<<"CREATE TABLE `"<<ptab->name.c_str();
          sql<<"` ("<<fstr[0]<<istr[0]<<") COMMENT='";
          sql<<ptab->comment
            <<"' ENGINE="<<(ptab->engine==""?def_engine:ptab->engine);
          sql<<" DEFAULT CHARSET="
            <<(ptab->charset==""?def_charset:ptab->charset);
          sql<<((ptab->charset!=""&&ptab->collate=="")?"":" COLLATE=")
            <<(ptab->collate==""?(ptab->charset!=""?"":def_collate):ptab->collate);
          sql<<" ROW_FORMAT="
            <<(ptab->rowformat==""?def_rowformat:ptab->rowformat);
          rs.Abfrage(sql.str(),aktc,obverb?-1:1); // falls obverb, dann sql-String ausgeben
          gesfehlr+=rs.obfehl;
          if (gesfehlr) Log(string("gesfehlr 1: ")+ltoan(gesfehlr),1,1);
          lesespalten(ptab,aktc,obverb>1,oblog);
        } // if (!dbres->row_count) 
        mysql_free_result(dbres);

        // Pruefung, ob Spalten hinzugefuegt werden muessen
        for(int gspn=0;gspn<ptab->feldzahl;gspn++) { // geplante Spalten
          binaer gefunden=falsch;
          for(unsigned j=0;j<spalt->num_rows;j++) { // reale Spalten
            if (!strcasecmp(ptab->felder[gspn].name.c_str(),spnamen[j])) {
              gefunden=wahr;
              break;
            }
          }
          if (!gefunden) {
            sql.str(std::string()); sql.clear();
            sql<<"ALTER TABLE `"<<ptab->name<<"` ADD "<<fstr[gspn];
            if (gspn) sql<<" AFTER `"<<ptab->felder[gspn-1].name<<"`";
            else sql<<" FIRST";
            sql<<istr[gspn];
            /*int erg=*/rs.Abfrage(sql.str(),aktc,obverb?-1:1);
            gesfehlr+=rs.obfehl;
            if (gesfehlr) Log(string("gesfehlr 2: ")+ltoan(gesfehlr),1,1);
          }
        }

        // Pruefung, ob Spalten geaendert oder verschoben werden muessen
        for(int gspn=0;gspn<ptab->feldzahl;gspn++) { // geplante Spalten
          binaer verschieb=falsch, aendere=falsch;
          for(unsigned spnr=0;spnr<spalt->num_rows;spnr++) { // reale Spalten
            if (!strcasecmp(ptab->felder[gspn].name.c_str(),spnamen[spnr])) { // Feldnamen identisch
              if (strcasecmp(sptyp[spnr],"mediumtext") && strcasecmp(sptyp[spnr],"blob") && strcasecmp(sptyp[spnr],"longblob") && 
                  strcasecmp(sptyp[spnr],"longtext") && strcasecmp(sptyp[spnr],"text")) {
                if ((ptab->felder[gspn].lenge!="0" && !ptab->felder[gspn].lenge.empty()) &&
                    atol(ptab->felder[gspn].lenge.c_str()) > (long)atol(splenge[spnr])) {
                  aendere=wahr;
                }
              }
              if (gspn) { // Verschiebung erst ab der zweiten geplanten Spalte reicht auch und vermeidet Speicherunterlaeufe
                verschieb=wahr; 
                if (spnr) if (!strcasecmp(ptab->felder[gspn-1].name.c_str(),spnamen[spnr-1])) verschieb=falsch;
                if (verschieb) spnr--;
              }
              if (verschieb || aendere) break;
            }
          }
          if (verschieb || aendere) {
            sql.str(std::string()); sql.clear();
            sql<<"ALTER TABLE `"<<ptab->name<<"` MODIFY "<<fstr[gspn];
            if (gspn) sql<<" AFTER `"<<ptab->felder[gspn-1].name<<"`";
            else sql<<" FIRST";
            /*int erg=*/rs.Abfrage(sql.str(),aktc,obverb?-1:1);
            gesfehlr+=rs.obfehl;
            if (gesfehlr) Log(string("gesfehlr 3: ")+ltoan(gesfehlr),1,1);
            if (verschieb) 
              lesespalten(ptab,aktc,obverb>1,oblog);
            if (aendere) {
              if (!istr[gspn].empty()) {
                RS rloesch(this,string("DROP INDEX `")+ptab->felder[gspn].name +"` ON `"+ptab->name+"`",aktc,obverb);
                sql.str(std::string()); sql.clear();
                sql<<"ALTER TABLE `"<<ptab->name<<"`"<<istr[gspn].substr(1);
                rs.Abfrage(sql.str(),aktc,obverb?-1:1);
              } // if (!istr[gspn].empty()) 
            } // if (aendere) 
          } // if (verschieb || aendere)
        } // for(int gspn=0;gspn<ptab->feldzahl;gspn++) 
				for(int i=0;i<ptab->indexzahl;i++) {
				  machind(ptab->name,&ptab->indices[i],aktc,obverb,oblog);
				} // for(int i=0;i<ptab->indexzahl;i++)
      } // case Mysql
      break;
    case Postgres:
		  caup<<"hier prueftab "<<ptab->name<<endl;
			exit(25);
      break;
  } // switch (DBS)
  return gesfehlr;
} // int DB::prueftab(Tabelle *ptab,bool obverb) 

// erweitert die Spaltenbreite einer Spalte auf mindenstens wlength, falls sie geringer ist
uchar DB::tuerweitern(const string& tabs, const string& feld,long wlength,const size_t aktc,int obverb)
{
  stringstream korr;
  string lenge;
  korr<<"SELECT character_maximum_length, data_type,is_nullable,column_default,column_comment FROM information_schema.columns WHERE table_schema='"<<
    db<<"' AND table_name='"<<tabs<<"' AND column_name='"<<feld<<"'";
  RS spaltlen(this,korr.str(),aktc,obverb);
  if (!spaltlen.obfehl) {
    char*** cerg;
    while(cerg= spaltlen.HolZeile(),cerg?*cerg:0) {
      if (*(*cerg+0)) {
        lenge=*(*cerg+0);
        if (atol(lenge.c_str())<wlength) {
          Log(Txd[T_Erweitere_Feld]+tabs+"."+feld+Txd[T_von]+lenge.c_str()+Txd[T_auf]+ltoan(wlength),1,1);
          korr.str(std::string()); korr.clear();
          if (*(*cerg+1) && *(*cerg+2)) {
            korr<<"ALTER TABLE `"<<tabs<<"` MODIFY COLUMN `"<<feld<<"` "<<*(*cerg+1)/*data_type*/<<"("<<wlength<<") "<<
              (!strcasecmp(*(*cerg+2),"yes")?"NULL":"NOT NULL")<<" "<<(*(*cerg+3)?string("DEFAULT '")+*(*cerg+3)+"'":"")<<
              " COMMENT '"<<ersetzAllezu(*(*cerg+4),"'","\\'")<<"'";
            RS spaltaend(this,korr.str(),aktc,-1/*obverb*/);
            if (spaltaend.fnr==1074) {
              korr.str(std::string()); korr.clear();
              string neufeld;
              if (!strcasecmp(*(*cerg+1),"binary")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"varbinary")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"tinyblob")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"blob")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"char")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"varchar")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"text")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"tinytext")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"mediumtext")) neufeld="longtext";
              else if (!strcasecmp(*(*cerg+1),"mediumblob")) neufeld="longblob";
              if (!neufeld.empty()) {
                Log(Txd[T_Aendere_Feld]+tabs+"."+feld+" von: "+*(*cerg+1)+" auf: "+neufeld,1,1);
                korr<<"ALTER TABLE `"<<tabs<<"` MODIFY COLUMN `"<<feld<<"` "<<neufeld/*data_type*/<<" "<<
                  (!strcasecmp(*(*cerg+2),"yes")?"NULL":"NOT NULL")<<" "<<(*(*cerg+3)?string("DEFAULT '")+*(*cerg+3)+"'":"")<<
                  " COMMENT '"<<ersetzAllezu(*(*cerg+4),"'","\\'")<<"'";
                RS spaltaend2(this,korr.str(),aktc,-1/*obverb*/);
              }
            } // if (fnr==1074) 
          }
          return -1; // Aenderung durchgefuehrt
        } // if (atol(lenge.c_str())<wlength) 
        return 0; // kein Fehler, keine Aenderung noetig
      } else {
      } // if (**cerg) else
    } // while(cerg= HolZeile(),cerg?*cerg:0) 
  } else {
    cerr<<Txd[T_falsche_Fehlernr]<<spaltlen.fnr<<Txd[T_bei_der_Abfrage_der_Spaltenlaenge_bei_Tabelle]<<tabs<<
      Txd[T_und_Feld]<<feld<<endl<<Txd[T_mit]<<korr.str()<<endl;
    return 1;
  } // if (!obfehl) else 
  return 5;  // wird nie erreicht, verhindert aber Compilerfehlermeldung
} // tuerweitern

// in: RS::insert() und RS::update
void DB::erweitern(const string& tabs, vector<instyp> einf,const size_t aktc,int obverb,uchar obsammeln, const unsigned long *maxl)
{
  for(uint i=0;i<einf.size();i++) {
    long wlength;
    if (obsammeln) {
      wlength = maxl[i];
    } else {
      wlength = einf[i].wert.length();
    } //     if (obsammeln)
    tuerweitern(tabs,einf[i].feld,wlength,aktc,obverb);
  } //   for(uint i=0;i<einf.size();i++)
} // RS::erweitern

// in: RS::insert() und RS::update
int DB::machbinaer(const string& tabs, const size_t aktc,const string& fmeld,int obverb)
{
  Log(violetts+__FUNCTION__+"()"+schwarz+" tabs. "+blau+tabs+schwarz+" fmeld: "+blau+fmeld+schwarz+" obverb: "+ltoan(obverb),obverb);
  size_t p1,p2,p3,p4;
  p1=fmeld.find("'")+1;
  if (p1==string::npos) return 1;
  p2=fmeld.find("'",p1)+1;
  if (p2==string::npos) return 2;
  //                string inc=fmeld.substr(p1,p2-p1-1);
  p3=fmeld.find("'",p2)+1;
  if (p3==string::npos) return 3;
  p4=fmeld.find("'",p3)+1;
  if (p4==string::npos) return 4;
  const string feld=fmeld.substr(p3,p4-p3-1);
  stringstream korr;
  string lenge;
  string neufeld;
  korr<<"SELECT character_maximum_length p0, data_type p1,is_nullable p2,column_default p3,column_comment p4"
    " FROM information_schema.columns WHERE table_schema='"<<
    db<<"' AND table_name='"<<tabs<<"' AND column_name='"<<feld<<"'";
  RS spaltlen(this,korr.str(),aktc,obverb);
  if (!spaltlen.obfehl) {
    char*** cerg;
    while(cerg= spaltlen.HolZeile(),cerg?*cerg:0) {
      if (*(*cerg+0)) {
        lenge=*(*cerg+0);
        if (!strcasecmp(*(*cerg+1),"CHAR")) neufeld="BINARY";
        else if (!strcasecmp(*(*cerg+1),"VARCHAR")) neufeld="VARBINARY";
        else continue;
        while(1) { 
          korr.str(std::string()); korr.clear();
          korr<<"ALTER TABLE `"<<tabs<<"` MODIFY COLUMN `"<<feld<<"` "<<neufeld/*data_type*/<<"("<<lenge<<") "<<
            (!strcasecmp(*(*cerg+2),"yes")?"NULL":"NOT NULL")<<" "<<(*(*cerg+3)?string("DEFAULT '")+*(*cerg+3)+"'":"")<<
            " COMMENT '"<<ersetzAllezu(*(*cerg+4),"'","\\'")<<"'";
          RS spaltaend(this,korr.str(),aktc,-1/*obverb*/);
          if (mysql_errno(this->conn[aktc])!=1406) break;
          lenge=ltoan(atol(lenge.c_str())+10); 
        } //         while(1)
        return -1; // Aenderung durchgefuehrt
      } //       if (*(*cerg+0))
      return 0; // kein Fehler, keine Aenderung noetig
    } //     while(cerg= spaltlen.HolZeile(),cerg?*cerg:0)
    return 6;
  } //   if (!spaltlen.obfehl)
  return 7;
} // RS::machbinaer

inline string instyp::ersetze(const char *u, const char* alt, const char* neu) 
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
  } //   if (alt[0]==0 || !strcmp(alt,neu)) else
  return erg;
} // ersetze(char *u, const char* alt, const char* neu)

inline string *instyp::sersetze( string *src, string const& target, string const& repl) 
{
  if (target.length()) {
    if (src->length()) {
      size_t idx = 0;
      for (;;) {
        idx = src->find( target, idx);
        if (idx == string::npos)  break;
        src->replace( idx, target.length(), repl);
        idx += repl.length();
      }
    }
  }
  return src;
} // sersetze( string src, string const& target, string const& repl)



sqlft::sqlft(DBSTyp eDBS, const string& vwert):
  string(vwert) 
{
  ersetze("\\","\\\\");
  ersetze("\'","\\\'");
  insert(0,1,dvb(eDBS));
  append(1,dve(eDBS));
} // sqlft::sqlft(DBSTyp eDBS, const string& vwert)

sqlft::sqlft(DBSTyp eDBS, const string *vwert):
  string(*vwert) 
{
  ersetze("\\","\\\\");
  ersetze("\'","\\\'");
  insert(0,1,dvb(eDBS));
  append(1,dve(eDBS));
} // sqlft::sqlft(DBSTyp eDBS, const string *vwert)

sqlft::sqlft(DBSTyp eDBS, char* vwert,bool obzahl):
  string(vwert) 
{
  if (!obzahl) {
    ersetze("\\","\\\\");
    ersetze("\'","\\\'");
    insert(0,1,dvb(eDBS));
    append(1,dve(eDBS));
  }
} // sqlft::sqlft(DBSTyp eDBS, char* vwert,bool obzahl)

sqlft::sqlft(DBSTyp eDBS, char* vwert,char* zs):
  string(vwert) 
{
  ersetze("\\","\\\\");
  ersetze("\'","\\\'");
  insert(0,1,dvb(eDBS));
  insert(0,zs);
  append(1,dve(eDBS));
} // sqlft::sqlft(DBSTyp eDBS, char* vwert,char* zs)

string *sqlft::ersetze(const char* alt, const char* neu) 
{
  if (size()){
    string erg;
    if (alt[0]==0 || !strcmp(alt,neu)) {
      erg=c_str();
    } else {
      erg="";
      for(char* p=(char*)c_str();*p;p++)  {
        char *pi = (char*)alt;
        int i=0,gleich=1;
        for(;*(pi+i);i++)
          if (*(pi+i)!=*(p+i))
          {gleich=0;break;}
        if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
      }
    }
    this->assign(erg);
  } //   if (size())
  return this;
} // ersetze(char *u, const char* alt, const char* neu)

string *sqlft::sersetze( string *src, string const& target, string const& repl) 
{
  if (target.length()) {
    if (src->length()) {
      size_t idx = 0;
      for (;;) {
        idx = src->find( target, idx);
        if (idx == string::npos)  break;
        src->replace( idx, target.length(), repl);
        idx += repl.length();
      }
    }
  }
  this->assign(*src);
  return this;
} // sersetze( string src, string const& target, string const& repl)


sqlft::sqlft(DBSTyp eDBS, time_t *tm): string(21,0)
{
  struct tm zt={0};
  memcpy(&zt,localtime(tm),sizeof zt);
  druckeein(eDBS,&zt);
} // sqlft::sqlft(DBSTyp eDBS, time_t *tm): string(21,0)

void stmax(int *zahl,int stellen=2)
{
 int grenze=1;
 for(int ui=0;ui<stellen;ui++) grenze*=10;
 grenze-=1;
 while (*zahl>grenze) (*zahl)/=10;
} // void stmax(int *zahl,int stellen=2)

void sqlft::druckeein(DBSTyp eDBS, tm *zt) 
{
	stmax(&zt->tm_year,4);
	stmax(&zt->tm_mon);
	stmax(&zt->tm_mday);
	stmax(&zt->tm_hour);
	stmax(&zt->tm_min);
	stmax(&zt->tm_sec);
  sprintf((char*)c_str(),"%c%.4d-%.2d-%.2d %.2d:%.2d:%.2d%c",dvb(eDBS),zt->tm_year+1900,zt->tm_mon+1,zt->tm_mday,zt->tm_hour,zt->tm_min,zt->tm_sec,dve(eDBS));
} // void sqlft::druckeein(DBSTyp eDBS, tm *zt)

sqlft::sqlft(DBSTyp eDBS, tm *zt):
  string(21,0) 
{
  druckeein(eDBS,zt);
} // sqlft::sqlft(DBSTyp eDBS, tm *zt):

sqlft::sqlft(DBSTyp eDBS, uchar c):
  string(1,0) 
{
  sprintf((char*)c_str(),"%d",c);
}

sqlft::sqlft(DBSTyp eDBS, char c):
  string(1,0) 
{
  sprintf((char*)c_str(),"%d",c);
}

sqlft::sqlft(DBSTyp eDBS, int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%i",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, long int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%li",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, unsigned int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%u",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, unsigned long int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%lu",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, long long int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%llu",i);
  resize(strlen(c_str()));
} // sqlft::sqlft(DBSTyp eDBS, long long int i)

void DB::LetzteID(string *erg,const size_t aktc) 
{
  if (erg) {
    switch (DBS) {
      case MySQL:
        {
          RS rs(this,"select LAST_INSERT_ID()",aktc,/*obverb=*/1);
          *erg= *rs.HolZeile()[0];
        }
        break;
      case Postgres:
		  caup<<"hier letzteid"<<endl;
			exit(26);
        break;
    } //     switch (DBS)
  } //   if (erg)
} // void DB::LetzteID(string *erg)

char* DB::tmtosql(tm *tmh,char* buf) 
{
  switch (DBS) {
    case MySQL:
			stmax(&tmh->tm_year,4);
			stmax(&tmh->tm_mon);
			stmax(&tmh->tm_mday);
      sprintf(buf,"%.4d%.2d%.2d",tmh->tm_year+1900,tmh->tm_mon+1,tmh->tm_mday);
      break;
    case Postgres:
		  caup<<"hier tmtosql"<<endl;
			exit(27);
      break;
  } //   switch (DBS)
  return buf;
} // char* DB::tmtosql(tm *tmh,char* buf)

//
char* DB::tmtosqlmZ(tm *tmh,char* buf) 
{
  switch (DBS) {
    case MySQL:
			stmax(&tmh->tm_year,4);
			stmax(&tmh->tm_mon);
			stmax(&tmh->tm_mday);
			stmax(&tmh->tm_hour);
			stmax(&tmh->tm_min);
			stmax(&tmh->tm_sec);
      sprintf(buf,"%.4d%.2d%.2d%.2d%.2d%.2d",tmh->tm_year+1900,tmh->tm_mon+1,tmh->tm_mday,tmh->tm_hour,tmh->tm_min,tmh->tm_sec);
      break;
    case Postgres:
		  caup<<"hier tmtosql"<<endl;
			exit(28);
      break;
  } //   switch (DBS)
  return buf;
} // char* DB::tmtosqlmZ(tm *tmh,char* buf) 

my_ulonglong DB::affrows(const size_t aktc) 
{ // affected rows
  switch (DBS) {
    case MySQL:
      arows = mysql_affected_rows(conn[aktc]);
      return arows;
      break;
    case Postgres:
		  caup<<"hier affrows"<<endl;
			exit(29);
      break;
  } //   switch (DBS)
  return arows=0;
} // my_ulonglong DB::affrows() { // affected rows

char*** RS::HolZeile() 
{
  switch (db->DBS) {
    case MySQL:
      if (!obfehl)// Anfrage erfolgreich, Rückgabedaten werden verarbeitet
        if (result) {  // Es liegen Zeilen vor
          row = mysql_fetch_row(result);
          return &row;
        }
      break;
    case Postgres:
		  caup<<"hier HolZeile"<<endl;
			exit(30);
      break;
  }
  return (char***)0;
} // char** DB::HolZeile() {


RS::RS(DB* pdb) 
{
  weisezu(pdb);
}

void RS::weisezu(DB* pdb) 
{
  db=pdb;
  this->result = 0;
#ifdef mitpostgres 
	this->pres=0;
#endif
  // um bei wiederholten Abfragen vorher mysql_free_result aufrufen zu koennen
  obfehl=-1;
}

// wird aufgerufen im template RS::Abfrage
// fuer obverb gibt es die Stufen: -2 (zeige auch bei Fehlern nichts an), -1 (zeige SQL an), 0, 1
int RS::doAbfrage(const size_t aktc/*=0*/,int obverb/*=0*/,uchar asy/*=0*/,int oblog/*=0*/) 
{
  fnr=0;
  int obfalsch=0;
  // fuer wiederholten Abfragen
	switch (db->DBS) {
    case MySQL:
      if (!obfehl)  {
        mysql_free_result(result);
        obfehl=-1;
      }
      num_rows=0;
      num_fields=0;
      if (obverb==1)
        Log("SQL: "+drots+sql+schwarz,1,1);
      if (!db->conn[aktc]) {
       fnr=9999;
       fehler=Txd[T_Datenbank_nicht_zu_oeffnen];
      } else {
        if (asy) {
          obfalsch=mysql_send_query(db->conn[aktc],sql.c_str(),sql.length());
        } else {
          obfalsch=mysql_real_query(db->conn[aktc],sql.c_str(),sql.length());
				}
        if (obfalsch) {
          fnr=mysql_errno(db->conn[aktc]);
          fehler=mysql_error(db->conn[aktc]);
          if (fnr==1138) { // Invalid use of NULL value; bei Spaltenverschiebungen kann oft NOT NULL nicht mehr geaendert werden
            string lsql;
            transform(sql.begin(),sql.end(),std::back_inserter(lsql),::toupper);
            if ((!lsql.find("ALTER TABLE") || !lsql.find("CREATE TABLE")) && lsql.find("NOT NULL")!=string::npos) {
              lsql=caseersetze(sql,"NOT NULL","");
              if (!mysql_real_query(db->conn[aktc],lsql.c_str(),lsql.length())) goto erfolg;
              else {
                fnr=mysql_errno(db->conn[aktc]);
                fehler=mysql_error(db->conn[aktc]);
              }
            } // if ((!lsql.find("ALTER TABLE") || !lsql.find("CREATE TABLE")) && lsql.find("NOT NULL")!=string::npos) 
          } // if (fnr==1138)
          obfehl=1;
					string aktcs=ltoan(aktc);
          Log("aktc: "+drots+aktcs+": "+schwarz+Txd[T_Fehler_db]+drots+ltoan(fnr)+schwarz+" (\""+fehler+"\") in doAbfrage, sql: "+
              tuerkis+sql+schwarz,(fnr!=1406 && obverb!=-2) || (fnr==1406 && obverb==1),1);
          if (!fehler.find("Disk full"))
          exit(115);
        } else {
erfolg:
          obfehl=0;
          result = mysql_store_result(db->conn[aktc]);
          if (result) {
            num_fields = mysql_num_fields(result);
            num_rows = mysql_num_rows(result);
          } else {
          }
        } // if (mysql_real_query(db->conn[aktc],sql.c_str(),sql.length())) else  
      } // if (!db->conn[aktc]) else
			if (obfehl) if ((fnr!=1406 && obverb && obverb!=-2) || (fnr==1406 && obverb==1)) {
				//		printf("Fehler %u: %s\n", fnr, fehler);
				cerr<<Txd[T_Fehler_db]<<drot<<fnr<<schwarz<<Txd[T_bei_Abfrage]<<blau<<sql<<schwarz<<": "<<endl<<drot<<fehler<<schwarz<<endl;
			}
      break;
    case Postgres:
#ifdef mitpostgres 
			const string ausfstr= "Ausfuehr: "+sql;
			Log(ausfstr+" ...",obverb?-1:0,0);
			pres = PQexec(db->pconn, sql.c_str());
			fnr=PQresultStatus(pres);
			if (fnr == PGRES_COMMAND_OK){
				Log(ausfstr+" ok",obverb==-2?0:obverb,0);
			} else {
				if ((obverb&&obverb!=-2)||oblog) {
					fehler=PQresultErrorMessage(pres);
					if (fehler.find("existiert bereits")!=string::npos) {
						Log(ausfstr+" existierte bereits",obverb,oblog);
					} else {
						uchar zeiggenau=1;
							if (fehler.find("existiert nicht")!=string::npos) {
								Log(ausfstr+" existierte nicht",obverb,oblog);
								zeiggenau=0;
							}
						if (zeiggenau) {
							//	 Log("\b\b\b",logscreen?-1:0,0);
							Log(ausfstr+"mit \""+rot+PQresStatus(PQresultStatus(pres))+schwarz+"\" gescheitert, \nFehlermeldung: '"+rot+fehler+schwarz,1,1);
						} // (errmsg.find("existiert bereits")!=-1)
					}  
				} // (logscreen||oblog)) KLAA
			} // (pres != PGRES_COMMAND_OK && (logscreen||oblog)) KLAA
			if (betroffen) *betroffen=PQcmdTuples(pres);
			PQclear(pres);
#endif
			break;
  } // 	switch (db->DBS)
  return (int)obfehl;
} // RS::doAbfrage


RS::RS(DB* pdb,const char* const psql,const size_t aktc,int obverb) 
{
  weisezu(pdb);
  Abfrage(psql,aktc,obverb);
} // RS::RS(DB* pdb,const char* const psql,const size_t aktc,int obverb) 

RS::RS(DB* pdb,stringstream psqls,const size_t aktc,int obverb) 
{
  const string ueber=psqls.str();
  weisezu(pdb);
  Abfrage(ueber,aktc,obverb);
} // RS::RS(DB* pdb,stringstream psqls,const size_t aktc,int obverb) 

RS::RS(DB* pdb,const string& psql,const size_t aktc,int obverb) 
{
  weisezu(pdb);
  Abfrage(psql,aktc,obverb);
} // RS::RS(DB* pdb,const string& psql,const size_t aktc,int obverb) 

RS::~RS() 
{
  if (db)
    switch (db->DBS) {
      case MySQL:
        if (!obfehl) {
          mysql_free_result(result);
          obfehl=-1;
        }
        break;
      case Postgres:
		  caup<<"hier ~RS"<<endl;
			exit(30);
        break;
    }
} // RS::~RS() 

// fuer obverb gibt es die Stufen: -2 (zeige auch bei Fehlern nichts an), -1 (zeige SQL an), 0, 1
void RS::update(const string& utab, vector< instyp > einf,int obverb, const string& bedingung,const size_t aktc/*=0*/,uchar asy/*=0*/) 
{
  ulong locks=0;

  switch (db->DBS) {
    case MySQL:
      isql=string("UPDATE ")+db->dnb+utab+db->dne+" SET ";// string( hier nicht streichen!
      for(uint i = 0;i<einf.size();i++) {
        isql+=db->dnb+einf[i].feld+db->dne;
        isql+=" = ";
        if (einf[i].obkeinwert)
          if (einf[i].wert.find(' ')==string::npos)
            isql+=(einf[i].wert); // z.B. `althyla` = null
          else
            isql+=db->dnb+(einf[i].wert)+db->dne; // z.B. `althyla`=`hyla`
        else
          isql+=(einf[i].wert);
        if (i<einf.size()-1)
          isql+=", ";
      } //       for(uint i = 0;i<einf.size();i++)
      isql+=" WHERE ";
      isql+=bedingung;
      break;
    case Postgres:
		  caup<<"hier update 1"<<endl;
			exit(31);
      break;
  } // switch (db->DBS) 


  switch (db->DBS) {
    case MySQL:
      {
        char ***cerg;
        string altsqlm;
        RS sqlm(db,"SHOW VARIABLES LIKE 'sql_mode'",aktc,obverb);
        if (!sqlm.obfehl) while (cerg=sqlm.HolZeile(),cerg?*cerg:0) {
          if (*(*cerg+1)) if (!strcmp(*(*cerg+1),"STRICT_ALL_VARIABLES")) {
            altsqlm=*(*cerg+1);
            Abfrage("SET sql_mode = 'STRICT_ALL_TABLES'",aktc,obverb);
          } // if (*(*cerg+1)) if (!strcmp(*(*cerg+1),"STRICT_ALL_VARIABLES")) 
        } // if (!sqlm.obfehl) while (cerg=sqlm.HolZeile(),cerg?*cerg:0) 
        for (int iru=0;iru<2;iru++) { // interne Runde
          Abfrage(isql,aktc,obverb,asy);
          if (!obfehl) {
						// nach Gebrauch loeschen
						isql.clear();
						break;
          }  else {
            Log(tuerkiss+"SQL: "+schwarz+isql,(fnr!=1406 && obverb!=-2) || (fnr==1406 && obverb==-1),1);
            const string fmeld=mysql_error(db->conn[aktc]);
            Log(mysql_error(db->conn[aktc]),(fnr!=1406 && obverb!=-2) || (fnr==1406 && obverb==-1),1);
            if (fnr==1406) {
              db->erweitern(utab,einf,aktc,obverb,0);
            }  else if (fnr==1213) { // Deadlock found
              locks++;
              mysql_commit(db->conn[aktc]);
              continue;
            } else if (fnr==1366) { // Incorrect string value
              db->machbinaer(utab,aktc,fmeld,0);
            } else {
              cout<<rot<<Txk[T_Fehler]<<schwarz<<fnr<<Txd[T_bei_sql_Befehl]<<isql<<endl;
              break; 
            } //             if (fnr==1406) else else else 
          } //   if (!obfehl) else
        } //  for (int iru=0;iru<2;iru++) 
        if (!altsqlm.empty()) 
          Abfrage("SET sql_mode = '"+altsqlm+"'",aktc,obverb);
      } // case
      break;
    case Postgres:
		  caup<<"hier update 2"<<endl;
			exit(32);
      break;
  } //   switch (db->DBS)
} // void RS::update(const string& utab, vector< instyp > einf,int obverb, const string& bedingung,uchar asy) 

/*
	 sammeln=1 mit Puffer (isql) anfangen
	 sammeln=0 ohne Puffer/Puffer auf Datenbank schreiben
 */
// fuer obverb gibt es die Stufen: -2 (zeige auch bei Fehlern nichts an), -1 (zeige SQL an), 0, 1
void RS::insert(const string& itab, vector< instyp > einf,const size_t aktc/*=0*/,uchar sammeln/*=0*/,
		int obverb/*=0*/,string *id/*=0*/,uchar eindeutig/*=0*/,uchar asy/*=0*/,svec *csets/*=0*/) 
{
	ulong locks=0;
	uchar obhauptfehl=0;
  static uchar dochanfangen=0; // => bei Erreichen von maxzaehler in der naechsten Runde neu anfangen
  static unsigned long zaehler=0; // Zahl der tatsaechlich einzufuegenden Datensaetze 
  //1. falls 0, dann auch Kopfzeile nicht behandeln, 2. falls Maxzaehler erreicht, dann Zwischeneinfuegen
  const int maxzaehler=100; // wg. Performance: Maximalzahl fuer Sammelinsert
  static unsigned long *maxl=0; // fuer Feldlaengenkorrekturen 
  // <<"insert in "<<drot<<itab<<schwarz<<" anfangen: "<<(int)anfangen<<" sammeln: "<<(int)sammeln<<endl;
  uchar obeinfuegen=1; // Datensatz einfuegen, da noch nicht vorhanden
	uchar anfangen=isql.empty();
  if (id) *id="";
  if (dochanfangen) {
    anfangen=1;
    dochanfangen=0;
  } //   if (dochanfangen)
  if (anfangen)
    zaehler=0;
  if (anfangen) {
    if (maxl) {
      delete[] maxl; maxl=0;
    }
  } //   if (anfangen)
  if (!maxl) {
    maxl= new unsigned long[einf.size()];
    for (unsigned long k=0;k<einf.size();k++){
      maxl[k]=0;
    }
  } //   if (!maxl)
  for (unsigned long k=0;k<einf.size();k++){
    if (einf[k].wert.length()>maxl[k]) {
      maxl[k]=einf[k].wert.length();
    }
  } //   for (unsigned long k=0;k<einf.size();k++)
  if (eindeutig) {
    string autoz;
    stringstream aut; // , autid;
    switch (db->DBS) {
      case MySQL:
        aut/*id*/<<"SELECT column_name FROM information_schema.columns WHERE table_schema='"<<db->db<<
          "' AND table_name = '"<<itab<<"' AND extra = 'auto_increment'";
        Abfrage(aut.str().c_str(),aktc,obverb);
        obhauptfehl=obfehl;
        if (!obfehl) {
          autoz=*HolZeile()[0];
          // Datensatz schon vorhanden?
          aut.str(std::string()); aut.clear();
          aut<<"SELECT `"<<autoz<<"` FROM `"<<itab<<"` WHERE ";
          for(uint i=0;i<einf.size();i++){
            if (i) aut<<" AND ";
            aut<<db->dnb<<einf[i].feld<<db->dne<<"="<<einf[i].wert;
          }
          Abfrage(aut.str(),aktc,obverb);
          if (!obfehl) {
            char*** erg= HolZeile();
            if (*erg) {
              if (id) *id=*erg[0];
              obeinfuegen=0;
            } //             if (*erg)
            break;
            // Feld zu kurz
          } else {
            Log(string(Txd[T_Fehler_beim_Pruefen_auf_Vorhandensein_des_Datensatzes])+mysql_error(db->conn[aktc]),1,1);
          } // (!obfehl)
        } // (!obfehl)
        break;
      case Postgres:
		  caup<<"hier insert 1"<<endl;
			exit(35);
        break;
    } // switch (db->DBS)
  } // eindeutig
  if (obeinfuegen) {
    if (einf.size()) zaehler+=1;
    if (!anfangen && zaehler==maxzaehler) {
      sammeln=0;
      dochanfangen=1;
    } //     if (!anfangen && zaehler==maxzaehler)
  } //   if (obeinfuegen)

  if (anfangen) {
    switch (db->DBS) {
      case MySQL:
        isql=string("INSERT INTO ")+db->dnb+itab+db->dne+'('; // string( hier nicht streichen!
        for(uint i = 0;i<einf.size();i++) {
          if (i) isql+=',';
          isql+=db->dnb+einf[i].feld+db->dne;
        }
        isql+=") VALUES(";
        break;
      case Postgres:
		  caup<<"hier insert 2"<<endl;
			exit(36);
        break;
    } // switch (db->DBS) 
  } // if (obeinfuegen)

  if (obeinfuegen) {
    switch (db->DBS) {
      case MySQL:
				if (einf.size()) {
					if (zaehler>1) isql+=",(";
					for(uint i = 0;i<einf.size();i++) {
						if (i) {
							isql+=',';
						} //           if (i)
						isql+=(einf[i].wert);
					} //         for(uint i = 0;i<einf.size();i++)
					isql+=")";
				} // 				if (einf.size())
        break;
      case Postgres:
		  caup<<"hier insert 3"<<endl;
			exit(37);
			break;
		} // switch (db->DBS) 
  } // if (obeinfuegen)

  if (!sammeln)if (zaehler) {
		switch (db->DBS) {
      case MySQL:
        {
          char ***cerg;
          string altsqlm;
          RS sqlm(db,"SHOW VARIABLES LIKE 'sql_mode'",aktc,obverb);
          if (!sqlm.obfehl) while (cerg=sqlm.HolZeile(),cerg?*cerg:0) {
            if (*(*cerg+1)) if (!strcmp(*(*cerg+1),"STRICT_ALL_VARIABLES")) 
              altsqlm=*(*cerg+1);
            Abfrage("SET sql_mode = 'STRICT_ALL_TABLES'",aktc,obverb);
          }
           // interne Runde
          for (int iru=0;iru<2;iru++) {
						for(size_t iiru=0;iiru<(csets?csets->size():1);iiru++) {
						  if (csets)
								RS zs(db,"SET NAMES '"+csets->at(iiru)+"'",aktc,/*obverb=*/1);
							Abfrage(isql,aktc,obverb,asy);
							if (csets) if (iiru)
								RS zs(db,"SET NAMES '"+csets->at(0)+"'",aktc,/*obverb=*/1);
							if (!fnr) break;
						} // 						for(size_t iiru=0;iiru<(csets?csets->size():1);iiru++)
            if (id) {
              if (obfehl) *id="null";
              else *id=ltoan(mysql_insert_id(db->conn[aktc]));
            } // if (id)
            if (!obfehl) {
							// nach Gebrauch loeschen
							isql.clear();
							break;
            }  else {
							Log(tuerkiss+"SQL: "+schwarz+isql,(fnr!=1406 && obverb!=-2) || (fnr==1406 && obverb==-1),1);
              const string fmeld=mysql_error(db->conn[aktc]);
              Log(fmeld,(fnr!=1406 && obverb!=-2) || (fnr==1406 && obverb==-1),1);
              if (fnr==1406){
                db->erweitern(itab,einf,aktc,obverb, sammeln || (!sammeln && !anfangen),maxl);
              }  else if (fnr==1213){ // Deadlock found
                locks++;
                mysql_commit(db->conn[aktc]);
                continue;
              } else if (fnr==1366) { // Incorrect string value
                db->machbinaer(itab,aktc,fmeld,0);
              } else {
								cerr<<rot<<Txk[T_Fehler]<<schwarz<<fnr<<Txd[T_bei_sql_Befehl]<<isql<<endl;
								exit(113);
                break; 
              } // if (fnr==1406) else else else
            } //             if (id) else else else
          } //  for (int iru=0;iru<2;iru++) 
          if (!altsqlm.empty()) 
            Abfrage("SET sql_mode = '"+altsqlm+"'",aktc,obverb);
        } // case MySQL
        break;
      case Postgres:
		  caup<<"hier insert 4"<<endl;
			exit(38);
			break;
		} // 		switch (db->DBS)
  }  // if (!sammeln)if (zaehler)
  if (!sammeln) if (!obhauptfehl){
    if (maxl) {
      delete[] maxl; maxl=0;
    }
  } //   if (!sammeln) if (!obhauptfehl)
} // int DB::insert(vector< instyp > einf,const char** erg,int anfangen=1,int sammeln=0) 

void DB::prueffunc(const string& pname, const string& body, const string& para, const size_t aktc, int obverb, int oblog)
{
  Log(violetts+Txd[T_prueffunc]+schwarz+" "+pname,obverb,oblog);
  const string mhost = host=="localhost"?host:"%";
  const string owner="`"+user+"`@`"+mhost+"`";
  for(uchar runde=0;runde<2;runde++) {
    uchar fehlt=1;
		RS rs0(this,"SHOW FUNCTION STATUS WHERE db='"+db+"' AND name='"+pname+"';",aktc,obverb);
		if (!rs0.obfehl) {
			if (rs0.result->row_count){
				RS rs(this,"SHOW CREATE FUNCTION `"+pname+"`",aktc,obverb);
				char ***cerg;
				while (cerg=rs.HolZeile(),cerg?*cerg:0) {
					for(uint i=1;i<=2;i++) {
						if (*(*cerg+i)) if (strstr(*(*cerg+i),body.c_str())) if (strstr(*(*cerg+i),owner.c_str())) {
							fehlt=0;
							break; // for(uint
						} // 						if (*(*cerg+i)) if (strstr(*(*cerg+i),body.c_str())) if (strstr(*(*cerg+i),owner.c_str()))
					} // 					for(uint i=1;i<=2;i++)
					break; // while(cerg=
				} // 				while (cerg=rs.HolZeile(),cerg?*cerg:0)
			} // 			if (rs0.result->row_count)
		} // 		if (!rs0.obfehl)
    if (fehlt) {
      DB *aktMyp;
      if (!runde) aktMyp=this; else {
        DB MySup(DBS,this->linstp,this->host.c_str(),"root",this->rootpwd.c_str(),0,this->db.c_str(),0,0,0,obverb,oblog);
        aktMyp=&MySup;
      }
      string proc= "DROP FUNCTION IF EXISTS `"+pname+"`";
      RS rs0(aktMyp, proc,aktc,obverb);
      proc = "CREATE DEFINER="+owner+" FUNCTION `"+pname+"`\n"+para+body;
      RS rs1(aktMyp, proc,aktc,obverb);
    } else 
      break; // for(uchar runde=0
  } //   for(uchar runde=0;runde<2;runde++)
} // void DB::prueffunc(const string& pname, const string& body, const string& para, int obverb, int oblog)

void RS::clear()
{
  sql.clear();
  obfehl=-1;
  fehler="";
  fnr=0;
  result=NULL;
  row=NULL;
  num_fields=0;
  // table.clear();
  feld.clear();
  typ.clear(); 
  lenge.clear();
  prec.clear();
  kommentar.clear();
} // clear
