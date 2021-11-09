SET SERVEROUTPUT ON;

select * from subiecte;
SELECT * FROM vestimentatie ORDER BY 4;
SELECT * FROM sustine order by 1;
/*1.Enuntati o cerere in limbaj natural, pe schema de examen, care sa implice in rezolvare un cursor 
cu parametru ce extrage informatiile din cel putin 2 tabele si care utilizeaza cel putin o functie grup.
Scrieti un subprogram care utilizeaza acest cursor. Vor fi returnate cel putin doua variabile.*/

/*Creati un subprogram care sa intoarca pentru fiecare sponsor numarul de prezentari care au mai mult de 2 articole de vestimentatie,
si numarul total de astfel de prezentari pentru toti sponsorii.*/
DECLARE
TYPE tab_nr IS TABLE OF NUMBER(10);
nr NUMBER(5) := 0;
t tab_nr;
PROCEDURE f_prezentari (nr_prezentari_total OUT NUMBER, t_nr OUT tab_nr)
IS
TYPE tab_prezentari IS TABLE OF prezentare.cod_pr%TYPE;
t tab_prezentari;
CURSOR cur_pr(cod sponsor.cod_sponsor%TYPE) IS
        (SELECT s.cod_pr cd
        FROM sustine s
         JOIN prezentare p ON (s.cod_pr = p.cod_pr)
         JOIN vestimentatie v ON (v.cod_prezentare = p.cod_pr)
         WHERE s.cod_sp = cod
         GROUP BY s.cod_pr 
         HAVING COUNT(cod_vestimentatie) >= 2);
BEGIN
nr_prezentari_total := 0;
t_nr := tab_nr();
FOR cur_sp IN (SELECT cod_sponsor
               FROM sponsor) LOOP
OPEN cur_pr(cur_sp.cod_sponsor);
    FETCH cur_pr BULK COLLECT INTO t;
    nr_prezentari_total := nr_prezentari_total +  t.COUNT;
    t_nr.EXTEND;
    t_nr(t_nr.LAST) := t.COUNT;
CLOSE cur_pr;    
END LOOP;
END;
BEGIN
f_prezentari(nr,t);
DBMS_OUTPUT.PUT_LINE('Nr total de astfel de prezentari:' || nr);
FOR i IN t.FIRST..t.LAST LOOP
    DBMS_OUTPUT.PUT_LINE('Nr prezentari pe sponsor:' || t(i));
END LOOP;
END;
/

SELECT * FROM sponsor;
SELECT * FROM sustine;
SELECT * FROM vestimentatie order by 4;


/*Vom numi "pereche" un tip de date ce foloseste in definirea lui alte doua tipuri de date diferite ("tip1", respectiv "tip2"). 
Definiti un astfel de tip de date, indicati ce anume reprezinta si utilizati-l prin adaugarea unei coloane de acest tip la unul 
dintre tabelele din schema de examen. Cu ajutorul unui bloc stocat actualizati coloana adaugata cu informatii relevante din schema de examen.*/

/*Adaugati in sponsor o coloana pereche care sa tina codul si numele primei prezentari sustinute de acel sponsor si codurile prezentarilor sustinute de sponsor*/
CREATE OR REPLACE TYPE rec_pr_prezentare IS OBJECT
    (cod_pr NUMBER(10),
     nume VARCHAR2(50));
/
CREATE OR REPLACE TYPE tab_prezentari IS TABLE OF NUMBER(10);
/
 
CREATE OR REPLACE TYPE perechee IS OBJECT 
    (prez rec_pr_prezentare,
    prezentari tab_prezentari);
/

ALTER TABLE SPONSOR
ADD (info_p perechee)
NESTED TABLE info_p.prezentari STORE AS info_p_lco;

SELECT * FROM sponsor;

<<ACTUALIZARE>>
DECLARE
CURSOR c_prez(parametru sponsor.cod_sponsor%TYPE) IS (SELECT cod_pr FROM sustine WHERE cod_sp = parametru);
t tab_prezentari;
pair perechee;
info_prima rec_pr_prezentare := rec_pr_prezentare(NULL, NULL);
BEGIN
    FOR c IN (SELECT cod_sponsor FROM sponsor)
    LOOP
        OPEN c_prez(c.cod_sponsor); 
        FETCH c_prez BULK COLLECT INTO t;
        CLOSE c_prez;
    
    IF t.COUNT > 0 THEN
    SELECT rec_pr_prezentare(cod_pr, nume) INTO info_prima
    FROM prezentare
    JOIN sustine USING(cod_pr)
    WHERE cod_sp = c.cod_sponsor
    AND data = (SELECT MIN(data) FROM prezentare 
                   JOIN sustine USING(cod_pr)
                   WHERE cod_sp = c.cod_sponsor);
    END IF;
    
    pair := perechee(info_prima, t);
    UPDATE sponsor
    SET info_p = pair
    WHERE cod_sponsor = c.cod_sponsor;
    END LOOP;
END;
/

DESCRIBE sponsor;
SELECT * FROM sponsor;