--------------CURSOARE---------------
SET SERVEROUTPUT ON;
/*1. Ob?ine?i pentru fiecare departament numele acestuia ?i num?rul de angaja?i, într-una din
urm?toarele forme:
“ În departamentul <nume departament> nu lucreaz? angajati”.
“ În departamentul <nume departament> lucreaz? un angajat”.
“ În departamentul <nume departament> lucreaz? <numar> angajati”.*/

DECLARE
nume departments.department_name%TYPE;
nr   NUMBER;
CURSOR c IS
    SELECT department_name nume, COUNT(*) nr_ang
    FROM departments 
    JOIN employees USING(department_id)
    GROUP BY department_name;
BEGIN
OPEN c;
LOOP
    FETCH c INTO nume, nr;
    EXIT WHEN c%NOTFOUND = TRUE;
    IF nr = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || nume || ' nu lucreaza angajati.');
    ELSIF nr = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || nume || ' lucreaza un angajat.');
    ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || nume || ' lucreaza ' || nr || ' angajati.');
    END IF;
END LOOP;
CLOSE c;
END;
/

/*2. Rezolva?i exerci?iul 1 men?inând informa?iile din cursor în colec?ii. Comenta?i. Procesa?i toate
liniile din cursor, înc?rcând la fiecare pas câte 5 linii.*/
--------CURSOR SI COLECTII-----------
DECLARE
TYPE tab_nume IS TABLE OF departments.department_name%TYPE;
TYPE tab_nr IS TABLE OF NUMBER(4);
t_nume tab_nume;
t_nr tab_nr;
CURSOR c IS
    SELECT department_name nume, COUNT(*) nr_ang
    FROM departments 
    JOIN employees USING(department_id)
    GROUP BY department_name;
BEGIN
    OPEN c;
    FETCH c BULK COLLECT INTO t_nume, t_nr;
    CLOSE c;
    FOR i IN t_nume.FIRST..t_nume.LAST LOOP
        IF t_nr(i) = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || t_nume(i) || ' nu lucreaza angajati.');
        ELSIF t_nr(i) = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || t_nume(i) || ' lucreaza un angajat.');
        ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || t_nume(i) || ' lucreaza ' || t_nr(i) || ' angajati.');
    END IF;
    END LOOP;
END;
/

/* Rezolva?i problema folosind cursorul ?i o singur? colec?ie.*/
---------CURSOR CU RECORD------------
/* !!!!!!!!!!!!!!!!! CUM FOLOSIM RECORD SI CURSOARE?
DECLARE
TYPE dep_pair IS RECORD
    (dep_name departments.department_name%TYPE,
     nr_ang NUMBER(4));
TYPE tablou IS TABLE OF dep_pair;
t tablou;
CURSOR c IS
    SELECT department_name nume, COUNT(*) nr_ang
    FROM departments 
    JOIN employees USING(department_id)
    GROUP BY department_name;
BEGIN
    OPEN c;
    FETCH c BULK COLLECT INTO t;
    CLOSE c;
    FOR i IN t.FIRST..t.LAST LOOP
        IF t.nr_ang(i) = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || t.dep_name(i) || ' nu lucreaza angajati.');
        ELSIF t.nr_ang(i) = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || t.dep_name(i) || ' lucreaza un angajat.');
        ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || t.dep_name(i) || ' lucreaza ' || t.nr_ang(i) || ' angajati.');
    END IF;
    END LOOP;
END;
/
*/

/*Rezolva?i exerci?iul 1 folosind un ciclu cursor.*/
----CICLU CURSOR-------
DECLARE
CURSOR c IS
    SELECT department_name nume, COUNT(*) nr
    FROM departments 
    JOIN employees USING(department_id)
    GROUP BY department_name;
BEGIN

FOR i IN c LOOP
    IF i.nr = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' nu lucreaza angajati.');
    ELSIF i.nr = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' lucreaza un angajat.');
    ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' lucreaza ' || i.nr || ' angajati.');
    END IF;
END LOOP;
END;
/


/*4. Rezolva?i exerci?iul 1 folosind un ciclu cursor cu subcereri. */
------ CICLU CURSOR CU SUBCERERI----------

BEGIN
FOR i IN   (SELECT department_name nume, COUNT(*) nr
            FROM departments 
            JOIN employees USING(department_id)
            GROUP BY department_name) 
    LOOP
    IF i.nr = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' nu lucreaza angajati.');
    ELSIF i.nr = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' lucreaza un angajat.');
    ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' lucreaza ' || i.nr || ' angajati.');
    END IF;
