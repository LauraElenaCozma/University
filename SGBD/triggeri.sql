/*Exercitiul 1 - Defini?i un declan?ator care s? nu permit? ?tergerea informa?iilor din tabelul dept_*** dac?
utilizatorul este SCOTT.*/


CREATE OR REPLACE TRIGGER trig1 
BEFORE DELETE ON dept_lco
BEGIN
    IF UPPER(user) = UPPER('lauracozma') THEN
        RAISE_APPLICATION_ERROR(-20001, 'Nu se poate sterge din tabelul dept_lco');
    END IF;
END;
/

DELETE FROM dept_lco;

/*2. Crea?i un declan?ator prin care s? nu se permit? m?rirea comisionului astfel încât s? dep??easc?
50% din valoarea salariului.*/
CREATE OR REPLACE TRIGGER trig2
BEFORE UPDATE OF commission_pct ON emp_lco
FOR EACH ROW
BEGIN
    IF (:NEW.commission_pct > 0.5) THEN 
        RAISE_APPLICATION_ERROR(-20001, 'Nu se poate mari commission_pct');
    END IF;
END;
/

UPDATE emp_lco
SET commission_pct = 0.99;

/*3. a. Introduce?i în tabelul info_dept_*** coloana numar care va reprezenta pentru fiecare
departament num?rul de angaja?i care lucreaz? în departamentul respectiv. Popula?i cu date
aceast? coloan? pe baza informa?iilor din schem?.*/
CREATE TABLE info_dept_lco (id NUMBER(5), nume_dept VARCHAR2(25),plati NUMBER(8,2));

INSERT INTO info_dept_lco
SELECT department_id,department_name,SUM(salary)
FROM employees JOIN departments USING(department_id)
GROUP BY department_id,department_name;

SELECT * FROM info_dept_lco;

ALTER TABLE info_dept_lco
ADD (numar NUMBER);

UPDATE info_dept_lco d
SET numar = (SELECT COUNT(employee_id) 
            FROM employees
            WHERE department_id = d.id);
            
/*b. Defini?i un declan?ator care va actualiza automat aceast? coloan? în func?ie de actualiz?rile
realizate asupra tabelului info_emp_***.*/
CREATE OR REPLACE PROCEDURE actualizare_nr_ang(cod NUMBER, numar_ang NUMBER)
IS
BEGIN
    UPDATE info_dept_lco
    SET numar = numar + numar_ang
    WHERE id = cod;
END;
/

CREATE TABLE info_emp_lco (id,nume,prenume,salariu,id_dept) AS SELECT employee_id,last_name,
first_name,salary,department_id
FROM employees;


CREATE OR REPLACE TRIGGER trig3
AFTER UPDATE OR DELETE OR INSERT ON info_emp_lco
FOR EACH ROW
BEGIN
    IF INSERTING 
        THEN actualizare_nr_ang(:NEW.id_dept, 1);
    ELSIF UPDATING('id_dept')  
        THEN 
            actualizare_nr_ang(:OLD.id_dept, -1);
            actualizare_nr_ang(:NEW.id_dept, 1);
    ELSE
        actualizare_nr_ang(:OLD.id_dept, -1);
    END IF;
END;
/


UPDATE info_emp_lco
SET id_dept = 60
WHERE id = 100;

INSERT INTO info_emp_lco
VALUES (500, 'aaa','aa', 10000, 60);

SELECT *
FROM info_emp_lco;

SELECT *
FROM info_dept_lco;

DELETE FROM info_emp_lco
WHERE id = 500;

ROLLBACK;


/*4. Defini?i un declan?ator cu ajutorul c?ruia s? se implementeze restric?ia conform c?reia într-un
departament nu pot lucra mai mult de 45 persoane (se vor utiliza doar tabelele emp_*** ?i
dept_*** f?r? a modifica structura acestora).*/
SELECT * FROM emp_lco;

SET SERVEROUTPUT ON;
--mutating table, trebuie sa folosim 2 triggeri
--unul la nivel de comanda
--unul la nicel de linie care foloseste o colectie dintr-un pachet
CREATE OR REPLACE TRIGGER trig4
AFTER INSERT ON emp_lco
FOR EACH ROW
DECLARE
v_nr NUMBER;
BEGIN
SELECT COUNT(employee_id)
INTO v_nr
FROM emp_lco;
IF v_nr > 45 THEN
    RAISE_APPLICATION_ERROR(-20001, 'NU PUTETI INSERA MAI MULT DE 45 DE PERSOANE');
END IF;
END;
/

SELECT COUNT(employee_id), department_id
FROM emp_lco
GROUP BY department_id;
--45 de ang sunt in dep 50


INSERT INTO emp_lco
VALUES (employees_seq.NEXTVAL, 'Prenume', 'Nume', 'a', 't', SYSDATE,'IT_PROG', 10000, 0.1, 100, 50, 100);

