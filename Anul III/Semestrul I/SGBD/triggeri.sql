----- TRIGGERI ------

/*Defini?i un declan?ator care s? permit? lucrul asupra tabelului emp_*** (INSERT, UPDATE,
DELETE) decât în intervalul de ore 8:00 - 20:00, de luni pân? sâmb?t? (declan?ator la nivel
de instruc?iune).*/
CREATE OR REPLACE TRIGGER emp_lco.trig_ora
BEFORE INSERT OR UPDATE OR DELETE
ON emp_lco
BEGIN
    IF (TO_CHAR(SYSDATE, 'D') = 1 OR TO_CHAR(SYSDATE, 'HH24') NOT BETWEEN 8 AND 20)
    THEN 
        RAISE_APPLICATION_ERROR(-20001, 'tabelul nu poate fi actualizat');
    END IF;
END;
/
-- Nu vom avea drepturile sa il compilam


/*Defini?i un declan?ator prin care s? nu se permit? mic?orarea salariilor angaja?ilor din tabelul
emp_*** (declan?ator la nivel de linie).*/
-- Varianta 1
-- cu NEW si OLD ca Variabile de legatura
CREATE OR REPLACE TRIGGER trig_mics_sal_1
BEFORE UPDATE OF salary
ON emp_lco
FOR EACH ROW
BEGIN
    IF (:NEW.salary < :OLD.salary) 
    THEN 
        RAISE_APPLICATION_ERROR (-20002, 'Salariul nu poate fi micsorat');
    END IF;
END;
/

UPDATE emp_lco
SET salary = 0.8 * salary;

ROLLBACK;

-- Varianta 2
-- Cu NEW si OLD in WHEN
CREATE OR REPLACE TRIGGER trig_mics_sal_2
BEFORE UPDATE OF salary
ON emp_lco
FOR EACH ROW
WHEN (NEW.salary < OLD.salary)
BEGIN
    RAISE_APPLICATION_ERROR(-20002, 'Salariul nu poate fi micsorat');
END;
/

/*3. Crea?i un declan?ator care s? nu permit? m?rirea limitei inferioare a grilei de salarizare 1,
respectiv mic?orarea limitei superioare a grilei de salarizare 7 decât dac? toate salariile se
g?sesc în intervalul dat de aceste dou? valori modificate. Se va utiliza tabelul job_grades_***.*/

CREATE TABLE job_grades_lco AS SELECT * FROM job_grades;
SELECT * FROM job_grades_lco;
SELECT MIN(salary), MAX(salary)
FROM emp_lco;

SELECT * FROM job_grades_lco;
CREATE OR REPLACE TRIGGER trig_grila_sal
BEFORE
UPDATE OF lowest_sal, highest_sal ON job_grades_lco
FOR EACH ROW
DECLARE
min_sal emp_lco.salary%TYPE;
max_sal emp_lco.salary%TYPE;
exceptie EXCEPTION;
BEGIN
SELECT MIN(salary), MAX(salary) INTO min_sal, max_sal
FROM emp_lco;
IF (:OLD.grade_level = 1) AND (min_sal < :NEW.lowest_sal)
    THEN RAISE exceptie;
END IF;
IF (:OLD.grade_level = 7) AND (max_sal > :NEW.highest_sal)
    THEN RAISE exceptie;
END IF;
EXCEPTION
WHEN exceptie
THEN RAISE_APPLICATION_ERROR(-20003, 'Grila de salarizare nu poate fi modificata');
END;
/

UPDATE job_grades_lco
SET lowest_sal = 1200;

/*4. a. Crea?i tabelul info_dept_*** cu urm?toarele coloane:
- id (codul departamentului) – cheie primar?;
- nume_dept (numele departamentului);
- plati (suma alocat? pentru plata salariilor angaja?ilor care lucreaz? în departamentul
respectiv).
b. Introduce?i date în tabelul creat anterior corespunz?toare informa?iilor existente în schem?.
c. Defini?i un declan?ator care va actualiza automat câmpul plati atunci când se introduce un
nou salariat, respectiv se ?terge un salariat sau se modific? salariul unui angajat.*/
CREATE OR REPLACE PROCEDURE modif_salariu(cod_dep dept_lco.department_id%TYPE,
                                          sal emp_lco.salary%TYPE)
    IS
    BEGIN
    UPDATE info_dept_lco
    SET plati = plati + sal
    WHERE id = cod_dep;
    END;
    /

SELECT * FROM info_emp_lco;
SELECT * FROM dept_lco;
SELECT * FROM emp_lco order by 3;
DROP TABLE dept_lco;
CREATE TABLE dept_lco AS SELECT * FROM departments;
CREATE OR REPLACE TRIGGER trig_4
BEFORE INSERT OR DELETE OR UPDATE OF salary ON emp_lco
FOR EACH ROW
BEGIN
    IF DELETING THEN
        modif_salariu(:OLD.department_id, -:OLD.salary);
    ELSIF UPDATING THEN
        modif_salariu(:NEW.department_id, -:OLD.salary + :NEW.salary);
    ELSE 
         modif_salariu(:NEW.department_id, :NEW.salary);
    END IF;
