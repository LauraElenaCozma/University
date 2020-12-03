SET SERVEROUTPUT ON;

----------------COMPARATII CU VALOAREA NULL---------------
/*Rezultatul blocului PL/SQL este:
valoare <> NULL este != TRUE
NULL = NULL este != TRUE
Deci orice valoare comparata cu null este diferita de true*/
DECLARE
    x NUMBER(1) := 5;
    y x%TYPE    := NULL;
BEGIN
    IF x <> y THEN 
        DBMS_OUTPUT.PUT_LINE('Valoare <> null este true');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Valoare <> null este != true');
    END IF;
    x := NULL;
    IF x = y THEN
        DBMS_OUTPUT.PUT_LINE('null = null este true');
    ELSE
        DBMS_OUTPUT.PUT_LINE('null = null este =! true');
    END IF;
END;
/

--------------Tipul RECORD-------------------
/*Defini?i tipul înregistrare emp_record care con?ine câmpurile employee_id, salary ?i job_id. Apoi,
defini?i o variabil? de acest tip.*/
DECLARE 
    TYPE emp_record IS RECORD          --definirea tipului record
        (employee_id employees.employee_id%TYPE, 
        salary employees.salary%TYPE,
        job_id employees.job_id%TYPE);
    v_ang emp_record;
BEGIN
    ----Initializati si afisati variabila definita
    v_ang.employee_id := 2020;
    v_ang.salary := 10000;
    v_ang.job_id := 'SA_MAN';
    DBMS_OUTPUT.PUT_LINE('Cod angajat: ' || v_ang.employee_id || ' salariu ' || v_ang.salary || ' cod job ' || v_ang.job_id);
    
    /*Ini?ializa?i variabila cu valorile corespunz?toare angajatului având codul 101. Afi?a?i variabila.*/
    SELECT employee_id, salary, job_id INTO v_ang
    FROM employees
    WHERE employee_id = 101;
    DBMS_OUTPUT.PUT_LINE('DUPA SELECT: Cod angajat: ' || v_ang.employee_id || ' salariu ' || v_ang.salary || ' cod job ' || v_ang.job_id);
    
    /*?terge?i angajatul având codul 100 din tabelul emp_*** ?i re?ine?i în variabila definit? anterior
    informa?ii corespunz?toare acestui angajat. Anula?i modific?rile realizate.*/
    DELETE FROM emp_lco
    WHERE employee_id = 100
    RETURNING employee_id, salary, job_id INTO v_ang;
    DBMS_OUTPUT.PUT_LINE('DUPA DELETE: Cod angajat: ' || v_ang.employee_id || ' salariu ' || v_ang.salary || ' cod job ' || v_ang.job_id);
END;
/
rollback;

/*Declara?i dou? variabile cu aceea?i structur? ca ?i tabelul emp_***. ?terge?i din tabelul emp_***
angaja?ii 100 ?i 101, men?inând valorile ?terse în cele dou? variabile definite. Folosind cele dou?
variabile, introduce?i informa?iile ?terse în tabelul emp_***.*/
DECLARE
    v_ang1 employees%ROWTYPE;
    v_ang2 employees%ROWTYPE;
BEGIN
    DELETE FROM emp_lco
    WHERE employee_id = 100
    RETURNING employee_id, first_name, last_name, email, phone_number,
    hire_date, job_id, salary, commission_pct, manager_id,department_id
    INTO v_ang1;
    DBMS_OUTPUT.PUT_LINE('v_ang1: Cod angajat: ' || v_ang1.employee_id || ' salariu ' || v_ang1.salary || ' cod job ' || v_ang1.job_id 
                    || ' commission_pct ' || v_ang1.commission_pct || ' manager_id ' || v_ang1.manager_id 
                    || ' department_id ' || v_ang1.department_id );
    INSERT INTO emp_lco
    VALUES v_ang1;
        
    DELETE FROM emp_lco
    WHERE employee_id = 101
    RETURNING employee_id, first_name, last_name, email, phone_number,
    hire_date, job_id, salary, commission_pct, manager_id,department_id
    INTO v_ang2;
    
    INSERT INTO emp_lco
    VALUES(1000,'FN','LN','E',null,sysdate, 'AD_VP',1000, null,100,90);
    DBMS_OUTPUT.PUT_LINE('v_ang2: Cod angajat: ' || v_ang2.employee_id || ' salariu ' || v_ang2.salary || ' cod job ' || v_ang2.job_id 
                        || ' commission_pct ' || v_ang2.commission_pct || ' manager_id ' || v_ang2.manager_id 
                        || ' department_id ' || v_ang2.department_id );
    UPDATE emp_lco
    SET ROW = v_ang2
    WHERE employee_id = 1000;
