SET SERVEROUTPUT ON
<<numele_meu>>
BEGIN
DBMS_OUTPUT.PUT('Ana are ');
DBMS_OUTPUT.PUT('mere!!');
DBMS_OUTPUT.PUT_LINE('superb');
DBMS_OUTPUT.NEW_LINE;
END;
/

DECLARE
    v_prenume VARCHAR2(20);
    v_nume VARCHAR2(20) := 'ana';
BEGIN
    DBMS_OUTPUT.PUT_LINE(v_nume);
END;
/

<<principal>>
DECLARE
v_client_id NUMBER(4):= 1600; 
v_client_nume VARCHAR2(50):= 'N1'; 
v_nou_client_id NUMBER(3):= 500;
BEGIN
 <<secundar>>
 DECLARE
v_client_id NUMBER(4):=2000;
v_client_nume VARCHAR2(50) :='N2';
v_nou_client_id NUMBER(4):=5000;
v_nou_client_nume VARCHAR2(50):='N3';
BEGIN
v_client_id:= v_nou_client_id; 
principal.v_client_nume:= v_client_nume ||' '|| v_nou_client_nume; 
--pozi?ia 1
DBMS_OUTPUT.PUT('v_client_id = ' || v_client_id || ' v_client_nume = ' || v_client_nume 
                || ' v_nou_client_id = ' || v_nou_client_id || ' v_nou_client_nume = ' || v_nou_client_nume);
DBMS_OUTPUT.NEW_LINE;
END;
v_client_id:= (v_client_id *12)/10;
--pozi?ia 2 
DBMS_OUTPUT.PUT('v_client_id = ' || v_client_id || ' v_client_nume = ' || v_client_nume);
DBMS_OUTPUT.NEW_LINE;
END;
/

VARIABLE g_mesaj VARCHAR2(20)

BEGIN
    :g_mesaj := 'Im here';
END;
/
PRINT g_mesaj;

DECLARE
    v_dep_name VARCHAR2(20);
BEGIN
SELECT department_name INTO v_dep_name
FROM departments
JOIN employees USING(department_id)
GROUP BY department_name
HAVING COUNT(employee_id) = (SELECT MAX(COUNT(employee_id)) FROM employees GROUP BY department_id);
DBMS_OUTPUT.PUT_LINE(v_dep_name);
END;

--cu variabile de legatura
VARIABLE g_dep_name VARCHAR2(20)
VARIABLE g_num_ang VARCHAR2(20)

BEGIN
SELECT department_name, COUNT(employee_id) INTO :g_dep_name, :g_num_ang
FROM departments
JOIN employees USING(department_id)
GROUP BY department_name
HAVING COUNT(employee_id) = (SELECT MAX(COUNT(employee_id)) FROM employees GROUP BY department_id);
DBMS_OUTPUT.PUT_LINE(:g_dep_name || ' are ' || :g_num_ang);
END;
/
PRINT g_dep_name;

--7 salariu anual + bonus
SET VERIFY ON
DECLARE
    v_nume employees.last_name%TYPE;
    v_cod employees.employee_id%TYPE := &cod;
    v_salariu NUMBER(20);
    v_bonus NUMBER(20);
BEGIN
SELECT last_name, salary * 12 INTO v_nume, v_salariu
FROM employees
WHERE employee_id = v_cod;
DBMS_OUTPUT.PUT_LINE('Numele = ' || v_nume || ' salariu = ' || v_salariu);
IF v_salariu > 200001 THEN v_bonus := 20000;
ELSIF v_salariu > 100001 THEN v_bonus := 10000;
ELSE v_bonus := 5000;
END IF;
DBMS_OUTPUT.PUT_LINE('bonus = ' || v_bonus);
END;
/

DECLARE
    v_nume employees.last_name%TYPE;
    v_cod employees.employee_id%TYPE := &cod;
    v_salariu NUMBER(20);
    v_bonus NUMBER(20);
BEGIN
SELECT last_name, salary * 12 INTO v_nume, v_salariu
FROM employees
WHERE employee_id = v_cod;
CASE
    WHEN v_salariu > 200001 THEN v_bonus := 20000;
    WHEN v_salariu BETWEEN 100001 AND 200000 THEN v_bonus := 10000;
    ELSE v_bonus := 5000;
END CASE;
DBMS_OUTPUT.PUT_LINE('bonus = ' || v_bonus); 
EXCEPTION
WHEN NO_DATA_FOUND THEN DBMS_OUTPUT.PUT_LINE('Nu exista angajat cu acest cod');
END;
/