END;
/
INSERT INTO emp_lco(employee_id, last_name, email, hire_date,
job_id, salary, department_id)
VALUES (emp_lco_seq.NEXTVAL, 'N1', 'n1@g.com',sysdate, 'SA_REP', 2000, 90);
ROLLBACK;
DELETE FROM emp_lco
WHERE employee_id = 211;
DROP PROCEDURE modif_salariu;
DROP TRIGGER trig_4;



/* 5 c. Crea?i vizualizarea v_info_*** care va con?ine informa?ii complete despre angaja?i ?i
departamentele acestora. Folosi?i cele dou? tabele create anterior, info_emp_***, respectiv
info_dept_***. */
SELECT * FROM info_emp_lco;
SELECT * FROM info_dept_lco;

CREATE OR REPLACE VIEW v_info_lco AS
    SELECT e.id, e.nume, e.prenume, e.salariu, e.id_dept, d.nume_dept, d.plati
    FROM info_emp_lco e, info_dept_lco d
    WHERE e.id_dept = d.id;
/    
SELECT * FROM user_updatable_columns
WHERE table_name = UPPER('v_info_lco'); --nu se pot modifica coloanele acestei vizualizari

/*e. Defini?i un declan?ator prin care actualiz?rile ce au loc asupra vizualiz?rii se propag?
automat în tabelele de baz? (declan?ator INSTEAD OF). Se consider? c? au loc
urm?toarele actualiz?ri asupra vizualiz?rii:
- se adaug? un angajat într-un departament deja existent;
- se elimin? un angajat;
- se modific? valoarea salariului unui angajat;
- se modific? departamentul unui angajat (codul departamentului).*/

CREATE OR REPLACE TRIGGER trig_viz
    INSTEAD OF INSERT OR DELETE OR UPDATE ON v_info_lco
    FOR EACH ROW
    BEGIN
        IF INSERTING THEN
            --se presupune ca departamentul exista; 
            --se actualizeaza info_emp si info_dept;
        INSERT INTO info_emp_lco
        VALUES (:NEW.id, :NEW.nume, :NEW.prenume, :NEW.salariu, :NEW.id_dept);
        
        UPDATE info_dept_lco
        SET plati = NVL(plati, 0) + :NEW.salariu
        WHERE id = :NEW.id_dept;
        
    ELSIF DELETING THEN
        --se elimina un angajat
        DELETE FROM info_emp_lco
        WHERE id = :OLD.id;
        
        --modificam coloana plati din info_dept
        UPDATE info_dept_lco
        SET plati = NVL(plati, 0) - :OLD.salariu
        WHERE id = :OLD.id_dept;
    
    ELSIF UPDATING('salariu') THEN
        UPDATE info_emp_lco
        SET salariu = :NEW.salariu
        WHERE id = :OLD.id;
        
        UPDATE info_dept_lco
        SET plati = NVL(plati, 0) - :OLD.salariu + :NEW.salariu
        WHERE id = :OLD.id_dept;
        
    ELSIF UPDATING('id_dept') THEN
        UPDATE info_emp_lco
        SET id_dept = :NEW.id_dept
        WHERE id = :OLD.id;
        
        UPDATE info_dept_lco
        SET plati = NVL(plati, 0) - :OLD.salariu
        WHERE id = :OLD.id_dept;
        
        UPDATE info_dept_lco
        SET plati = NVL(plati, 0) + :NEW.salariu
        WHERE id = :NEW.id_dept;
    END IF;
END;
/   

/*f. Verifica?i dac? declan?atorul definit func?ioneaz? corect.*/
SELECT * FROM info_dept_lco;
SELECT * FROM info_emp_lco;
SELECT * FROM v_info_lco;
INSERT INTO v_info_lco
VALUES (400, 'N1', 'P1', 3000, 10, 'Nume dept', 0);

UPDATE v_info_lco
SET salariu=salariu + 1000
WHERE id=400;

UPDATE v_info_lco  --nu se actualizeaza in tabele
SET nume = 'N2'
WHERE id=400;

/*6. Defini?i un declan?ator care s? nu se permit? ?tergerea informa?iilor din tabelul emp_*** de
c?tre utilizatorul grupa***.*/
CREATE OR REPLACE TRIGGER trig_sterge_grupa
    BEFORE DELETE ON emp_lco
BEGIN
    IF USER = UPPER('grupa44') THEN
    RAISE_APPLICATION_ERROR(-20002, 'Nu este permisa stergerea de care acest utilizator');
    END IF;
END;
/

DROP TRIGGER trig_sterge_grupa;

/* 7 a. Crea?i tabelul audit_*** cu urm?toarele câmpuri:
- utilizator (numele utilizatorului);
- nume_bd (numele bazei de date);
- eveniment (evenimentul sistem);
- nume_obiect (numele obiectului);
- data (data producerii evenimentului).*/

CREATE TABLE audit_lco
    (utilizator VARCHAR2(30),
    nume_bd     VARCHAR2(50),
    eveniment VARCHAR2(20),
    nume_obiect VARCHAR2(30),
    data DATE);

