CREATE TABLE Conturi (
	NRCONT varchar2 (30) NOT NULL ,
	SOLD float (20) NULL,
	IDPERS int NOT NULL);

ALTER TABLE Conturi
ADD CONSTRAINT PK_Conturi PRIMARY KEY (NRCONT);

ALTER TABLE Conturi
ADD CONSTRAINT FK_ConturiPersoana
FOREIGN KEY (IDPERS) REFERENCES Persoane(IDPERS);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('401', 1000, 935656);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('101', 2000, 935656);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('400', 1000, 935656);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('102', 1000, 935657);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('103', 2500, 935652);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('104', 4500, 935659);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('105', 1500, 935650);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('106', 1100, 935653);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('107', 900, 935654);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('108', 3400, 935651);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('109', 2800, 935655);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('110', 4700, 935660);

Insert into Conturi (NRCONT, SOLD, IDPERS) values ('200', 5000, 102301);