END;
/

SELECT * FROM emp_lco
ORDER BY 1;

ROLLBACK;


----------TABLOU INDEXAT----------------------
/*4. Defini?i un tablou indexat de numere. Introduce?i în acest tablou primele 10 de numere naturale.*/
DECLARE
TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
tablou tablou_indexat;
BEGIN
FOR i IN 1..10 LOOP
    tablou(i) := i;
END LOOP;
/*Afi?a?i num?rul de elemente al tabloului ?i elementele acestuia.*/
DBMS_OUTPUT.PUT_LINE('Pct a');
DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || tablou.COUNT);
FOR i IN 1..10 LOOP
    DBMS_OUTPUT.PUT(tablou(i) || ' ');
END LOOP;
DBMS_OUTPUT.NEW_LINE;
/*Seta?i la valoarea null elementele de pe pozi?iile impare. Afi?a?i num?rul de elemente al tabloului
?i elementele acestuia.*/
FOR i IN 1..10 LOOP
    IF i MOD 2 = 1 THEN
        tablou(i) := NULL;
    END IF;
END LOOP;
DBMS_OUTPUT.PUT_LINE('Pct b');
DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || tablou.COUNT);
FOR i IN tablou.FIRST..tablou.LAST LOOP
    DBMS_OUTPUT.PUT(NVL(tablou(i), 0) || ' ');
END LOOP;
DBMS_OUTPUT.NEW_LINE;
/*?terge?i primul element, elementele de pe pozi?iile 5, 6 ?i 7, respectiv ultimul element. Afi?a?i
valoarea ?i indicele primului, respectiv ultimului element. Afi?a?i elementele tabloului ?i num?rul
acestora.*/
DBMS_OUTPUT.PUT_LINE('Pct c');
tablou.DELETE(tablou.FIRST);
tablou.DELETE(5,7);
tablou.DELETE(tablou.LAST);
DBMS_OUTPUT.PUT_LINE('Indice primul element: ' || tablou.FIRST || ' valoare: ' ||tablou(tablou.FIRST));
DBMS_OUTPUT.PUT_LINE('Indice ultimul element: ' || tablou.LAST || ' valoare: ' ||tablou(tablou.LAST));
DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || tablou.COUNT);
FOR i IN tablou.FIRST..tablou.LAST LOOP
    IF tablou.EXISTS(i) THEN         --ATENTIE SA VERIFICAM DACA EXISTA
        DBMS_OUTPUT.PUT(NVL(tablou(i), 0) || ' ');
    END IF;
/*
aveam 0 2 0 4 0 6 0 8 0 10
Stergem primul elem, 5 6 7 si 10
ramanem cu:
_ 2 0 4 _ _ _ 8 0
*/
END LOOP;
DBMS_OUTPUT.NEW_LINE;
/*?terge?i toate elementele tabloului.*/
tablou.DELETE;
DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || tablou.COUNT);
END;
/

/*Defini?i un tablou indexat de înregistr?ri având tipul celor din tabelul emp_***. ?terge?i primele
dou? linii din tabelul emp_***. Afi?a?i elementele tabloului. Folosind tabelul indexat ad?uga?i înapoi
cele dou? linii ?terse.*/
DECLARE
    TYPE tablou_indexat IS TABLE OF emp_lco%ROWTYPE INDEX BY BINARY_INTEGER;
    t tablou_indexat;