/*b. Defini?i un declan?ator care s? introduc? date în acest tabel dup? ce utilizatorul a folosit o
comand? LDD (declan?ator sistem - la nivel de schem?). */
-- ATENTIE: declansator sistem
CREATE OR REPLACE TRIGGER trig_sistem
    AFTER CREATE OR DROP OR ALTER ON SCHEMA
    BEGIN
        INSERT INTO audit_lco
        VALUES (SYS.LOGIN_USER, SYS.DATABASE_NAME, SYS.SYSEVENT,
                SYS.DICTIONARY_OBJ_NAME, SYSDATE);
END;
/
ALTER TABLE info_dept_lco
DROP COLUMN plus;

SELECT * FROM audit_lco;
SELECT * FROM info_dept_lco;

/*8. Defini?i un declan?ator care s? nu permit? modificarea:
- valorii salariului maxim astfel încât acesta s? devin? mai mic decât media tuturor salariilor;
- valorii salariului minim astfel încât acesta s? devin? mai mare decât media tuturor salariilor.
Observa?ie:
În acest caz este necesar? men?inerea unor variabile în care s? se re?in? salariul minim,
salariul maxim, respectiv media salariilor. Variabilele se definesc într-un pachet, iar apoi pot
fi referite în declan?ator prin nume_pachet.nume_variabila.

Este necesar s? se defineasc? doi declan?atori:
- un declan?ator la nivel de comand? care s? actualizeze variabilele din pachet.
- un declan?ator la nivel de linie care s? realizeze verificarea condi?iilor.*/

--DE CE NU FUNCTIONEAZA UN SINGUR DECLANSATOR?
-- ATENTIE!

CREATE OR REPLACE PACKAGE pachet_8
AS
    sal_min emp_lco.salary%TYPE;
    sal_max emp_lco.salary%TYPE;
    sal_med emp_lco.salary%TYPE;
END pachet_8;
/

--trigger care actualizeaza la update valorile minime/maxime/medii
CREATE OR REPLACE TRIGGER trig_8_get_limits
BEFORE UPDATE OF salary ON emp_lco
BEGIN
    SELECT MIN(salary), MAX(salary), AVG(salary) INTO
    pachet_8.sal_min, pachet_8.sal_max, pachet_8.sal_med
    FROM emp_lco;
END;
/

CREATE OR REPLACE TRIGGER trig_8_linii
BEFORE UPDATE OF salary ON emp_lco
FOR EACH ROW
BEGIN
    IF (:OLD.salary = pachet_8.sal_min AND :NEW.salary > pachet_8.sal_med)
    THEN
        RAISE_APPLICATION_ERROR(-20001, 'Salariul depaseste valoarea medie');
    ELSIF (:OLD.salary = pachet_8.sal_max AND :NEW.salary < pachet_8.sal_med)
    THEN
        RAISE_APPLICATION_ERROR(-20001, 'Salariul este sub valoarea medie');
    END IF;
END;
/

SELECT AVG(salary), MIN(salary), MAX(salary)
FROM emp_lco;

SELECT * FROM emp_lco;
UPDATE emp_lco 
SET salary = 6000
WHERE employee_id = 100;

--Exercitii propuse
/*1. Defini?i un declan?ator care s? permit? ?tergerea informa?iilor din tabelul dept_*** dac?
utilizatorul este lauracozma.*/
CREATE OR REPLACE TRIGGER trig_scott
BEFORE DELETE ON dept_lco
BEGIN
IF UPPER(USER) = UPPER('lauracozma') THEN
RAISE_APPLICATION_ERROR (-20002, 'Nu ai voie sa stergi!');
END IF;
END;
/

DELETE from dept_lco;
ROLLBACK;

/*2. Crea?i un declan?ator prin care s? nu se permit? m?rirea comisionului astfel încât s? dep??easc?
50% din valoarea salariului.*/
CREATE OR REPLACE TRIGGER trig_comision
BEFORE UPDATE OF commission_pct ON emp_lco
FOR EACH ROW
BEGIN
    IF(:NEW.commission_pct > 0.5) THEN
        RAISE_APPLICATION_ERROR(-20001, 'E prea mare comisionul');
    END IF;
END;
/

UPDATE emp_lco
SET commission_pct = 0.7
WHERE employee_id = 100; -- trigger declansat


/*3. a. Introduce?i în tabelul info_dept_*** coloana numar care va reprezenta pentru fiecare
departament num?rul de angaja?i care lucreaz? în departamentul respectiv. Popula?i cu date
aceast? coloan? pe baza informa?iilor din schem?.
b. Defini?i un declan?ator care va actualiza automat aceast? coloan? în func?ie de actualiz?rile
realizate asupra tabelului info_emp_***.*/
CREATE OR REPLACE PROCEDURE modifica_nr_ang(id_dept info_emp_lco.id_dept%TYPE,
                                            val NUMBER)
AS
BEGIN
    UPDATE info_dept_lco
    SET numar = NVL(numar, 0) + val
    WHERE id = id_dept;
END;
/

CREATE OR REPLACE TRIGGER trig_numar_ang
AFTER DELETE OR INSERT OR UPDATE OF id_dept ON info_emp_lco
FOR EACH ROW
BEGIN
IF DELETING THEN
    modifica_nr_ang(:OLD.id_dept, -1);
