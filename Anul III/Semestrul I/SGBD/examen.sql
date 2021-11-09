CREATE TABLE furnizori
    (id_furnizor NUMBER,
    nume_furnizor VARCHAR2(30),
    tara          VARCHAR2(30),
    PRIMARY KEY (id_furnizor));

DROP TABLE produse_lco;

CREATE TABLE produse
    (id_prod NUMBER,
    nume_prod VARCHAR2(30),
    id_furnizor NUMBER,
    pret        NUMBER,
    PRIMARY KEY (id_prod),
    FOREIGN KEY (id_furnizor) REFERENCES furnizori(id_furnizor));


CREATE TABLE comenzi
    (id_comanda NUMBER,
    id_prod NUMBER,
    cantitate NUMBER,
    PRIMARY KEY(id_comanda),
    FOREIGN KEY (id_prod) REFERENCES produse(id_prod));
--II a a) Ce este o cheie primara, dar o cheie extern?? Furniza?i câte un exemplu din schema
-- definit? mai sus.
/* O cheie primara reprezinta un camp sau o multime de campuri ce va identifica in mod unic inregistrarile dintr-o tabela.
Ea are valori unice in tabel si nu poate avea valoarea null.
Exemplu: id_furnizor, id_comanda, id_prod reprezinta chei primare in tabelele furnizori, comenzi, respectiv produse.

O cheie straina reprezinta o coloana sau o multime de coloane care creeaza o relatie intre doua tabele. Un rand sau mai multe
randuri din tabela ce contine cheia straina pot referi la doar un rand din tabela de referit. Nu are valori unice, dar valorile
trebuie sa se afle printre valorile coloanei referite. O tabela poate avea mai multe chei externe care fac referire la 
mai multe tabele.
Exemplu: id_prod este cheie straina in tabelul comenzi, fiecarei comenzi corespunzandu-i un produs
id_furnizor este cheie straina in tabelul produse, fiecare produs avand un furnizor. Mai multe produse pot avea acelasi furnizor*/


-- II b Enumera?i câte 2 deosebiri ?i asem?n?ri dintre un tip de date vector ?i un tip de date
--tablou imbricat.
/*Asemanari:
    - vectorii si tablourile imbricate pot fi definite atat in blocuri pl/sql cat si la nivel de schema
    CREATE OR REPLACE TYPE... sau TYPE in bloc PL/SQL
    - vectorii si tablourile imbricate pot aparea in definirea tabelelor bazei de date
    - atat vectorul cat si tabloul imbricat au nevoie de constructor pentru a fi initializate.
    v := vector();
    t := tablou_imbri();
Deosebiri:
    - vectorul are o dimensiune maxima stabilita la declararea tipului, insa tabloul imbricat nu are
    o dimensiune maxima(dimensiunea se modifica dinamic)
    - vectorul este dens, iar tabloul imbricat este dens doar la inceput. Dupa ce se fac operatii pe el
    poate deveni nedens

/* c. Ce este un cursor? Care sunt deosebirile dintre un cursor predefinit ?i un cursor
dinamic?*/
/* Un cursor este un pointer care pointeaza catre rezultatul unui query. Atunci cand se proceseaza
o comanda sql, se foloseste o zona de memorie numita zona context. Cursorul va pointa la zona context.
Cu ajutorul cursoarelor, programul PL/SQL poate controla context area si transformarile rezultate in urma
procesarii comenzii.

Un cursor predefinit nu poate fi denumit, deci nu poate fi controlat din alta zona din cod.
Cursorul preferinit este creat automat cand are loc o comanda. Au loc automat operatiile OPEN
FETCH si CLOSE.
Cel explicit trebuie sa fie definit explicit de utilizator atribuindu-i-se un nume, dupa care
trebuie apelate comenzile OPEN FETCH si CLOSE pentru a fi folosit.*/

/*Enun?a?i o cerere pe schema aleas? care s? poat? fi rezolvat? cu o func?ie, dar s? nu
poat? fi rezolvat? cu o procedur?. Comenta?i. (0.5p)

O functie poate sa apara in clauzele ORDER BY, GROUP BY, HAVING, ORDER BY intr-o comanda sql, deoarece returneaza un rezultat, 
insa procedura nu poate fi folosita astfel

Enunt:
Sa se afiseze comenzile a caror valoare este mai mare decat valoarea medie a tututor comenzilor.
Pentru valoarea medie a tuturor comenzilor se va utiliza o functie stocata*/

