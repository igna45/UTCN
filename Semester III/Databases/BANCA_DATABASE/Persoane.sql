CREATE TABLE Persoane (
	IDPERS int NOT NULL ,
	NUME varchar (20) NOT NULL ,
	ADRESA varchar (20) NOT NULL ,
	GEN varchar (1) NOT NULL ,
	DATA_NASTERII date NOT NULL,
	EMAIL varchar(25) NOT NULL,
	DATA_SYSDATE date NULL);

ALTER TABLE Persoane
ADD CONSTRAINT PK_Persoane PRIMARY KEY (IDPERS);

ALTER TABLE Persoane ADD 
  CONSTRAINT CK_PersoaneGen CHECK (GEN IN ('M', 'F'));

ALTER TABLE Persoane ADD 
  CONSTRAINT CK_PersoanaDataNastere([DATA_NASTERII]>=[DATA_SYSDATE] AND [DATA_NASTERII]<=[DATA_NASTERII])

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935654, 'Badic Mihai', 'ICPE SA', 'M', '12-Feb-2000', 'badeamihai@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935650, 'Bidian Dan', '468 Brasov', 'M', '09-Jun-1989', 'bidiandan@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935651, 'Bicu Aida', 'ICMET', 'F', '14-Aug-2001', 'bicuaida@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935652, 'Bogdan Octavian', '238 Sibiu', 'M', '12-Oct-1980', 'bogdanoctavian@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935653, 'Cazacu Maria', 'ICPE FR', 'F', '22-Sep-2003', 'cazacumaria@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935660, 'Lascu Daniel', 'SE nr 4', 'M', '12-Dec-2002', 'lascudaniel@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935655, 'Munteanu Adrian', 'ICL 45', 'M', '24-May-1979', 'munteanuadrian@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935656, 'Nicoara Tania', 'ICMET 4', 'F', '28-Mar-1985', 'nicoaratania@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935657, 'Pacurar Claudia', 'AGIR', 'F', '13-Jul-1981', 'pacurarclaudia@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (935659, 'Teodor Emil', 'DPESR nr 78', 'M', '12-Sep-1982', 'teodoremil@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (102301, 'Mircea Emil', 'Str. Princip nr. 12', 'M', '12-Sep-1998', 'mirceaemil@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (100, 'Popa Valentin', 'SA OP', 'M', '19-Nov-2001', 'popavalentin@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (900, 'Cristian Minge', 'AS PO', 'M', '19-Nov-2002', 'cristianminge@');

Insert into Persoane (IDPERS, NUME, ADRESA, GEN, DATA_NASTERII, EMAIL) values (901, 'Mariana Stefania', 'DSF 56', 'F', '12-Dec-2002', 'marianastefania@');