END LOOP;
END;
/

/*5. Ob?ine?i primii 3 manageri care au cei mai mul?i subordona?i. Afi?a?i numele managerului,
respectiv num?rul de angaja?i.
a. Rezolva?i problema folosind un cursor explicit.*/
/*b. Modifica?i rezolvarea anterioar? astfel încât s? ob?ine?i primii 4 manageri care îndeplinesc
condi?ia. Observa?i rezultatul ob?inut ?i specifica?i dac? la punctul a s-a ob?inut top 3
manageri?*/  
--da??????????????????
DECLARE
v_id employees.employee_id%TYPE;
v_nume employees.last_name%TYPE;
v_nr NUMBER(4);
CURSOR c IS
    SELECT e1.employee_id, e1.last_name, COUNT(e2.employee_id) nr
    FROM employees e1
    JOIN employees e2 ON (e1.employee_id = e2.manager_id)
    GROUP BY e1.employee_id, e1.last_name
    ORDER BY 3 DESC;
BEGIN
OPEN c;
LOOP
   FETCH c INTO v_id,v_nume, v_nr;
   EXIT WHEN c%ROWCOUNT>3 OR c%NOTFOUND;
   DBMS_OUTPUT.PUT_LINE('Managerul ' || v_nume || ' are ' || v_nr || ' angajati.');
END LOOP;
CLOSE c;
END;
/

/*6. Rezolva?i exerci?iul 5 folosind un ciclu cursor.*/
DECLARE
CURSOR c IS
    SELECT e1.employee_id, e1.last_name, COUNT(e2.employee_id) nr
    FROM employees e1
    JOIN employees e2 ON (e1.employee_id = e2.manager_id)
    GROUP BY e1.employee_id, e1.last_name
    ORDER BY 3 DESC;
BEGIN
FOR i IN c LOOP
   EXIT WHEN c%ROWCOUNT>3 OR c%NOTFOUND;
   DBMS_OUTPUT.PUT_LINE('Managerul ' || i.last_name || ' are ' || i.nr || ' angajati.');
END LOOP;
END;
/

/*8. Modifica?i exerci?iul 1 astfel încât s? ob?ine?i doar departamentele în care lucreaz? cel pu?in x
angaja?i, unde x reprezint? un num?r introdus de la tastatur?. */
DECLARE
x NUMBER(4) := &num;
nume departments.department_name%TYPE;
nr   NUMBER;
CURSOR c IS
    SELECT department_name nume, COUNT(*) nr_ang
    FROM departments 
    JOIN employees USING(department_id)
    GROUP BY department_name
    ORDER BY 2 DESC;  -----sortam dupa numarul de angajati pentru a ne opri cand numarul de angajati scade
BEGIN
OPEN c;
LOOP
    FETCH c INTO nume, nr;
    EXIT WHEN c%NOTFOUND = TRUE OR nr < x;
    IF nr = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || nume || ' nu lucreaza angajati.');
    ELSIF nr = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || nume || ' lucreaza un angajat.');
    ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || nume || ' lucreaza ' || nr || ' angajati.');
    END IF;
END LOOP;
CLOSE c;
END;
/



----- CU CICLU CURSOR CU PARAMETRU ---------
DECLARE
x NUMBER(4) := &num;
CURSOR c (parametru NUMBER) IS
    SELECT department_name nume, COUNT(*) nr_ang
    FROM departments 
    JOIN employees USING(department_id)
    GROUP BY department_name
    HAVING COUNT(*) > parametru;
    ----fara having: ORDER BY 2 DESC; sortam dupa numarul de angajati pentru a ne opri cand numarul de angajati scade
BEGIN
FOR i IN c(x) LOOP
    IF i.nr_ang = 0 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' nu lucreaza angajati.');
    ELSIF i.nr_ang = 1 THEN DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' lucreaza un angajat.');
    ELSE DBMS_OUTPUT.PUT_LINE('In departmentul ' || i.nume || ' lucreaza ' || i.nr_ang || ' angajati.');
    END IF;
END LOOP;
END;
/

DECLARE
v_x number(4) := &p_x;
CURSOR c (paramentru NUMBER) IS
 SELECT department_name nume, COUNT(employee_id) nr
 FROM departments d, employees e
 WHERE d.department_id=e.department_id
 GROUP BY department_name
 HAVING COUNT(employee_id)> paramentru;