ELSIF INSERTING THEN
    modifica_nr_ang(:NEW.id_dept, 1);
ELSE 
    modifica_nr_ang(:OLD.id_dept, -1);
    modifica_nr_ang(:NEW.id_dept, 1);
END IF;
END;
/

SELECT * FROM info_emp_lco;
SELECT * FROM info_dept_lco;

UPDATE info_emp_lco
SET id_dept = 40
WHERE id = 100; --se porneste triggerul

ROLLBACK;

/*5. Defini?i un declan?ator cu ajutorul c?ruia s? se implementeze restric?ia conform c?reia într-un
departament nu pot lucra mai mult de 45 persoane (se vor utiliza doar tabelele emp_*** ?i
dept_*** f?r? a modifica structura acestora).*/

--EROARE LA AFTER: table is mutating
CREATE OR REPLACE TRIGGER trig_nr_max_ang
AFTER INSERT OR UPDATE OF department_id ON emp_lco
FOR EACH ROW
DECLARE
v_ang NUMBER;
BEGIN
SELECT COUNT(employee_id) INTO v_ang
FROM emp_lco
WHERE department_id = :NEW.department_id;
IF v_ang + 1 > 45 THEN
RAISE_APPLICATION_ERROR(-20001, 'Nr de angajati e rpea mare');
END IF;
END;
/
ALTER TRIGGER trig_nr_max_ang DISABLE;

SELECT * FROM emp_lco;
SELECT * FROM info_dept_lco;

INSERT INTO emp_lco
VALUES(303, 'Daphne', 'Bridgerton', 'DBRIDGE', null, sysdate, 'IT_PROG', 1000, null, 103, 100, 103);

--Varianta corecta
--facem un pachet
CREATE OR REPLACE PACKAGE pkt_max_ang
AS
TYPE t_cod IS TABLE OF dept_lco.department_id%TYPE
INDEX BY BINARY_INTEGER;
v_cod_dep t_cod;
v_nr_intrari BINARY_INTEGER := 0;
END pkt_max_ang;
/

--trigger la nivel de linie
CREATE OR REPLACE TRIGGER trig_max_ang_linie
BEFORE INSERT OR UPDATE OF department_id ON emp_lco
FOR EACH ROW
BEGIN
pkt_max_ang.v_nr_intrari := pkt_max_ang.v_nr_intrari + 1;
pkt_max_ang.v_cod_dep(pkt_max_ang.v_nr_intrari) := :NEW.department_id;
END;
/

--trigger la nivel de intructiune
CREATE OR REPLACE TRIGGER trig_max_ang_instr
AFTER INSERT OR UPDATE OF department_id ON emp_lco
DECLARE
v_max_emp CONSTANT NUMBER := 45;
v_emp_curent NUMBER;
v_cod_dep dept_lco.department_id%TYPE;
BEGIN
--parcurge fiecare dep inserat si verifica daca e in limita
FOR i IN 1..pkt_max_ang.v_nr_intrari LOOP
    v_cod_dep := pkt_max_ang.v_cod_dep(i);
    SELECT COUNT(*)
    INTO v_emp_curent
    FROM emp_lco
    WHERE department_id = v_cod_dep;
    IF(v_emp_curent >= v_max_emp) THEN
        pkt_max_ang.v_nr_intrari := 0;
        RAISE_APPLICATION_ERROR(-20001, 'Prea multi angajati in dep avand codul ' || v_cod_dep);
    END IF;
END LOOP;

pkt_max_ang.v_nr_intrari := 0;
END;
/
SELECT * FROM info_dept_lco;
drop table emp_lco;
create table emp_lco as select * from employees;
ALTER TABLE emp_lco DISABLE ALL TRIGGERS;
INSERT INTO emp_lco
    (SELECT
        *
    FROM
        employees
    WHERE
        department_id = 80);

Seen a trimis Azi la 00:00
SELECT
    department_id,
    COUNT(*)
FROM
    emp_lco
GROUP BY
    department_id;
ROLLBACK;
/*Sa se creeze un declansator care:
a) daca este eliminat un departament, va sterge toti angajatii care lucreaza in
departamentul respectiv;
b) daca se schimba codul unui departament, va modifica aceasta valoare pentru fiecare
angajat care lucreaza in departamentul respectiv.*/
CREATE OR REPLACE TRIGGER trig_cascade
BEFORE DELETE OR UPDATE OF department_id ON dept_lco
FOR EACH ROW
BEGIN
IF DELETING THEN
    DELETE FROM emp_lco
    WHERE department_id = :OLD.department_id;
ELSIF UPDATING THEN
    UPDATE emp_lco
    SET department_id = :NEW.department_id
    WHERE department_id = :OLD.department_id;
END IF;
END;
/

UPDATE dept_lco
SET department_id = 12
WHERE department_id = 100;

SELECT * FROM emp_lco ORDER BY department_id;

ROLLBACK;

DELETE FROM dept_lco
WHERE department_id = 100;

ALTER TABLE dept_lco
DISABLE ALL TRIGGERS;


