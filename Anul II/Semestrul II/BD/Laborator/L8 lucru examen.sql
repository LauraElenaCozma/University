-- L8
/*S? se creeze tabelul ANGAJATI_pnu (pnu se alcatuie?te din prima liter? din prenume ?i primele
dou? din numele studentului) corespunz?tor schemei rela?ionale:
ANGAJATI_pnu(cod_ang number(4), nume varchar2(20), prenume varchar2(20), email char(15),
data_ang date, job varchar2(10), cod_sef number(4), salariu number(8, 2), cod_dep number(2))
în urm?toarele moduri:
a) f?r? precizarea vreunei chei sau constrângeri;
b) cu precizarea cheilor primare la nivel de coloan? si a constrangerilor NOT NULL pentru
coloanele nume ?i salariu;
c) cu precizarea cheii primare la nivel de tabel si a constrângerilor NOT NULL pentru coloanele
nume ?i salariu.
Se presupune c? valoarea implicit? a coloanei data_ang este SYSDATE.*/
--a
CREATE TABLE ANGAJATI_ECO(
    cod_ang number(4),
    nume varchar2(20),
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10), 
    cod_sef number(4), 
    salariu number(8, 2), 
    cod_dep number(2)
    );
    
DROP TABLE angajati_eco;

--b
CREATE TABLE ANGAJATI_ECO(
    cod_ang number(4) PRIMARY KEY,
    nume varchar2(20) not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10), 
    cod_sef number(4), 
    salariu number(8, 2) not null, 
    cod_dep number(2)
    );
    
--c
CREATE TABLE ANGAJATI_ECO(
    cod_ang number(4),
    nume varchar2(20) not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10), 
    cod_sef number(4), 
    salariu number(8, 2) not null, 
    cod_dep number(2),
    constraint pk_ang_eco primary key(cod_ang)
    );
    
/*2. Insert*/
INSERT INTO angajati_eco (cod_ang, nume, prenume, email, data_ang, job, cod_sef, salariu, cod_dep)
VALUES (100, 'Nume1', 'Prenume1', 'Nume1', null, 'Director', null, 20000, 10);
INSERT INTO angajati_eco (cod_ang, nume, prenume, email, data_ang, job, cod_sef, salariu, cod_dep)
VALUES (103, 'Nume4', 'Prenume4', 'Nume4', null, 'Inginer', 100, 9000, 20);
INSERT INTO angajati_eco
VALUES (101, 'Nume2', 'Prenume2', 'Nume2', TO_DATE('02-02-2004','DD-MM-YYYY'), 'Inginer', 100, 5000, 20,null);
INSERT INTO angajati_eco
VALUES (102, 'Nume3', 'Prenume3', 'Nume3', TO_DATE('05-06-2000','DD-MM-YYYY'), 'Analist', 101, 5000, 20,null);
INSERT INTO angajati_eco
VALUES (101, 'Nume2', 'Prenume2', 'Nume2', TO_DATE('02-02-2004','DD-MM-YYYY'), 'Inginer', 100, 5000, 20,null);
INSERT INTO angajati_eco
VALUES (104, 'Nume5', 'Prenume5', 'Nume5', null, 'Analist', 101, 3000, 30);


/*Crea?i tabelul ANGAJATI10_pnu, prin copierea angaja?ilor din departamentul 10 din tabelul
ANGAJATI_pnu. Lista?i structura noului tabel. Ce se observ??*/
CREATE TABLE angajati0_eco
AS SELECT * FROM angajati_eco
WHERE cod_dep = 10;

SELECT * FROM angajati_eco;
SELECT * FROM USER_CONSTRAINTS WHERE TABLE_NAME LIKE 'ANGAJATI0_ECO%';

/*4.Introduceti coloana comision in tabelul ANGAJATI_pnu. Coloana va avea tipul de date
NUMBER(4,2).*/
ALTER TABLE angajati_eco
ADD (comision NUMBER(4, 2));

/*5. Este posibil? modificarea tipului coloanei salariu în NUMBER(6,2)?*/
ALTER TABLE angajati_eco
MODIFY(salariu NUMBER(6, 2));

ALTER TABLE angajati_eco
MODIFY(salariu DEFAULT 1000);

/*7.Modifica?i tipul coloanei comision în NUMBER(2, 2) ?i al coloanei salariu la NUMBER(10,2), în
cadrul aceleia?i instruc?iuni.*/
ALTER TABLE angajati_eco
MODIFY(comision NUMBER(2, 2),
    salariu number(10, 2));
desc angajati_eco

/*8.Actualizati valoarea coloanei comision, setând-o la valoarea 0.1 pentru salaria?ii al c?ror job
începe cu litera A. (UPDATE)*/
UPDATE angajati_eco
SET comision = 0.1
WHERE UPPER(SUBSTR(job, 1, 1)) = 'A';

/*9.Modifica?i tipul de date al coloanei email în VARCHAR2.*/
ALTER TABLE angajati_eco
MODIFY (email varchar2(20));

/*10. Ad?uga?i coloana nr_telefon în tabelul ANGAJATI_pnu, setându-i o valoare implicit?.*/
ALTER TABLE angajati_eco
ADD (nr_telefon varchar2(11) default 0700000000);