BEGIN
 FOR i in c(v_x) LOOP
 DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume||
 ' lucreaza '|| i.nr||' angajati');
 END LOOP;
END;
/


/*9. M?ri?i cu 1000 salariile celor care au fost angaja?i în 2000 (din tabelul emp_***) 
blocând liniile înainte de actualizare (cursor SELECT FOR UPDATE).*/
SET SERVEROUTPUT ON

--Facem un query in care selectam numele si salariul celor angajati in 2000
SELECT last_name, hire_date, salary
FROM emp_lco
WHERE EXTRACT(year FROM hire_date) = 2000;

--Declaram un cursor la aceasta subcerere si facem update
DECLARE
CURSOR c IS
SELECT last_name, hire_date, salary
FROM emp_lco
WHERE EXTRACT(year FROM hire_date) = 2000
FOR UPDATE OF salary WAIT 5;
BEGIN
FOR i IN c LOOP
UPDATE emp_lco
SET salary = salary + 1000
WHERE CURRENT OF c;
END LOOP;
END;
/
ROLLBACK;

UPDATE emp_lco  --- CUM TREBUIE APELATE PENTRU A SE VEDEA WAIT?
SET salary = salary * 1.5;

/*10. Pentru fiecare dintre departamentele 10, 20, 30 ?i 40, ob?ine?i numele precum ?i lista numelor
angaja?ilor care î?i desf??oar? activitatea în cadrul acestora. Rezolva?i problema folosind:
a. cele trei tipuri de cursoare studiate;
b. expresii cursor.*/
----TODO: cu cursor clasic si cursor cu subcereri
--cursor ciclu
----!!!!!!! ATENTIE MAI DIFICIL; cu parametru; in laborator cu subcereri
DECLARE
CURSOR c_dep IS
SELECT d.department_id, department_name
FROM departments d
WHERE d.department_id IN (10, 20, 30, 40);
CURSOR c_emp(prop NUMBER) IS
SELECT last_name
FROM employees
WHERE department_id = prop;
BEGIN
FOR i IN c_dep LOOP
    DBMS_OUTPUT.PUT_LINE('Id departament: ' || i.department_id || 
            ' nume department: ' || i.department_name);
    FOR j IN c_emp(i.department_id) LOOP
        DBMS_OUTPUT.PUT_LINE('-------Nume angajat: ' || j.last_name);
    END LOOP;
END LOOP;
END;
/

--CU EXPRESII CURSOR - NESTED CURSOR
DECLARE
    TYPE refcursor IS REF CURSOR;
    CURSOR c_dept IS
        SELECT department_name,
            CURSOR (SELECT last_name
                    FROM employees
                    WHERE department_id = d.department_id)
        FROM departments d
        WHERE department_id IN (10, 20, 30, 40);
v_dep_name departments.department_name%TYPE;
v_cursor refcursor;
v_last_name employees.last_name%TYPE;
BEGIN
OPEN c_dept;
LOOP
    FETCH c_dept INTO v_dep_name, v_cursor;
    EXIT WHEN c_dept%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Nume department: ' || v_dep_name);
    ---- ATENTIE: TREBUIE FOLOSIT LOOP, nu drept cursor ciclu; EL SE DESCHIDE SI INCHIDE AUTOMAT
    ---- atunci cand e luat din c_dept
    LOOP
        FETCH v_cursor INTO v_last_name;
        EXIT WHEN v_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('-------Nume angajat: ' || v_last_name);
    END LOOP;
END LOOP;
CLOSE c_dept;
END;
/

------------------ CURSOR DINAMIC ------------------------------
/*11. Declara?i un cursor dinamic care întoarce linii de tipul celor din tabelul emp_***. În func?ie
de o op?iune introdus? de la tastatur? (una dintre valorile 1, 2 sau 3) deschide?i cursorul astfel
încât s? reg?seasc?:
- toate informa?iile din tabelul emp_*** (pentru op?iunea 1);
- doar angaja?ii având salariul cuprins între 10000 ?i 20000 (pentru op?iunea 2);
- doar salaria?ii angaja?i în anul 2000 (pentru op?iunea 3).
Verifica?i ce se întâmpl? în cazul în care introduce?i o valoare diferit? de 1, 2 sau 3. Modifica?i
corespunz?tor.*/
DECLARE
TYPE cursor_emp IS REF CURSOR RETURN employees%ROWTYPE;
c cursor_emp;
v_emp employees%ROWTYPE;
opt NUMBER := &optiune;
BEGIN
IF opt = 1 THEN OPEN c FOR
                        SELECT * 
                        FROM employees;