/*6. a. Crea?i un tabel cu urm?toarele coloane:
- user_id (SYS.LOGIN_USER);
- nume_bd (SYS.DATABASE_NAME);
- erori (DBMS_UTILITY.FORMAT_ERROR_STACK);
- data.*/
CREATE TABLE erori_lco
    (user_id VARCHAR2(30),
     nume_bd VARCHAR2(50),
     erori VARCHAR2(100),
     data  DATE);
     
/*b. Defini?i un declan?ator sistem (la nivel de baz? de date) care s? introduc? date în acest tabel
referitoare la erorile ap?rute.*/

CREATE OR REPLACE TRIGGER trig_sistem_erori
    AFTER DROP OR ALTER OR CREATE ON SCHEMA
    BEGIN
        INSERT INTO erori_lco
        VALUES (SYS.LOGIN_USER, SYS.DATABASE_NAME, DBMS_UTILITY.FORMAT_ERROR_STACK, SYSDATE);
END;
/

SELECT * FROM erori_lco;
CREATE TABLE emp_lco2 AS SELECT * FROM emp_lco;
ALTER TABLE emp_lco2
ADD PRIMARY KEY(employee_id); --la comenzile de CREATE SI ALTER se adauga in tabel cu sau fara erori


--- Laboratoare Vasile

/* Trigger care la stergerea unui angajat care este manager, pune in locul sau
angajatul care a avut cel mai mare salariu dintre angajatii care se aflau in acel departament.*/

--varianta 1, trebuie verificata
CREATE OR REPLACE PACKAGE pack_1
AS
    TYPE t_index IS TABLE OF NUMBER INDEX BY BINARY_INTEGER;
    t t_index;
    nr NUMBER := 0;
END;
/

CREATE OR REPLACE TRIGGER trig_1
BEFORE DELETE ON employees
FOR EACH ROW
BEGIN
    pack_1.nr := pack_1.nr + 1;
    pack_1.t(pack_1.nr) := :NEW.employee_id;
END;
/


CREATE OR REPLACE TRIGGER trig_1_instr
AFTER DELETE ON employees
DECLARE
ck_mgr NUMBER;
new_mgr NUMBER;
BEGIN
    FOR i IN 1..pack_1.nr LOOP
        SELECT COUNT(*) INTO ck_mgr
        FROM employees
        WHERE manager_id = pack_1.t(i);
        
        IF ck_mgr > 0 THEN
            SELECT employee_id INTO new_mgr
            FROM employees
            WHERE manager_id = pack_1.t(i) 
            AND salary = (SELECT MAX(salary) 
                        FROM employees
                        WHERE manager_id = pack_1.t(i));
                        
            UPDATE employees
            SET manager_id = new_mgr
            WHERE manager_id = pack_1.t(i) ;
        END IF;
    END LOOP;
    pack_1.nr := 0;
    pack_1.t.DELETE;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        pack_1.nr := 0;
        pack_1.t.DELETE;
        RAISE_APPLICATION_ERROR(-20001, 'Nu are subordonati');
    WHEN TOO_MANY_ROWS THEN
        pack_1.nr := 0;
        pack_1.t.DELETE;
        RAISE_APPLICATION_ERROR(-20002, 'Prea multi subordonati cu acelasi salariu');
    WHEN OTHERS THEN
        pack_1.nr := 0;
        pack_1.t.DELETE;
        RAISE_APPLICATION_ERROR(-20003, 'Alta eroare');
END;
/
--- vom avea eroare table is mutating
--salvam intr-un pachet managerii care se sterg impreuna cu numarul lor intr-un trigger la nivel de linie
--in triggerul pe instructiune pe fiecare manager sters actualizam subalternii

CREATE OR REPLACE PACKAGE pkt_mgr_del
    AS
    TYPE t_mgr IS TABLE OF emp_lco.employee_id%TYPE INDEX BY BINARY_INTEGER;
    v_mgr t_mgr;
    nr_mgr NUMBER := 0;
END;
/

CREATE OR REPLACE TRIGGER trig_mgr_del_row
    BEFORE DELETE ON emp_lco
    FOR EACH ROW
    BEGIN
        pkt_mgr_del.nr_mgr := pkt_mgr_del.nr_mgr + 1;
        pkt_mgr_del.v_mgr(pkt_mgr_del.nr_mgr) := :OLD.employee_id;
        DBMS_OUTPUT.PUT_LINE('In linie ' || pkt_mgr_del.v_mgr(pkt_mgr_del.nr_mgr));

    END;
    /
    