/*11. Suprima?i coloana nr_telefon.*/
ALTER TABLE angajati_eco
DROP COLUMN nr_telefon;
ROLLBACK;

DELETE FROM angajati0_eco;

/*12. Redenumi?i tabelul ANGAJATI_pnu în ANGAJATI3_pnu.*/
RENAME angajati_eco TO angajati3_eco;
SELECT * from angajati3_eco;
RENAME angajati3_eco TO angajati_eco;

/*15. Crea?i ?i tabelul DEPARTAMENTE_pnu,*/
CREATE TABLE departamente_eco (
    cod_dep number(2), 
    nume varchar2(15) not null,
    cod_director number(4));
    
desc departamente_eco

insert into departamente_eco values(10, 'Administrativ', 100);
insert into departamente_eco values(20, 'Proiectare', 101);
insert into departamente_eco values(30, 'Programare', null);

/*17. Se va preciza apoi cheia primara cod_dep, f?r? suprimarea ?i recreerea tabelului (comanda
ALTER).*/
ALTER TABLE departamente_eco
ADD CONSTRAINT departamente_eco_pk PRIMARY KEY(cod_dep);

/*18. S? se precizeze constrângerea de cheie extern? pentru coloana cod_dep din ANGAJATI_pnu:
a) f?r? suprimarea tabelului (ALTER TABLE);
b) prin suprimarea ?i recrearea tabelului, cu precizarea noii constrângeri la nivel de coloan?
({DROP, CREATE} TABLE). De asemenea, se vor mai preciza constrângerile (la nivel de coloan?,
dac? este posibil):*/
ALTER TABLE angajati_eco
ADD CONSTRAINT angajati_eco_fk FOREIGN KEY(cod_dep) REFERENCES departamente_eco(cod_dep);

DROP TABLE angajati_eco;

--b
CREATE TABLE ANGAJATI_ECO(
    cod_ang number(4) PRIMARY KEY,
    nume varchar2(20) not null,
    prenume varchar2(20),
    email char(15) UNIQUE,
    data_ang date default sysdate,
    job varchar2(10), 
    cod_sef number(4), 
    salariu number(8, 2) not null, 
    comision number (4, 2),
    cod_dep number(2) REFERENCES DEPARTAMENTE_ECO(cod_dep) CHECK (cod_dep > 0),
    CONSTRAINT ang_eco_uq1 UNIQUE(nume, prenume),
    CONSTRAINT ang_eco_ck1 CHECK (salariu > comision * 100)
    );
    
--c
CREATE TABLE ANGAJATI_ECO(
    cod_ang number(4),
    nume varchar2(20) not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10), 
    cod_sef number(4), 
    salariu number(8, 2) not null, 
    comision number (4, 2),
    cod_dep number(2),
    CONSTRAINT ang_eco_pk PRIMARY KEY(cod_ang),
    CONSTRAINT ang_eco_uq2 UNIQUE(email),
    CONSTRAINT ang_eco_uq1 UNIQUE(nume, prenume),
    CONSTRAINT ang_eco_ck1 CHECK (salariu > comision * 100),
    CONSTRAINT ang_eco_ck2 CHECK (cod_dep > 0),
    CONSTRAINT ang_eco_fk FOREIGN KEY(cod_dep) REFERENCES DEPARTAMENTE_ECO(cod_dep)
    );
    
DROP TABLE departamente_eco;
SELECT constraint_name, constraint_type, table_name
FROM user_constraints
WHERE lower(table_name) IN ('angajati_eco', 'departamente_eco');

/*24.Introduce?i constrângerea NOT NULL asupra coloanei email.*/
ALTER TABLE angajati_eco
MODIFY email NOT NULL;

/*25. (Incerca?i s?) ad?uga?i o nou? înregistrare în tabelul ANGAJATI_pnu, care s? corespund? codului
de departament 50. Se poate?*/
INSERT INTO angajati_eco (cod_ang, nume, prenume, email, data_ang, job, cod_sef, salariu, cod_dep)
VALUES (105, 'Nume6', 'Prenume6', 'Nume6', null, 'Director', null, 20000, 50); -- parent key not found

/*26. Ad?uga?i un nou departament, cu numele Analiza, codul 60 ?i directorul null în
DEPARTAMENTE_pnu. COMMIT.*/
insert into departamente_eco values(60, 'Analiza', null);
commit;
DELETE FROM departamente_eco
WHERE cod_dep = 60;
rollback;

DELETE FROM departamente_eco
WHERE cod_dep = 20; --nu se poate
ROLLBACK;
SELECT * FROM departamente_eco;
SELECT * FROM angajati_eco;

INSERT INTO angajati_eco (cod_ang, nume, prenume, email, data_ang, job, cod_sef, salariu, cod_dep)
VALUES (106, 'Nume7', 'Prenume7', 'Nume7', null, 'Inginer', 114, 9000, 20);

ALTER TABLE angajati_eco
ADD CONSTRAINT ang_eco_ck3 CHECK (salariu < 30000);