BEGIN
    --stergem primele 2 randuri. Verificare cu ROWNUM <= 2
    DELETE FROM emp_lco
    WHERE ROWNUM <=2
    RETURNING employee_id, first_name, last_name, email, phone_number,
    hire_date, job_id, salary, commission_pct, manager_id,
    department_id
    BULK COLLECT INTO t;    --ATENTIE BULK COLLECT
    
    --afisare elemente tablou
    DBMS_OUTPUT.PUT_LINE (t(1).employee_id ||' ' || t(1).last_name);
    DBMS_OUTPUT.PUT_LINE (t(2).employee_id ||' ' || t(2).last_name);

    --inserare in tablou
    INSERT INTO emp_lco
    VALUES t(1);
    INSERT INTO emp_lco
    VALUES t(2);
END;
/
SELECT * FROM emp_lco
ORDER BY 1;
ROLLBACK;


-----------------TABLOU IMBRICAT------------------------------

/*Ex 4 cu tablou imbricat*/
DECLARE
TYPE tablou_imbricat IS TABLE OF NUMBER;
t tablou_imbricat := tablou_imbricat(); --DIFERENTA FATA DE TABLOU INDEXAT
BEGIN
    -- pct a
    DBMS_OUTPUT.PUT_LINE('Pct a');
    FOR i IN 1..10 LOOP
        t.EXTEND;       --DIFERENTA FATA DE TABLOU INDEXAT
        t(i) := i;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || t.COUNT);
    FOR i IN t.FIRST..t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    --pct b
    DBMS_OUTPUT.PUT_LINE('Pct b');
    FOR i IN t.FIRST..t.LAST LOOP
        IF i MOD 2 = 1 THEN
            t(i) := NULL;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || t.COUNT);
    FOR i IN t.FIRST..t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    --pct c
    t.DELETE(t.FIRST);
    t.DELETE(5,7);
    t.DELETE(t.LAST);
    DBMS_OUTPUT.PUT_LINE('Indice primul element: ' || t.FIRST || ' valoare: ' ||t(t.FIRST));
    DBMS_OUTPUT.PUT_LINE('Indice ultimul element: ' || t.LAST || ' valoare: ' ||t(t.LAST));
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || t.COUNT);
    FOR i IN t.FIRST..t.LAST LOOP
        IF t.EXISTS(i) THEN
            DBMS_OUTPUT.PUT(NVL(t(i),0) || ' ');
        END IF;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    --pct d
    DBMS_OUTPUT.PUT_LINE('Pct d');
    t.DELETE;
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || t.COUNT);
END;
/

