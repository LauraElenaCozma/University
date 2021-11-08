-- Tema laborator 12 --

-- Exercitiul 19 --
/*Suprima?i ?i recrea?i tabelul, specificând toate constrângerile la nivel de tabel (în m?sura în care
este posibil).*/
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
        CONSTRAINT cod_ang_lco_pk PRIMARY KEY(cod_ang),
        CONSTRAINT email_lco_u UNIQUE(email),
        CONSTRAINT ang_lco_u UNIQUE(nume, prenume),
        CONSTRAINT cod_dep_lco_ck CHECK(cod_dep > 0),
        CONSTRAINT ang_lco_ck CHECK (salariu > comision * 100),
        CONSTRAINT cod_dep_lco_fk FOREIGN KEY (cod_dep) REFERENCES DEPARTAMENTE_LCO(cod_dep),
        CONSTRAINT cod_sef_lco_fk FOREIGN KEY (cod_sef) REFERENCES ANGAJATI_LCO(cod_ang)
        );

SELECT * FROM angajati_lco;


-- Exercitiul 20 --
/*Reintroduce?i date în tabel, utilizând (?i modificând, dac? este necesar fi?ierul l8p2.sql.*/
INSERT INTO angajati_lco(cod_ang, nume, prenume, email, data_ang, job, salariu, cod_dep)
VALUES (100, 'Nume1', 'Prenume1','Prenume1',null,'Director', 20000,10);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (101, 'Nume2', 'Prenume2','Nume2',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer', 100, 20000,10);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (102, 'Nume3', 'Prenume3','Nume3',TO_DATE('05-06-2000','dd-mm-yyyy'),'Analist', 101, 50000,20);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (103, 'Nume4', 'Prenume4','Prenume4',null,'Inginer', 100, 90000,20);

INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (104, 'Nume5', 'Prenume5','Nume5',null,'Analist', 101, 3000,30);

-- Exercitiul 21 --
/*Ce se întâmpl? dac? se încearc? suprimarea tabelului departamente_pnu?*/
DROP TABLE departamente_lco;
-- nu se poate deoarece exista o constrangere de cheie straina spre tabelul respectiv
SELECT * FROM departamente_lco;

-- Exercitiul 22 --
/*Analiza?i structura vizualiz?rilor USER_TABLES, TAB, USER_CONSTRAINTS.*/
DESC USER_TABLES
select * from user_tables;
DESC tab
select * from tab;
DESC user_constraints
select * from user_constraints;

-- Exercitiul 23 --
--a Lista?i informa?iile relevante (cel pu?in nume, tip ?i tabel) despre constrângerile asupra tabelelor angajati_pnu ?i departamente_pnu.
SELECT constraint_name, constraint_type, table_name
FROM user_constraints
WHERE LOWER(table_name) IN ('angajati_lco', 'departamente_lco');

-- b Afla?i care sunt coloanele la care se refer? constrângerile asupra tabelelor angajati_pnu ?i departamente_pnu.
SELECT table_name, constraint_name, column_name
FROM user_cons_columns
WHERE LOWER(table_name) IN ('angajati_lco', 'departamente_lco');

-- Exercitiul 24 --
/*Introduce?i constrângerea NOT NULL asupra coloanei email.*/
ALTER TABLE angajati_lco
MODIFY email NOT NULL;
-- nu se poate deeoarece exista inregistrari nule la email
DELETE FROM angajati_lco;
--si acum inseram noi inregistrari

-- Exercitiul 25 --
/*(Incerca?i s?) ad?uga?i o nou? înregistrare în tabelul ANGAJATI_pnu, care s? corespund? codului
de departament 50. Se poate?*/
INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (105, 'Nume6', 'Prenume6','Nume6',null,'Analist', 101, 3000,50);
select * from departamente_lco;
--nu se poate nu exista departamentul 50

-- Exercitiul 26 --
/*Ad?uga?i un nou departament, cu numele Analiza, codul 60 ?i directorul null în
DEPARTAMENTE_pnu. COMMIT.*/
INSERT INTO departamente_lco(cod_dep, nume, cod_director)
VALUES (60, 'Analiza', null);
COMMIT;

-- Exercitiul 27 --
/*(Incerca?i s?) ?terge?i departamentul 20 din tabelul DEPARTAMENTE_pnu. Comenta?i.*/
DELETE FROM departamente_lco
WHERE cod_dep = 20;
--nu se poate; exista o inregitrare in angajati din acest departament
SELECT * FROM angajati_lco;

-- Exercitiul 28 --
/*?terge?i departamentul 60 din DEPARTAMENTE_pnu. ROLLBACK.*/
DELETE FROM departamente_lco
WHERE cod_dep = 60;
ROLLBACK;

-- Exercitiul 29 --
/*29. (Incerca?i s?) introduce?i un nou angajat, specificând valoarea 114 pentru cod_sef. Ce se ob?ine?*/
INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (106, 'Nume7', 'Prenume7','Nume7',TO_DATE('05-06-2000','dd-mm-yyyy'),'Analist', 114, 50000,20);
--integrity constraint (GRUPA44.COD_SEF_LCO_FK) violated - parent key not found
--nu a gasit seful

-- Exercitiul 30 --
/*Ad?uga?i un nou angajat, având codul 114. Incerca?i din nou introducerea înregistr?rii de la
exerci?iul 29.*/
INSERT INTO angajati_lco(cod_ang, nume, prenume, email,data_ang, job, cod_sef,salariu, cod_dep)
VALUES (114, 'Nume6', 'Prenume6','Nume6',TO_DATE('05-06-2000','dd-mm-yyyy'),'Analist', 102, 50000,20);
--terbuie sa inseram mai intai in tabelul cu cheia straina si dupa in tabelul curent

-- Exercitiul 31 --
/*Se dore?te ?tergerea automat? a angaja?ilor dintr-un departament, odat? cu suprimarea
departamentului. Pentru aceasta, este necesar? introducerea clauzei ON DELETE CASCADE în
definirea constrângerii de cheie extern?. Suprima?i constrângerea de cheie extern? asupra
tabelului ANGAJATI_pnu ?i reintroduce?i aceast? constrângere, specificând clauza ON DELETE
CASCADE.*/
ALTER TABLE angajati_lco
DROP CONSTRAINT cod_dep_lco_fk;

ALTER TABLE angajati_lco
ADD CONSTRAINT cod_dep_lco_fk 
FOREIGN KEY (cod_dep) REFERENCES DEPARTAMENTE_LCO(cod_dep) ON DELETE CASCADE;

-- Exercitiul 32 --
/*?terge?i departamentul 20 din DEPARTAMENTE_pnu. Ce se întâmpl?? Rollback.*/
DELETE FROM departamente_lco
WHERE cod_dep = 20;
SELECT * FROM angajati_lco;
SELECT * FROM departamente_lco;
ROLLBACK;

-- Exercitiul 33 --
/*Introduce?i constrângerea de cheie extern? asupra coloanei cod_director a tabelului
DEPARTAMENTE_pnu. Se dore?te ca ?tergerea unui angajat care este director de departament
s? atrag? dup? sine setarea automat? a valorii coloanei cod_director la null.*/
ALTER TABLE angajati_lco
DROP CONSTRAINT cod_sef_lco_fk;

ALTER TABLE angajati_lco
ADD CONSTRAINT cod_sef_lco_fk 
FOREIGN KEY (cod_sef) REFERENCES ANGAJATI_LCO(cod_ang) ON DELETE CASCADE;

-- Exercitiul 34 --
/*Actualiza?i tabelul DEPARTAMENTE_PNU, astfel încât angajatul având codul 102 s? devin?
directorul departamentului 30. ?terge?i angajatul având codul 102 din tabelul ANGAJATI_pnu.
Analiza?i efectele comenzii. Rollback.
Este posibil? suprimarea angajatului având codul 101? Comenta?i.*/
UPDATE departamente_lco
SET cod_director = 102
WHERE cod_dep = 30;
SELECT * FROM angajati_lco;
SELECT * FROM departamente_lco;

DELETE FROM angajati_lco
WHERE cod_ang = 102;
ROLLBACK;
--se sterge angajatul dar ramane in tabela cu departamente

-- Exercitiul 35 --
/*Ad?uga?i o constrângere de tip check asupra coloanei salariu, astfel încât acesta s? nu poat?
dep??i 30000.*/
ALTER TABLE angajati_lco
ADD CONSTRAINT salariu_lco_ck CHECK (salariu <= 90000);
-- Exercitiul 36 --
/*36. Incerca?i actualizarea salariului angajatului 100 la valoarea 35000.*/
UPDATE angajati_lco
SET salariu = 95000
WHERE cod_ang = 104;
--check constraint (GRUPA44.SALARIU_LCO_CK) violated; nu este posibil

-- Exercitiul 37 --
/*37. Dezactiva?i constrângerea creat? anterior ?i reîncerca?i actualizarea. Ce se întâmpl? dac?
încerc?m reactivarea constrângerii?*/
ALTER TABLE angajati_lco
DROP CONSTRAINT salariu_lco_ck;
--este posibila reactivarea constrangerii