/*e) Enumera?i câte 2 deosebiri ?i asem?n?ri dintre un trigger la nivel de tabel ?i un
trigger la nivel de linie. (0.5p)
Deosebiri:
- Un trigger la nivel de tabel este executat o singura data pentru instructiunea care il declanseaza, 
chiar daca sunt afectate mai multe linii. Un trigger la nivel de linie se declanseaaza la fiecare linie
afectata.
- Triggerul la nivel de linie contine clauza for each row, iar celalalt nu.
- Cei la nivel de linie se pot folosi de :NEW si :OLD valorile vechi si noi ale campului afectat.

Asemanari:
- Amandoi se pot executa before sau after pentru o comanda
- Ambele tipuri se pot face pentru urmatoarele comenzi: DELETE INSERT si UPDATE*/

/*1. Pe schema dat? identifica?i o rela?ie de tipul 1:N (nota?i în rezolvare alegerea f?cut?):
a) defini?i dou? tabele care s? aib? câte dou? coloane: cheia primar? ?i o alt? coloan?
de tip vector, respectiv tablou imbricat; (0.5p)
b) cu ajutorul unui subprogram care prime?te ca parametru o valoarea din partea "one"
insera?i o linie în primul tabel care s? con?in? pe prima coloana valoarea data, iar în
coloana de tip vector lista valorilor corespunz?toare din cel de al doilea tabel (partea
de "many"); (1p)
c) cu ajutorul unui subprogram copia?i liniile din primul tabel în cel de al doilea, astfel
încât datele s? fie sortate cresc?tor în coloana tablou imbricat; (1p)
d) defini?i un bloc care utilizeaz? un cursor pentru a afi?a con?inutul unuia dintre
tabelele definite la punctul a) in func?ie de o op?iune citit? de la tastatura. (0.5p)*/

-- relatie 1:N este relatia furnizor - produse (un furnizor poate avea mai multe produse)
CREATE OR REPLACE TYPE tab_imbri IS TABLE of NUMBER;
/
CREATE TABLE furn_prod_imbri
    (id_furn NUMBER,
    prod tab_imbri,
    primary key (id_furn))
    NESTED TABLE prod STORE AS produse_furn;
    
DROP TABLE furn_prod_imbri;
CREATE OR REPLACE TYPE vector IS VARRAY(100) OF NUMBER;
/

CREATE TABLE furn_prod_vec
    (id_furn NUMBER,
    prod vector,
    PRIMARY KEY (id_furn));
    
DROP TABLE furn_prod_vec;
/*b) cu ajutorul unui subprogram care prime?te ca parametru o valoarea din partea "one"
insera?i o linie în primul tabel care s? con?in? pe prima coloana valoarea data, iar în
coloana de tip vector lista valorilor corespunz?toare din cel de al doilea tabel (partea
de "many");*/

CREATE OR REPLACE PROCEDURE proc_insert(furn NUMBER)
IS
t vector;
BEGIN
    SELECT id_prod BULK COLLECT INTO t
    FROM produse
    WHERE id_furnizor = furn;
    
    INSERT INTO furn_prod_vec
    VALUES (furn, t);
END;
/

SELECT* FROM furnizori;
INSERT INTO furnizori
VALUES (1, 'Altex', 'Romania');
INSERT INTO furnizori
VALUES (2, 'Kaufland', 'Germania');
INSERT INTO furnizori
VALUES (3, 'Carrefour', 'Romania');

SELECT * FROM produse;

INSERT INTO produse
VALUES (1, 'cafea', 3, 15);
INSERT INTO produse
VALUES (2, 'lapte', 3, 6);
INSERT INTO produse
VALUES (3, 'faina', 3, 5);
INSERT INTO produse
VALUES (4, 'telefon', 1, 1500);
INSERT INTO produse
VALUES (5, 'ciocolata', 2, 15);

BEGIN
    proc_insert(1);
    proc_insert(2);
        proc_insert(3);

END;
/

SELECT * FROM furn_prod_vec;
DROP TABLE furn_prod_vec;

/*c) cu ajutorul unui subprogram copia?i liniile din primul tabel în cel de al doilea, astfel
încât datele s? fie sortate cresc?tor în coloana tablou imbricat;*/
CREATE OR REPLACE PROCEDURE copiaza
IS
t tab_imbri := tab_imbri();
v vector := vector();
aux NUMBER;
BEGIN
    FOR i IN (SELECT * FROM furn_prod_vec) LOOP
    v.DELETE;
    t.DELETE;
    --copiem datele intr-un vector
    FOR j IN i.prod.FIRST..i.prod.LAST LOOP
        v.extend;
        v(v.last) := i.prod(j);
    END LOOP;
    --ordonam valorile din vector
    FOR j IN v.FIRST..(v.LAST-1) LOOP
        FOR k IN (j+1)..(v.LAST) LOOP
            IF (v(j) > v(k)) THEN
                aux := v(j);
                v(j) := v(k);
                v(k) := aux;
            END IF;
        END LOOP;
    END LOOP;
    
    FOR j IN v.FIRST..v.LAST LOOP
        t.EXTEND;
        t(t.LAST) := v(j);
    END LOOP;
    --DBMS_OUTPUT.PUT_LINE(t.FIRST || ' ' || t.LAST);
    INSERT INTO furn_prod_imbri
    VALUES (i.id_furn,t);
    END LOOP;