/*7.Declara?i un tip tablou imbricat de caractere ?i o variabil? de acest tip. Ini?ializa?i variabila cu
urm?toarele valori: m, i, n, i, m. Afi?a?i con?inutul tabloului, de la primul la ultimul element ?i
invers. ?terge?i elementele 2 ?i 4 ?i apoi afi?a?i con?inutul tabloului.*/
DECLARE
TYPE tablou_imbricat IS TABLE OF CHAR(1);
t tablou_imbricat := tablou_imbricat('z','i','n','i','m');
i NUMBER;
BEGIN
    --de la primul la ultimul
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
        i := t.NEXT(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    --de la ultimul la primul
    i := t.LAST;
    WHILE i >= t.FIRST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
        i := t.PRIOR(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    --stergem elementele 2 si 4
    t.DELETE(2);
    t.DELETE(4);
    DBMS_OUTPUT.PUT('Dupa stergere: ');
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
        i := t.NEXT(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    i := t.LAST;
    WHILE i >= t.FIRST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
        i := t.PRIOR(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/


-----------------VECTORI----------
--Ex 4 cu varray
DECLARE
    TYPE vector IS VARRAY(10) OF NUMBER;
    v vector := vector();
BEGIN
    FOR i IN 1..10 LOOP
        v.EXTEND;
        v(i) := i;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || v.COUNT);
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT(v(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    --pct b
    DBMS_OUTPUT.PUT_LINE('Pct b');
    FOR i IN v.FIRST..v.LAST LOOP
        IF i MOD 2 = 1 THEN
            v(i) := NULL;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || v.COUNT);
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT(NVL(v(i),0) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    --pct c
    /*DELETE NU MERGE PE VARRAY*/
    --pct d
    DBMS_OUTPUT.PUT_LINE('Pct d');
    v.DELETE;
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || v.COUNT);
END;
/

/*9. Defini?i tipul subordonati_*** (vector, dimensiune maxim? 10, men?ine numere). Crea?i tabelul
manageri_*** cu urm?toarele câmpuri: cod_mgr NUMBER(10), nume VARCHAR2(20), lista
subordonati_***. Introduce?i 3 linii în tabel. Afi?a?i informa?iile din tabel. ?terge?i tabelul creat,
apoi tipul.*/

CREATE OR REPLACE TYPE subordonati_lco IS VARRAY(10) OF NUMBER;
/
CREATE TABLE manageri_lco
    (cod_mgr NUMBER(10),
     nume VARCHAR2(20),
     lista subordonati_lco);
DECLARE
    v subordonati_lco := subordonati_lco(3,5);
    t manageri_lco.lista%TYPE;
BEGIN
    INSERT INTO manageri_lco 
    VALUES (1, 'Steve', subordonati_lco(1,2,3));
    INSERT INTO manageri_lco 
    VALUES (2, 'Iris', v);
    INSERT INTO manageri_lco 
    VALUES (3, 'Cynthia', null);
    
    SELECT lista INTO t
    FROM manageri_lco
    WHERE cod_mgr = 1;
    
    FOR i IN t.FIRST..t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
END;
/
SELECT * FROM manageri_lco;
DROP TABLE manageri_lco;
DROP TYPE subordonati_lco;

/*10. Crea?i tabelul emp_test_*** cu coloanele employee_id ?i last_name din tabelul employees.
Ad?uga?i în acest tabel un nou câmp numit telefon de tip tablou imbricat. Acest tablou va men?ine
pentru fiecare salariat toate numerele de telefon la care poate fi contactat. Insera?i o linie nou? în
tabel. Actualiza?i o linie din tabel. Afi?a?i informa?iile din tabel. ?terge?i tabelul ?i tipul.*/
CREATE TABLE emp_test_lco AS
SELECT employee_id, last_name FROM employees
WHERE ROWNUM <= 3;
CREATE OR REPLACE TYPE tablou_imbricat IS TABLE OF VARCHAR2(12);
/
ALTER TABLE emp_test_lco
ADD (telefon tablou_imbricat)
NESTED TABLE telefon STORE AS tabel_telefon_lco;

INSERT INTO emp_test_lco
VALUES(1, 'Louis', tablou_imbricat('0787405060','0233154462'));

UPDATE emp_test_lco
SET telefon = tablou_imbricat('0718288391')
WHERE employee_id = 102;
SELECT * FROM emp_test_lco;
DROP TABLE emp_test_lco;
DROP TYPE tablou_imbricat;

/*?terge?i din tabelul emp_*** salaria?ii având codurile men?inute într-un vector.*/
--varianta 1 pentru fiecare cod stergem din tabel
DECLARE
TYPE tip_cod IS VARRAY(5) OF NUMBER(3);
coduri tip_cod := tip_cod(205,206);
BEGIN
FOR i IN coduri.FIRST..coduri.LAST LOOP
    DELETE FROM emp_lco
    WHERE employee_id = coduri(i);
END LOOP;
END;
/
SELECT * FROM emp_lco ORDER BY 1;
ROLLBACK;

--varianta 2
DECLARE 
TYPE tip_cod IS VARRAY(20) OF NUMBER;
coduri tip_cod := tip_cod(205,206);
BEGIN
FORALL i IN coduri.FIRST..coduri.LAST  --cu forall; toate liniile colectiei transmise simultan
    DELETE FROM emp_lco
    WHERE employee_id = coduri(i);
END;
/
SELECT * FROM emp_lco;
ROLLBACK;

-------------EXERCITII PROPUSE-----------------
/*Men?ine?i într-o colec?ie codurile celor mai prost pl?ti?i 5 angaja?i care nu câ?tig? comision. Folosind aceast?
colec?ie m?ri?i cu 5% salariul acestor angaja?i. Afi?a?i valoarea veche a salariului, respectiv valoarea nou? a
salariului.*/
DECLARE
TYPE tablou IS TABLE OF emp_lco%ROWTYPE INDEX BY PLS_INTEGER; --functioneaza si cu tablou imbricat, fara constructor; DE CE?
t tablou;
BEGIN
SELECT * BULK COLLECT INTO t
FROM (SELECT *
FROM emp_lco
ORDER BY salary)
WHERE ROWNUM <= 5;
--mariti cu 5% salariul acestor angajati
FOR i in t.FIRST..t.LAST LOOP
    DBMS_OUTPUT.PUT_LINE('Cod ang: ' || t(i).employee_id || ' salariu initial: ' || t(i).salary); 
    UPDATE emp_lco
    SET salary = salary * 1.05
    WHERE employee_id = t(i).employee_id
    RETURNING salary INTO t(i).salary;
    DBMS_OUTPUT.PUT_LINE('Cod ang: ' || t(i).employee_id || ' salariu marit: ' || t(i).salary); 
END LOOP;
END;
/
SELECT * FROM emp_lco;

/*2. Defini?i un tip colec?ie denumit tip_orase_***. Crea?i tabelul excursie_*** cu urm?toarea structur?:
cod_excursie NUMBER(4), denumire VARCHAR2(20), orase tip_orase_*** (ce va con?ine lista
ora?elor care se viziteaz? într-o excursie, într-o ordine stabilit?; de exemplu, primul ora? din list? va fi primul
ora? vizitat), status (disponibil? sau anulat?).
c. Pentru o excursie al c?rui cod este dat, afi?a?i num?rul de ora?e vizitate, respectiv numele ora?elor.
d. Pentru fiecare excursie afi?a?i lista ora?elor vizitate.
e. Anula?i excursiile cu cele mai pu?ine ora?e vizitate.*/
CREATE OR REPLACE TYPE tip_orase_lco IS TABLE OF VARCHAR2(100);
/
CREATE TABLE excursie_lco
(cod_excursie NUMBER(4),
denumire VARCHAR2(20),
orase tip_orase_lco,
status VARCHAR2(20))
NESTED TABLE orase STORE AS tabel_orase_lco;

SELECT * FROM excursie_lco;
/*a. Insera?i 5 înregistr?ri în tabel.*/
INSERT INTO excursie_lco VALUES(1, 'Excursia 1', tip_orase_lco('Bucuresti', 'Cluj', 'Iasi'), 'disponibila');
INSERT INTO excursie_lco VALUES(2, 'Excursia 2', tip_orase_lco('Bucuresti', 'Ploiesti', 'Iasi'), 'disponibila');
INSERT INTO excursie_lco VALUES(3, 'Excursia 3', tip_orase_lco('Brasov', 'Sibiu'), 'anulata');
INSERT INTO excursie_lco VALUES(4, 'Excursia 4', tip_orase_lco('Timisoara'), 'disponibila');
INSERT INTO excursie_lco VALUES(5, 'Excursia 5', NULL, 'disponibila');

/*b. Actualiza?i coloana orase pentru o excursie specificat?:*/
DECLARE
    lista tip_orase_lco;
    v_cod_excursie excursie_lco.cod_excursie%TYPE := &&cod;
    v_oras1 VARCHAR2(100) := '&&oras1';
    v_oras2 VARCHAR2(100) := '&&oras2';
    v_oras1_inv VARCHAR2(100) := '&&oras3';
    v_oras2_inv VARCHAR2(100) := '&&oras4';
    v_oras_elim VARCHAR2(100) := '&&oras5';
    i NUMBER;   --o folosim si ca variabila de parcurgere
    poz NUMBER;
BEGIN
    SELECT orase INTO lista
    FROM excursie_lco
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Lista initiala');
    FOR i IN lista.FIRST..lista.LAST LOOP
        DBMS_OUTPUT.PUT(lista(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    --- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?;
    DBMS_OUTPUT.PUT_LINE('Lista dupa adaugare');
    lista.EXTEND();
    lista(lista.LAST) := v_oras1;
    FOR i IN lista.FIRST..lista.LAST LOOP
        DBMS_OUTPUT.PUT(lista(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    -- ad?uga?i un ora? nou în list?, ce va fi al doilea ora? vizitat în excursia respectiv?;
    DBMS_OUTPUT.PUT_LINE('Lista dupa a doua adaugare');
    --marim lista cu un element
    lista.EXTEND();
    --deplasam elementele
    i := lista.LAST;
    WHILE i >= 3 LOOP
        lista(i) := lista(i-1);
        i := lista.PRIOR(i);
    END LOOP;
    lista(2) := v_oras2;
    --afisare
    FOR i IN lista.FIRST..lista.LAST LOOP
        DBMS_OUTPUT.PUT(lista(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    -- inversa?i ordinea de vizitare a dou? dintre ora?e al c?ror nume este specificat;
    FOR i IN lista.FIRST..lista.LAST LOOP
        IF lista(i) = v_oras1_inv THEN
            lista(i) := v_oras2_inv;
        ELSIF lista(i) = v_oras2_inv THEN
            lista(i) := v_oras1_inv;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Dupa inversare:');
    FOR i IN lista.FIRST..lista.LAST LOOP
        DBMS_OUTPUT.PUT(lista(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    -- elimina?i din list? un ora? al c?rui nume este specificat.
    FOR i IN lista.FIRST..lista.LAST LOOP
        IF lista(i) = v_oras_elim THEN
            poz := i;
        END IF;
    END LOOP;
    IF(poz IS NOT null)     --daca exista orasul eliminat ATENTIE COMPARATIE CU IS NOT
        DBMS_OUTPUT.PUT_LINE('HERE');
    END IF;
    DBMS_OUTPUT.PUT_LINE('Dupa eliminare:');
    FOR i IN lista.FIRST..lista.LAST LOOP
        DBMS_OUTPUT.PUT(lista(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/
/*Pentru o excursie al c?rui cod este dat, afi?a?i num?rul de ora?e vizitate, respectiv numele ora?elor.*/
DECLARE 
lista tip_orase_lco;
BEGIN
    SELECT orase INTO lista
    FROM excursie_lco
    WHERE cod_excursie = &v_cod;
    DBMS_OUTPUT.PUT_LINE('Nr orase: ' || lista.COUNT);
    FOR i IN lista.FIRST..lista.LAST LOOP
        DBMS_OUTPUT.PUT(lista(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/
SELECT * FROM excursie_lco;
/*d. Pentru fiecare excursie afi?a?i lista ora?elor vizitate.*/
DECLARE
TYPE lista IS TABLE OF excursie_lco.cod_excursie%TYPE INDEX BY pls_integer;
t lista; --NU UITA DE DECLARAREA VARIABILEI
l_orase tip_orase_lco;
BEGIN
SELECT cod_excursie BULK COLLECT INTO t
FROM excursie_lco;

FOR i IN t.FIRST..t.LAST LOOP
    SELECT orase INTO l_orase
    FROM excursie_lco
    WHERE cod_excursie = t(i);
     
    IF l_orase IS NOT NULL THEN
        FOR j IN l_orase.FIRST..l_orase.LAST LOOP
            DBMS_OUTPUT.PUT('Excursia: ' || t(i) || ' ' || l_orase(j) || ' '); 
        END LOOP;
        DBMS_OUTPUT.NEW_LINE;
    ELSE
        DBMS_OUTPUT.PUT_LINE('Excursia: ' || t(i) || ' nu sunt orase de vizitat!'); 
    END IF;
END LOOP;
END;
/

/*e. Anula?i excursiile cu cele mai pu?ine ora?e vizitate.*/
DECLARE 
TYPE pereche IS RECORD 
(cod excursie_lco.cod_excursie%TYPE,
orase excursie_lco.orase%TYPE,
nr_orase NUMBER);
TYPE tabel IS TABLE OF pereche;
t tabel;
minim NUMBER := 10000;
lista tip_orase_lco;
BEGIN
    SELECT cod_excursie, orase, 0 BULK COLLECT INTO t
    FROM excursie_lco;
    
    FOR i IN t.FIRST..t.LAST LOOP
        --aflam nr minim de orase
        IF t(i).orase IS NOT NULL AND t(i).orase.COUNT < minim THEN
            minim := t(i).orase.COUNT;
        ELSIF t(i).orase IS NULL THEN minim := 0;
        END IF;
        IF t(i).orase IS NOT NULL THEN
            t(i).nr_orase := t(i).orase.COUNT;
        ELSE t(i).nr_orase := 0;
        END IF;
    END LOOP;
    
    FOR i IN t.FIRST..t.LAST LOOP
        IF t(i).nr_orase = minim THEN
            UPDATE excursie_lco
            SET status = 'anulata'
            WHERE cod_excursie = t(i).cod;
        END IF;
    END LOOP;
END;
/
SELECT * FROM EXCURSIE_LCO;
ROLLBACK;

--tablouri indexate, imbricate si varrays

SET SERVEROUTPUT ON

DECLARE
TYPE population IS TABLE OF NUMBER
    INDEX BY VARCHAR2(64);
TYPE numbers IS TABLE OF NUMBER
    INDEX BY PLS_INTEGER;
    
city_population population;
t_num numbers;
i VARCHAR2(64);
j NUMBER;
BEGIN
--will be stored in ascendant order
city_population('Roman') := 29300;
city_population('Paris') := 10200;
city_population('Aoma') := 503300;

city_population('Roman') := 2100;

i := city_population.FIRST;

WHILE i IS NOT NULL LOOP
    DBMS_OUTPUT.PUT_LINE('POPULATION OF ' || i || ' is ' || city_population(i));
    i := city_population.NEXT(i);
END LOOP;

t_num(10) := 2;
t_num(3) := 1;
t_num(21) := 4;

j := t_num.FIRST;

WHILE j IS NOT NULL LOOP
    DBMS_OUTPUT.PUT_LINE('VALUE OF ' || j || ' is ' || t_num(j));
    j := t_num.NEXT(j);
END LOOP;
END;
/

/*Defini?i un bloc anonim in cadrul c?ruia trebuie sa defini?i 3 tipuri de date (tablou, tablou imbricat, vector).
Ulterior, pentru fiecare variabila ?terge?i componentele care contin numere
impare. Parcurge?i cele 3 variabile de la prima la ultima componenta si invers.*/
DECLARE
TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
TYPE tablou_imbricat IS TABLE OF NUMBER;
TYPE vector IS VARRAY(150) OF NUMBER;
t_idx tablou_indexat;
t_imbri tablou_imbricat;
vec vector;
i NUMBER;
val NUMBER := 1;
BEGIN
/*Popula?i cu ajutorul clauzelor repetitive studiate 3 variabile de acest tip (minim 100 de numere) – clauza 
diferita pentru fiecare variabila. */
FOR i IN 1..21 LOOP
    t_idx(i) := i;
END LOOP;

--stergerea elementelor impare
i := t_idx.FIRST;
WHILE i IS NOT NULL LOOP
    IF t_idx(i) mod 2 = 1 THEN t_idx.DELETE(i);
    END IF;
    i := t_idx.NEXT(i);
END LOOP;
DBMS_OUTPUT.PUT_LINE('Tablou indexat');
--parcurgere de la inceput
FOR i IN t_idx.FIRST..t_idx.LAST LOOP
    IF t_idx.EXISTS(i) THEN
        DBMS_OUTPUT.PUT(t_idx(i) || ' ');
    END IF;
END LOOP;
DBMS_OUTPUT.NEW_LINE;

--parcurgere de la sfarsit
i := t_idx.LAST;
WHILE i IS NOT NULL LOOP
    IF t_idx.EXISTS(i) THEN
        DBMS_OUTPUT.PUT(t_idx(i) || ' ');
    END IF;
    i := t_idx.PRIOR(i);
END LOOP;
DBMS_OUTPUT.NEW_LINE;

t_imbri := tablou_imbricat();
t_imbri.EXTEND;
i := t_imbri.FIRST;
WHILE val <= 21 LOOP
    t_imbri(i) := val;
    t_imbri.EXTEND;
    i := t_imbri.NEXT(i);
    val := val + 1;
END LOOP;

--stergerea elementelor impare
i := t_imbri.FIRST;
WHILE i IS NOT NULL LOOP
    IF t_imbri(i) mod 2 = 1 THEN t_imbri.DELETE(i);  
    END IF;
    i := t_imbri.NEXT(i);
END LOOP;

DBMS_OUTPUT.PUT_LINE('Tablou imbricat');
--parcurgere de la inceput  !!!!!!!!!!!!!!!!!!!!!!!! DE CE EXISTA SI t_imbri(21)???????????????????
FOR i IN t_imbri.FIRST..t_imbri.LAST LOOP
    IF t_imbri.EXISTS(i) THEN
        DBMS_OUTPUT.PUT(t_imbri(i) || ' ');
    END IF;
END LOOP;
DBMS_OUTPUT.NEW_LINE;

--parcurgere de la sfarsit
i := t_imbri.LAST;
WHILE i IS NOT NULL LOOP
    IF t_imbri.EXISTS(i) THEN
        DBMS_OUTPUT.PUT(t_imbri(i) || ' ');
    END IF;
    i := t_imbri.PRIOR(i);
END LOOP;
DBMS_OUTPUT.NEW_LINE;

val := 1;
vec := vector();
vec.EXTEND;
i := vec.FIRST;
WHILE i <= 21 LOOP
    vec(i) := val;
    vec.EXTEND;
    i := vec.NEXT(i);
    val := val + 1;
END LOOP;

--stergerea elementelor impare
i := vec.FIRST;
WHILE i IS NOT NULL LOOP
    IF vec(i) mod 2 = 1 THEN vec.DELETE(i);  
    END IF;
    i := vec.NEXT(i);
END LOOP;
------ !!!!!!!!!!!!!! cum stergem pentru VARRAY???
END;
/

/*Defini?i un tip de date care sa permit? sa stoca?i o matrice p?tratic? de dimensiune n. Defini?i si ini?ializa?i o astfel
de variabila cu valori care apar pe coloana employees.employee_id. Afi?a?i con?inutul acestei
variabile parcurgând matricea in spirala.*/
DECLARE
TYPE line_m IS TABLE OF NUMBER;
TYPE matrix IS TABLE OF line_m;
TYPE emp_id IS TABLE OF employees.employee_id%TYPE INDEX BY PLS_INTEGER;
m matrix;
n NUMBER := &num;
emp emp_id;
idx_emp NUMBER;
fst NUMBER;
lst NUMBER;
BEGIN
SELECT employee_id BULK COLLECT INTO emp
FROM employees;
idx_emp := emp.FIRST;
m := matrix();
m.EXTEND(n);
FOR i IN 1..n LOOP
    m(i) := line_m(); ------- !!! DE CE NU FUNCTIONEAZA line_m(n)?
    m(i).EXTEND(n);
    FOR j IN 1..n LOOP
        m(i)(j) := emp(idx_emp);
        idx_emp := emp.NEXT(idx_emp);
    END LOOP;
END LOOP;

--parcurgere matrice
FOR i IN 1..n LOOP
    FOR j IN 1..n LOOP
        DBMS_OUTPUT.PUT(m(i)(j) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END LOOP;

--parcurgere in spirala
DBMS_OUTPUT.PUT_LINE('PARCURGERE IN SPIRALA');
fst := 1;
lst := n;
WHILE fst <= lst LOOP
    FOR i IN fst..lst LOOP
        DBMS_OUTPUT.PUT(m(fst)(i) || ' ');
    END LOOP;
    FOR i IN (fst + 1)..lst LOOP
        DBMS_OUTPUT.PUT(m(i)(lst) || ' ');
    END LOOP;
    idx_emp := lst - 1; --reused variable
    WHILE idx_emp >= fst LOOP
        DBMS_OUTPUT.PUT(m(lst)(idx_emp) || ' ');
        idx_emp := idx_emp - 1;
    END LOOP;
    idx_emp := lst - 1; --reused variable
    WHILE idx_emp > fst LOOP
        DBMS_OUTPUT.PUT(m(idx_emp)(fst) || ' ');
        idx_emp := idx_emp - 1;
    END LOOP;
    fst := fst + 1;
    lst := lst - 1;
END LOOP;
DBMS_OUTPUT.NEW_LINE;
END;
/