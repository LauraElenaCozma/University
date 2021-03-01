SELECT* FROM apel;
SELECT * FROM client;
SELECT * FROM subiecte;
SELECT * FROM telefon;
SELECT * FROM retea;

/*Pe un tabel dependent din schema de examen implementati cu ajutorul unui trigger o constrangere de integritate la alegere. (observatii: trebuie sa apara explicit pe ce tabel si care este constrangerea implementata*/
SELECT * FROM ALL_CONSTRAINTS WHERE table_name = 'APEL';
SELECT * FROM ALL_CONSTRAINTS WHERE table_name = 'TELEFON';
SELECT * FROM ALL_CONSTRAINTS WHERE table_name = 'CLIENT';
SELECT * FROM ALL_CONSTRAINTS WHERE table_name = 'RETEA';


/*Implementati constrangerea prin care un client nu poate initia mai mult de 3h de convorbiri pe zi.*/
-- 3h => 180 minute; verificam ca fiecare client sa aiba maxim 180 de minute in apelurile initiate pe toate numerele de telefon

CREATE OR REPLACE PACKAGE pack_1
AS
TYPE rec IS RECORD 
    (id_cl client.id_client%TYPE,
     data apel.data_start%TYPE);
TYPE t_index IS TABLE OF rec INDEX BY BINARY_INTEGER;
t t_index;
nr NUMBER := 0;
END;
/

CREATE OR REPLACE TRIGGER trig_1_row
BEFORE INSERT OR UPDATE ON apel
FOR EACH ROW
DECLARE
id_cl client.id_client%TYPE;
BEGIN
    SELECT cod_client INTO id_cl
    FROM telefon
    WHERE nr_telefon = :NEW.nr_tel_apelant;
    pack_1.nr := pack_1.nr + 1;
    pack_1.t(pack_1.nr).id_cl := id_cl;
    pack_1.t(pack_1.nr).data := :NEW.data_start;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20002, 'Nu s-au gasit date care sa satisfaca conditiile');
    WHEN TOO_MANY_ROWS THEN
        RAISE_APPLICATION_ERROR(-20003, 'S-au gasit prea multe date care sa satisfaca conditiile');
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20004, 'Alta eroare');
END;
/

CREATE OR REPLACE TRIGGER trig_1
AFTER INSERT OR UPDATE ON apel
DECLARE
nr_min NUMBER;
exceptie EXCEPTION;
BEGIN
    FOR i IN 1..pack_1.nr LOOP
    
        SELECT SUM(durata) INTO nr_min
        FROM apel a
        JOIN telefon t ON (a.nr_tel_apelant = t.nr_telefon)
        WHERE cod_client = pack_1.t(i).id_cl
        AND data_start = pack_1.t(i).data;
        IF nr_min > 180 THEN
            pack_1.t.DELETE;
            pack_1.nr := 0;
            RAISE exceptie;
        END IF;
    END LOOP;
    pack_1.t.DELETE;
    pack_1.nr := 0;
EXCEPTION
    WHEN exceptie THEN 
        RAISE_APPLICATION_ERROR(-20001, 'Clientul a vorbit mai mult de 180 de minute!');
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20002, 'Nu s-au gasit date care sa satisfaca conditiile');
    WHEN TOO_MANY_ROWS THEN
        RAISE_APPLICATION_ERROR(-20003, 'S-au gasit prea multe date care sa satisfaca conditiile');
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20004, 'Alta eroare');
END;
/

SELECT * FROM apel order by 1; 

INSERT INTO apel
VALUES ('0720946381', '0759487123', TO_DATE('10-MAY-10', 'DD-MON-YY'), 10);

INSERT INTO apel
VALUES ('0749173654', '0759487123', TO_DATE('10-MAY-10', 'DD-MON-YY'), 160);
UPDATE apel SET durata = 100;

ROLLBACK;
SELECT * FROM telefon order by 2; 




ROLLBACK;
SELECT * FROM APEL;
set SERVEROUTPUT ON;
SELECT * FROM telefon;
SELECT * FROM retea;
INSERT INTO telefon VALUES ('0720946322', 100, 102, 30, 100);
ROLLBACK;



ALTER TABLE apel ENABLE ALL TRIGGERS;