ELSIF opt = 2 THEN OPEN c FOR
                        SELECT * 
                        FROM employees
                        WHERE salary BETWEEN 10000 AND 20000;
ELSIF opt = 3 THEN OPEN c FOR
                        SELECT * 
                        FROM employees
                        WHERE EXTRACT(year FROM hire_date) = 2000;
ELSE DBMS_OUTPUT.PUT_LINE('Optiunea nu este valida');
END IF;
IF opt = 1 OR opt = 2 OR opt = 3 THEN
    LOOP
        FETCH c INTO v_emp;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_emp.last_name);
    END LOOP;
CLOSE c;
END IF;
END;
/

/*12. Citi?i de la tastatur? o valoare n. Prin intermediul unui cursor deschis cu ajutorul unui ?ir
dinamic ob?ine?i angaja?ii având salariul mai mare decât n. Pentru fiecare linie reg?sit? de
cursor afi?a?i urm?toarele informa?ii:
- numele ?i salariul dac? angajatul nu are comision;
- numele, salariul ?i comisionul dac? angajatul are comision.*/
DECLARE
TYPE cursor_ang IS REF CURSOR;
c cursor_ang;
v_nr NUMBER := &n;
v_name employees.last_name%TYPE;
v_salary employees.salary%TYPE;
v_commission employees.commission_pct%TYPE;
BEGIN
    OPEN c FOR
        'SELECT last_name, salary, commission_pct FROM employees WHERE salary > :bind_var'
        USING v_nr;
        --sau SELECT last_name, salary, commission_pct FROM employees WHERE salary > v_nr;
    LOOP
    FETCH c INTO v_name, v_salary, v_commission;
    EXIT WHEN c%NOTFOUND;
    IF v_commission IS NULL THEN
        DBMS_OUTPUT.PUT_LINE('Name: ' || v_name || ' salary: ' || v_salary);
    ELSE DBMS_OUTPUT.PUT_LINE('Name: ' || v_name || ' salary: ' || v_salary || ' commission: ' || v_commission);
    END IF;
    END LOOP;
    CLOSE c;
END;
/


--Exercitii propuse--
/*1. Pentru fiecare job (titlu – care va fi afi?at o singur? dat?) ob?ine?i lista angaja?ilor (nume ?i
salariu) care lucreaz? în prezent pe jobul respectiv. Trata?i cazul în care nu exist? angaja?i care
s? lucreze în prezent pe un anumit job. Rezolva?i problema folosind:
a. cursoare clasice
b. ciclu cursoare
c. ciclu cursoare cu subcereri
d. expresii cursor*/

--ne declaram un cursor v_job in care sa salvam titlu si codul de job
--v_emp nume salariu cu parametru v_job 

SET SERVEROUTPUT ON;

DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT last_name, salary, commission_pct
        FROM employees
        WHERE job_id = param_cod);
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;

BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    LOOP
    FETCH cur_emp INTO v_name, v_salary, v_commission;
    EXIT WHEN cur_emp%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu numele ' || v_name || ' are salariul ' || v_salary ||
                         ' si comisionul ' || NVL(v_commission,0));
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; --ATENTIE AICI NU MAI PUNEM PARAMETRU
    END LOOP;
    CLOSE cur_job;
END;
/

/*2. Modifica?i exerci?iul anterior astfel încât s? ob?ine?i ?i urm?toarele informa?ii:
- un num?r de ordine pentru fiecare angajat care va fi resetat pentru fiecare job
- pentru fiecare job
o num?rul de angaja?i
o valoarea lunar? a veniturilor angaja?ilor
o valoarea medie a veniturilor angaja?ilor
- indiferent job
o num?rul total de angaja?i
o valoarea total? lunar? a veniturilor angaja?ilor
o valoarea medie a veniturilor angaja?ilor*/
DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT last_name, salary, commission_pct
        FROM employees
        WHERE job_id = param_cod);
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;
    v_ind        NUMBER := 1;
    v_venit_job  NUMBER := 0;
    v_venit_total NUMBER := 0;
    v_nr_total   NUMBER := 0;
BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    LOOP
    FETCH cur_emp INTO v_name, v_salary, v_commission;
    EXIT WHEN cur_emp%NOTFOUND;
    
    DBMS_OUTPUT.PUT_LINE(v_ind || '. Angajatul cu numele ' || v_name || ' are salariul ' || v_salary ||
                         ' si comisionul ' || NVL(v_commission,0));
    v_ind := v_ind + 1;
    v_venit_job := v_venit_job + v_salary * (1 + NVL(v_commission,0));
    END LOOP;
    v_ind := v_ind - 1;
    v_nr_total := v_nr_total + v_ind;
    
    DBMS_OUTPUT.PUT_LINE('Numarul de angajati: ' || v_ind);
    DBMS_OUTPUT.PUT_LINE('Valoarea veniturilor lunare: ' || v_venit_job);
    DBMS_OUTPUT.PUT_LINE('Media veniturilor lunare: ' || v_venit_job/v_ind);
    v_ind := 1;
    v_venit_total := v_venit_total + v_venit_job;
    v_venit_job := 0;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; 
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Venit total: ' || v_venit_total);
    DBMS_OUTPUT.PUT_LINE('Numar total de angajati: ' || v_nr_total);
    DBMS_OUTPUT.PUT_LINE('Media veniturilor: ' || ROUND(v_venit_total/v_nr_total,3));
    CLOSE cur_job;
END;
/

/*3. Modifica?i exerci?iul anterior astfel încât s? ob?ine?i suma total? alocat? lunar pentru plata
salariilor ?i a comisioanelor tuturor angaja?ilor, iar pentru fiecare angajat cât la sut? din aceast?
sum? câ?tig? lunar.*/
DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT last_name, salary, commission_pct
        FROM employees
        WHERE job_id = param_cod);
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;
    v_ind        NUMBER := 1;
    v_venit_job  NUMBER := 0;
    v_venit_total NUMBER := 0;
    v_nr_total   NUMBER := 0;
    suma_salarii NUMBER := 0;
    suma_comisioane NUMBER := 0;
    TYPE rec IS RECORD (nume employees.last_name%TYPE,
                        salariu employees.salary%TYPE,
                        comision employees.commission_pct%TYPE);
    TYPE ind IS TABLE OF rec INDEX BY BINARY_INTEGER;
    v ind;
BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    FETCH cur_emp BULK COLLECT INTO v;
    
    FOR i IN v.FIRST..v.LAST LOOP
        SELECT SUM(salary) INTO suma_salarii
        FROM employees;
        SELECT SUM(salary * NVL(commission_pct,0)) INTO suma_comisioane
        FROM employees;
        
        DBMS_OUTPUT.PUT_LINE(v_ind || '. Angajatul cu numele ' || v(i).nume || ' are salariul ' || 
                            v(i).salariu || ' si comisionul ' || NVL(v(i).comision,0)
                            || ' si castiga ' || ROUND(v(i).salariu/suma_salarii,3)
                            || ' si ' || ROUND((v(i).salariu * NVL(v(i).comision,0))/suma_comisioane,3));
        
        v_ind := v_ind + 1;
        v_venit_job := v_venit_job + v(i).salariu * (1 + NVL(v(i).comision,0));
                
        v_ind := v_ind - 1;
        v_nr_total := v_nr_total + v_ind;
        
        DBMS_OUTPUT.PUT_LINE('Numarul de angajati: ' || v_ind);
        DBMS_OUTPUT.PUT_LINE('Valoarea veniturilor lunare: ' || v_venit_job);
        DBMS_OUTPUT.PUT_LINE('Media veniturilor lunare: ' || v_venit_job/v_ind);
    
    END LOOP;
    v_ind := 1;
    v_venit_total := v_venit_total + v_venit_job;
    v_venit_job := 0;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; 
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Venit total: ' || v_venit_total);
    DBMS_OUTPUT.PUT_LINE('Numar total de angajati: ' || v_nr_total);
    DBMS_OUTPUT.PUT_LINE('Media veniturilor: ' || ROUND(v_venit_total/v_nr_total,3));
    CLOSE cur_job;
END;
/


/*4. Modifica?i exerci?iul anterior astfel încât s? ob?ine?i pentru fiecare job primii 5 angaja?i care
câ?tig? cel mai mare salariu lunar. Specifica?i dac? pentru un job sunt mai pu?in de 5 angaja?i.*/
DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT last_name, salary, commission_pct
        FROM employees
        WHERE job_id = param_cod);
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;

BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    LOOP
    FETCH cur_emp INTO v_name, v_salary, v_commission;
    EXIT WHEN cur_emp%NOTFOUND OR cur_emp%ROWCOUNT > 5;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu numele ' || v_name || ' are salariul ' || v_salary ||
                         ' si comisionul ' || NVL(v_commission,0));
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; 
    END LOOP;
    CLOSE cur_job;
END;
/
