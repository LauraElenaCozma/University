
        
-- Laborator 8 --
CREATE TABLE ANGAJATI_LCO (
        cod_ang NUMBER(4) PRIMARY KEY,
        nume VARCHAR2(20) NOT NULL,
        prenume VARCHAR2(20),
        email CHAR(15),
        data_ang DATE,
        job VARCHAR2(10),
        cod_sef NUMBER(4),
        salariu NUMBER(8, 2) NOT NULL,
        cod_dep NUMBER(2));
DESC angajati_lco

DROP TABLE angajati_lco;

--C
select * from angajati_lco;
DROP TABLE angajati_lco;
CREATE TABLE ANGAJATI_LCO (
        cod_ang NUMBER(4),
        nume VARCHAR2(20) NOT NULL,
        prenume VARCHAR2(20),
        email CHAR(15),
        data_ang DATE,
        job VARCHAR2(10),
        cod_sef NUMBER(4),
        salariu NUMBER(8, 2) NOT NULL,
        cod_dep NUMBER(2),
        CONSTRAINT cod_ang_pk PRIMARY KEY(cod_ang));

--d
CREATE TABLE ANGAJATI_LCO (
        cod_ang NUMBER(4),
        nume VARCHAR2(20) NOT NULL,
        prenume VARCHAR2(20),
        email CHAR(15),
        data_ang DATE default SYSDATE,
        job VARCHAR2(10),
        cod_sef NUMBER(4),
        salariu NUMBER(8, 2) NOT NULL,
        cod_dep NUMBER(2),
        CONSTRAINT ang_lco_pk PRIMARY KEY(cod_ang)
        );
        
