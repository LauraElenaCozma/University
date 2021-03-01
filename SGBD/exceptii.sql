/*2. S? se creeze tabelul error_*** care va con?ine dou? câmpuri: cod de tip NUMBER ?i mesaj de
tip VARCHAR2(100). S? se creeze un bloc PL/SQL care s? permit? gestiunea erorii „divide by
zero” în dou? moduri: prin definirea unei excep?ii de c?tre utilizator ?i prin captarea erorii interne a
sistemului. Codul ?i mesajul erorii vor fi introduse în tabelul error_***.*/

SELECT * FROM error_lco;
CREATE TABLE error_lco
(cod NUMBER,
mesaj VARCHAR2(100));

DECLARE
v_cod NUMBER;
v_mesaj VARCHAR2(100);
x NUMBER;
exceptie EXCEPTION;
BEGIN
    x := 1;
    IF x = 1 THEN
        RAISE exceptie;
    ELSE
        x := x / (x-1);
    END IF;
EXCEPTION
    WHEN exceptie THEN 
        v_cod := -20001;
        v_mesaj := 'x=1 det impartire la 0';
        INSERT INTO error_lco
        VALUES (v_cod, v_mesaj);
END;
/

--Varianta 2
DECLARE
    v_cod NUMBER;
    v_mesaj VARCHAR2(100);
    x NUMBER;
    exceptie EXCEPTION;
BEGIN
    x := 1;
    x := x / (x - 1);
EXCEPTION
    WHEN ZERO_DIVIDE THEN
    v_cod := SQLCODE;
    v_mesaj := SUBSTR(SQLERRM, 1, 100);
    INSERT INTO error_lco
        VALUES (v_cod, v_mesaj);
END;
/
/*3. S? se creeze un bloc PL/SQL prin care s? se afi?eze numele departamentului care func?ioneaz?
într-o anumit? loca?ie. Dac? interogarea nu întoarce nicio linie, atunci s? se trateze excep?ia ?i s? se
insereze în tabelul error_*** codul erorii -20002 cu mesajul “nu exista departamente in locatia
data”. Dac? interogarea întoarce o singur? linie, atunci s? se afi?eze numele departamentului. Dac?

interogarea întoarce mai multe linii, atunci s? se introduc? în tabelul error_*** codul erorii -20003
cu mesajul “exista mai multe departamente in locatia data”.
Testa?i pentru urm?toarele loca?ii: 1400, 1700, 3000.*/

DECLARE
loc departments.location_id%TYPE := &p_loc;
dep departments.department_name%TYPE;
BEGIN
    SELECT department_name INTO dep
    FROM departments
    WHERE location_id = loc;
    DBMS_OUTPUT.PUT_LINE('Nume dep: ' || dep);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20002, 'Nu exista departamente in locatia data');
    WHEN TOO_MANY_ROWS THEN
        RAISE_APPLICATION_ERROR(-20003, 'Exista exista mai multe departamente in locatia data');
END;
/

/*4. S? se adauge constrângerea de cheie primar? pentru câmpul department_id din tabelul dept_***
?i constrângerea de cheie extern? pentru câmpul department_id din tabelul emp_*** care refer?
câmpul cu acela?i nume din tabelul dept_***.
S? se creeze un bloc PL/SQL care trateaz? excep?ia ap?rut? în cazul în care se ?terge un
departament în care lucreaz? angaja?i (excep?ie intern? nepredefinit?).*/

ALTER TABLE dept_lco
ADD CONSTRAINT c_pr_lco PRIMARY KEY(department_id);

ALTER TABLE emp_lco
ADD CONSTRAINT c_fk_lco FOREIGN KEY(department_id)
    REFERENCES dept_lco;

DECLARE
    exceptie EXCEPTION;
    PRAGMA EXCEPTION_INIT(exceptie, -02292);
BEGIN  
    DELETE FROM dept_lco
    WHERE department_id = &p_cod;
EXCEPTION
    WHEN exceptie THEN
    DBMS_OUTPUT.PUT_LINE('Nu puteti sterge dep');
END;
/

/*5. S? se creeze un bloc PL/SQL prin care se afi?eaz? num?rul de salaria?i care au venitul anual mai
mare decât o valoare dat?. S? se trateze cazul în care niciun salariat nu îndepline?te aceast? condi?ie
(excep?ii externe).*/
DECLARE
nr NUMBER;
BEGIN
    SELECT COUNT(employee_id)
    INTO nr
    FROM emp_lco
    WHERE (salary + salary * NVL(commission_pct, 0)) * 12 > &p_val;
    DBMS_OUTPUT.PUT_LINE(nr || ' angajati!');
    IF nr = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Nu exista ang');
    END IF;
END;
/


/*6. S? se m?reasc? cu 1000 salariul unui angajat al c?rui cod este dat de la tastatur?. S? se trateze
cazul în care nu exist? angajatul al c?rui cod este specificat. Tratarea excep?ie se va face în
sec?iunea executabil?.*/
BEGIN
UPDATE emp_lco
SET salary = salary + 1000
WHERE employee_id = &p_emp;

IF SQL%NOTFOUND THEN
    RAISE_APPLICATION_ERROR(-20099, 'Angajatul nu exista');
END IF;
END;
/
ROLLBACK;