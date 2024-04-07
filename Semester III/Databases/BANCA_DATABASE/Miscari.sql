CREATE TABLE Miscari (
	NRCARD int NOT NULL ,
	DATA_ORA timestamp NOT NULL ,
	VALOARE int NOT NULL,
	SCOP varchar2(20) NOT NULL);


ALTER TABLE Miscari
ADD CONSTRAINT PK_Miscari PRIMARY KEY (NRCARD, DATA_ORA);


ALTER TABLE Miscari
ADD CONSTRAINT FK_MiscariCarduri
FOREIGN KEY (NRCARD) REFERENCES Carduri(NRCARD);

ALTER TABLE Miscari
ADD CONSTRAINT CHK_MiscariScop CHECK (scop!='rata' or (scop='rata' AND valoare<=200));



Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43524442, convert(DATETIME, '02-Sep-2022 10:39:14 AM'), 400, 'facturi');

--Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526170, convert(DATETIME, '22-Sep-2022 10:39:14 AM'), 200, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526171, convert(DATETIME, '16-Aug-2022 12:23:20 PM'), 2000, 'plati cash');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526172, convert(DATETIME, '12-Dec-2022 05:30:12 PM'), 290, 'facturi');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526173, convert(DATETIME, '02-Oct-2022 06:10:34 PM'), 190, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526174, convert(DATETIME, '22-Jan-2022 06:49:10 PM'), 1500, 'plati cash');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526175, convert(DATETIME, '07-Feb-2022 05:29:49 PM'), 150, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526176, convert(DATETIME, '09-Jul-2022 06:36:29 PM'), 500, 'facturi');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526177, convert(DATETIME, '18-Sep-2022 06:59:59 PM'), 50, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526178, convert(DATETIME, '15-Nov-2022 05:21:59 PM'), 350, 'facturi');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526179, convert(DATETIME, '02-May-2022 11:23:32 AM'), 3000, 'plati cash');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (43526180, convert(DATETIME, '05-Sep-2022 05:56:20 PM'), 190, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (102301, convert(DATETIME, '01-Jan-2022 05:56:20 PM'), 80, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (102301, convert(DATETIME, '01-Jan-2021 06:56:20 PM'), 180, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (102301, convert(DATETIME, '20-Jun-2022 05:26:20 PM'), 60, 'rata');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (102301, convert(DATETIME, '29-Jul-2022 08:26:20 PM'), 600, 'facturi');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (102301, convert(DATETIME, '30-Aug-2022 03:26:20 PM'), 1000, 'plati cash');

Insert into Miscari (NRCARD, DATA_ORA, VALOARE, SCOP) values (102301, convert(DATETIME, '19-Dec-2022 02:26:20 PM'), 800, 'plati cash');