-- Exercitiul 2 --
INSERT INTO angajati_lco(cod_ang, nume, prenume, data_ang, job, salariu, cod_dep)
VALUES (100, 'Nume1', 'Prenume1',null,'Director', 20000,10);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (101, 'Nume2', 'Prenume2','Nume2',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer', 100, 20000,10);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (102, 'Nume3', 'Prenume3','Nume3',TO_DATE('05-06-2000','dd-mm-yyyy'),'Analist', 101, 50000,20);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (103, 'Nume4', 'Prenume4',null,null,'Inginer', 100, 90000,20);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (104, 'Nume5', 'Prenume5','Nume5',null,'Analist', 101, 3000,30);

-- Exercitiul 3
CREATE TABLE angajati10_lco
AS SELECT * 
FROM angajati_lco 
WHERE cod_dep = 10;
SELECT * FROM angajati10_lco;
desc angajati_lco
desc angajati10_lco
-- doar constrangerile not null se copiaza, nu si primary key

-- Exercitiul 4
ALTER TABLE angajati_lco 
ADD comision NUMBER(4,2);
desc angajati_lco

-- Exercitiul 5 
--daca avem date in tabel nu ne da voie, putem sa marim dimensiunea;column to be modified must be empty to decrease precision or scale
ALTER TABLE angajati_lco 
MODIFY salariu NUMBER(6,2); --nu se poate


-- Exercitiul 6
ALTER TABLE angajati_lco 
MODIFY salariu DEFAULT 0;
-- se vor aplica dupa aceasta coloana

-- Exercitiul 7
ALTER TABLE angajati_lco 
MODIFY (comision NUMBER(2,2), salariu NUMBER(10,2));

-- Exercitiul 8 
/*Actualizati valoarea coloanei comision, setând-o la valoarea 0.1 pentru salaria?ii al c?ror job
începe cu litera A. (UPDATE)*/
UPDATE angajati_lco
SET comision = 0.1
WHERE UPPER(job) LIKE 'A%';

-- Exercitiul 9
ALTER TABLE angajati_lco 
MODIFY email VARCHAR2; --nu ruleaza pentru ca nu avem dimensiunea

-- Exercitiul 10
ALTER TABLE angajati_lco 
ADD nr_telefon NUMBER DEFAULT 0;  --merge, putem folosi fara sa indicam nr dde cifre, la varchar2 nu

-- Exercitiul 11
SELECT * FROM angajati_lco;

ALTER TABLE angajati_lco
DROP column nr_telefon;
--ce efect are rollback?
ROLLBACK; --nu revine inapoi

-- Exercitiul 12
RENAME angajati_lco TO angajati3_lco;

-- Exercitiul 13
SELECT * FROM TAB;
RENAME angajati3_lco TO angajati_lco;

-- Exercitiul 14
TRUNCATE TABLE angajati_lco ; --a sters tot ce e inauntru
ROLLBACK;
--a sters si nu mai poti da inapoi dupa rollback

--Exeercitiul 15
CREATE TABLE departamente_lco (cod_dep NUMBER(2), 
                                nume VARCHAR2(15) NOT NULL,
                                cod_director NUMBER(4));
DROP TABLE departamente_lco;

--Exercitiul 16
INSERT INTO departamente_lco(cod_dep, nume, cod_director)
VALUES (10, 'Administrativ', 100);

INSERT INTO departamente_lco(cod_dep, nume, cod_director)
VALUES (20, 'Proiectare', 101);

INSERT INTO departamente_lco(cod_dep, nume, cod_director)
VALUES (30, 'Programare', null);

--Exercitiul 17
ALTER TABLE departamente_lco
ADD CONSTRAINT dep_pk PRIMARY KEY(cod_dep);

--trebuie sa avem grija cand adaugam o constrangere sa nu fie incalcata de val anterioare
-- Exercitiul 18
ALTER TABLE angajati_lco
ADD CONSTRAINT emp_lco_fk FOREIGN KEY (cod_dep) REFERENCES DEPARTAMENTE_ADO(cod_dep); 

--b
DROP TABLE angajati_lco;
CREATE TABLE ANGAJATI_LCO (
        cod_ang NUMBER(4) PRIMARY KEY,
        nume VARCHAR2(20) NOT NULL,
        prenume VARCHAR2(20),
        email CHAR(15) UNIQUE,
        data_ang DATE default SYSDATE,
        job VARCHAR2(10),
        cod_sef NUMBER(4) REFERENCES ANGAJATI_LCO(cod_ang),
        salariu NUMBER(8, 2) NOT NULL,
        cod_dep NUMBER(2) CHECK(cod_dep > 0) REFERENCES DEPARTAMENTE_LCO(cod_dep),
        comision NUMBER(2, 2),
        CONSTRAINT ang_lco_u UNIQUE(nume, prenume),
        CONSTRAINT ang_lco_ck CHECK (salariu > comision * 100)
        );


-- Laborator 8 continuare --

--ex 18 b
CREATE TABLE ANGAJATI_LCO (
        cod_ang NUMBER(4) PRIMARY KEY,
        nume VARCHAR2(20) NOT NULL,
        prenume VARCHAR2(20),
        email CHAR(15) UNIQUE,
        data_ang DATE default SYSDATE,
        job VARCHAR2(10),
        cod_sef NUMBER(4) REFERENCES ANGAJATI_LCO(cod_ang),
        salariu NUMBER(8, 2) NOT NULL,
        cod_dep NUMBER(2) CHECK(cod_dep > 0) REFERENCES DEPARTAMENTE_LCO(cod_dep),
        comision NUMBER(2, 2),
        CONSTRAINT ang_lco_u UNIQUE(nume, prenume),              -- nu se poate la niv de coloana pt ca implica 2 col
        CONSTRAINT ang_lco_ck CHECK (salariu > comision * 100)   -- nu se poate la niv de coloana pt ca implica 2 col
        );
        
-- Exercitiul 19
DROP TABLE angajati_lco;
CREATE TABLE ANGAJATI_LCO (
        cod_ang NUMBER(4),
        nume VARCHAR2(20) NOT NULL,
        prenume VARCHAR2(20),
        email CHAR(15),
        data_ang DATE default SYSDATE,
        job VARCHAR2(10),
        cod_sef NUMBER(4),
        salariu NUMBER(8, 2) NOT NULL,
        cod_dep NUMBER(2),
        comision NUMBER(2, 2),
        CONSTRAINT ang_lco_u UNIQUE(nume, prenume),              -- nu se poate la niv de coloana pt ca implica 2 col
        CONSTRAINT ang_lco_ck CHECK (salariu > comision * 100),   -- nu se poate la niv de coloana pt ca implica 2 col
        CONSTRAINT ang_lco_pk PRIMARY KEY(cod_ang),
        CONSTRAINT ang_lco_fk FOREIGN KEY(cod_sef)  REFERENCES ANGAJATI_LCO(cod_ang),
        CONSTRAINT ang_lco_ck2 CHECK(cod_dep > 0),
        CONSTRAINT ang_lco_fk2 FOREIGN KEY(cod_dep) REFERENCES DEPARTAMENTE_LCO(cod_dep),
        CONSTRAINT ang_lco_u2 UNIQUE(email)
        );
        
-- Exeercitiul 20
INSERT INTO angajati_lco(cod_ang, nume, prenume,email, data_ang, job, salariu, cod_dep)
VALUES (100, 'Nume1', 'Prenume1','sa',null,'Director', 2000,10);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (101, 'Nume2', 'Prenume2','Nume2',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer', 100, 2000,10);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (102, 'Nume3', 'Prenume3','Nume3',TO_DATE('05-06-2000','dd-mm-yyyy'),'Analist', 101, 5000,20);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (103, 'Nume4', 'Prenume4',null,null,'Inginer', 100, 9000,20);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (104, 'Nume5', 'Prenume5','Nume5',null,'Analist', 101, 3000,30);


-- Exercitiul 21
DROP TABLE departamente_lco;
-- nu se poate, deoarece avem constrangere de cheie straina pe cod_dep

-- Exercitiul 22
SELECT * FROM tab;

SELECT * FROM user_tables;

-- Exercitiul 23
SELECT constraint_name, constraint_type, table_name
FROM user_constraints
WHERE lower(table_name) IN ('angajati_lco', 'departamente_lco');

--b
SELECT table_name, constraint_name, column_name
FROM user_cons_columns
WHERE LOWER(table_name) IN ('angajati_lco', 'departamente_lco');

-- Exercitiul 24
ALTER TABLE angajati_lco 
MODIFY email NOT NULL;

UPDATE angajati_lco
SET email = 'EMAIL'
WHERE cod_ang = 100;

-- Exercitiul 25
INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (105, 'Nume6', 'Prenume6','Nume6',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer', 100, 2000,50);
--incercam sa inseram un angajat intr un dep care nu exista; avem constrangere de cheie straina, nu se poate

--Exercitiul 26
INSERT INTO departamente_lco VALUES(60,'Analiza',null);


-- Exercitiul 27
DELETE FROM departamente_lco
WHERE cod_dep = '20';
--avem angajat in acest dep si nu merge

-- Exercitiul 28
DELETE FROM departamente_lco
WHERE cod_dep = '60';
SELECT * FROM departamente_lco;
ROLLBACK;
--nu avem ang in dep 60 si putem sterge


-- Exercitiul 29
INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (106, 'Nume8', 'Prenume8','Nume8',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer', 114, 2000,60);
--nu se poate pt ca nu exista ang 114

-- Ex 30
INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (114, 'Nume7', 'Prenume7','Nume7',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer', 101, 2000,60);

-- inseram mai intai in tabelul parinte si dupa in tabelul copi;

-- Exercitiul 31
ALTER TABLE angajati_lco
DROP CONSTRAINT ang_lco_fk2;

ALTER TABLE angajati_lco
ADD CONSTRAINT ang_lco_fk2 FOREIGN KEY (cod_dep) REFERENCES departamente_lco(cod_dep)
ON DELETE CASCADE;

-- Exercitiul 32
DELETE FROM departamente_lco
WHERE cod_dep = 20;
-- acum s-a sters
SELECT * from angajati_lco;
SELECT * from departamente_lco;
ROLLBACK;
-- Exercitiul 33
ALTER TABLE departamente_lco
ADD CONSTRAINT dep_lco_fk FOREIGN KEY (cod_director) REFERENCES angajati_lco(cod_ang) ON DELETE CASCADE;

-- Exercitiul 34
UPDATE departamente_lco
SET cod_director = 102 WHERE cod_dep = 30;

DELETE FROM angajati_ado WHERE cod_ang = 102;
ROLLBACK;
--recuoerez doar angajatul cu codul 102, dar la director nu se actualizeaza

DELETE FROM angajati_ado WHERE cod_ang = 101;
--constrangere de cheie straina

-- Exercitiul 35
SELECT * FROM angajati_lco;
ALTER TABLE angajati_lco
ADD CONSTRAINT ang_lco_ck3 CHECK(salariu < 30000);

-- Exercitiul 36
UPDATE angajati_lco
SET salariu = 35000 WHERE cod_ang = 100; -- merge

-- Exercitiul 37
ALTER TABLE angajati_lco
MODIFY CONSTRAINT ang_lco_ck3 DISABLE;

ALTER TABLE angajati_lco
MODIFY CONSTRAINT ang_lco_ck3 ENABLE; --nu mai merge pentru ca sunt salarii care nu respecta