CREATE OR REPLACE TRIGGER trig_mgr_del_instr
    AFTER DELETE ON emp_lco
    DECLARE
    old_mgr emp_lco.employee_id%TYPE;
    ck_mgr NUMBER;
    new_mgr emp_lco.employee_id%TYPE;
    BEGIN
        DBMS_OUTPUT.PUT_LINE('nr elem ' || pkt_mgr_del.nr_mgr);
        FOR i IN 1..pkt_mgr_del.nr_mgr LOOP
            DBMS_OUTPUT.PUT_LINE('In for ' || pkt_mgr_del.v_mgr(i));
            IF pkt_mgr_del.v_mgr(i) <> 0 THEN
                old_mgr := pkt_mgr_del.v_mgr(i); 
                pkt_mgr_del.v_mgr(i) := 0;
                SELECT COUNT(*) INTO ck_mgr
                FROM emp_lco
                WHERE manager_id = old_mgr;
                                DBMS_OUTPUT.PUT_LINE(ck_mgr || ' ' || old_mgr);
                
                IF ck_mgr > 0 THEN
                    --cel sters a fost un manager deoarece avea minim un subordonat
                    --vedem care din subordonati avea salariul maxim; el e noul manager
                    --DBMS_OUTPUT.PUT_LINE(pkt_mgr_del.v_mgr(i));
                    SELECT employee_id INTO new_mgr
                    FROM emp_lco
                    WHERE manager_id = old_mgr
                        AND salary = (SELECT MAX(salary) FROM emp_lco
                                    WHERE manager_id = old_mgr);
                    
                    UPDATE emp_lco
                    SET manager_id = new_mgr
                    WHERE manager_id = old_mgr;
                END IF;
            END IF;
        END LOOP;
        EXCEPTION
        WHEN TOO_MANY_ROWS
        THEN
            pkt_mgr_del.nr_mgr := 0;
            pkt_mgr_del.v_mgr.DELETE;
            RAISE_APPLICATION_ERROR(-20001, 'Mai multi au salariu maxim');
        pkt_mgr_del.nr_mgr := 0;
        pkt_mgr_del.v_mgr.DELETE;
    END;
    /
SET SERVEROUTPUT ON;
SELECT * FROM emp_lco ORDER  BY manager_id;
SELECT * FROM emp_lco ORDER  BY 1;

SELECT * FROM emp_lco WHERE manager_id = 114;
DELETE FROM emp_lco
WHERE employee_id = 114;
ROLLBACK;
DROP TABLE emp_lco;
CREATE TABLE emp_lco AS SELECT * FROM employees;
ALTER TRIGGER trig_del_manag DISABLE;

ALTER TABLE emp_lco
disable all triggers;
DROP TRIGGER trig_mgr_del_instr;
DROP TRIGGER trig_mgr_del_row;

/*3. S? se creeze un trigger care s? permit? ca numai salaria?ii având codul job-ului AD_PRES sau
AD_VP s? poat? câ?tiga mai mult de 15000. */
CREATE OR REPLACE TRIGGER trig_sal_15000
    BEFORE UPDATE OR INSERT OF salary ON emp_lco
    FOR EACH ROW
    BEGIN
    IF UPPER(:NEW.job_id) <> 'AD_PRES' AND UPPER(:NEW.job_id) <> 'AD_VP'
        AND :NEW.salary > 15000
        THEN RAISE_APPLICATION_ERROR(-20001, 'Ai salariu prea mare');
    END IF;
    END;
/

SELECT * FROM emp_lco;

UPDATE emp_lco
SET salary = 16000
WHERE employee_id = 103;
ROLLBACK;

DROP TRIGGER trig_sal_15000;

/*7. S? se creeze un trigger check_sal care garanteaz? ca, ori de câte ori un angajat nou este
introdus în tabelul EMPLOYEES sau atunci când este modificat salariul sau codul job-ului unui
angajat, salariul se încadreaz? între minimul ?i maximul salariior corespunz?toare job-ului
respectiv. Se vor exclude angajatii AD_PRES. */
CREATE OR REPLACE TRIGGER check_sal
BEFORE INSERT OR UPDATE ON emp_lco
FOR EACH ROW
DECLARE
minim jobs.min_salary%TYPE;
maxim jobs.max_salary%TYPE;
BEGIN
    IF INSERTING OR UPDATING('salary') OR UPDATING('job_id') THEN
        IF UPPER(:NEW.job_id) <> 'AD_PRES' THEN
            SELECT min_salary, max_salary INTO minim, maxim
            FROM jobs
            WHERE job_id = :NEW.job_id;
            IF :NEW.salary < minim OR :NEW.salary > maxim THEN
                RAISE_APPLICATION_ERROR(-20002, 'Nu e bun salariul');
            END IF;
        END IF;
    END IF;
END;
/
SELECT * FROM jobs;
SELECT * FROM emp_lco;
ROLLBACK;
UPDATE emp_lco
SET job_id = 'IT_PROG', salary = 60000
WHERE employee_id = 100;
DROP TRIGGER check_sal;
SET SERVEROUTPUT ON;

-- VARIANTA 2. MINIMUL SI MAXIMUL EXISTENT
CREATE OR REPLACE PACKAGE pkt_check_sal
AS
TYPE t_index IS TABLE OF employees.employee_id%TYPE INDEX BY BINARY_INTEGER;
t_emp t_index;
nr_emp NUMBER := 0;
END;
/

CREATE OR REPLACE TRIGGER check_sal_lin
BEFORE INSERT OR UPDATE OF salary, job_id ON emp_lco
FOR EACH ROW
    BEGIN
    DBMS_OUTPUT.PUT_LINE('Aici ' || pkt_check_sal.nr_emp); 

        pkt_check_sal.nr_emp := pkt_check_sal.nr_emp + 1;
        pkt_check_sal.t_emp(pkt_check_sal.nr_emp) := :NEW.employee_id;