SELECT employee_id, last_name, salary * 12
FROM employees;

DECLARE
 i POSITIVE:=1;
 max_loop CONSTANT POSITIVE:=10;
BEGIN
 i:=1;
 LOOP
 i:=i+1;
 DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
 EXIT WHEN i>max_loop;
 END LOOP;
 i:=1;
 DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/

--ex 1 singuri
DECLARE
numar number(3):=100;
mesaj1 varchar2(255):='text 1';
mesaj2 varchar2(255):='text 2';
BEGIN
 DECLARE
 numar number(3):=1;
 mesaj1 varchar2(255):='text 2';
 mesaj2 varchar2(255):='text 3';
 BEGIN
 numar:=numar+1;
 mesaj2:=mesaj2||' adaugat in sub-bloc';
 DBMS_OUTPUT.PUT_LINE('NUMAR = ' || numar || ' mesaj1 = ' || mesaj1 || ' mesaj2 = ' || mesaj2);
 END;
numar:=numar+1;
mesaj1:=mesaj1||' adaugat un blocul principal';
mesaj2:=mesaj2||' adaugat in blocul principal';
 DBMS_OUTPUT.PUT_LINE('NUMAR = ' || numar || ' mesaj1 = ' || mesaj1 || ' mesaj2 = ' || mesaj2);
END;
/

--2
/*Se d? urm?torul enun?: Pentru fiecare zi a lunii octombrie (se vor lua în considerare ?i zilele din
lun? în care nu au fost realizate împrumuturi) ob?ine?i num?rul de împrumuturi efectuate.
a. Încerca?i s? rezolva?i problema în SQL f?r? a folosi structuri ajut?toare.
b. Defini?i tabelul octombrie_*** (id, data). Folosind PL/SQL popula?i cu date acest tabel.
Rezolva?i în SQL problema dat?.
*/

CREATE TABLE oct_lco(id NUMBER, data date);
--b
DECLARE
v_nr NUMBER;
data_curr date := TO_DATE('1 OCTOBER', 'DD MONTH');
BEGIN
    for CONTOR in 1..31  LOOP
        SELECT COUNT(*)
        INTO v_nr
        FROM rental
        WHERE TO_CHAR(book_date, 'DD MM') = TO_CHAR(data_curr +contor - 1, 'DD MM');
        INSERT INTO oct_lco VALUES(v_nr, data_curr + contor - 1);
    END LOOP;
END;
/


SELECT * FROM member
ORDER BY 1;

/*Defini?i un bloc anonim în care s? se determine num?rul de filme (titluri) împrumutate de un
membru al c?rui nume este introdus de la tastatur?. Trata?i urm?toare*/
SET VERIFY OFF
DECLARE
    v_filme NUMBER(20);
    v_nume VARCHAR2(20):='&nume_citit';
BEGIN
    SELECT COUNT(*) INTO v_filme
    FROM rental
    JOIN member USING (member_id)
    WHERE UPPER(last_name) = UPPER(v_nume);
    DBMS_OUTPUT.PUT_LINE('Nr filme ' || v_filme);
END;
/

--4
DECLARE
    v_filme NUMBER(20);
    v_total_filme NUMBER(20);
    v_nume VARCHAR2(20):='&nume_citit';
    v_procent NUMBER(4);
BEGIN
    SELECT COUNT(title_id) INTO v_total_filme
    FROM title;
    
    SELECT COUNT(*) INTO v_filme
    FROM rental
    JOIN member USING (member_id)
    WHERE UPPER(last_name) = UPPER(v_nume);
    DBMS_OUTPUT.PUT_LINE(v_filme);
    v_procent := (v_filme / v_total_filme) * 100;
    
    CASE 
    WHEN v_procent > 75 THEN DBMS_OUTPUT.PUT_LINE('Categoria 1');
    WHEN v_procent > 50 THEN DBMS_OUTPUT.PUT_LINE('Categoria 2');
    WHEN v_procent > 25 THEN DBMS_OUTPUT.PUT_LINE('Categoria 3');
    ELSE DBMS_OUTPUT.PUT_LINE('Categoria 4');
    END CASE;
    DBMS_OUTPUT.PUT_LINE('Nr filme ' || v_filme || ' procent ' || v_procent);
END;
/
/*Categoria 1 (a împrumutat mai mult de 75% din titlurile existente)
- Categoria 2 (a împrumutat mai mult de 50% din titlurile existente)
- Categoria 3 (a împrumutat mai mult de 25% din titlurile existente)
- Categoria 4 (altfel)*/
SELECT * FROM member;