END;
/

BEGIN
    copiaza;
END;
/
SELECT * FROM furn_prod_imbri;
DELETE FROM furn_prod_imbri;
SET SERVEROUTPUT ON;


/*d) defini?i un bloc care utilizeaz? un cursor pentru a afi?a con?inutul unuia dintre
tabelele definite la punctul a) in func?ie de o op?iune citit? de la tastatura.*/

DECLARE
v_opt NUMBER := &p_opt;
BEGIN
    IF v_opt = 1 THEN
        FOR i IN (SELECT * FROM furn_prod_vec) LOOP
            DBMS_OUTPUT.PUT_LINE(i.id_furn || ' Cu produsele:');
            IF i.prod.COUNT <> 0 THEN
            FOR j IN i.prod.FIRST..i.prod.LAST LOOP
                DBMS_OUTPUT.PUT(i.prod(j) || ' ' );
            END LOOP;
            DBMS_OUTPUT.NEW_LINE;
            ELSE
            DBMS_OUTPUT.PUT_LINE('Nu are produse asociate');
            END IF;
        END LOOP;
    ELSIF v_opt = 2 THEN
            FOR i IN (SELECT * FROM furn_prod_imbri) LOOP
            DBMS_OUTPUT.PUT_LINE(i.id_furn || ' Cu produsele:');
            IF i.prod.COUNT <> 0 THEN
            FOR j IN i.prod.FIRST..i.prod.LAST LOOP
                DBMS_OUTPUT.PUT(i.prod(j) || ' ' );
            END LOOP;
            DBMS_OUTPUT.NEW_LINE;
            ELSE
            DBMS_OUTPUT.PUT_LINE('Nu are produse asociate');
            END IF;
        END LOOP;
    ELSE
        RAISE_APPLICATION_ERROR(-20001, 'Nu ai introdus o optiune valida');
    END IF;
END;
/

SELECT * FROM furn_prod_vec;

SELECT * FROM produse;


/*2. Simula?i cu ajutorul unui trigger constrângerea de cheie primar? pe un tabel din schema
aleas?.*/
--Implementez constrangerea de cheie primara pe tabelul produse
CREATE OR REPLACE PACKAGE pack_primary_key
AS
    TYPE tab_idx IS TABLE OF NUMBER INDEX BY BINARY_INTEGER;
    nr NUMBER := 0;
    prod tab_idx;
END;
/

CREATE OR REPLACE TRIGGER trig_pk_instr
BEFORE INSERT OR UPDATE OF id_prod ON produse
BEGIN
    pack_primary_key.nr := 0;
    pack_primary_key.prod.DELETE;
    DBMS_OUTPUT.PUT_LINE('HERE');
    FOR i IN (SELECT id_prod FROM produse) LOOP
        pack_primary_key.nr := pack_primary_key.nr + 1;
        pack_primary_key.prod(pack_primary_key.nr) := i.id_prod;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE(pack_primary_key.nr);
END;
/
CREATE OR REPLACE TRIGGER trig_primary_key
BEFORE INSERT OR UPDATE OF id_prod ON produse
FOR EACH ROW
DECLARE
nr NUMBER;
BEGIN
    DBMS_OUTPUT.PUT_LINE('HERE 2');
    DBMS_OUTPUT.PUT_LINE(:NEW.id_prod);

    IF :NEW.id_prod IS NULL THEN
        RAISE_APPLICATION_ERROR(-20001, 'Cheia primara nu poate fi null');
    ELSE
        FOR i IN 1..pack_primary_key.nr LOOP
            IF :NEW.id_prod = pack_primary_key.prod(i) THEN
                        
                RAISE_APPLICATION_ERROR(-20002, 'Cheia primara trebuie sa fie unica!');
            END IF;
        END LOOP;
        pack_primary_key.prod(pack_primary_key.prod.LAST) := :NEW.id_prod;
        DBMS_OUTPUT.PUT_LINE('END');
    END IF;
END;
/

SELECT * FROM produse;
INSERT INTO produse VALUES (2, 'sare', 2, 7);
UPDATE produse
SET id_prod = 10;