END;
/

CREATE OR REPLACE TRIGGER check_sal_instr
AFTER INSERT OR UPDATE OF salary, job_id ON emp_lco
DECLARE
cod emp_lco.employee_id%TYPE;
emp emp_lco%ROWTYPE;
minim emp_lco.salary%TYPE;
maxim emp_lco.salary%TYPE;
BEGIN 
DBMS_OUTPUT.PUT_LINE(pkt_check_sal.nr_emp); 
    FOR i IN 1..pkt_check_sal.nr_emp LOOP
DBMS_OUTPUT.PUT_LINE(pkt_check_sal.t_emp(i)); 

        IF pkt_check_sal.t_emp(i) <> 0 THEN
           DBMS_OUTPUT.PUT_LINE('Angajatul ' || pkt_check_sal.t_emp(i)); 
            SELECT * INTO emp
            FROM emp_lco
            WHERE employee_id = pkt_check_sal.t_emp(i);
            
            pkt_check_sal.t_emp(i) := 0;
            --DBMS_OUTPUT.PUT_LINE('Salariu ' || emp.salary); 

            IF UPPER(emp.job_id) <> 'AD_PRES' THEN
                SELECT MIN(salary), MAX(salary) INTO minim, maxim
                FROM employees
                WHERE job_id = emp.job_id;
                IF emp.salary < minim OR emp.salary > maxim THEN
                    pkt_check_sal.t_emp.DELETE;
                    pkt_check_sal.nr_emp := 0;
                    RAISE_APPLICATION_ERROR(-20002, 'Nu e bun salariul');
                END IF;
            END IF;            
        END IF;
    END LOOP;
    pkt_check_sal.t_emp.DELETE;
    pkt_check_sal.nr_emp := 0;
END;
/
DROP TRIGGER check_sal_instr;
DROP TRIGGER check_sal_lin;


/*Sa se scrie un trigger prin intermediul caruia unui angajat nu poate fi penalizat(nu poate
fi mutat pe un job cu media salariilor mai mica decat media salariilor jobului anterior)*/
CREATE OR REPLACE FUNCTION func_med(jb_id VARCHAR2)
RETURN NUMBER
IS
med NUMBER;
BEGIN
    SELECT AVG(salary) INTO med
    FROM emp_lco
    WHERE UPPER(job_id) = UPPER(jb_id);
    RETURN med;
END;
/
CREATE OR REPLACE PACKAGE pack_med
AS
TYPE t_index IS TABLE OF NUMBER INDEX BY VARCHAR2(30);
t_med t_index;
END;
/

CREATE OR REPLACE TRIGGER trig_med_lin
BEFORE UPDATE OF job_id ON emp_lco
BEGIN
    FOR job IN (SELECT job_id FROM jobs) LOOP
        DBMS_OUTPUT.PUT_LINE(job.job_id);
        pack_med.t_med(job.job_id) := func_med(job.job_id);
    END LOOP;
END;
/

CREATE OR REPLACE TRIGGER trig_med_each_row
BEFORE UPDATE OF job_id ON emp_lco
FOR EACH ROW
BEGIN
    IF (pack_med.t_med(:NEW.job_id) < pack_med.t_med(:OLD.job_id))
        THEN 
        RAISE_APPLICATION_ERROR(-20001, 'Nu poti merge intr-un job cu medie mai mica a salariilor');
    END IF;
END;
/

SELECT * FROM emp_lco;
SELECT AVG(salary) 
    FROM emp_lco
    WHERE UPPER(job_id) = 'IT_PROG';
    
UPDATE emp_lco
SET job_id = 'AD_PRES'
WHERE employee_id = 103;
ROLLBACK;


SELECT * FROM jobs;


/*Implementati constrangerea conform careia un angajat intotdeauna trebuie sa aiba un salariu valid
(salariul sa fie cuprins intre min_salary si max_salary pentru jobul respectiv)*/

CREATE OR REPLACE TRIGGER trig_sal
BEFORE INSERT OR UPDATE OF salary ON emp_lco
FOR EACH ROW
DECLARE
min_sal NUMBER;
max_sal NUMBER;
BEGIN
    SELECT min_salary, max_salary INTO min_sal, max_sal
    FROM jobs
    WHERE UPPER(job_id) = UPPER(:NEW.job_id);
    IF (:NEW.salary > max_sal) OR (:NEW.salary < min_sal) THEN
        RAISE_APPLICATION_ERROR(-20001, 'Salariul nu se incadreaza in limite');
    END IF;
END;
/

SELECT * FROM emp_lco;

UPDATE emp_lco
SET salary = 30000
WHERE employee_id = 100;

ROLLBACK;
--trigger in caz ca se modifica si in jobs
CREATE OR REPLACE TRIGGER trig_jobs
BEFORE INSERT OR UPDATE OF min_salary, max_salary ON jobs
FOR EACH ROW
DECLARE
min_sal NUMBER;
max_sal NUMBER;
BEGIN
    SELECT MIN(salary), MAX(salary) INTO min_sal, max_sal
    FROM emp_lco
    WHERE UPPER(job_id) = UPPER(:NEW.job_id);
    
    IF min_sal < :NEW.min_salary  OR max_sal > :NEW.max_salary
        THEN   RAISE_APPLICATION_ERROR(-20001, 'Salariul nu se incadreaza in limite');
    END IF;
END;
/

--Probleme propuse curs
--2. Trigger care s? nu permit? ca un pe?te s? fie reintrodus într-un acvariu în care a mai fost. 

CREATE OR REPLACE PACKAGE pack_crescut
AS
TYPE rec IS RECORD
    (peste crescut.cod_peste%TYPE,
    acvariu crescut.cod_acvariu%TYPE);
TYPE t_index IS TABLE OF rec INDEX BY BINARY_INTEGER;
t t_index;
nr NUMBER := 0;
END;
/
CREATE OR REPLACE TRIGGER trig_crescut_row
BEFORE INSERT OR UPDATE OF cod_acvariu ON crescut
FOR EACH ROW
BEGIN
DBMS_OUTPUT.PUT_LINE(:NEW.cod_peste || ' ' || :NEW.cod_acvariu);
pack_crescut.nr := pack_crescut.nr + 1;
pack_crescut.t(pack_crescut.nr).peste := :NEW.cod_peste;
pack_crescut.t(pack_crescut.nr).acvariu := :NEW.cod_acvariu;
END;
/

CREATE OR REPLACE TRIGGER trig_crescut
AFTER INSERT OR UPDATE OF cod_acvariu ON crescut
DECLARE
nr_acv NUMBER;
BEGIN
    FOR i IN 1..pack_crescut.nr LOOP
        SELECT COUNT(*) INTO nr_acv
        FROM crescut
        WHERE cod_peste = pack_crescut.t(i).peste
        AND cod_acvariu = pack_crescut.t(i).acvariu;
        
        IF nr_acv > 1 THEN
            DBMS_OUTPUT.PUT_LINE('Before' || pack_crescut.t.count || ' ' || pack_crescut.nr);
            pack_crescut.t.DELETE;
            pack_crescut.nr := 0;
            DBMS_OUTPUT.PUT_LINE('After ' || pack_crescut.t.count || ' ' || pack_crescut.nr);
            RAISE_APPLICATION_ERROR(-20001, 'PESTELE A MAI FOST IN ACEST ACVARIU');
        END IF;
    END LOOP;
    pack_crescut.t.DELETE;
    pack_crescut.nr := 0;
END;
/

SELECT * FROM crescut;

INSERT INTO crescut VALUES(1, 1, sysdate, sysdate);
ROLLBACK;
insert INTO CRESCUT (SELECT * FROM CRESCUT WHERE ROWNUM <=10);
BEGIN
    DBMS_OUTPUT.PUT_LINE(pack_crescut.t.count || ' ' || pack_crescut.nr);
END;
/

UPDATE crescut
set cod_acvariu = 1
WHERE cod_peste = 1;

/*Trigger care s? implementeze constrângerea 
prin care un utilaj s? nu fie utilizat mai mult de 12 ore pe zi.*/
SELECT * FROM lucreaza;
SELECT * FROM utilaj;
SELECT * FROM angajat;
SELECT * FROM firma;
SELECT * FROM info;

UPDATE LUCREAZA
SET NR_ORE = 7
WHERE cod_angajat = 501 AND id_utilaj = 50;
ROLLBACK;
CREATE OR REPLACE PACKAGE pack_utilaje
AS
TYPE rec IS RECORD 
    (cod_ut lucreaza.id_utilaj%TYPE,
     data lucreaza.data%TYPE);
TYPE t_index IS TABLE OF rec INDEX BY BINARY_INTEGER;
t t_index;
nr NUMBER := 0;
END;
/

CREATE OR REPLACE TRIGGER trig_utilaje_row
BEFORE UPDATE OR INSERT ON lucreaza
FOR EACH ROW
BEGIN
    pack_utilaje.nr := pack_utilaje.nr + 1;
    pack_utilaje.t(pack_utilaje.nr).cod_ut := :NEW.id_utilaj;
    pack_utilaje.t(pack_utilaje.nr).data := :NEW.data; 
END;
/

CREATE OR REPLACE TRIGGER trig_utilaje
AFTER UPDATE OR INSERT ON lucreaza
DECLARE
nr_ore NUMBER;
BEGIN
    FOR i IN 1..pack_utilaje.nr LOOP
        SELECT SUM(nr_ore) INTO nr_ore
        FROM lucreaza
        WHERE id_utilaj = pack_utilaje.t(i).cod_ut
        AND data = pack_utilaje.t(i).data;
        
        IF nr_ore > 12 THEN
            pack_utilaje.t.DELETE;
            pack_utilaje.nr := 0;
            RAISE_APPLICATION_ERROR(-20001, 'Utilajul a fost folosit prea mult!');
        END IF;
    END LOOP;
    pack_utilaje.t.DELETE;
    pack_utilaje.nr := 0;
END;
/
